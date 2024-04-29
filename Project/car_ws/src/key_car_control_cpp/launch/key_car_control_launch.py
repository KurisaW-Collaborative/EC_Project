import launch
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='key_car_control_cpp',
            executable='key_car_control_node',
            name='key_car_control_node',
            output='screen'
        )
    ])

