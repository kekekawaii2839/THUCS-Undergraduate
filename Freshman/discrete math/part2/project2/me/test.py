import tensorflow as tf
import numpy as np
tf.enable_eager_execution()

t = tf.constant([[1, 2, 3], [4, 5, 6]])
n = t.numpy()
print(n)