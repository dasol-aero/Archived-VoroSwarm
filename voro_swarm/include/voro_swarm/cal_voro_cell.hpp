#ifndef _VORO_SWARM_CAL_VORO_CELL_HPP_
#define _VORO_SWARM_CAL_VORO_CELL_HPP_


#include <ctime>
#include <cstdlib>
#include <vector>
#include <memory>
#include <iostream>

#include <Eigen/Eigen>
#include <voro++/voro++.hh>

#include "voro_swarm/voro_cell.hpp"


namespace voro_swarm{


class CalVoroCell{

public:

  /* API */
  bool set_input_and_make_container(const std::vector<Eigen::Vector3d>& input_points,
                                    const double&                       input_container_margin);
  bool get_voro_cell(const int& point_ind, VoroCell& voro_cell);

  /* API: Helper */
  static std::vector<Eigen::Vector3d> get_random_input_points(const int& num_points);

private:

  /* boolean */
  bool initialized_ = false;

  /* input */  
  std::vector<Eigen::Vector3d> input_points_;
  double                       input_container_margin_;

  /* container */
  int    num_points_;
  double points_xmin_;
  double points_xmax_;
  double points_ymin_;
  double points_ymax_;
  double points_zmin_;
  double points_zmax_;
  double container_xmin_;
  double container_xmax_;
  double container_ymin_;
  double container_ymax_;
  double container_zmin_;
  double container_zmax_;
  std::shared_ptr<voro::container> container_;

};


} // END OF NAMESPACE


#endif // END OF FILE
