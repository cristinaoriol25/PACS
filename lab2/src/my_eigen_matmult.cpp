#include <iostream>
#include <iomanip>
#include <array>
#include <random>

#include <Eigen/Dense>


const int MAX_VAL = 3;


void testEigen(const size_t N) {
  using namespace Eigen; using namespace std;
  clock_t t_ini = clock(), t_mult;
  MatrixXd A = MatrixXd::Random(N,N), B = MatrixXd::Random(N,N);
  t_ini = clock() - t_ini;
  t_mult = clock();
  MatrixXd C = A*B;
  t_mult = clock()- t_mult;
  std::cout << fixed << setprecision(5) << ((float)t_ini)/CLOCKS_PER_SEC << "\t"
            << fixed << setprecision(5) << ((float)t_mult)/CLOCKS_PER_SEC << "\n";
}


int main(int argc, char** argv) {
  testEigen(atoi(argv[1]));
  return 0;
}
