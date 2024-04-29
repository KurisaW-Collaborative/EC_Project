#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

class KeyCarControlNode : public rclcpp::Node
{
public:
    KeyCarControlNode() : Node("key_car_control")
    {
        // Create publishers for control commands
        forward_pub_ = create_publisher<std_msgs::msg::String>("cmd_forward", 10);
        backward_pub_ = create_publisher<std_msgs::msg::String>("cmd_backward", 10);
        left_pub_ = create_publisher<std_msgs::msg::String>("cmd_left", 10);
        right_pub_ = create_publisher<std_msgs::msg::String>("cmd_right", 10);

        // Set up non-blocking keyboard input
        setNonBlockingInput();
        timer_ = create_wall_timer(std::chrono::milliseconds(100), std::bind(&KeyCarControlNode::keyboardInputCallback, this));
    }

    ~KeyCarControlNode()
    {
        // Restore original terminal settings
        restoreTerminalSettings();
    }

private:
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr forward_pub_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr backward_pub_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr left_pub_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr right_pub_;
    rclcpp::TimerBase::SharedPtr timer_;
    int keyboard_fd_;
    struct termios original_terminal_settings_;

    void setNonBlockingInput()
    {
        // Save original terminal settings
        tcgetattr(STDIN_FILENO, &original_terminal_settings_);

        // Set terminal to non-canonical mode (raw mode) to enable non-blocking input
        struct termios new_settings = original_terminal_settings_;
        new_settings.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);

        // Open stdin in non-blocking mode
        int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

        // Store keyboard file descriptor
        keyboard_fd_ = STDIN_FILENO;
    }

    void restoreTerminalSettings()
    {
        // Restore original terminal settings
        tcsetattr(STDIN_FILENO, TCSANOW, &original_terminal_settings_);
    }

    void keyboardInputCallback()
    {
        char key;
        if (read(keyboard_fd_, &key, 1) < 0)
        {
            if (errno != EAGAIN) // EAGAIN means no data available
            {
                perror("read");
            }
            return;
        }

        std_msgs::msg::String msg;
        msg.data = "stop"; // Default command is to stop

        switch (key)
        {
        case 'w':
            msg.data = "forward";
            forward_pub_->publish(msg);
            printKeyInfo("Forward");
            break;
        case 's':
            msg.data = "backward";
            backward_pub_->publish(msg);
            printKeyInfo("Backward");
            break;
        case 'a':
            msg.data = "left";
            left_pub_->publish(msg);
            printKeyInfo("Left");
            break;
        case 'd':
            msg.data = "right";
            right_pub_->publish(msg);
            printKeyInfo("Right");
            break;
        case 'q':
            // Quit the node when 'q' is pressed
            rclcpp::shutdown();
            break;
        }
    }

    void printKeyInfo(const std::string& keyName)
    {
        RCLCPP_INFO(get_logger(), "Pressed key: %s", keyName.c_str());
    }
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<KeyCarControlNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

