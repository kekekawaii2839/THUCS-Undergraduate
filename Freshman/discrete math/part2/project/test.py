import networkx as nx
import numpy as np
import itertools

universities = ['THU', 'PKU', 'RUC', 'BNU', 'BIT' ,'BUAA', 'CAU', 'MUC']
d = np.array([[0, 2.2, 3.5, 5.4, 4.6, 2.3, 2.25, 5.5],
     [2.2, 0, 2.24, 5.85, 3, 3.29, 4.5, 4.22],
     [3.5, 2.24, 0, 4.13, 1.22, 2.81, 4.81, 2.07],
     [5.4, 5.85, 4.13, 0, 4.6, 3.3, 4.82, 4.14],
     [4.6, 3, 1.22, 4.6, 0, 3.85, 5.99, 1.24],
     [2.3, 3.29, 2.81, 3.3, 3.85, 0, 2.17, 4.41],
     [2.25, 4.5, 4.81, 4.82, 5.99, 2.17, 0, 6.54],
     [5.5, 4.22, 2.07, 4.14, 1.24, 4.41, 6.54, 0]])

'''G = nx.from_numpy_matrix(d)
nx.set_node_attributes(G, dict(zip(range(len(universities)), universities)), 'name')

travel = nx.approximation.traveling_salesman_problem(G, cycle=True)
print(nx.path_weight(G, travel, weight='weight'))
print([G.nodes[travel[i]]['name'] for i in range(len(travel))])'''

G = nx.Graph()
G.add_nodes_from(universities)
for i in range(len(universities)):
    for j in range(i+1, len(universities)):
        G.add_edge(universities[i], universities[j], weight=d[i][j])

min_length = float('inf')
shortest_path = []
for p in itertools.permutations(universities):
    l = sum([G[p[i]][p[i+1]]['weight'] for i in range(len(universities)-1)])
    l += G[p[-1]][p[0]]['weight']
    if l < min_length:
        min_length = l
        shortest_path = p
print(min_length)
print(shortest_path)