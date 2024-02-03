import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import binom
import scipy.stats as stats

# 定义二项分布的参数
n = 25  # 总试验次数
p = 0.6  # 成功的概率

# 生成X轴上的值，即成功的次数
x = np.arange(0, n+1)

# 计算每个成功次数对应的概率
pmf = binom.pmf(x, n, p)

mean = n * p  # 均值
std_dev = np.sqrt(n * p * (1 - p))  # 标准差

lower_bound = mean - 2 * std_dev  # 区间下界
upper_bound = mean + 2 * std_dev  # 区间上界

# 使用CDF计算概率
probability = stats.norm.cdf(upper_bound, loc=mean, scale=std_dev) \
    - stats.norm.cdf(lower_bound, loc=mean, scale=std_dev)
print('probability: ', probability)

# 绘制二项分布图
plt.bar(x, pmf)
plt.title('n={}, p={}'.format(n, p))
plt.show()
