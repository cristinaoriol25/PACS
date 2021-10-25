#include <iostream>
#include <iomanip> // setprecision
#include <vector>
#include <random>
#include <sys/time.h>

using namespace std;


// Nota: https://man7.org/linux/man-pages/man2/gettimeofday.2.html
// POSIX.1-2008 marks gettimeofday() as obsolete,
//        recommending the use of clock_gettime(2) instead.


const double MAX_VAL = 3;


class Matrix {
private:
  std::vector<std::vector<double>> vals;
public:

  Matrix(const std::vector<std::vector<double>> _vals) : vals(_vals){}

  Matrix(const size_t N, const size_t M) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> dis(0, MAX_VAL); // distribution in range [1, 6]

    for (size_t i = 0; i<N; i++) {
      vals.emplace_back();
      auto& b = vals.back();
      for (size_t j = 0; j<M; j++) {
        b.emplace_back(dis(rng));
        // vals[i][j] = dis(rng);
      }
    }
  }

  Matrix() {
  }

  std::string to_string() const {
    std::string s = "";
    for (const auto& r : vals) {
      for (const auto& v : r) {
        s+=std::to_string(v) + "\t";
      }
      s+="\n";
    }
    return s;
  }

  size_t rows() const {
    return vals.size();
  }

  size_t cols() const {
    return vals.back().size();
  }

  std::vector<double>& operator[] (size_t i) {
    return vals[i];
  }

  const std::vector<double>& operator[] (size_t i) const {
    return vals[i];
  }

  void resize(size_t n) {
    vals.resize(n);
  }
};

void mult(const Matrix& A, const Matrix& B, Matrix& res) {
  size_t N = A.rows(), M = A.cols();
  res.resize(N);
  for (size_t i = 0; i<N; i++) {
    for (size_t j = 0; j<M; j++) {
      res[i].resize(M);
      res[i][j] = 0;
      for (size_t k = 0; k<N; k++) {
        res[i][j] += A[i][k]*B[k][j];
      }
    }
  }
}


double as_seconds(const struct timeval& tval) {
  return double(tval.tv_sec)+double(tval.tv_usec)*1e-6;
}

double elapsed_seconds(const struct timeval& tval_ini, const struct timeval& tval_end) {
  return as_seconds(tval_end) - as_seconds(tval_ini);
}

int main(int argc, char** argv) {
  using namespace std;
  const size_t N = atoi(argv[1]);

  struct timeval tval_ini, tval_end; // timestamps
  //float t_init, t_mult; // seconds for ini and mult
  // Get timestamps:
  gettimeofday(&tval_ini, NULL);
  Matrix A(N,N), B(N,N), C;
  gettimeofday(&tval_end, NULL);
  // initialization time in sec:
  auto t_init = elapsed_seconds(tval_ini, tval_end);//tval_end.tv_usec - tval_ini.tv_usec;

  // Same for the multiplication:
  gettimeofday(&tval_ini, NULL);
  mult(A,B,C);
  gettimeofday(&tval_end, NULL);
  auto t_mult = elapsed_seconds(tval_ini, tval_end);//tval_end.tv_usec - tval_ini.tv_usec;

  // cout << "Seconds: " << timestamp.tv_sec << endl
  //     << "Microseconds: " << timestamp.tv_usec << endl;
  std::cout << fixed << setprecision(5) << t_init << " "
            << fixed << setprecision(5) << t_mult << " ";
  return 0;
}
