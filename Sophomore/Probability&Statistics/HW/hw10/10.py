import numpy as np
import matplotlib.pyplot as plt

n = 100
mu = 5
m = 1000

dataset = np.random.standard_normal(n) + mu

theta_hat_stars = []

for _ in range(m):
    sample = [dataset[np.random.randint(0, n)] for __ in range(n)]
    theta_hat_star = np.exp(np.mean(sample))
    theta_hat_stars.append(theta_hat_star)

temp = [(haha - np.mean(theta_hat_stars))**2 for haha in theta_hat_stars]
v_boot = np.mean(temp)

plt.hist(theta_hat_stars, bins=20)
# plt.show()

print("v_boot:", v_boot)