#ifndef CONSTEXPR_RAYTRACER_MATH_HPP
#define CONSTEXPR_RAYTRACER_MATH_HPP

#include <cmath>
#include <concepts>
#include <limits>

namespace MathUtil {

template <class T>
concept strict_float = std::is_same_v<T, float>;

constexpr bool approx_equal(float a, float b,
                            float epsilon = 0.0001f) noexcept {
  return std::abs(a - b) < epsilon;
}

constexpr int iround(float f) noexcept {
  return static_cast<int>(std::lround(f));
}

namespace detail {

constexpr float sqrt_newton_raphson(float x, float curr, float prev) {
  return curr == prev ? curr
                      : sqrt_newton_raphson(x, 0.5f * (curr + x / curr), curr);
}

}  // namespace detail

constexpr float sqrt(float x, float seed = 0) {
  return x >= 0 && x < std::numeric_limits<float>::infinity()
             ? detail::sqrt_newton_raphson(x, x, seed)
             : std::numeric_limits<float>::quiet_NaN();
}

}  // namespace MathUtil

#endif