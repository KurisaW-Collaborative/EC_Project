import os

data_dir = "./fire_detection_dataset"
file_path = "./file.txt"

with open(file_path, 'w') as f:
    for label, class_name in enumerate(['noFire', 'fire']):
        image_files = os.listdir(os.path.join(data_dir, class_name))
        for image_file in image_files:
            image_path = os.path.join(data_dir, class_name, image_file)
            f.write("{} {}\n".format(image_path, label))
