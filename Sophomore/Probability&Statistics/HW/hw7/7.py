import random

y_list = []

for i in range(100000):
    x = random.random()
    y = random.random()*(1-x)+x
    y_list.append(y)

print(1-sum(y_list)/len(y_list))