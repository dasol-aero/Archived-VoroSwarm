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

  /* declaration */
  voro::voronoicell_neighbor vcn;

  /* compute cell */
  if(!container_->compute_cell(vcn, 0, point_ind)) { return false; }

  /* cell: point */
  voro_cell.point_ = input_points_[point_ind];

  /* cell: vertex */
  {

    /* vertices */
    std::vector<double> x;
    vcn.vertices(voro_cell.point_(0), voro_cell.point_(1), voro_cell.point_(2), x);

    /* parsing */
    voro_cell.num_vertex_ = x.size() / 3;
    voro_cell.set_vertex_.clear();
    voro_cell.set_vertex_.reserve(voro_cell.num_vertex_);
    for (int i = 0; i < voro_cell.num_vertex_ * 3; i += 3){
      voro_cell.set_vertex_.push_back(Eigen::Vector3d(x[i], x[i + 1], x[i + 2]));
    }

  }

  /* cell: face */
  {

    /* faces */
    std::vector<int> x;
    vcn.face_vertices(x);

    /* parsing: number of face */
    voro_cell.num_face_ = vcn.number_of_faces();

    /* parsing: set of face - clear and reserve */
    voro_cell.set_face_.clear();
    voro_cell.set_face_.reserve(voro_cell.num_face_);

    /* parsing: set of face - push back */
    int base = 0;
    while (base < (int)x.size()){
      int num = x[base]; // NOTE: number of vertices for this face
      Eigen::MatrixXd face(num, 3); // NOTE: shape = N x 3
      for (int i = base + 1; i < base + 1 + num; i++){
        face.row(i - base - 1) = voro_cell.set_vertex_[x[i]].transpose(); // NOTE: column to row vector
      }
      voro_cell.set_face_.push_back(face);
      base += 1 + num;
    }

  }





  // HERE: neighbor
  // for test purpose, it is iterated for all voronoi cells, later only summarize info for the specific cell.
  // add num_neighbors
  // std::cout << "----------" << std::endl;
  // for (int i = 0; i < num_points_; i++){
  //   container_->compute_cell(vcn, 0, i);
  //   std::vector<int> neighbors;
  //   vcn.neighbors(neighbors);
  //   std::printf("point ind: %d, neighboring point indices: ", i);
  //   for (int ni : neighbors){
  //     if (ni >= 0) { std::cout << ni << " "; }
  //   }
  //   std::cout << std::endl;
  // }





  /* return */
  voro_cell.initialized_ = true;
  return voro_cell.initialized_;

}


std::vector<Eigen::Vector3d> CalVoroCell::get_random_input_points(const int& num_points){
  std::srand(std::time(0)); // NOTE: random seed for 'Eigen::Vector3d::Random()'
  std::vector<Eigen::Vector3d> x;
  for (int i = 0; i < num_points; i++){ x.push_back(Eigen::Vector3d::Random()); }
  return x;
}


} // END OF NAMESPACE
