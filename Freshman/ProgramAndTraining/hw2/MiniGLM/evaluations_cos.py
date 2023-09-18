import numpy as np
import tiktoken
import os
from contextlib import nullcontext
import torch
import tiktoken
from model import GLMConfig, MiniGLM
import time
import finetuner

out_dir = 'out'
num_samples = 1 # number of samples to draw
max_new_tokens = 512 # number of tokens generated in each sample
temperature = 1 # 1.0 = no change, < 1.0 = less random, > 1.0 = more random, in predictions
top_k = 200 # retain only the top_k most likely tokens, clamp others to have 0 probability
seed = 1234
device = 'cuda' # examples: 'cpu', 'cuda', 'cuda:0', 'cuda:1', etc.
dtype = 'bfloat16' if torch.cuda.is_available() and torch.cuda.is_bf16_supported() else 'float16' # 'float32' or 'bfloat16' or 'float16'
compile = True # use PyTorch 2.0 to compile the model to be faster
exec(open('configurator.py').read()) # overrides from command line or config file
# -----------------------------------------------------------------------------
torch.manual_seed(seed)
torch.cuda.manual_seed(seed)
torch.backends.cuda.matmul.allow_tf32 = True # allow tf32 on matmul
torch.backends.cudnn.allow_tf32 = True # allow tf32 on cudnn
device_type = 'cuda' if 'cuda' in device else 'cpu' # for later use in torch.autocast
ptdtype = {'float32': torch.float32, 'bfloat16': torch.bfloat16, 'float16': torch.float16}[dtype]
ctx = nullcontext() if device_type == 'cpu' else torch.amp.autocast(device_type=device_type, dtype=ptdtype)
# init from a model saved in a specific directory
ckpt_path = os.path.join(out_dir, 'ckpt.pt')
checkpoint = torch.load(ckpt_path, map_location=device)
config = GLMConfig(**checkpoint['model_args'])
model = MiniGLM(config)
state_dict = checkpoint['model']
unwanted_prefix = '_orig_mod.'
for k,v in list(state_dict.items()):
    if k.startswith(unwanted_prefix):
        state_dict[k[len(unwanted_prefix):]] = state_dict.pop(k)
model.load_state_dict(state_dict)
model.eval()
model.to(device)

embedding_model = finetuner.build_model('jinaai/jina-embedding-l-en-v1')
def cos_sim(data):
    global embedding_model
    embeddings = finetuner.encode(
        model=embedding_model,
        data=data
    )
    return finetuner.cos_sim(embeddings[0], embeddings[1])

stop_token = tiktoken.get_encoding('cl100k_base').encode('<|endoftext|>', allowed_special='all')[0]
def generate(prompt):
    global model
    enc = tiktoken.get_encoding("cl100k_base")
    encode = lambda s: enc.encode(s, allowed_special={"<|endoftext|>"})
    decode = lambda l: enc.decode(l, errors='replace')

    if not prompt.endswith('<|endoftext|>'):
        prompt += '<|endoftext|>'

    outputs = []
    # encode the beginning of the prompt
    if prompt.startswith('FILE:'):
        with open(prompt[5:], 'r', encoding='utf-8') as f:
            prompts = [line.strip() for line in f.readlines()]

        for prompt in prompts:
            prompt_ids = encode(prompt)
            x = (torch.tensor(prompt_ids, dtype=torch.long, device=device)[None, ...])

            # run generation
            with torch.no_grad():
                with ctx:
                    for k in range(num_samples):
                        y = model.generate(x, max_new_tokens, temperature=temperature, top_k=top_k, stop_token=stop_token)
                        print("Prompt:", prompt)
                        output = decode(y[0].tolist())
                        outputs.append(output)
    else:
        prompt_ids = encode(prompt)
        x = (torch.tensor(prompt_ids, dtype=torch.long, device=device)[None, ...])

        # run generation
        with torch.no_grad():
            with ctx:
                for k in range(num_samples):
                    y = model.generate(x, max_new_tokens, temperature=temperature, top_k=top_k, stop_token=stop_token)
                    output = decode(y[0].tolist())
                    outputs.append(output)
    try:
        result = outputs[0].split('<|endoftext|>')[1].replace('�', '')
        return result
    except Exception as e:
        print('error:', e)
        return outputs

encoder = tiktoken.get_encoding('cl100k_base')

val_data = np.memmap('qa_val.bin', dtype=np.uint32, mode='r')

scores = []

start_time = time.time()
for i in range(0, len(val_data), 512):
    qa_token = val_data[i:i + 512]
    qa = encoder.decode(qa_token)
    
    question = qa.split('<|endoftext|>')[0]
    answer = qa.split('<|endoftext|>')[1]
    generated_answer = generate(question)
    print(question)
    print(answer)
    print(generated_answer)
    score = cos_sim([answer, generated_answer])
    print(score)
    scores.append(score)
    print('-'*30)

print('time:', time.time() - start_time)
print('total num:', len(scores))
print('average score:', np.mean(scores))
