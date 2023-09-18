import os
os.environ["OMP_NUM_THREADS"] = "1"

import torch

batch_q, seq_len_q, dim_q = map(int, input().split())
q = torch.zeros(batch_q, seq_len_q, dim_q)
for _ in range(batch_q * seq_len_q):
    q[_ // seq_len_q, _ % seq_len_q, :] = torch.tensor(list(map(float, input().split())))

batch_k, seq_len_k, dim_k = map(int, input().split())
k = torch.zeros(batch_k, seq_len_k, dim_k)
for _ in range(batch_k * seq_len_k):
    k[_ // seq_len_k, _ % seq_len_k, :] = torch.tensor(list(map(float, input().split())))

batch_v, seq_len_v, dim_v = map(int, input().split())
v = torch.zeros(batch_v, seq_len_v, dim_v)
for _ in range(batch_v * seq_len_v):
    v[_ // seq_len_v, _ % seq_len_v, :] = torch.tensor(list(map(float, input().split())))

attn = torch.bmm(q, k.transpose(1, 2)) / (dim_k ** 0.5)
attn = torch.softmax(attn, dim=2)
out = torch.bmm(attn, v)

for _ in range(batch_q):
    for __ in range(seq_len_q):
        print(' '.join(['%.2f' % out[_, __, ___] for ___ in range(dim_v)]))