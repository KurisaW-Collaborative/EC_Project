import os

# 设置所需路径信息
base_folder = './fire_detection_dataset'
no_fire_folder = 'noFire'
fire_folder = 'fire'

# 定义写入文件函数
def write_to_file(file_path, label):
    with open('fire.txt', 'a') as file:
        file.write(f'{file_path} {label}\n')

# 处理 noFire 文件夹
no_fire_path = os.path.join(base_folder, no_fire_folder)
for i, file_name in enumerate(os.listdir(no_fire_path)):
    if file_name.endswith('.png'):
        file_path = os.path.join(no_fire_path, file_name)
        write_to_file(file_path, 0)

# 处理 fire 文件夹
fire_path = os.path.join(base_folder, fire_folder)
for i, file_name in enumerate(os.listdir(fire_path)):
    if file_name.endswith('.png'):
        file_path = os.path.join(fire_path, file_name)
        write_to_file(file_path, 1)
