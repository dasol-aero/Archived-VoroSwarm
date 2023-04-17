#include "voro_swarm/voro_cell.hpp"


namespace voro_swarm{


visualization_msgs::msg::Marker VoroCell::get_msg_marker_from_face(
  const Eigen::MatrixXd& face,
  const std::string&     frame_id,
  const int&             id,
  const double&          line_width,
  const double&          color_r,
  const double&          color_g,
  const double&          color_b,
  const double&          color_a
){

  /* declaration */
  visualization_msgs::msg::Marker mk;

  /* check */
  if (!(face.rows() >= 3)) { return mk; } // NOTE: return empty message
  if (!(face.cols() == 3)) { return mk; } // NOTE: return empty message

  /* packing */
  // FIX: [LATER] header.stamp?
  mk.header.frame_id    = frame_id;
  mk.id                 = id;
  mk.type               = visualization_msgs::msg::Marker::LINE_STRIP;
  mk.action             = visualization_msgs::msg::Marker::ADD;
  mk.pose.position.x    = 0;
  mk.pose.position.y    = 0;
  mk.pose.position.z    = 0;  
  mk.pose.orientation.w = 1;
  mk.pose.orientation.x = 0;
  mk.pose.orientation.y = 0;
  mk.pose.orientation.z = 0;
  mk.scale.x            = line_width;
  mk.color.r            = color_r;
  mk.color.g            = color_g;
  mk.color.b            = color_b;
  mk.color.a            = color_a;

  /* points */
  geometry_msgs::msg::Point pt;  
  for (int i = 0; i < face.rows(); i++){
    pt.x = face(i, 0);
    pt.y = face(i, 1);
    pt.z = face(i, 2);
    mk.points.push_back(pt);
  }
  mk.points.push_back(mk.points[0]); // NOTE: make 'line strip' to be closed

  /* return */
  return mk;

}


} // END OF NAMESPACE
