#include "rclcpp/rclcpp.hpp"

#include "voro_swarm/cal_voro_cell.hpp"
#include "voro_swarm/voro_cell.hpp"


int main(int argc, char** argv){

  /* node */
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("node_test_cal_voro_cell");
  auto publisher = node->create_publisher<visualization_msgs::msg::MarkerArray>("node_test_cal_voro_cell/voro_cell", 9);







  
  int n = 5;
  auto input_points = voro_swarm::CalVoroCell::get_random_input_points(n);
  voro_swarm::CalVoroCell cal_voro_cell;
  voro_swarm::VoroCell voro_cell;
  cal_voro_cell.set_input_and_make_container(input_points, 0.1);
  cal_voro_cell.get_voro_cell(0, voro_cell);





  visualization_msgs::msg::MarkerArray msg;  
  Eigen::MatrixXd face;
  face.resize(4, 3);
  face << 0, 0, 1,
          1, 0, 1,
          1, 1, 0,
          0, 1, 1;
  visualization_msgs::msg::Marker mk = voro_swarm::VoroCell::get_msg_marker_from_face(face, "map", 0, 0.03, 1, 1, 0, 1);
  msg.markers.push_back(mk);
  





  /* loop */
  rclcpp::Rate rate(1.0);
  while(rclcpp::ok()){
    publisher->publish(msg);
    rate.sleep();
  }

  /* shutdown */
  rclcpp::shutdown();

  /* return */
  return 0;

}
