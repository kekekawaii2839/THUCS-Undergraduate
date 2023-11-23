from multiprocessing import Pool, cpu_count
import time

result = 1

def print_func(id):
    global result
    start_time = time.time()
    for i in range(40000000):
        result *= (i + 1)
        result %= 998244353
    end_time = time.time()
    print('id:', id, 'result:', result, 'elapsed:', end_time - start_time)
    return result

num_procs = 4
pool = Pool(processes=cpu_count())

# 1 map
start_time = time.time()
results = pool.map(print_func, range(num_procs))
print(results)
end_time = time.time()

# 2 imap
# start_time = time.time()
# for result in pool.imap(print_func, range(num_procs)):
#     print(result)
# end_time = time.time()

# 3 imap_unordered
# start_time = time.time()
# for result in pool.imap_unordered(print_func, range(num_procs)):
#     print(result)
# end_time = time.time()

print("Elapsed:", end_time - start_time)
print("Result in the main process:", result)