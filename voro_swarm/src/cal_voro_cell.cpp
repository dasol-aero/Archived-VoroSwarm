#include "voro_swarm/cal_voro_cell.hpp"


namespace voro_swarm{


bool CalVoroCell::set_input_and_make_container(const std::vector<Eigen::Vector3d>& input_points,
                                               const double&                       input_container_margin){

  /* check */
  if (!(input_points.size() > 0)){
    initialized_ = false;
    return initialized_;
  }
  if (!(input_container_margin > 0)){
    initialized_ = false;
    return initialized_;
  }

  /* copy */
  input_points_           = input_points;
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
  container_xmin_ = points_xmin_ - input_container_margin_;
  container_xmax_ = points_xmax_ + input_container_margin_;
  container_ymin_ = points_ymin_ - input_container_margin_;
  container_ymax_ = points_ymax_ + input_container_margin_;
  container_zmin_ = points_zmin_ - input_container_margin_;
  container_zmax_ = points_zmax_ + input_container_margin_;  
  container_ = std::make_shared<voro::container>(
    container_xmin_,
    container_xmax_,
    container_ymin_,
    container_ymax_,
    container_zmin_,
    container_zmax_,
    1, 1, 1,
    false, false, false,
    num_points_
  );

  /* put points */
  for (int i = 0; i < num_points_; i++){
    container_->put(i, input_points_[i](0), input_points_[i](1), input_points_[i](2));
  }

  /* print */
  std::printf("[INFO] num_points: %d\n", num_points_);
  std::printf("[INFO] points_xmin, max: %.4f, %.4f\n", points_xmin_, points_xmax_);
  std::printf("[INFO] points_ymin, max: %.4f, %.4f\n", points_ymin_, points_ymax_);
  std::printf("[INFO] points_zmin, max: %.4f, %.4f\n", points_zmin_, points_zmax_);
  std::printf("[INFO] container_xmin, max: %.4f, %.4f\n", container_xmin_, container_xmax_);
  std::printf("[INFO] container_ymin, max: %.4f, %.4f\n", container_ymin_, container_ymax_);
  std::printf("[INFO] container_zmin, max: %.4f, %.4f\n", container_zmin_, container_zmax_);
  std::cout <<"[INFO] voro::container created at " << container_ << std::endl;

  /* return */
  initialized_ = true;
  return initialized_;

}


bool CalVoroCell::get_voro_cell(const int& point_ind, VoroCell& voro_cell){

  /* check */
  if (!initialized_)              { return false; }
  if (!(point_ind >= 0))          { return false; }
  if (!(point_ind < num_points_)) { return false; }

  /* compute cell */
  voro::voronoicell_neighbor vcn;
  container_->compute_cell(vcn, 0, point_ind);





  // FIX: vertex
  std::vector<double> x;
  vcn.vertices(input_points_[point_ind](0), input_points_[point_ind](1), input_points_[point_ind](2), x);  
  std::cout << "vertices" << std::endl;
  for (int i = 0; i < (int)x.size(); i+= 3){
    std::printf("%.4f  %.4f  %.4f\n", x[i], x[i + 1], x[i + 2]);
  }
  




  // FIX: face
  std::cout << "---" << std::endl;
  std::cout << "# of vertices for each face" << std::endl;
  std::vector<int> f1;
  vcn.face_orders(f1);
  for (int a : f1) { std::cout << a << std::endl; }
  

  std::cout << "---" << std::endl;
  std::cout << "vertex indices for each face" << std::endl;
  std::vector<int> f2;
  vcn.face_vertices(f2);
  for (int a : f2){
    std::cout << a << std::endl;
  }

  


  /* return */
  return true;

}


std::vector<Eigen::Vector3d> CalVoroCell::get_random_input_points(const int& num_points){
  std::srand(std::time(0)); // NOTE: random seed for 'Eigen::Vector3d::Random()'
  std::vector<Eigen::Vector3d> x;
  for (int i = 0; i < num_points; i++){ x.push_back(Eigen::Vector3d::Random()); }
  return x;
}


} // END OF NAMESPACE
