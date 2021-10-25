#include <iostream>
#include <iomanip>
#include <array>
#include <random>
#include <sys/time.h>

#include <Eigen/Dense>


const int MAX_VAL = 3;


void testEigen(const size_t N) {
  using namespace Eigen; using namespace std;
  struct timeval tval_ini, tval_end; // timestamps
  float t_init, t_mult; // seconds for ini and mult
  // Get timestamps:
  gettimeofday(&tval_ini, NULL);
  MatrixXd A = MatrixXd::Random(N,N), B = MatrixXd::Random(N,N), C;
  gettimeofday(&tval_end, NULL);
  // initialization time in sec:
  t_init = tval_end.tv_usec - tval_ini.tv_usec;

  // Same for the multiplication:
  gettimeofday(&tval_ini, NULL);
  C = A*B;
  gettimeofday(&tval_end, NULL);
  t_mult = tval_end.tv_usec - tval_ini.tv_usec;

  // cout << "Seconds: " << timestamp.tv_sec << endl
  //     << "Microseconds: " << timestamp.tv_usec << endl;
  std::cout << fixed << setprecision(5) << t_init*1e-6 << " "
            << fixed << setprecision(5) << t_mult*1e-6 << " ";
}


int main(int argc, char** argv) {
  testEigen(atoi(argv[1]));
  return 0;
}
