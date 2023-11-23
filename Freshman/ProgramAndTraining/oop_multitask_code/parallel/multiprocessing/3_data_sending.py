from multiprocessing import Process, Queue
import time

num_procs = 4

def worker(task_queue, result_queue):
    for data in iter(task_queue.get, None):
        result = data * 2
        result_queue.put((data, result))
    result_queue.put(None)

def master(task_queue):
    for i in range(100000):
        task_queue.put(i)
    for _ in range(num_procs):
        task_queue.put(None)

procs = []

QUEUE_LIMIT = 100

task_queue, result_queue = Queue(maxsize=QUEUE_LIMIT), Queue(maxsize=QUEUE_LIMIT)

start_time = time.time()
for id in range(num_procs):
    proc = Process(target=worker, args=(task_queue, result_queue))
    procs.append(proc)
    proc.start()

proc_master = Process(target=master, args=(task_queue,))
proc_master.start()

num_active = num_procs
with open('output.txt', 'w') as f:
    while True:
        data = result_queue.get()
        if data is None:
            num_active -= 1
            if num_active == 0:
                break
        else:
            data, result = data
            f.write(f"{data} {result}\n")

end_time = time.time()
print("Elapsed:", end_time - start_time)
