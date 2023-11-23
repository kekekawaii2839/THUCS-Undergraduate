from concurrent.futures import ThreadPoolExecutor
import threading
import time

result = 1

lock = threading.Lock()

def print_func(id):
    global result
    start_time = time.time()
    for i in range(id * 100000):
        lock.acquire(blocking=True)
        result *= (i + 1)
        result %= 998244353
        lock.release()
    end_time = time.time()
    print('id:', id, 'result:', result, 'elapsed:', end_time - start_time)
    return result

num_tasks = 4

start_time = time.time()
with ThreadPoolExecutor(max_workers=3) as executor:
    for task_result in executor.map(print_func, range(num_tasks)):
        print(task_result)
end_time = time.time()

print("Elapsed:", end_time - start_time)
print("Result in the main process:", result)