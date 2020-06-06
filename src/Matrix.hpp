#include <algorithm>
#include <array>
#include <functional>

#include "Math.hpp"
#include "Tuple.hpp"

template <int Rows, int Cols = Rows>
class Matrix {
 public:
  using Storage = std::array<float, static_cast<size_t>(Cols* Rows)>;

  using value_type = Storage::value_type;
  using const_reference = Storage::const_reference;
  using difference_type = Storage::difference_type;
  using reference = Storage::reference;
  using size_type = Storage::size_type;
  using iterator = Storage::iterator;
  using const_iterator = Storage::const_iterator;

  [[nodiscard]] constexpr Matrix() noexcept = default;

  [[nodiscard]] constexpr Matrix(Storage data) noexcept
      : storage_(std::move(data)) {}

  [[nodiscard]] constexpr Matrix(const Matrix& other) noexcept
      : storage_(other.storage_) {}

  [[nodiscard]] constexpr Matrix(Matrix&& other) noexcept
      : storage_(std::move(other.storage_)) {}

  template <strict_float... Args>
  [[nodiscard]] constexpr Matrix(Args... args)
      : storage_{std::forward<Args>(args)...} {}

  [[nodiscard]] constexpr reference at(int row, int col) noexcept {
    assert(row >= 0 && col >= 0 && row < Rows && col < Cols);
    return storage_[static_cast<size_t>(row * Cols + col)];
  }

  [[nodiscard]] constexpr const_reference at(int row, int col) const noexcept {
    assert(row >= 0 && col >= 0 && row < Rows && col < Cols);
    return storage_[static_cast<size_t>(row * Cols + col)];
  }

  [[nodiscard]] constexpr iterator begin() noexcept { return storage_.begin(); }

  [[nodiscard]] constexpr const_iterator begin() const noexcept {
    return storage_.begin();
  }

  [[nodiscard]] constexpr const_iterator cbegin() const noexcept {
    return storage_.cbegin();
  }

  [[nodiscard]] constexpr iterator end() noexcept { return storage_.end(); }

  [[nodiscard]] constexpr const_iterator end() const noexcept {
    return storage_.end();
  }

  [[nodiscard]] constexpr const_iterator cend() const noexcept {
    return storage_.cend();
  }

 protected:
  Storage storage_;
};

/*
  Matrix operators
*/

template <int Rows, int Cols>
[[nodiscard]] constexpr bool operator==(
    const Matrix<Rows, Cols>& lhs, const Matrix<Rows, Cols>& rhs) noexcept {
  return std::equal(lhs.begin(), lhs.end(), rhs.begin(),
                    [](float a, float b) { return aprox_equal(a, b); });
}

template <int A, int B, int C>
[[nodiscard]] constexpr Matrix<A, C> operator*(
    const Matrix<A, B>& lhs, const Matrix<B, C>& rhs) noexcept {
  Matrix<A, C> result{};

  for (int i = 0; i < A; ++i) {
    for (int k = 0; k < B; ++k) {
      for (int j = 0; j < C; ++j) {
        result.at(i, j) += lhs.at(i, k) * rhs.at(k, j);
      }
    }
  }

  return result;
}

[[nodiscard]] constexpr Tuple operator*(const Matrix<4>& lhs,
                                        const Tuple& rhs) noexcept {
  return Tuple(lhs.at(0, 0) * rhs.x + lhs.at(0, 1) * rhs.y +
                   lhs.at(0, 2) * rhs.z + lhs.at(0, 3) * rhs.w,
               lhs.at(1, 0) * rhs.x + lhs.at(1, 1) * rhs.y +
                   lhs.at(1, 2) * rhs.z + lhs.at(1, 3) * rhs.w,
               lhs.at(2, 0) * rhs.x + lhs.at(2, 1) * rhs.y +
                   lhs.at(2, 2) * rhs.z + lhs.at(2, 3) * rhs.w,
               lhs.at(3, 0) * rhs.x + lhs.at(3, 1) * rhs.y +
                   lhs.at(3, 2) * rhs.z + lhs.at(3, 3) * rhs.w);
}

/*
  Matrix non-member functions
*/

namespace MatrixUtils {

/*
  Forward declarations
*/

template <int Rows, int Cols>
[[nodiscard]] constexpr float cofactor(const Matrix<Rows, Cols>& matrix,
                                       int row, int col) noexcept;

/*
  Definitions
*/

template <int Dim>
[[nodiscard]] constexpr Matrix<Dim> identity() noexcept {
  Matrix<Dim> identity_matrix = {};

  for (int i = 0; i < Dim; ++i) {
    identity_matrix.at(i, i) = 1;
  }

  return identity_matrix;
}

template <int Rows, int Cols>
[[nodiscard]] constexpr Matrix<Cols, Rows> transpose(
    const Matrix<Rows, Cols>& matrix) noexcept {
  Matrix<Cols, Rows> transposed_matrix;

  for (int i = 0; i < Rows; ++i) {
    for (int j = 0; j < Cols; ++j) {
      transposed_matrix.at(j, i) = matrix.at(i, j);
    }
  }

  return transposed_matrix;
}

[[nodiscard]] constexpr float determinant(const Matrix<2>& matrix) noexcept {
  return matrix.at(0, 0) * matrix.at(1, 1) - matrix.at(0, 1) * matrix.at(1, 0);
}

template <int Rows, int Cols>
[[nodiscard]] constexpr float determinant(
    const Matrix<Rows, Cols>& matrix) noexcept {
  float result = 0.f;
  for (int i = 0; i < Rows; ++i) {
    result += matrix.at(0, i) * cofactor(matrix, 0, i);
  }
  return result;
}

template <int Rows, int Cols>
requires(Rows > 1 && Cols > 1)
    [[nodiscard]] constexpr Matrix<Rows - 1, Cols - 1> submatrix(
        const Matrix<Rows, Cols>& matrix, int row, int col) noexcept {
  Matrix<Rows - 1, Cols - 1> submatrix;

  for (int i = 0, dest_i = 0; i < Rows; ++i) {
    if (i == row) continue;

    for (int j = 0, dest_j = 0; j < Cols; ++j) {
      if (j == col) continue;

      submatrix.at(dest_i, dest_j) = matrix.at(i, j);
      ++dest_j;
    }

    ++dest_i;
  }

  return submatrix;
}

template <int Rows, int Cols>
[[nodiscard]] constexpr float minor(const Matrix<Rows, Cols>& matrix, int row,
                                    int col) noexcept {
  return determinant(submatrix(matrix, row, col));
}

template <int Rows, int Cols>
[[nodiscard]] constexpr float cofactor(const Matrix<Rows, Cols>& matrix,
                                       int row, int col) noexcept {
  return (row + col) % 2 == 0 ? minor(matrix, row, col)
                              : -minor(matrix, row, col);
}

template <int Rows, int Cols>
[[nodiscard]] constexpr bool is_invertible(
    const Matrix<Rows, Cols>& matrix) noexcept {
  return determinant(matrix) != 0;
}

template <int Rows, int Cols>
[[nodiscard]] constexpr Matrix<Rows, Cols> inverse(
    const Matrix<Rows, Cols>& matrix) noexcept {
  assert(is_invertible(matrix));

  Matrix<Rows, Cols> result;

  for (int i = 0; i < Rows; ++i) {
    for (int j = 0; j < Cols; ++j) {
      // We set the matrix at (column, row) to accomplish the transpose
      // operation:
      result.at(j, i) = cofactor(matrix, i, j) / determinant(matrix);
    }
  }

  return result;
}
}  // namespace MatrixUtils