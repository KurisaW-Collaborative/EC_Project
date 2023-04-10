# import os
#
# path = './fire_detection_dataset/noFire'
#
# count = 1
# for file_name in os.listdir(path):
#     if file_name.endswith('.jpg'):
#         old_path = os.path.join(path, file_name)
#         new_path = os.path.join(path, f"non_fire.{count}.png") # 使用f-string格式化文件名
#         os.rename(old_path, new_path)
#         count += 1





from PIL import Image
import os

# 定义图像尺寸
img_size = (256, 256)

# 定义数据集路径
data_dir = './fire_detection_dataset/fire'

# 遍历数据集中所有图片，检查其尺寸并进行调整
for img_path in os.listdir(data_dir):
    img_path = os.path.join(data_dir, img_path)
    with open(img_path, 'rb') as f:
        img = Image.open(f)
        # 获取当前图像尺寸
        width, height = img.size
        if width != img_size[0] or height != img_size[1]:
            # 调整图像尺寸
            img = img.resize(img_size, Image.ANTIALIAS)
            # 保存新尺寸的图像
            img.save(img_path)

        print("Image {} size: {}".format(img_path, img.size))
