#include "rclcpp/rclcpp.hpp"

#include "voro_swarm/cal_voro_cell.hpp"
#include "voro_swarm/voro_cell.hpp"


// HERE: make launch file & update it accordingly


int main(int argc, char** argv){

  /* node */
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("node_test_cal_voro_cell");
  auto publisher = node->create_publisher<visualization_msgs::msg::MarkerArray>("node_test_cal_voro_cell/voro_cell", 9);

  /* voronoi: container */
  int n = 20;
  voro_swarm::CalVoroCell cal_voro_cell;
  cal_voro_cell.set_input_and_make_container(voro_swarm::CalVoroCell::get_random_input_points(n), 0.5);

  /* visualization loop */
  rclcpp::Rate rate(1.0);
  int counter = 0;
  while(rclcpp::ok()){
    counter++;
    int point_ind = counter % n;

    voro_swarm::VoroCell voro_cell;
    cal_voro_cell.get_voro_cell(point_ind, voro_cell);

    visualization_msgs::msg::MarkerArray msg;
    Eigen::Vector3d color = (Eigen::Vector3d::Random() + Eigen::Vector3d(1, 1, 1)) * 0.5;
    msg = voro_cell.get_msg_marker_array("map", std::to_string(point_ind), 0.08, 0.02, color(0), color(1), color(2), 0.8, true);

    publisher->publish(msg);
    rate.sleep();
  }

  /* shutdown */
  rclcpp::shutdown();

  /* return */
  return 0;

}
