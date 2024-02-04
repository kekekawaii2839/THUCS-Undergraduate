import seaborn as sns
import matplotlib.pyplot as plt

# 输入数据
x = [2017, 2018, 2019, 2020, 2021, 2022]
y1 = "0.1854 	0.4604 	0.6975 	0.5189 	0.9577 	0.8339 ".split("\t")
y2 = "0.0511 	0.5647 	0.5487 	0.5176 	0.6993 	0.5771 ".split("\t")
y3 = "1.8957 	0.9916 	1.5924 	1.0796 	0.7131 	0.9135 ".split("\t")

y1 = [float(i) for i in y1]
y2 = [float(i) for i in y2]
y3 = [float(i) for i in y3]

# 设置颜色代码
color1 = "#038355" # 孔雀绿
color2 = "#ffc34e" # 向日黄
color3 = "#ff7f00" # 橙色

# 设置字体
font = {'family' : 'SimHei',
        'size'   : 12}
plt.rc('font', **font)

# 绘图
# sns.set_style("whitegrid") # 设置背景样式
sns.lineplot(x=x, y=y1, color=color1, linewidth=2.0, marker="o", markersize=8, markeredgecolor="white", markeredgewidth=1.5, label='利润率(默克)')
sns.lineplot(x=x, y=y2, color=color2, linewidth=2.0, marker="s", markersize=8, markeredgecolor="white", markeredgewidth=1.5, label='利润率(强生)')
sns.lineplot(x=x, y=y3, color=color3, linewidth=2.0, marker="^", markersize=8, markeredgecolor="white", markeredgewidth=1.5, label='利润率(辉瑞)')

# 添加标题和标签
# plt.title("Title", fontweight='bold', fontsize=14)
plt.xlabel("年份", fontsize=12)

# 添加图例
plt.legend(loc='best', frameon=True, fontsize=10)

# 设置刻度字体和范围
plt.xticks(fontsize=10)
plt.yticks(fontsize=10)

# 设置坐标轴样式
for spine in plt.gca().spines.values():
    spine.set_edgecolor("#CCCCCC")
    spine.set_linewidth(1.5)
plt.gca().spines['top'].set_visible(False)
plt.gca().spines['right'].set_visible(False)

# 显示图像
plt.show()