"""import numpy as np

t = int(input())
for i in range(t):
    n, m = map(int, input().split())
    a = np.zeros((n, m))
    for j in range(n):
        a[j] = np.array(list(map(int, input().split())))
    #swap array's first and last row
    a[[0, n-1]] = a[[n-1, 0]]
    #swap array's first and last column
    a[:, [0, m-1]] = a[:, [m-1, 0]]
    #1->0 0->1
    a = 1 - a
    for j in range(n):
        print(*a[j].astype(int))"""

"""import numpy as np

a = np.array(list(map(int, input().split())))
b = np.array(list(map(int, input().split())))
cos_sim = np.dot(a, b) / (np.linalg.norm(a) * np.linalg.norm(b))
print(f"{cos_sim:.2f}")"""

"""import pandas as pd
import io

data = []
while True:
    try:
        input_ = input()
        data.append(input_)
    except EOFError:
        break
data = '\n'.join(data)
df = pd.read_csv(io.StringIO(data))

column_names = df.columns.values.tolist()
for column_name in column_names:
    df["inv_"+column_name] = [int(1/x*100) if x!=0 else 0 for x in df[column_name]]

for x in df.columns.values.tolist():
    print(x, end=" ")
print()
for i in range(len(df)):
    for x in df.iloc[i].values.tolist():
        print(x, end=" ")
    print()"""

import pandas as pd
import io

data = []
while True:
    try:
        input_ = input()
        data.append(input_)
    except EOFError:
        break
data = '\n'.join(data)
df = pd.read_csv(io.StringIO(data))

list = []

for index, row in df.iterrows():
    if row["text"] not in list:
        list.append(row["text"])
    else:
        if row["keep_if_dup"] == "No":
            df.drop(index, inplace=True)

for i in range(len(df)):
    for x in df.iloc[i].values.tolist():
        print(x, end=" ")
    print()