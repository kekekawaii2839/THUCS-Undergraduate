"""import numpy as np
from scipy.sparse import csr_matrix
from sklearn.metrics.pairwise import cosine_similarity

m1, m2, n, a, b = map(int, input().split())

row_a = []
col_a = []
data_a = []

row_b = []
col_b = []
data_b = []

for x in range(a):
    i, j, k = map(int, input().split())
    row_a.append(i-1)
    col_a.append(j-1)
    data_a.append(k)
for x in range(b):
    i, j, k = map(int, input().split())
    row_b.append(i-1)
    col_b.append(j-1)
    data_b.append(k)

matrix_a = csr_matrix((data_a, (row_a, col_a)), shape=(m1, n))
matrix_b = csr_matrix((data_b, (row_b, col_b)), shape=(m2, n))

similarity_matrix = cosine_similarity(matrix_a, matrix_b)
c, d = np.unravel_index(np.argmax(similarity_matrix), similarity_matrix.shape)

print(c+1, d+1)"""

import numpy as np
from sklearn.cluster import KMeans

n, d, k = map(int, input().split())

data = []
for _ in range(n):
    point = list(map(int, input().split()))
    data.append(point)
data = np.array(data)

kmeans = KMeans(n_clusters=k, random_state=0, n_init='auto')
kmeans.fit(data)

labels = kmeans.labels_
cluster_points = {i: [] for i in range(k)}
for i, label in enumerate(labels):
    cluster_points[label].append(data[i])

cluster_means = []
for cluster_id in range(k):
    cluster_data = np.array(cluster_points[cluster_id])
    cluster_mean = np.mean(cluster_data, axis=0)
    cluster_means.append(cluster_mean)
cluster_means = sorted(cluster_means, key=lambda x: tuple(x))

for mean in cluster_means:
    formatted_mean = ['%.2f' % val for val in mean]
    print(' '.join(formatted_mean))
