import tiktoken
import json
import numpy as np
import random

encoder = tiktoken.get_encoding('cl100k_base')

qa_train = []
qa_test = []

line_num = open('qa_refined.jsonl', 'r', encoding='utf-8').read().count('\n')

eos_token = encoder.encode('<|endoftext|>', allowed_special='all')[0]

with open('qa_refined.jsonl', 'r', encoding='utf-8') as f:
    # shuffle the lines of the file
    f = [line for line in f]
    f = random.sample(f, len(f))
    for line_index, line in enumerate(f):
        data = json.loads(line)
        question = data['Question']
        answer = data['Answer']
        prompt = '问：' + question + '<|endoftext|>答：' + answer + '<|endoftext|>'
        tokens = encoder.encode(prompt, allowed_special="all")
        tokens = tokens[:511] + [eos_token]
        if len(tokens) < 512:
            tokens.extend([eos_token] * (512 - len(tokens)))
        if line_index < line_num * 0.9:
            # print(tokens.index(eos_token))
            qa_train.extend(tokens)
        else:
            qa_test.extend(tokens)

qa_train = np.array(qa_train, dtype=np.uint32)
qa_test = np.array(qa_test, dtype=np.uint32)

qa_train.tofile('qa_train.bin')
qa_test.tofile('qa_val.bin')