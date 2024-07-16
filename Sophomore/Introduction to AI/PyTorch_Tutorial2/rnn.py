import torch

input_size = 4
hidden_size = 4
batch_size = 1
num_layers = 1
idx2char = ['e', 'h', 'l', 'o']
x_data = [1, 0, 2, 2, 3]  # hello
y_data = [3, 1, 2, 3, 2]  # ohlol
one_hot_lookup = [[1, 0, 0, 0],
                  [0, 1, 0, 0],
                  [0, 0, 1, 0],
                  [0, 0, 0, 1]]


class RNN(torch.nn.Module):
    def __init__(self, input_size, hidden_size, batch_size, num_layers):
        super(RNN, self).__init__()
        self.input_size = input_size
        self.hidden_size = hidden_size
        self.batch_size = batch_size
        self.num_layers = num_layers
        self.rnn = torch.nn.RNN(input_size=self.input_size, hidden_size=self.hidden_size, num_layers=self.num_layers)

    def forward(self, input):
        hidden = torch.zeros(self.num_layers, self.batch_size, self.hidden_size)
        out, _ = self.rnn(input, hidden)
        return out.view(-1, self.hidden_size)


if __name__ == '__main__':
    x_one_hot = [one_hot_lookup[x] for x in x_data]
    inputs = torch.Tensor(x_one_hot).view(-1, batch_size, input_size)
    labels = torch.LongTensor(y_data)

    net = RNN(input_size, hidden_size, batch_size, num_layers)
    criterion = torch.nn.CrossEntropyLoss()
    optimizer = torch.optim.Adam(net.parameters(), lr=0.05)

    for epoch in range(100):
        optimizer.zero_grad()
        outputs = net(inputs)
        loss = criterion(outputs, labels)
        loss.backward()
        optimizer.step()

        _, idx = outputs.max(dim=1)
        print(f"Epoch {epoch}/99, Loss {loss.item():.4f}: {''.join([idx2char[x] for x in idx])}")
