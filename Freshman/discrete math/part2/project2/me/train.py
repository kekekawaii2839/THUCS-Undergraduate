from utils import DataSet
from gcn import GCLayer, GCModel
import tensorflow as tf
tf.compat.v1.enable_eager_execution()

#variable definition
print("yosoro~")
dataset = DataSet(path="citeseer/", dataset="citeseer")
features, adj, labels, train_mask, val_mask, test_masks = dataset.get_data()

G = [features, adj]
model = GCModel(input_dim=features.shape[1], output_dim=labels.shape[1])

loss_object = tf.keras.losses.CategoricalCrossentropy(from_logits=False) #这才是one-hot label该用的函数
optimizer = tf.keras.optimizers.Adam(learning_rate=0.01) #使用Adam优化器

epoch_num = 200

def calc_grad(model, inputs, targets, train_mask):
    with tf.GradientTape() as tape:
        predictions = model(inputs, training=True)
        #print("shapes=", targets.shape, predictions.shape, train_mask.shape)
        true = tf.gather_nd(targets, tf.where(train_mask)) #这里不能写成targets[train_mask]
        pred = tf.gather_nd(predictions, tf.where(train_mask)) #因为train_mask是bool类型的, 不能用来索引
        #print("shapes2=", true.shape, pred.shape)
        loss = loss_object(y_true=true, y_pred=pred)
    return loss, tape.gradient(loss, model.trainable_variables)

def testing(mask):
    predictions = model(G)
    first = tf.math.argmax(tf.gather_nd(predictions, tf.where(mask)), -1)
    second = tf.math.argmax(tf.cast(tf.gather_nd(labels, tf.where(mask)), dtype=tf.float32), -1)
    ll = tf.math.equal(first, second)
    acc = tf.reduce_mean(tf.cast(ll, dtype=tf.float32))
    return acc

#training
print("start training...")
for epoch in range(epoch_num+1):
    loss, grads = calc_grad(model, G, labels, train_mask)
    optimizer.apply_gradients(zip(grads, model.trainable_variables))

    train_acc = testing(train_mask)
    val_acc = testing(val_mask)
    test_acc = testing(test_masks)
    if epoch % 10 == 0:
        print("epoch: {}, loss: {}, train_acc: {}, val_acc: {}, test_acc: {}".format(epoch, loss.numpy(), train_acc.numpy(), val_acc.numpy(), test_acc.numpy()))