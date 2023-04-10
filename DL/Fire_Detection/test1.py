import numpy as np
import paddle.fluid as fluid
from paddle.fluid.dygraph.nn import Conv2D, Pool2D, Linear
from paddle.fluid.dygraph.base import to_variable
from paddle.vision.transforms import transforms


class FireDetectionModel(fluid.dygraph.Layer):
    def __init__(self, num_classes=2):
        super(FireDetectionModel, self).__init__()
        self.resnet = fluid.dygraph.ResNet50(pretrained=True)
        self.fc = Linear(in_features=2048, out_features=num_classes, act='softmax')

    def forward(self, inputs):
        x, _ = self.resnet(inputs)
        x = self.fc(x)
        return x

# 数据预处理：随机翻转和裁剪
train_transforms = transforms.Compose([
    transforms.RandomHorizontalFlip(),
    transforms.RandomCrop((265, 256))
])

val_transforms = transforms.Compose([
    transforms.CenterCrop((265, 256))
])


data_path = './file.txt'
train_dataset = MyDataset(data_path, mode='train', shuffle=True)
val_dataset = MyDataset(data_path, mode='val')

# 构建训练集和验证集
train_dataset = FireDataset(train_list, transform=train_transforms)
val_dataset = FireDataset(val_list, transform=val_transforms)

train_reader = paddle.batch(
    paddle.reader.shuffle(train_dataset, buf_size=500),
    batch_size=32)

val_reader = paddle.batch(val_dataset, batch_size=32)

# 模型定义
with fluid.dygraph.guard(place=fluid.CUDAPlace(0)):
    model = FireDetectionModel(num_classes=2)
    model.train()
    optimizer = fluid.optimizer.AdamOptimizer(learning_rate=0.001, regularization=fluid.regularizer.L2Decay(1e-5), parameter_list=model.parameters())

    # 训练模型
    for epoch in range(epoch_num):
        print('Epoch:', epoch+1)
        for batch_id, data in enumerate(train_reader()):
            image_data, label_data = zip(*data)

            img = to_variable(np.array(image_data).astype('float32').reshape(-1, 3, 265, 256))
            label = to_variable(np.array(label_data).astype('int64').reshape(-1, 1))

            logits = model(img)
            loss = fluid.layers.softmax_with_cross_entropy(logits, label)
            avg_loss = fluid.layers.mean(loss)

            avg_loss.backward()
            optimizer.minimize(avg_loss)
            model.clear_gradients()

            if batch_id % 10 == 0:
                print("Batch {} | Loss {}".format(batch_id + 1, avg_loss.numpy()[0]))

        # 每个epoch结束后在验证集上评估模型
        model.eval()
        accs = []
        for batch_id, data in enumerate(val_reader()):
            image_data, label_data = zip(*data)

            img = to_variable(np.array(image_data).astype('float32').reshape(-1, 3, 265, 256))
            label = to_variable(np.array(label_data).astype('int64').reshape(-1, 1))

            logits = model(img)
            preds = fluid.layers.softmax(logits)
            acc = fluid.layers.accuracy(preds, label)
            accs.append(acc.numpy()[0])

        avg_acc = np.mean(accs)
        print("Validation Accuracy {}".format(avg_acc))

        fluid.save_dygraph(model.state_dict(), './fire_detection_model')

    print("Training finished!")
