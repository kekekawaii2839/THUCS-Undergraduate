import matplotlib.pyplot as plt
import scipy.stats as stats

# 参数设置
n = 10  # 试验次数
p_x = 0.9  # 成功的概率
p_y = 0.1  # 成功的概率

# 生成X和Y的取值范围
x_values = range(-n-1, n+1)
y_values = range(-n-1, n+1)

# 计算X和Y的概率质量函数值
pmf_x = stats.binom.pmf(x_values, n, p_x)
pmf_y = stats.binom.pmf(y_values, n, p_y)

# 绘制X的概率质量函数图
plt.bar(x_values, pmf_x, width=0.1, align='center', alpha=0.5, label='X ~ B(10, 0.9)')
plt.xlabel('X Values')
plt.ylabel('Probability')
plt.legend()
plt.grid(True)
plt.show()

# 绘制Y的概率质量函数图
plt.bar([y+8 for y in y_values], pmf_y, width=0.1, align='center', alpha=0.5, label='Y-8 ~ B(10, 0.1)')
plt.xlabel('Y Values')
plt.ylabel('Probability')
plt.legend()
plt.grid(True)
plt.show()
