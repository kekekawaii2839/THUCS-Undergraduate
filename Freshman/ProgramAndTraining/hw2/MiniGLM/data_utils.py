import os
import tiktoken
import torch
import numpy as np

train_data = None
val_data = None

encoder = tiktoken.get_encoding('cl100k_base')
eos_token = encoder.encode('<|endoftext|>', allowed_special='all')[0]

def init_data_pretrain(dataset):
    global train_data, val_data
    
    data_dir = os.path.join('data', dataset)
    train_data = np.memmap(os.path.join(data_dir, 'train.bin'), dtype=np.uint32, mode='r')
    val_data = np.memmap(os.path.join(data_dir, 'val.bin'), dtype=np.uint32, mode='r')

def init_data_sft(dataset):
    global train_data, val_data
    
    data_dir = os.path.join('data', dataset)
    train_data = np.memmap(os.path.join(data_dir, 'qa_train.bin'), dtype=np.uint32, mode='r')
    val_data = np.memmap(os.path.join(data_dir, 'qa_val.bin'), dtype=np.uint32, mode='r')

def get_batch_pretrain(split, batch_size, block_size, device):
    global train_data, val_data
    data = train_data if split == 'train' else val_data
    ix = torch.randint(len(data) - block_size, (batch_size,))
    x = torch.stack([torch.from_numpy((data[i:i+block_size]).astype(np.int64)) for i in ix])
    y = torch.stack([torch.from_numpy((data[i+1:i+1+block_size]).astype(np.int64)) for i in ix])
    loss_mask = torch.ones_like(x, dtype=torch.float64)
    
    device_type = 'cuda' if 'cuda' in device else 'cpu'
    if device_type == 'cuda':
        # pin arrays x,y, which allows us to move them to GPU asynchronously (non_blocking=True)
        x, y, loss_mask = x.pin_memory().to(device, non_blocking=True), y.pin_memory().to(device, non_blocking=True), loss_mask.pin_memory().to(device, non_blocking=True)
    else:
        x, y, loss_mask = x.to(device), y.to(device), loss_mask.to(device)
    return x, y, loss_mask
    
def get_batch_sft(split, batch_size, block_size, device): 
    global train_data, val_data
    data = train_data if split == 'train' else val_data
    # 随机选择batch_size个长度为block_size的序列，第一个token的位置一定是block_size的整数倍
    ix = torch.randint(len(data) - block_size, (batch_size,))
    ix = ix - ix % block_size
    x = torch.stack([torch.from_numpy((data[i:i+block_size]).astype(np.int64)) for i in ix])
    y = torch.stack([torch.from_numpy((data[i+1:i+1+block_size]).astype(np.int64)) for i in ix])
    # 设置loss_mask
    # 第一次碰到eos_token的位置之前都是question，均设置为0
    # 第二次碰到eos_token的位置之后都是padding，均设置为0
    loss_mask = torch.ones_like(x, dtype=torch.float64)
    for i in range(batch_size):
        f = False
        for j in range(block_size):
            if y[i][j] == eos_token and not f:
                loss_mask[i][:j] = 0
                f = True
            elif y[i][j] == eos_token and f:
                loss_mask[i][j+1:] = 0
                break
    # print(np.array(loss_mask[0]).tolist())
    
    device_type = 'cuda' if 'cuda' in device else 'cpu'
    if device_type == 'cuda':
        # pin arrays x,y, which allows us to move them to GPU asynchronously (non_blocking=True)
        x, y, loss_mask = x.pin_memory().to(device, non_blocking=True), y.pin_memory().to(device, non_blocking=True), loss_mask.pin_memory().to(device, non_blocking=True)
    else:
        x, y, loss_mask = x.to(device), y.to(device), loss_mask.to(device)
    return x, y, loss_mask