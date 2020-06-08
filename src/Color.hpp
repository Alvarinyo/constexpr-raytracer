#ifndef CONSTEXPR_RAYTRACER_COLOR_HPP
#define CONSTEXPR_RAYTRACER_COLOR_HPP

#include "Math.hpp"

struct Color {
  constexpr Color(float red_, float green_, float blue_)
      : red(red_), green(green_), blue(blue_) {}

  constexpr Color() = default;

  [[nodiscard]] constexpr Color operator-() const noexcept {
    return Color(-red, -green, -blue);
  }

  constexpr Color& operator+=(const Color& rhs) noexcept {
    red += rhs.red;
    green += rhs.green;
    blue += rhs.blue;
    return *this;
  }

  constexpr Color& operator-=(const Color& rhs) noexcept {
    red -= rhs.red;
    green -= rhs.green;
    blue -= rhs.blue;
    return *this;
  }

  constexpr Color& operator*=(const Color& rhs) noexcept {
    red *= rhs.red;
    green *= rhs.green;
    blue *= rhs.blue;
    return *this;
  }

  constexpr Color& operator*=(float rhs) noexcept {
    red *= rhs;
    green *= rhs;
    blue *= rhs;
    return *this;
  }

  constexpr Color& operator/=(float rhs) noexcept {
    red /= rhs;
    green /= rhs;
    blue /= rhs;
    return *this;
  }

  [[nodiscard]] friend constexpr bool operator==(const Color& lhs,
                                                 const Color& rhs) noexcept {
    return approx_equal(lhs.red, rhs.red) &&
           approx_equal(lhs.green, rhs.green) &&
           approx_equal(lhs.blue, rhs.blue);
  }

  float red{0.f};
  float green{0.f};
  float blue{0.f};
};

[[nodiscard]] constexpr Color operator+(Color lhs, const Color& rhs) noexcept {
  lhs += rhs;
  return lhs;
}

[[nodiscard]] constexpr Color operator-(Color lhs, const Color& rhs) noexcept {
  lhs -= rhs;
  return lhs;
}

[[nodiscard]] constexpr Color operator*(Color lhs, const Color& rhs) noexcept {
  lhs *= rhs;
  return lhs;
}

[[nodiscard]] constexpr Color operator*(Color lhs, float rhs) noexcept {
  lhs *= rhs;
  return lhs;
}

[[nodiscard]] constexpr Color operator/(Color lhs, float rhs) noexcept {
  lhs /= rhs;
  return lhs;
}

#endif