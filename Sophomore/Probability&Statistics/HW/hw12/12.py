import numpy as np
import math

lambda_val = 1
num_simulations = 1000
sample_size = 20

sample_means = []
results = []

for _ in range(num_simulations):
    samples = np.random.poisson(lambda_val, size=sample_size)
    sample_mean = np.mean(samples)
    sample_means.append(sample_mean)

for sample_mean in sample_means:
    if abs(sample_mean - 1) < 1.84 * math.sqrt(lambda_val / sample_size):
        results.append(1)
    else:
        results.append(0)

print(results.count(0))