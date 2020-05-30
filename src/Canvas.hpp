#ifndef CONSTEXPR_RAYTRACER_CANVAS_HPP
#define CONSTEXPR_RAYTRACER_CANVAS_HPP

#include <cassert>
#include <vector>

#include "Color.hpp"

// TODO: make a constexpr vector implementation to substitute std::vector

class Canvas {
 public:
  using ColorRow = std::vector<Color>;
  using ColorMatrix = std::vector<ColorRow>;

  Canvas(ptrdiff_t width, ptrdiff_t height) noexcept
      : pixels_(static_cast<ColorMatrix::size_type>(height),
                ColorRow(static_cast<ColorRow::size_type>(width),
                         Color(0.f, 0.f, 0.f))) {
    assert(width > 0 && height > 0);
  }

  [[nodiscard]] ColorMatrix pixels() const noexcept { return pixels_; }

  [[nodiscard]] ptrdiff_t width() const noexcept {
    if (pixels_.empty()) return 0;

    return static_cast<ptrdiff_t>(pixels_[0].size());
  }

  [[nodiscard]] ptrdiff_t height() const noexcept {
    return static_cast<ptrdiff_t>(pixels_.size());
  }

  [[nodiscard]] bool empty() const noexcept { return pixels_.empty(); }

  void write_pixel(ptrdiff_t x, ptrdiff_t y, const Color& color) noexcept {
    assert(x < width() && x >= 0 && y < height() && y >= 0);

    pixels_[static_cast<ColorMatrix::size_type>(y)]
           [static_cast<ColorRow::size_type>(x)] = color;
  }

  [[nodiscard]] Color pixel_at(ptrdiff_t x, ptrdiff_t y) const noexcept {
    return pixels_[static_cast<ColorMatrix::size_type>(y)]
                  [static_cast<ColorRow::size_type>(x)];
  }

 private:
  ColorMatrix pixels_{};
};

[[nodiscard]] bool in_range(const Canvas& c, ptrdiff_t x,
                            ptrdiff_t y) noexcept {
  return x < c.width() && x >= 0 && y < c.height() && y >= 0;
}

#endif
