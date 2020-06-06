#ifndef CONSTEXPR_RAYTRACER_MATRIX_TRANSFORMATIONS
#define CONSTEXPR_RAYTRACER_MATRIX_TRANSFORMATIONS

#include <iostream>

#include "Matrix.hpp"

namespace Transformations {

/*
  Forward declarations
*/
class Transformation;

[[nodiscard]] constexpr Transformation translation(float x, float y,
                                                   float z) noexcept;
[[nodiscard]] constexpr Transformation scaling(float x, float y,
                                               float z) noexcept;
[[nodiscard]] constexpr Transformation rotation_x(float radians) noexcept;
[[nodiscard]] constexpr Transformation rotation_y(float radians) noexcept;
[[nodiscard]] constexpr Transformation rotation_z(float radians) noexcept;
[[nodiscard]] constexpr Transformation shearing(float xy, float xz, float yx,
                                                float yz, float zx,
                                                float zy) noexcept;

/*
  Transformation:

  This class provides a fluent API to perform chained matrix transformations
*/

class Transformation : public Matrix<4> {
 public:
  [[nodiscard]] constexpr Transformation() noexcept : Matrix<4>{} {};

  [[nodiscard]] constexpr Transformation(Matrix<4>::Storage data) noexcept
      : Matrix<4>(std::move(data)) {}

  [[nodiscard]] constexpr Transformation(const Matrix<4>& other) noexcept
      : Matrix<4>(other) {}

  [[nodiscard]] constexpr Transformation(Matrix<4>&& other) noexcept
      : Matrix<4>(std::move(other)) {}

  template <strict_float... Args>
  [[nodiscard]] constexpr Transformation(Args... args)
      : Matrix<4>{std::forward<Args>(args)...} {}

  [[nodiscard]] constexpr Transformation translation(float x, float y,
                                                     float z) noexcept {
    return Transformations::translation(x, y, z) * (*this);
  }

  [[nodiscard]] constexpr Transformation scaling(float x, float y,
                                                 float z) noexcept {
    return Transformations::scaling(x, y, z) * (*this);
  }

  [[nodiscard]] constexpr Transformation rotation_x(float radians) noexcept {
    return Transformations::rotation_x(radians) * (*this);
  }

  [[nodiscard]] constexpr Transformation rotation_y(float radians) noexcept {
    return Transformations::rotation_y(radians) * (*this);
  }

  [[nodiscard]] constexpr Transformation rotation_z(float radians) noexcept {
    return Transformations::rotation_z(radians) * (*this);
  }

  [[nodiscard]] constexpr Transformation shearing(float xy, float xz, float yx,
                                                  float yz, float zx,
                                                  float zy) noexcept {
    return Transformations::shearing(xy, xz, yx, yz, zx, zy) * (*this);
  }
};

/*
  Transformation factory functions

  Transformations implementation
*/

[[nodiscard]] constexpr Transformation translation(float x, float y,
                                                   float z) noexcept {
  Matrix<4> result = MatrixUtils::identity<4>();
  result.at(0, 3) = x;
  result.at(1, 3) = y;
  result.at(2, 3) = z;
  return result;
}

[[nodiscard]] constexpr Transformation scaling(float x, float y,
                                               float z) noexcept {
  Matrix<4> result = {};
  result.at(0, 0) = x;
  result.at(1, 1) = y;
  result.at(2, 2) = z;
  result.at(3, 3) = 1;
  return result;
}

[[nodiscard]] constexpr Transformation rotation_x(float radians) noexcept {
  return Transformation{1.f,
                        0.f,
                        0.f,
                        0.f,
                        0.f,
                        std::cos(radians),
                        -std::sin(radians),
                        0.f,
                        0.f,
                        std::sin(radians),
                        std::cos(radians),
                        0.f,
                        0.f,
                        0.f,
                        0.f,
                        1.f};
}

[[nodiscard]] constexpr Transformation rotation_y(float radians) noexcept {
  return Transformation{
      std::cos(radians),  0.f, std::sin(radians), 0.f, 0.f, 1.f, 0.f, 0.f,
      -std::sin(radians), 0.f, std::cos(radians), 0.f, 0.f, 0.f, 0.f, 1.f};
}

[[nodiscard]] constexpr Transformation rotation_z(float radians) noexcept {
  return Transformation{std::cos(radians),
                        -std::sin(radians),
                        0.f,
                        0.f,
                        std::sin(radians),
                        std::cos(radians),
                        0.f,
                        0.f,
                        0.f,
                        0.f,
                        1.f,
                        0.f,
                        0.f,
                        0.f,
                        0.f,
                        1.f};
}

[[nodiscard]] constexpr Transformation shearing(float xy, float xz, float yx,
                                                float yz, float zx,
                                                float zy) noexcept {
  return Transformation{1.f, xy, xz,  0.f, yx,  1.f, yz,  0.f,
                        zx,  zy, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f};
}

}  // namespace Transformations

#endif