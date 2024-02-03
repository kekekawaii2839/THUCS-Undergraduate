from matplotlib import pyplot
import random
import numpy as np

def coin():
    return random.random() < 0.6

sum_list = []
for x in range(100):
    x = []
    y = []
    for i in range(10000):
        x.append(i)
        y.append(coin())
    sum = []
    for i in range(10000):
        sum.append(y[0:i].count(True) / (i + 1))
    # pyplot.scatter(x, sum, s=1)
    # pyplot.show()
    sum_list.append(np.sum(y))

print(np.average(sum_list))
pyplot.hist(sum_list)
pyplot.show()