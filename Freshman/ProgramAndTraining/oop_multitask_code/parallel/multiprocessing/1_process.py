from multiprocessing import Process
import time

result = 1

def print_func(id):
    global result
    start_time = time.time()
    for i in range(id * 10000000):
        result *= (i + 1)
        result %= 998244353
    end_time = time.time()
    print('id:', id, 'result:', result, 'elapsed:', end_time - start_time)

num_procs = 4
procs = []

start_time = time.time()
for id in range(num_procs):
    proc = Process(target=print_func, args=(id,))
    procs.append(proc)
    proc.start()

for proc in procs:
    proc.join()

end_time = time.time()
print("Elapsed:", end_time - start_time)
print("Result in the main process:", result)