#include "voro_swarm/voro_cell.hpp"


namespace voro_swarm{


visualization_msgs::msg::MarkerArray VoroCell::get_msg_marker_array(
  const std::string& frame_id,
  const std::string& ns,
  const double&      point_size,
  const double&      line_width,
  const double&      color_r,
  const double&      color_g,
  const double&      color_b,
  const double&      color_a,
  const bool&        reset
){

  /* declaration */
  int id = 0;
  visualization_msgs::msg::MarkerArray msg;

  /* check */
  if (!initialized_) { return msg; } // NOTE: return empty message

  /* reset */
  if (reset) { msg.markers.push_back(get_msg_marker_for_reset()); }

  /* voronoi cell: point */
  msg.markers.push_back(get_msg_marker_from_point(point_, frame_id, ns, id++, point_size, color_r, color_g, color_b, color_a));

  /* voronoi cell: faces */
  for (int i = 0; i < num_face_; i++){
    msg.markers.push_back(get_msg_marker_from_face(set_face_[i], frame_id, ns, id++, line_width, color_r, color_g, color_b, color_a));
  }





  // FIX: temporal code, clean up
  for (int i = 0; i < num_neighbor_; i++){
    msg.markers.push_back(get_msg_marker_from_point(set_neighbor_[i], frame_id, ns, id++, point_size, color_r, color_g, color_b, color_a));
  }





  /* return */
  return msg;

}


visualization_msgs::msg::Marker VoroCell::get_msg_marker_from_point(
  const Eigen::Vector3d& point,
  const std::string&     frame_id,
  const std::string&     ns,
  const int&             id,
  const double&          point_size,
  const double&          color_r,
  const double&          color_g,
  const double&          color_b,
  const double&          color_a
){

  /* declaration */
  visualization_msgs::msg::Marker mk;

  /* packing */
  // TODO: header.stamp using std::chrono
  mk.header.frame_id    = frame_id;
  mk.ns                 = ns;
  mk.id                 = id;
  mk.type               = visualization_msgs::msg::Marker::SPHERE;
  mk.action             = visualization_msgs::msg::Marker::ADD;
  mk.pose.position.x    = point(0);
  mk.pose.position.y    = point(1);
  mk.pose.position.z    = point(2);
  mk.pose.orientation.w = 1;
  mk.pose.orientation.x = 0;
  mk.pose.orientation.y = 0;
  mk.pose.orientation.z = 0;
  mk.scale.x            = point_size;
  mk.scale.y            = point_size;
  mk.scale.z            = point_size;
  mk.color.r            = color_r;
  mk.color.g            = color_g;
  mk.color.b            = color_b;
  mk.color.a            = color_a;

  /* return */
  return mk;

}


visualization_msgs::msg::Marker VoroCell::get_msg_marker_from_face(
  const Eigen::MatrixXd& face,
  const std::string&     frame_id,
  const std::string&     ns,
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
  // TODO: header.stamp using std::chrono
  mk.header.frame_id    = frame_id;
  mk.ns                 = ns;
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

  /* packing: points */
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


visualization_msgs::msg::Marker VoroCell::get_msg_marker_for_reset(void){
  visualization_msgs::msg::Marker mk;
  mk.id     = std::numeric_limits<int32_t>::max();
  mk.action = visualization_msgs::msg::Marker::DELETEALL;
  return mk;
}


} // END OF NAMESPACE
