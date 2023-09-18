"""import math

a, b, c = map(int, input().split())

if a == 0:
    if b == 0:
        if c == 0:
            print("5")
        else:
            print("4")
    else:
        x = -c / b
        if c == 0:
            x = 0
        print("6")
        print("{:.2f}".format(x))
else:
    delta = b ** 2 - 4 * a * c
    if delta > 0:
        x1 = (-b + math.sqrt(delta)) / (2 * a)
        x2 = (-b - math.sqrt(delta)) / (2 * a)
        print("1")
        print("{:.2f} {:.2f}".format(min(x1, x2), max(x1, x2)))
    elif delta == 0:
        x = -b / (2 * a)
        print("2")
        print("{:.2f}".format(x))
    else:
        print("3")"""

"""def find_unique_characters(source_str, target_str):
    unique_chars = []

    for char in source_str:
        if char not in target_str and char not in unique_chars:
            unique_chars.append(char)

    unique_chars.sort()  # 按字母顺序排序
    result = ' '.join(unique_chars)  # 用空格连接字符

    return result
source_str = input()
target_str = input()

result = find_unique_characters(source_str, target_str)
print(result)"""

"""n = int(input())
a = list(map(int, input().split()))
target = int(input())

for i in range(n):
    for j in range(n):
        if i != j and a[i] + a[j] == target:
            print(i, j)
            exit()"""

"""def find_most_freq_num(a):
    max_count = 0
    max_num = 0
    for num in a:
        count = a.count(num)
        if count > max_count:
            max_count = count
            max_num = num
    return max_num

n = int(input())
a = []
for i in range(n):
    a.append(int(input()))
a.sort()
print(find_most_freq_num(a))"""

def yes(input):
    if input == input[::-1]:
        return True
    else:
        return False

string = input()
res = ""
for i in range(len(string)):
    for j in range(i+1, len(string)+1):
        if yes(string[i:j]):
            if len(string[i:j]) > len(res):
                res = string[i:j]
print(res)