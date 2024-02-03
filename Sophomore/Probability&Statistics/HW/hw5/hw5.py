import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import expon

# 生成 10000 个均匀分布 U(0, 1) 的随机数
random_numbers = np.random.uniform(0, 1, 10000)

# 计算 -ln(1 - y) 对应的 x 值
x_values = -np.log(1 - random_numbers)

# 绘制直方图
plt.hist(x_values, bins=1000, density=True, alpha=0.7, color='blue', label='Histogram')

# 生成指数分布的概率密度函数
x = np.linspace(0, np.max(x_values), 100)
y = expon.pdf(x, scale=1)

# 绘制指数分布的概率密度函数
plt.plot(x, y, 'r-', label='Exponential PDF')

plt.xlabel('x')
plt.ylabel('Probability Density')
plt.title('Histogram and Exponential PDF')
plt.legend()
plt.show()
