#include <fstream>
#include <iostream>

#include "../src/Canvas.hpp"
#include "../src/Color.hpp"
#include "../src/MatrixTransformations.hpp"
#include "../src/Ppm.hpp"
#include "../src/Ray.hpp"
#include "../src/Tuple.hpp"

void paint_point(Canvas& canvas, float x, float z) {
  const auto canvas_x = canvas.width() / 2 + MathUtil::iround(x);
  const auto canvas_y = canvas.height() / 2 + MathUtil::iround(z);
  canvas.write_pixel(canvas_x, canvas_y, Color(1.f, 0.3f, 0.2f));
}

int main() {
  using namespace TupleUtil;
  using namespace RayUtil;
  using namespace MatrixUtil;

  constexpr Tuple ray_origin = point(0, 0, -5);
  constexpr float wall_z = 10.f;
  constexpr float wall_size = 7.f;
  constexpr int canvas_pixels = 100;
  constexpr float pixel_size = wall_size / canvas_pixels;
  constexpr float half = wall_size / 2;

  Canvas canvas(canvas_pixels, canvas_pixels);
  constexpr Color color(1, 0, 0);
  Sphere shape;

  shape.transform = scaling(0.5, 1, 1).shearing(1, 0, 0, 0, 0, 0);

  for (int row = 0; row < canvas_pixels; ++row) {
    const auto world_y = half - pixel_size * static_cast<float>(row);
    for (int col = 0; col < canvas_pixels; ++col) {
      const auto world_x = half - pixel_size * static_cast<float>(col);

      const auto position = point(world_x, world_y, wall_z);

      const Ray ray(ray_origin, normalize(position - ray_origin));
      const auto xs = intersect(ray, shape);

      if (xs.has_value()) {
        canvas.write_pixel(row, col, color);
      }
    }
  }

  std::ofstream ostrm("sphere_silhouette.ppm");
  ostrm << CanvasUtil::to_ppm(canvas);
}