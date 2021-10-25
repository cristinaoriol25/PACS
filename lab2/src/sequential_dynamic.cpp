#include <iostream>
#include <iomanip> // setprecision
#include <vector>
#include <random>
#include <ctime>


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


int main(int argc, char** argv) {
  using namespace std;
  const size_t N = atoi(argv[1]);
  clock_t t_ini = clock(), t_mult;
  Matrix A(N,N), B(N,N), C;
  t_ini = clock() - t_ini;
  t_mult = clock();
  mult(A,B,C);
  t_mult = clock()- t_mult;
  std::cout << fixed << setprecision(5) << ((float)t_ini)/CLOCKS_PER_SEC << " "
            << fixed << setprecision(5) << ((float)t_mult)/CLOCKS_PER_SEC << " ";
  return 0;
}
