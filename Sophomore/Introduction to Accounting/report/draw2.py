import seaborn as sns
import matplotlib.pyplot as plt

# 输入数据
x = [100330, 94940, 66260, 59280, 58050, 50540, 46160, 45220, 44350, 36150, 30000, 28550, 27280, 26640, 26320, 25280, 25000, 19260, 19160, 18200]
y = ["Pfizer", "Johnson & Johnson", "Roche", "Merck & Co", "Abbvie", "Novartis", "Bristol Myers Squibb", "Sanofi", "AstraZeneca", "GSK", "Takeda", "Eli Lilly and Company", "Gilead Sciences", "Bayer", "Amgen", "Boehringer Ingelheim", "Novo Nordisk", "Moderna", "Merck KGaA", "BioNTech"]

# 设置字体
font = {'family' : 'SimHei',
        'size'   : 12}
plt.rc('font', **font)

# 使用Seaborn设置样式
sns.set(style="whitegrid")

# 创建subplot
fig, ax = plt.subplots(figsize=(10, 10))

# 使用Seaborn绘制条形图
colors = sns.color_palette("pastel", len(x))
sns.barplot(x=x, y=y, palette=colors, ax=ax)

# 设置标题
ax.set_title("Top 20 drug companies by revenue(2022)")
ax.set_xlabel("Pharma revenue($ million)")

# 显示百分比标签
for i, v in enumerate(x):
    ax.text(v + 1000, i, f'{v/sum(x)*100:.1f}%', color='black', va='center')

# 显示图形
plt.show()
