import tensorflow as tf

class GCLayer(tf.keras.layers.Layer):
    def __init__(self, input_dim, output_dim,
                 activation=None, w_regularizer=None, 
                 dropout_rate=5e-4):
        super(GCLayer, self).__init__()
        self.input_dim = input_dim
        self.output_dim = output_dim
        self.activation = activation #激活函数, 可以是ReLU或者softmax
        self.w_regularizer = w_regularizer
        self.dropout_rate = dropout_rate

    def build(self, input_shape):
        self.w = self.add_weight(shape=(self.input_dim, self.output_dim),
                                 initializer='glorot_uniform')

    def call(self, nodes, edges):
        #计算论文中的(A~)*X*W
        #print(nodes.shape, edges.shape, self.w.shape)
        xw = tf.matmul(nodes, self.w)
        output = tf.matmul(edges, xw)
        if self.activation is not None:
            output = self.activation(output)
        output = tf.nn.dropout(output, rate=self.dropout_rate)
        return output

class GCModel(tf.keras.Model):
    def __init__(self, input_dim, output_dim):
        super(GCModel, self).__init__()

        self.GN1 = GCLayer(input_dim, 16, activation=tf.keras.activations.relu, w_regularizer=tf.keras.regularizers.l2(5e-4))
        self.GN2 = GCLayer(16, output_dim, activation=tf.keras.activations.softmax)
    
    def call(self, x, training=False):
        #使用tf.cast将x[0]和x[1]转换为float32类型, 不然报错
        nodes = tf.cast(x[0], dtype=tf.float32)
        edges = tf.cast(x[1], dtype=tf.float32)
        H1 = self.GN1(nodes, edges)
        H2 = self.GN2(H1, edges)
        return H2