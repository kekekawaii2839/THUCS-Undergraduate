import numpy as np
import matplotlib.pyplot as plt
import scipy.stats as stats

# 生成100个标准正态分布的随机数
data = np.random.randn(100)

# 绘制正态 Q-Q 图
stats.probplot(data, dist="norm", plot=plt)
plt.title("Normal Q-Q Plot")
plt.xlabel("Theoretical Quantiles")
plt.ylabel("Sample Quantiles")

plt.show()

# 生成100个服从指数分布（参数lambda = 2）的随机数
lambda_parameter = 2
data = np.random.exponential(scale=1/lambda_parameter, size=100)

# 绘制正态 Q-Q 图
stats.probplot(data, dist="norm", plot=plt)
plt.title("Normal Q-Q Plot for Exponential Distribution")
plt.xlabel("Theoretical Quantiles")
plt.ylabel("Sample Quantiles")

plt.show()