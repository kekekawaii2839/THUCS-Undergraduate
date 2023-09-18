"""def h_index(citations):
    citations.sort()
    for i in range(len(citations)):
        if citations[i] >= len(citations) - i:
            return len(citations) - i
    return 0

citations = [int(x) for x in input().split()]
print(h_index(citations))"""

"""import re
email_str = input()

pattern = r"(\w+)@(\w+)\.(\w+)"

result = re.match(pattern, email_str)
if result:
    print("True")
else:
    print("False")"""

class database:
    def __init__(self):
        self.db = {}
    
    def query(self, key):
        if key in self.db:
            return self.db[key]
        else:
            return None
    
    def insert(self, key, value):
        self.db[key] = value
    
    def delete(self, key):
        if key in self.db:
            del self.db[key]
    
    def sort(self):
        self.db = sorted(self.db.items(), key=lambda x: x[0])

db = database()
n, m = map(int, input().split())
for i in range(n):
    key, value = input().split()
    db.insert(key, value)
for i in range(m):
    inst = input().split()
    func = inst[0]
    if func == "Q":
        key = inst[1]
        print(db.query(key))
    elif func == "A":
        key = inst[1]
        value = inst[2]
        db.insert(key, value)
    elif func == "D":
        key = inst[1]
        db.delete(key)

db.sort()
for key, value in db.db:
    print(key, value)