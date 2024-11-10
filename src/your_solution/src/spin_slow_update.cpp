#include "spin_slow_update.h"

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SlowSolution>());
  rclcpp::shutdown();
  return 0;
}

SlowSolution::SlowSolution() : Node("slowsolution") {
  pos_subscription = this->create_subscription<ArrayMsg>(
    "measuredpos", 10, std::bind(&SlowSolution::pos_callback, this, std::placeholders::_1));
  
  predicted_pos_publisher = this->create_publisher<ArrayMsg>("predictedpos", 10);
}

void SlowSolution::pos_callback(const ArrayMsg::SharedPtr msg) {
  RCLCPP_INFO(this->get_logger(), "Received position: [%f, %f]", msg->data[0], msg->data[1]);

  ArrayMsg predicted_pos_msg;
  predicted_pos_msg.data = {msg->data[0], msg->data[1]};
  predicted_pos_publisher->publish(predicted_pos_msg);

  
}