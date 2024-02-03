import random
from matplotlib import pyplot as plt

x = range(1, 10001)
y = [sum(random.choices([1, -1], k=i)) for i in x]

plt.plot(x, y)
plt.show()