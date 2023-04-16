#include "voro_swarm/cal_voro_cell.hpp"


int main(void){

  int n = 100;
  auto input_points = voro_swarm::CalVoroCell::get_random_input_points(n);

  voro_swarm::CalVoroCell cal_voro_cell;
  cal_voro_cell.set_input_and_make_container(input_points, 0, 0.1);


  /* return */
  return 0;

}
