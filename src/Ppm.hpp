#ifndef CONSTEXPR_RAYTRACER_PPM_HPP
#define CONSTEXPR_RAYTRACER_PPM_HPP

#include <cmath>
#include <string>

#include "Canvas.hpp"

namespace ppm {

[[nodiscard]] std::string header(const Canvas& canvas) noexcept {
  return "P3\n" + std::to_string(canvas.width()) + ' ' +
         std::to_string(canvas.height()) + "\n255\n";
}

[[nodiscard]] std::string pixel_string(const Canvas& canvas) noexcept {
  static constexpr auto normalize_float = [](float color_value) {
    if (color_value < 0.f) return 0l;
    if (color_value > 1.f) return 255l;
    return std::lround(color_value * 255.f);
  };

  std::string pixel_str;
  for (const auto& row : canvas.pixels()) {
    for (const Color& pixel : row) {
      pixel_str += std::to_string(normalize_float(pixel.red)) + ' ' +
                   std::to_string(normalize_float(pixel.green)) + ' ' +
                   std::to_string(normalize_float(pixel.blue)) + ' ';
    }
    pixel_str.back() = '\n';
  }
  return pixel_str;
}

void split_lines(std::string& pixel_string) noexcept {
  ptrdiff_t line_size = 0;
  auto last_whitespace = pixel_string.begin();
  for (auto it = pixel_string.begin(); it != pixel_string.end(); ++it) {
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

[[nodiscard]] std::string payload(const Canvas& canvas) noexcept {
  if (canvas.empty()) return "";

  auto payload = pixel_string(canvas);
  split_lines(payload);
  return payload;
}

[[nodiscard]] std::string to_ppm(const Canvas& canvas) noexcept {
  return header(canvas) + payload(canvas);
}

}  // namespace ppm

#endif