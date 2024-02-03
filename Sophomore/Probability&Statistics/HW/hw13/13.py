import numpy as np
from scipy.stats import t

n = 100
alpha = 0.05

counter1 = 0
counter2 = 0

for _ in range(10000):
    samples = np.random.normal(5, 1, n)
    x_bar = np.average(samples)
    x_2 = (samples[0] + samples[-1]) / 2
    S_square = np.var(samples)
    S_square_2 = np.var([samples[0], samples[-1]])

    # boundary1 = t.ppf(1-alpha, n - 1) * np.sqrt(S_square / n)
    # boundary2 = t.ppf(1-alpha, 1) * np.sqrt(S_square_2 / 2)
    p1 = 1-t.cdf((x_bar - 5.2)/(np.sqrt(S_square / n)), n - 1)
    p2 = 1-t.cdf((x_2 - 5.2)/(np.sqrt(S_square_2 / 2)), 1)
    # print(f"假设检验1: 当 x_bar-5.2>={boundary1} 时, 拒绝原假设")
    print(f"假设检验1: p1 = {p1}")
    print(f"样本均值: {x_bar}")
    if p1 < alpha:
        print("拒绝原假设")
        counter1 += 1
    else:
        print("接受原假设")
    print(f"假设检验2: p2 = {p2}")
    print(f"(X_1+X_n)/2: {x_2}")
    if p2 < alpha:
        print("拒绝原假设")
        counter2 += 1
    else:
        print("接受原假设")
    print("----------------------------------")

print(f"假设检验1: 拒绝原假设的次数: {counter1}")
print(f"假设检验2: 拒绝原假设的次数: {counter2}")