"""import torch

def manipulate_tensor(tensor):
    tmp = tensor[-1].clone()
    tensor[-1] = tensor[0]
    tensor[0] = tmp
    tmp2 = tensor[:, 0].clone()
    tensor[:, 0] = tensor[:, -1]
    tensor[:, -1] = tmp2
    
    tensor = 1 - tensor
    
    return tensor

T = int(input())
results = []

for _ in range(T):
    n, m = map(int, input().split())
    tensor = []
    for _ in range(n):
        row = list(map(int, input().split()))
        tensor.append(row)
    tensor = torch.tensor(tensor)
    manipulated_tensor = manipulate_tensor(tensor)
    results.append(manipulated_tensor.tolist())

for result in results:
    for row in result:
        print(" ".join(map(str, row)))"""

"""import torch

a = torch.tensor(list(map(int, input().split())), dtype=torch.float32)
b = torch.tensor(list(map(int, input().split())), dtype=torch.float32)

cosine_similarity = torch.dot(a, b) / (torch.norm(a) * torch.norm(b))
print(f'{cosine_similarity:.2f}')"""

"""import torch

n, m, l = map(int, input().split())
word_list = []
sentence_pair_list = []
for _ in range(n):
    word_list.append(input())
for _ in range(m):
    sentence_pair_list.append(input().split(','))

for i in range(len(sentence_pair_list)):
    sentence_pair = sentence_pair_list[i]
    for j in range(len(sentence_pair)):
        sentence_pair[j] = sentence_pair[j].lower()
        sentence_pair[j] = sentence_pair[j].split()
        sentence_pair[j] = torch.tensor([word_list.index(word) for word in sentence_pair[j]])
    sentence_pair = torch.concat((sentence_pair[0], sentence_pair[1]), dim=0)
    if len(sentence_pair) > l:
        sentence_pair = sentence_pair[:l]
    elif len(sentence_pair) < l:
        padding = torch.ones(l - len(sentence_pair), dtype=torch.int64) * -1
        sentence_pair = torch.concat((sentence_pair, padding), dim=0)
    sentence_pair_list[i] = sentence_pair.tolist()

for sentence_pair in sentence_pair_list:
    print(" ".join(map(str, sentence_pair)))"""

x = 1
def haha(x):
    x += 1
haha(x)
print(x)
