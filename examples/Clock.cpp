#include <fstream>
#include <iostream>
#include <numbers>

#include "../src/Canvas.hpp"
#include "../src/MatrixTransformations.hpp"
#include "../src/Ppm.hpp"
#include "../src/Tuple.hpp"

void paint_point(Canvas& canvas, float x, float z) {
  const auto canvas_x = canvas.width() / 2 + std::lround(x);
  const auto canvas_y = canvas.height() / 2 + std::lround(z);
  canvas.write_pixel(canvas_x, canvas_y, Color(1.f, 0.3f, 0.2f));
}

int main() {
  Canvas c(400, 400);

  const auto radius = static_cast<float>(c.width()) * (3.f / 8.f);
  auto clock_hand = point(0.f, 0.f, 1.f) * radius;
  const auto one_hour_rotation =
      MatrixUtil::rotation_y(std::numbers::pi_v<float> / 6.f);

  for (int i = 0; i <= 11; ++i) {
    paint_point(c, clock_hand.x, clock_hand.z);
    clock_hand = one_hour_rotation * clock_hand;
  }

  std::ofstream ofs("clock.ppm");
  ofs << ppm::to_ppm(c);

  return 0;
}