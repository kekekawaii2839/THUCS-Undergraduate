import sys

my_str = sys.stdin.read()

my_str = my_str.split()
my_str = ''.join(my_str)
print(my_str)