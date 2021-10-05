#include <iostream>
#include <array>
#include <random>

#include <Eigen/Dense>

#define EIGEN_DONT_VECTORIZE

const int MAX_VAL = 3;


int main(int argc, char** argv) {
  using namespace Eigen;
  const size_t N = atoi(argv[1]);
  MatrixXd A = MatrixXd::Random(N,N), B = MatrixXd::Random(N,N);
  MatrixXd C = A*B;
  // std::cout << A<< "\n\n"<< B<< "\n\n"<< C << "\n";
  /*mult(A,B,C);
  std::cout << "A:\n" << A.to_string() << "\n"
            << "B:\n" << B.to_string() << "\n"
            << "A*B:\n" << C.to_string() << "\n";
            */
  return 0;
}
