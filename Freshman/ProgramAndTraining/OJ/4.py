"""class Pet:
    def __init__(self, name):
        self.name = name
        self.happiness = 0
        self.smart = 0
        self.health = 0
        
    def play(self):
        self.happiness += 10
        self.smart += 2
        self.health += 6
    
    def eat(self):
        self.happiness += 5
        self.smart += 1
        self.health += 10
        
    def sleep(self):
        self.happiness += 3
        self.smart += 1
        self.health += 5

people = []

n = int(input())
for i in range(n):
    infos = input().split()
    pet_names = input().split()
    people.append({
        'name': infos[0],
        'money': int(infos[1]),
        'pet_num': int(infos[2]),
        'pets': [Pet(name) for name in pet_names]
    })

m = int(input())
for i in range(m):
    operation_infos = input().split()
    person_index = -1
    for j in range(len(people)):
        if people[j]['name'] == operation_infos[0]:
            person_index = j
            break
    if person_index == -1:
        raise ValueError('Person not found')
    person = people[person_index]
    pet_index = -1
    for j in range(len(person['pets'])):
        if person['pets'][j].name == operation_infos[1]:
            pet_index = j
            break
    if pet_index == -1:
        raise ValueError('Pet not found')
    pet = person['pets'][pet_index]
    if operation_infos[2] == 'play':
        pet.play()
        person['money'] -= 10
    elif operation_infos[2] == 'eat':
        pet.eat()
        person['money'] -= 5
    elif operation_infos[2] == 'sleep':
        pet.sleep()
        person['money'] -= 3
    else:
        raise ValueError('Operation not found')
    
for person in people:
    output = ''
    output += person['name'] + ' '
    output += str(person['money']) + ' '
    
    max_happiness = -1
    max_smart = -1
    max_health = -1
    for pet in person['pets']:
        max_happiness = max(max_happiness, pet.happiness)
        max_smart = max(max_smart, pet.smart)
        max_health = max(max_health, pet.health)
    output += str(max_happiness) + ' '
    output += str(max_smart) + ' '
    output += str(max_health)
    print(output)
"""

import threading
from threading import Thread
import time

lock = threading.Lock()

l = []
def thread_func(id, instructions):
    global l
    for inst in instructions:
        time.sleep(0.1)
        if inst[0] != id:
            continue
        if inst[1] == 1:
            lock.acquire()
        elif inst[1] == -1:
            lock.release()
        elif inst[1] == 0:
            if lock.locked():
                l.append(id)
                print(l)
        else:
            raise ValueError('Invalid instruction')
    return

instructions = []
num_threads, num_instructions = map(int, input().split(' '))
for i in range(num_instructions):
    instructions.append([item for item in map(int, input().split(' '))])

threads = []
try:
    for id in range(num_threads):
        thread = Thread(target=thread_func, args=(id, instructions))
        threads.append(thread)
        thread.start()

    for thread in threads:
        thread.join()
except Exception as e:
    pass
