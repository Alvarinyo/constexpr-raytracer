#ifndef CONSTEXPR_RAYTRACER_CANVAS_HPP
#define CONSTEXPR_RAYTRACER_CANVAS_HPP

#include <cassert>
#include <concepts>
#include <vector>

#include "Color.hpp"

// TODO: make a constexpr vector implementation to substitute std::vector

class Canvas {
 public:
  using ColorRow = std::vector<Color>;
  using ColorMatrix = std::vector<ColorRow>;

  Canvas(size_t width, size_t height) noexcept
      : pixels_(height, ColorRow(width, Color(0.f, 0.f, 0.f))) {}

  [[nodiscard]] ColorMatrix pixels() const noexcept { return pixels_; }

  [[nodiscard]] size_t width() const noexcept {
    if (pixels_.empty()) return 0;
    return pixels_[0].size();
  }

  [[nodiscard]] size_t height() const noexcept { return pixels_.size(); }

  [[nodiscard]] bool empty() const noexcept { return pixels_.empty(); }

  void write_pixel(std::unsigned_integral auto x, std::unsigned_integral auto y,
                   const Color& color) noexcept {
    assert(y < height() && x < width());
    pixels_[y][x] = color;
  }

  [[nodiscard]] Color pixel_at(size_t x, size_t y) const noexcept {
    return pixels_[y][x];
  }

 private:
  ColorMatrix pixels_{};
};

#endif
