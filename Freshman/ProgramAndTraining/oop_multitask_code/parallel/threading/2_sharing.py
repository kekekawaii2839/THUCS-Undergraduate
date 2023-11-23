from threading import Thread, Lock
import time

result = 1

lock = Lock()

def print_func(id):
    global result
    start_time = time.time()
    for i in range(id * 100000):
        lock.acquire(blocking=True) # 讲解blocking
        """The return value is True if the lock is acquired successfully, False if not (for example if the timeout expired).
        
        When invoked with the blocking argument set to True (the default), block until the lock is unlocked, then set it to locked and return True.

        When invoked with the blocking argument set to False, do not block. If a call with blocking set to True would block, return False immediately; otherwise, set the lock to locked and return True."""
        result *= (i + 1)
        result %= 998244353
        lock.release()
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