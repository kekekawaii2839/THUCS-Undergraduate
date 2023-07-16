import scipy.sparse as sp
import numpy as np

class DataSet():
    def __init__(self, path="cora/", dataset="cora"):
        self._path = path
        self._data = self.preprocess_data(dataset=dataset)
    
    def get_data(self):
        return self._data
    
    def load_data(self, dataset):
        print("Loading dataset {} ...".format(dataset))
        feature_labels = np.genfromtxt("{}{}.content".format(self._path, dataset), dtype=np.dtype(str))
        edges = np.genfromtxt("{}{}.cites".format(self._path, dataset), dtype=np.dtype(str))
        return feature_labels, edges
    
    def to_onehot(self, labels):
        classes = set(labels)
        classes_dict = {c: np.identity(len(classes))[i, :] for i, c in enumerate(classes)}
        labels_onehot = np.array(list(map(classes_dict.get, labels)), dtype=np.int32)
        return labels_onehot
    
    def preprocess_data(self, dataset):
        print("Preprocessing data ...")
        feature_labels, edges = self.load_data(dataset=dataset)

        features = feature_labels[:, 1:-1].astype(np.float32) #提取出除了第0列的id和最后一列的label以外的0和1, 即feature
        features /= features.sum(1).reshape(-1, 1) #normalize features

        labels_temp = feature_labels[:, -1] #提取出最后一列的label
        labels = self.to_onehot(labels_temp) #将label转化为one-hot形式

        idx = np.array(feature_labels[:, 0], dtype=np.dtype(str)) #提取出第0列的id
        idx_map = {j: i for i, j in enumerate(idx)} #构建id和index的映射关系
        temp_list = list(map(idx_map.get, edges.flatten()))
        #开始清洗数据
        for i in range(len(temp_list)):
            if temp_list[i] == None:
                temp_list[i] = -1
                if i%2 == 0:
                    temp_list[i+1] = -1
                else:
                    temp_list[i-1] = -1
        temp_list = [x for x in temp_list if x != -1]
        edge_index = np.array(temp_list, dtype=np.int32).reshape(int(len(temp_list)/2),2) #将edges中的id转化为index
        edge_index_len = len(edge_index) #不写这个临时变量会死循环最后memory error
        for i in range(edge_index_len):#将edge_index中的边的方向反转并加入进去
            edge_index = np.concatenate((edge_index, [[edge_index[i][1], edge_index[i][0]]])) #注意这里添加进去的元素的shape不要错
        
        #根据上面处理好的edge_index构建邻接矩阵, adj应当是对称的方阵
        adj = sp.coo_matrix((np.ones(len(edge_index)),
                             (edge_index[:, 0], edge_index[:, 1])),
                             shape=(features.shape[0], features.shape[0]),
                             dtype=np.float32)

        #根据论文的公式计算出(D~)^{-0.5}*(A+I)*(D~)^{-0.5}
        adj = adj + sp.eye(adj.shape[0]) #加上单位矩阵
        deg = np.array(adj.sum(1)) #计算每一行的和, 即论文中的D~
        d_s = sp.diags(np.power(deg, -0.5).flatten()) #计算D~的-0.5次方
        adj = d_s.dot(adj).dot(d_s).tocsr().todense() #计算出(D~)^{-0.5}*(A+I)*(D~)^{-0.5}, 并转换成密集矩阵以便后续计算

        #接下来设置训练集, 验证集和测试集
        train = np.arange(len(features)-150, len(features)) #训练集
        val = np.arange(len(features)-500, len(features)-150) #验证集
        test = np.arange(len(features)-500) #测试集, 2708是总的数据集大小, 后续可以改成自动计算

        train_mask = np.zeros(features.shape[0], dtype=np.bool) #构建训练集掩码
        train_mask[train] = True
        val_mask = np.zeros(features.shape[0], dtype=np.bool) #构建验证集掩码
        val_mask[val] = True
        test_mask = np.zeros(features.shape[0], dtype=np.bool) #构建测试集掩码
        test_mask[test] = True

        print('Dataset has {} nodes, {} edges and {} features.'.format(features.shape[0], edges.shape[0], features.shape[1]))

        return features, adj, labels, train_mask, val_mask, test_mask