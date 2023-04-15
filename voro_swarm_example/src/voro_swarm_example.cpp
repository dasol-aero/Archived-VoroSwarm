#include <ctime>
#include <chrono>
#include <iostream>

#include <Eigen/Eigen>
#include <voro++/voro++.hh>


constexpr int n = 1024; // NOTE: number of points


int main(void){

  /* random seed */
  std::srand(std::time(NULL)); // random seed using epoch time


  /* voro++ container */
  constexpr double x = 1.1;
  voro::container con(-x, x, -x, x, -x, x,
                      1, 1, 1,
                      false, false, false,
                      8);


  /* put points */
  Eigen::Vector3d r;
  for (int i = 0; i < n; i++){
    r = Eigen::Vector3d::Random();
    con.put(i, r(0), r(1), r(2));
    std::printf("put(%4d, %7.4f, %7.4f, %7.4f)\n", i + 1, r(0), r(1), r(2));
  }


  /* elapsed time : compute all cells */
  auto ts = std::chrono::high_resolution_clock::now();
  con.compute_all_cells();
  auto te = std::chrono::high_resolution_clock::now();
  double elapsed_ms = (double)(std::chrono::duration_cast<std::chrono::nanoseconds>(te - ts).count()) / 1e6;
  std::printf("elapsed time [ms]: %12.6f to compute all cells\n", elapsed_ms);


  /* elapsed time : compute a cell */
  ts = std::chrono::high_resolution_clock::now();
  voro::voronoicell_neighbor cell;
  con.compute_cell(cell, 0, n - 1); // compute the cell of the last point
  te = std::chrono::high_resolution_clock::now();
  elapsed_ms = (double)(std::chrono::duration_cast<std::chrono::nanoseconds>(te - ts).count()) / 1e6;
  std::printf("elapsed time [ms]: %12.6f to compute the single cell\n", elapsed_ms);


  /* accuracy : volume difference */
  double volume_container = std::pow(2 * x, 3);
  double volume_cells     = con.sum_cell_volumes();
  double volume_diff      = volume_container - volume_cells;
  std::printf("volume container : %20.16f\n"
              "volume cells     : %20.16f\n"
              "volume difference: %20.16f\n", volume_container, volume_cells, volume_diff);

  /* return */
  return 0;

}
