cmake_minimum_required(VERSION 3.5)
project(key_car_control_cpp)

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

# Add executable
add_executable(key_car_control_node src/key_car_control_node.cpp)

# Link executable with dependencies
ament_target_dependencies(key_car_control_node
    rclcpp
    std_msgs
)

# Install executable
install(TARGETS
    key_car_control_node
    DESTINATION lib/${PROJECT_NAME}
)

# Install launch files
install(DIRECTORY
    launch
    DESTINATION share/${PROJECT_NAME}/
)

ament_package()

