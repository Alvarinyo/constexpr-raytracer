
#ifndef CONSTEXPR_RAYTRACER_TUPLE_HPP
#define CONSTEXPR_RAYTRACER_TUPLE_HPP

#include <cassert>
#include <cmath>

#include "Math.hpp"

struct Tuple {
  constexpr Tuple(float x_, float y_, float z_, float w_) noexcept
      : x{x_}, y{y_}, z{z_}, w{w_} {}

  [[nodiscard]] constexpr bool is_point() const noexcept {
    return aprox_equal(w, 1.0f, 0.00001f);
  }

  [[nodiscard]] constexpr bool is_vector() const noexcept {
    return aprox_equal(w, 0.0f, 0.00001f);
  }

  [[nodiscard]] constexpr float magnitude() const noexcept {
    return std::sqrt(x * x + y * y + z * z + w * w);
  }

  constexpr Tuple normalized() const noexcept {
    const auto m = magnitude();
    return Tuple(x / m, y / m, z / m, w / m);
  }

  [[nodiscard]] friend constexpr bool operator==(const Tuple& lhs,
                                                 const Tuple& rhs) noexcept {
    return aprox_equal(lhs.x, rhs.x, 0.00001f) &&
           aprox_equal(lhs.y, rhs.y, 0.00001f) &&
           aprox_equal(lhs.z, rhs.z, 0.00001f) &&
           aprox_equal(lhs.w, rhs.w, 0.00001f);
  }

  constexpr Tuple& operator+=(const Tuple& rhs) noexcept {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;
    return *this;
  }

  constexpr Tuple& operator-=(const Tuple& rhs) noexcept {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;
    return *this;
  }

  constexpr Tuple& operator-() noexcept {
    x = -x;
    y = -y;
    z = -z;
    w = -w;
    return *this;
  }

  constexpr Tuple& operator*=(float rhs) noexcept {
    x *= rhs;
    y *= rhs;
    z *= rhs;
    w *= rhs;
    return *this;
  }

  constexpr Tuple& operator/=(float rhs) noexcept {
    x /= rhs;
    y /= rhs;
    z /= rhs;
    w /= rhs;
    return *this;
  }

  float x;
  float y;
  float z;
  float w;
};

[[nodiscard]] constexpr Tuple point(float x, float y, float z) noexcept {
  return Tuple(x, y, z, 1.0f);
}

[[nodiscard]] constexpr Tuple vector(float x, float y, float z) noexcept {
  return Tuple(x, y, z, 0.0f);
}

[[nodiscard]] constexpr Tuple operator+(Tuple lhs, const Tuple& rhs) noexcept {
  lhs += rhs;
  return lhs;
}

[[nodiscard]] constexpr Tuple operator-(Tuple lhs, const Tuple& rhs) noexcept {
  lhs -= rhs;
  return lhs;
}

[[nodiscard]] constexpr Tuple operator*(Tuple lhs, float rhs) noexcept {
  lhs *= rhs;
  return lhs;
}

[[nodiscard]] constexpr Tuple operator/(Tuple lhs, float rhs) noexcept {
  lhs /= rhs;
  return lhs;
}

[[nodiscard]] constexpr float dot(const Tuple& a, const Tuple& b) noexcept {
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

[[nodiscard]] constexpr Tuple cross(const Tuple& a, const Tuple& b) noexcept {
  assert(a.is_vector());
  assert(b.is_vector());
  return vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x);
}

#endif