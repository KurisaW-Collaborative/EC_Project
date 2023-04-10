import paddle
import paddle.fluid as fluid
import numpy as np
from PIL import Image
from paddle.vision.transforms import Compose, Normalize, ToTensor

# 定义模型
class FireDetectionModel(fluid.dygraph.Layer):
    def __init__(self, num_classes=2):
        super(FireDetectionModel, self).__init__()
        # First Convolutional Block
        self.conv1_1 = fluid.dygraph.Conv2D(num_channels=3, num_filters=16, filter_size=3, padding=1, act='relu')
        self.pool1 = fluid.dygraph.Pool2D(pool_size=2, pool_stride=2, pool_type='max')
        # Second Convolutional Block
        self.conv2_1 = fluid.dygraph.Conv2D(num_channels=16, num_filters=32, filter_size=3, padding=1, act='relu')
        self.pool2 = fluid.dygraph.Pool2D(pool_size=2, pool_stride=2, pool_type='max')
        # Third Convolutional Block
        self.conv3_1 = fluid.dygraph.Conv2D(num_channels=32, num_filters=64, filter_size=3, padding=1, act='relu')
        self.pool3 = fluid.dygraph.Pool2D(pool_size=2, pool_stride=2, pool_type='max')

        # Output layers
        fc_size = 64 * 28 * 28
        self.fc1 = fluid.dygraph.Linear(fc_size, 512, act='relu')
        self.drop1 = fluid.dygraph.Dropout(p=0.5)
        self.out = fluid.dygraph.Linear(512, num_classes)

    def forward(self, inputs):
        x = self.conv1_1(inputs)
        x = self.pool1(x)
        x = self.conv2_1(x)
        x = self.pool2(x)
        x = self.conv3_1(x)
        x = self.pool3(x)

        print('x shape:', x.shape)
        # x = fluid.layers.reshape(x, shape=[batch_size, 3, 256, 256])
        x = fluid.layers.reshape(x, shape=[batch_size , 3, 265, 256])
        x = self.fc1(x)
        x = self.drop1(x)
        x = self.out(x)
        return x


# 定义数据集读取器
class MyDataset(paddle.io.Dataset):
    def __init__(self, data_path, mode='train', rate=0.8, shuffle=False):
        super(MyDataset, self).__init__()
        self.img_paths = []
        self.labels = []
        self.mode = mode
        self.rate = rate
        self.img_size = (256, 256)

        # Read image paths and labels from files
        with open(data_path, 'r') as f:
            lines = f.readlines()
            for line in lines:
                path, label = line.strip().split(' ')
                self.img_paths.append(path)
                self.labels.append(int(label))

        # Divide dataset into training and validation sets
        if self.mode == 'train':
            self.img_paths = self.img_paths[:int(len(self.img_paths) * self.rate)]
            self.labels = self.labels[:int(len(self.labels) * self.rate)]
        else:
            self.img_paths = self.img_paths[int(len(self.img_paths) * self.rate):]
            self.labels = self.labels[int(len(self.labels) * self.rate):]

        self.transforms = Compose([
            ToTensor(),
            Normalize([0.485, 0.456, 0.406], [0.229, 0.224, 0.225])
        ])

        self.shuffle = shuffle

    def __getitem__(self, idx):
        img_path = self.img_paths[idx]
        label = self.labels[idx]
        img = self.load_image(img_path)
        return img, label

    def __len__(self):
        return len(self.img_paths)

    def load_image(self, path):
        with open(path, 'rb') as f:
            img = Image.open(f)
            img = img.convert('RGB')
        img = np.array(img).astype('float32')
        img /= 255
        img = Image.fromarray((img * 255).astype('uint8')).convert('RGB')
        img = img.resize(self.img_size)
        img = np.array(img).astype('float32')
        img /= 255
        img = paddle.to_tensor(img, dtype='float32')
        img = paddle.transpose(img, (2, 0, 1))
        return img


# 开启动态图模式
paddle.disable_static()

# 设置超参数
epoch_num = 24
batch_size = 8
learning_rate = 0.001

# 创建模型和优化器
model = FireDetectionModel()
optimizer = fluid.optimizer.Adam(learning_rate=learning_rate, parameter_list=model.parameters())

# 准备训练和验证集
data_path = './file.txt'
train_dataset = MyDataset(data_path, mode='train', shuffle=True)
val_dataset = MyDataset(data_path, mode='val')

train_loader = fluid.io.DataLoader(train_dataset, batch_size=batch_size, shuffle=True, num_workers=0)
val_loader = fluid.io.DataLoader(val_dataset, batch_size=batch_size, num_workers=0)

# 训练模型
for epoch in range(epoch_num):
    for batch_id, data in enumerate(train_loader):
        img, label = data
        logits = model(img)
        loss = fluid.layers.softmax_with_cross_entropy(logits, label)
        avg_loss = fluid.layers.mean(loss)

        avg_loss.backward()
        optimizer.minimize(avg_loss)
        model.clear_gradients()

        if batch_id % 10 == 0:
            print("Epoch {} | Batch {} | Loss {}".format(epoch + 1, batch_id + 1, avg_loss.numpy()[0]))

    # 每个epoch结束后在验证集上评估模型
    accs = []
    for batch_id, data in enumerate(val_loader):
        img, label = data
        logits = model(img)
        preds = fluid.layers.softmax(logits)
        acc = fluid.layers.accuracy(preds, label)
        accs.append(acc.numpy()[0])

    avg_acc = np.mean(accs)
    print("Epoch {} | Validation Accuracy {}".format(epoch + 1, avg_acc))

    fluid.save_dygraph(model.state_dict(), './fire_detection_model')

print("Training finished!")

# 加载模型
model_dict, _ = fluid.load_dygraph('./fire_detection_model')
infer_model = FireDetectionModel()
infer_model.load_dict(model_dict)


def predict(image_path, model):
    # 读取图像
    img = Image.open(image_path).convert('RGB')
    img = img.resize((256, 256))

    # 转换为Tensor并进行归一化
    transform = Compose([
        ToTensor(),
        Normalize([0.485, 0.456, 0.406], [0.229, 0.224, 0.225])
    ])
    img = transform(img)

    # 使用模型进行预测
    model.eval()
    with fluid.dygraph.no_grad():
        img = fluid.dygraph.to_variable(img[None, ...])
        logits = model(img)
        probs = fluid.layers.softmax(logits)
        preds = fluid.layers.argmax(probs, axis=-1)
        return preds.numpy()[0]

image_path = './test_image.jpg'
pred = predict(image_path, infer_model)
if pred == 0:
    print("The image is non-fire.")
else:
    print("The image is fire!")
