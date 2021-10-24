#include <iostream>
#include <array>
#include <random>

// #include <Eigen/Dense>
// #ifndef EIGEN_DONT_VECTORIZE
//    #define EIGEN_DONT_VECTORIZE
//  #endif
// // #define EIGEN_DONT_VECTORIZE
//
// // #pragma message(STRING(EIGEN_VECTORIZE))
// // #warning STRIEIGEN_VECTORIZENG(EIGEN_VECTORIZE)
// // #EIGEN_VECTORIZE
//
// #ifdef EIGEN_VECTORIZE
//
// int main(){
//   std::cout << "asjdhgousdhsoa\n";
// }
//
// #else


const int MAX_VAL = 3;



void testEigen(const size_t N) {
  using namespace Eigen;
  MatrixXd A = MatrixXd::Random(N,N), B = MatrixXd::Random(N,N);
  MatrixXd C = A*B;
}

int main(int argc, char** argv) {
  testEigen(atoi(argv[1]));
  // std::cout << A<< "\n\n"<< B<< "\n\n"<< C << "\n";
  /*mult(A,B,C);
  std::cout << "A:\n" << A.to_string() << "\n"
            << "B:\n" << B.to_string() << "\n"
            << "A*B:\n" << C.to_string() << "\n";
            */
  return 0;
}
