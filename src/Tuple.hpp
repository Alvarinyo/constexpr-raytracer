
#ifndef CONSTEXPR_RAYTRACER_TUPLE_HPP
#define CONSTEXPR_RAYTRACER_TUPLE_HPP

#include <cassert>
#include <cmath>

#include "Math.hpp"

struct Tuple {
  constexpr Tuple(float x_, float y_, float z_, float w_) noexcept
      : x{x_}, y{y_}, z{z_}, w{w_} {}

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

  [[nodiscard]] friend constexpr bool operator==(const Tuple& lhs,
                                                 const Tuple& rhs) noexcept {
    return approx_equal(lhs.x, rhs.x, 0.00001f) &&
           approx_equal(lhs.y, rhs.y, 0.00001f) &&
           approx_equal(lhs.z, rhs.z, 0.00001f) &&
           approx_equal(lhs.w, rhs.w, 0.00001f);
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

[[nodiscard]] constexpr bool is_point(const Tuple& tup) noexcept {
  return approx_equal(tup.w, 1.0f, 0.00001f);
}

[[nodiscard]] constexpr bool is_vector(const Tuple& tup) noexcept {
  return approx_equal(tup.w, 0.0f, 0.00001f);
}

[[nodiscard]] constexpr float magnitude(const Tuple& tup) noexcept {
  return std::sqrt(tup.x * tup.x + tup.y * tup.y + tup.z * tup.z +
                   tup.w * tup.w);
}

[[nodiscard]] constexpr Tuple normalize(Tuple tup) noexcept {
  const auto m = magnitude(tup);
  tup.x /= m;
  tup.y /= m;
  tup.z /= m;
  tup.w /= m;
  return tup;
}

[[nodiscard]] constexpr Tuple operator-(const Tuple& tup) noexcept {
  return Tuple(-tup.x, -tup.y, -tup.z, -tup.w);
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
  assert(is_vector(a));
  assert(is_vector(b));
  return vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x);
}

#endif