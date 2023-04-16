#ifndef _VORO_SWARM_CAL_VORO_CELL_HPP_
#define _VORO_SWARM_CAL_VORO_CELL_HPP_


#include <ctime>
#include <cstdlib>
#include <vector>
#include <memory>
#include <iostream>

#include <Eigen/Eigen>
#include <voro++/voro++.hh>


namespace voro_swarm{


class CalVoroCell{

public:

  /* API */
  bool set_input_and_make_container(const std::vector<Eigen::Vector3d>& input_points,
                                    const int&                          input_target_point_ind,
                                    const double&                       input_container_margin);


  /* API: Helper */
  static std::vector<Eigen::Vector3d> get_random_input_points(const int& num_points);

private:

  /* input */
  bool initialized_ = false;
  std::vector<Eigen::Vector3d> input_points_;
  int                          input_target_point_ind_;
  double                       input_container_margin_;

  /* voronoi cells container */
  int    num_points_;
  double points_xmin_;
  double points_xmax_;
  double points_ymin_;
  double points_ymax_;
  double points_zmin_;
  double points_zmax_;
  std::shared_ptr<voro::container> container_;

};


} // END OF NAMESPACE


#endif // END OF FILE
