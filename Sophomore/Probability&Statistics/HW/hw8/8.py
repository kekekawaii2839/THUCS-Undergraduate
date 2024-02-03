import random
import matplotlib.pyplot as plt
import numpy as np

list_x_hat = []

n = 1000

for j in range(1000):
    list_x = []
    for i in range(n):
        list_x.append(np.random.standard_cauchy())
        # list_x.append(random.uniform(0,1))
        # list_x.append(random.normalvariate(0,1))
    x_hat = sum(list_x)/n
    list_x_hat.append(x_hat)

plt.scatter(range(1000), list_x_hat)
plt.show()