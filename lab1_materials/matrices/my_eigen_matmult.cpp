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
  // std::cout << A<< "\n\n"<< B<< "\n\n"<< C << "\n";
  //mult(A,B,C);
  // std::cout << "A:\n" << A << "\n"
  //           << "B:\n" << B << "\n"
  //           << "A*B:\n" << C << "\n";

  return 0;
}
