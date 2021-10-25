#include <iostream>
#include <array>
#include <random>

#include <Eigen/Dense>


const int MAX_VAL = 3;


void testEigen(const size_t N) {
  using namespace Eigen;
  MatrixXd A = MatrixXd::Random(N,N), B = MatrixXd::Random(N,N);

  //asm("# vec?");
  MatrixXd C = A*B;
  //asm("# fin vec?");
}


int main(int argc, char** argv) {
  testEigen(atoi(argv[1]));
  return 0;
}
