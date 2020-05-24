#ifndef CONSTEXPR_RAYTRACER_CANVAS_HPP
#define CONSTEXPR_RAYTRACER_CANVAS_HPP

#include <cassert>
#include <charconv>
#include <cmath>
#include <string>
#include <vector>

#include "Color.hpp"
#include "Math.hpp"

// TODO: make a constexpr vector implementation to substitute std::vector

class Canvas {
 public:
  using ColorRow = std::vector<Color>;
  using ColorMatrix = std::vector<ColorRow>;

  Canvas(size_t width, size_t height) noexcept
      : pixels_(height, ColorRow(width, Color(0.f, 0.f, 0.f))) {}

  [[nodiscard]] ColorMatrix& pixels() noexcept { return pixels_; }

  [[nodiscard]] const ColorMatrix& pixels() const noexcept { return pixels_; }

  [[nodiscard]] size_t width() const noexcept {
    if (pixels_.empty()) return 0;
    return pixels_[0].size();
  }

  [[nodiscard]] size_t height() const noexcept { return pixels_.size(); }

  void write_pixel(size_t x, size_t y, const Color& color) noexcept {
    pixels_[y][x] = color;
  }

  [[nodiscard]] Color pixel_at(size_t x, size_t y) const noexcept {
    return pixels_[y][x];
  }

  [[nodiscard]] std::string ppm_header() const noexcept {
    return "P3\n" + std::to_string(width()) + ' ' + std::to_string(height()) +
           "\n255\n";
  }

  [[nodiscard]] std::string ppm_pixels() const noexcept {
    static constexpr auto normalize_float = [](float pixel) {
      if (pixel < 0.f) return 0l;
      if (pixel > 1.f) return 255l;
      return std::lround(pixel * 255.f);
    };

    std::string ppm_pixels;
    for (const auto& row : pixels_) {
      for (const Color& pixel : row) {
        ppm_pixels += std::to_string(normalize_float(pixel.red)) + ' ' +
                      std::to_string(normalize_float(pixel.green)) + ' ' +
                      std::to_string(normalize_float(pixel.blue)) + ' ';
      }
      ppm_pixels.back() = '\n';
    }
    return ppm_pixels;
  }

  void ppm_split_lines(std::string& ppm_pixels) const noexcept {
    ptrdiff_t line_size = 0;
    auto last_whitespace = ppm_pixels.begin();
    for (auto it = ppm_pixels.begin(); it != ppm_pixels.end(); ++it) {
      if (*it == ' ') last_whitespace = it;
      if (line_size == 70) {
        *last_whitespace = '\n';
        line_size = std::distance(last_whitespace, it);
      } else {
        ++line_size;
      }
      if (*it == '\n') line_size = 0;
    }
  }

  [[nodiscard]] std::string ppm_payload() const noexcept {
    if (pixels_.empty()) return "";

    auto ppm_payload = ppm_pixels();
    ppm_split_lines(ppm_payload);
    return ppm_payload;
  }

  [[nodiscard]] std::string to_ppm() const noexcept {
    return ppm_header() + ppm_payload();
  }

 private:
  ColorMatrix pixels_{};
};

#endif
