import numpy as np

k = 10
p_true = 0.5
n = 10

samples = np.random.binomial(k, p_true, size=n)

mean_estimation = np.mean(samples)
variance_estimation = np.var(samples)

p_e = 1-variance_estimation/mean_estimation
k_e = mean_estimation/p_e

print(p_e, k_e)