#include "voro_swarm/cal_voro_cell.hpp"


int main(void){

  // FIX: test code
  int n = 5;
  auto input_points = voro_swarm::CalVoroCell::get_random_input_points(n);

  voro_swarm::CalVoroCell cal_voro_cell;
  voro_swarm::VoroCell voro_cell;
  cal_voro_cell.set_input_and_make_container(input_points, 0.1);
  cal_voro_cell.get_voro_cell(0, voro_cell);





  /* return */
  return 0;

}
