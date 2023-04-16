#ifndef _VORO_SWARM_VORO_CELL_HPP_
#define _VORO_SWARM_VORO_CELL_HPP_


#include <vector>

#include <Eigen/Eigen>


namespace voro_swarm{


class VoroCell{

public:

  /* boolean */
  bool initialized_ = false;

  /* data */
  Eigen::Vector3d              point_;
  int                          num_vertex_;
  std::vector<Eigen::Vector3d> set_vertex_;
  int                          num_face_;
  std::vector<Eigen::MatrixXd> set_face_;

};


} // END OF NAMESPACE


#endif // END OF FILE
