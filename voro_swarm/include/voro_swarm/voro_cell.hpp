#ifndef _VORO_SWARM_VORO_CELL_HPP_
#define _VORO_SWARM_VORO_CELL_HPP_


#include <cstdint>
#include <limits>
#include <vector>
#include <iostream>

#include <Eigen/Eigen>

#include "geometry_msgs/msg/point.hpp"
#include "visualization_msgs/msg/marker.hpp"
#include "visualization_msgs/msg/marker_array.hpp"


namespace voro_swarm{


class VoroCell{

public:

  /* API */
  visualization_msgs::msg::MarkerArray get_msg_marker_array(
    const std::string& frame_id,
    const std::string& ns,
    const double&      point_size,
    const double&      line_width,
    const double&      color_r,
    const double&      color_g,
    const double&      color_b,
    const double&      color_a,
    const bool&        reset // NOTE: if true, it deletes all markers before the update
  );

  /* API: Helper */
  static visualization_msgs::msg::Marker get_msg_marker_from_point(
    const Eigen::Vector3d& point,
    const std::string&     frame_id,
    const std::string&     ns,
    const int&             id,
    const double&          point_size,
    const double&          color_r,
    const double&          color_g,
    const double&          color_b,
    const double&          color_a
  );
  static visualization_msgs::msg::Marker get_msg_marker_from_face(
    const Eigen::MatrixXd& face,
    const std::string&     frame_id,
    const std::string&     ns,
    const int&             id,
    const double&          line_width,
    const double&          color_r,
    const double&          color_g,
    const double&          color_b,
    const double&          color_a
  );
  static visualization_msgs::msg::Marker get_msg_marker_for_reset(void);

  /* ----------------------------------------- */

  /* boolean */
  bool initialized_ = false;

  /* data */
  Eigen::Vector3d              point_;
  int                          num_vertex_;
  std::vector<Eigen::Vector3d> set_vertex_;
  int                          num_face_;
  std::vector<Eigen::MatrixXd> set_face_;
  int                          num_neighbor_;
  std::vector<Eigen::Vector3d> set_neighbor_;

};


} // END OF NAMESPACE


#endif // END OF FILE
