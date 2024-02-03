import numpy as np
import matplotlib.pyplot as plt

mu = 100
sigma = 10
random_numbers = np.random.normal(mu, sigma, 1000)

plt.hist(random_numbers, bins=30, density=True, alpha=0.6, color='g')
plt.show()

# (2)
num_samples = 1000
data = np.random.normal(mu, sigma, num_samples)

sample_size = 1000
samples = np.random.choice(data, sample_size, replace=True)

plt.hist(samples, bins=20, edgecolor='k')
plt.title('Random Samples from N(100, 100)')
plt.xlabel('Value')
plt.ylabel('Frequency')
plt.show()