#include <iostream>
#include <iomanip>
#include <array>
#include <random>

#include <Eigen/Dense>


const int MAX_VAL = 3;


void testEigen(const size_t N) {
  using namespace Eigen; using namespace std;
  // initialization:
  clock_t t_ini = clock(), t_mult;
  MatrixXd A = MatrixXd::Random(N,N), B = MatrixXd::Random(N,N), C;
  t_ini = clock() - t_ini;
  // multiplication:
  t_mult = clock();
  C = A*B;
  t_mult = clock()- t_mult;
  // output:
  std::cout << fixed << setprecision(5) << ((float)t_ini)/CLOCKS_PER_SEC << " "
            << fixed << setprecision(5) << ((float)t_mult)/CLOCKS_PER_SEC << " ";
}


int main(int argc, char** argv) {
  testEigen(atoi(argv[1]));
  return 0;
}
