#include "voro_swarm/cal_voro_cell.hpp"


namespace voro_swarm{


bool CalVoroCell::set_input_and_make_container(const std::vector<Eigen::Vector3d>& input_points,
                                               const int&                          input_target_point_ind,
                                               const double&                       input_container_margin){

  /* check */
  if (!(input_points.size() > 0)){
    initialized_ = false;
    return initialized_;
  }
  if (!(input_target_point_ind >= 0)){
    initialized_ = false;
    return initialized_;    
  }
  if (!(input_target_point_ind < (int)input_points.size())){
    initialized_ = false;
    return initialized_;
  }
  if (!(input_container_margin > 0)){
    initialized_ = false;
    return initialized_;
  }

  /* copy */
  input_points_           = input_points;
  input_target_point_ind_ = input_target_point_ind;
  input_container_margin_ = input_container_margin;

  /* voronoi cells container */
  num_points_ = input_points_.size();
  for (int i = 0; i < num_points_; i++){    
    if (i == 0){
      points_xmin_ = input_points_[i](0);
      points_xmax_ = input_points_[i](0);
      points_ymin_ = input_points_[i](1);
      points_ymax_ = input_points_[i](1);
      points_zmin_ = input_points_[i](2);
      points_zmax_ = input_points_[i](2);
    } else {
      points_xmin_ = std::min(points_xmin_, input_points_[i](0));
      points_xmax_ = std::max(points_xmax_, input_points_[i](0));
      points_ymin_ = std::min(points_ymin_, input_points_[i](1));
      points_ymax_ = std::max(points_ymax_, input_points_[i](1));
      points_zmin_ = std::min(points_zmin_, input_points_[i](2));
      points_zmax_ = std::max(points_zmax_, input_points_[i](2));
    }
  }
  container_ = std::make_shared<voro::container>(
    points_xmin_ - input_container_margin_,
    points_xmax_ + input_container_margin_,
    points_ymin_ - input_container_margin_,
    points_ymax_ + input_container_margin_,
    points_zmin_ - input_container_margin_,
    points_zmax_ + input_container_margin_,
    1, 1, 1,
    false, false, false,
    num_points_
  );
  std::printf("[INFO] num_points: %d\n", num_points_);
  std::printf("[INFO] points_xmin, max: %.4f, %.4f\n", points_xmin_, points_xmax_);
  std::printf("[INFO] points_ymin, max: %.4f, %.4f\n", points_ymin_, points_ymax_);
  std::printf("[INFO] points_zmin, max: %.4f, %.4f\n", points_zmin_, points_zmax_);
  std::cout <<"[INFO] voro::container created at " << container_ << std::endl;

  /* return */
  return initialized_;

}


std::vector<Eigen::Vector3d> CalVoroCell::get_random_input_points(const int& num_points){
  std::srand(std::time(0)); // NOTE: random seed for 'Eigen::Vector3d::Random()'
  std::vector<Eigen::Vector3d> x;
  for (int i = 0; i < num_points; i++){ x.push_back(Eigen::Vector3d::Random()); }
  return x;
}


} // END OF NAMESPACE
