#ifndef CONSTEXPR_RAYTRACER_MATH_HPP
#define CONSTEXPR_RAYTRACER_MATH_HPP

#include <algorithm>
#include <cassert>
#include <cmath>
#include <concepts>

constexpr bool aprox_equal(float a, float b,
                           float epsilon = 0.00001f) noexcept {
  return std::abs(a - b) < epsilon;
}

constexpr unsigned long ulround(std::floating_point auto arg) {
  assert(arg >= 0);
  return static_cast<unsigned long>(lround(arg));
}

#endif