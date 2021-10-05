#include <iostream>
#include <array>
#include <random>

const double MAX_VAL = 3;

template <std::size_t N, std::size_t M>
class Matrix {
private:
  std::array<std::array<double, N>, M> vals;
public:

  Matrix<N,M>(const std::array<std::array<double, N>, M> _vals) : vals(_vals){}
  Matrix<N,M>() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> dis(0, MAX_VAL); // distribution in range [1, 6]

    for (size_t i = 0; i<N; i++) {
      for (size_t j = 0; j<M; j++) {
        vals[i][j] = dis(rng);
      }
    }
  }

  std::string to_string() const {
    std::string s = "";
    for (size_t i = 0; i<N; i++) {
      for (size_t j = 0; j<M; j++) {
        s+=std::to_string(vals[i][j]) + "\t";
      }
      s+="\n";
    }
    return s;
  }

  std::array<double, N>& operator[] (size_t i) {
    return vals[i];
  }

  const std::array<double, N>& operator[] (size_t i) const {
    return vals[i];
  }
};



template <std::size_t N, std::size_t M>
void mult(const Matrix<N,M>& A, const Matrix<M,N>& B, Matrix<N,N>& res) {
  for (size_t i = 0; i<N; i++) {
    for (size_t j = 0; j<M; j++) {
      res[i][j] = 0;
      for (size_t k = 0; k<N; k++) {
        res[i][j] += A[i][k]*B[k][j];
      }
    }
  }
}


int main() {
  const size_t N = 200;
  Matrix<N,N> A, B, C;
  mult(A,B,C);
  /*std::cout << "A:\n" << A.to_string() << "\n"
            << "B:\n" << B.to_string() << "\n"
            << "A*B:\n" << C.to_string() << "\n";*/

  return 0;
}s
