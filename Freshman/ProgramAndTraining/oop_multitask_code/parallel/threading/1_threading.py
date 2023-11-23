from threading import Thread
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

num_threads = 4
threads = []

start_time = time.time()
for id in range(num_threads):
    thread = Thread(target=print_func, args=(id,))
    threads.append(thread)
    thread.start()

for thread in threads:
    thread.join()

end_time = time.time()
print("Elapsed:", end_time - start_time)
print("Result in the main process:", result)