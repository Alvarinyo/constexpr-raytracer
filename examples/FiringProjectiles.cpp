#include <fstream>
#include <iostream>

#include "../src/Canvas.hpp"
#include "../src/Ppm.hpp"
#include "../src/Tuple.hpp"

using namespace TupleUtil;

std::string to_string(const Tuple& tup) {
  return '{' + std::to_string(tup.x) + ", " + std::to_string(tup.y) + ", " +
         std::to_string(tup.z) + ", " + std::to_string(tup.w) + '}';
}

struct Projectile {
  Tuple position;
  Tuple velocity;
};

struct Environment {
  Tuple gravity;
  Tuple wind;
};

constexpr Projectile tick(Projectile proj, const Environment& env) {
  proj.position += proj.velocity;
  proj.velocity += env.gravity + env.wind;
  return proj;
}

int main() {
  const Environment e = {vector(0.f, -0.05f, 0.f), vector(-0.01f, 0.f, 0.f)};
  Projectile p = {point(0.f, 1.f, 0.f), normalize(vector(1.f, 1.8f, 0.f)) * 8};
  Canvas c(800, 600);

  for (;;) {
    const auto pixel_x = iround(p.position.x);
    const auto pixel_y = c.height() - iround(p.position.y);

    if (!in_range(c, pixel_x, pixel_y)) break;

    std::cout << "Position: " << to_string(p.position)
              << ", Velocity: " << to_string(p.velocity) << '\n';

    c.write_pixel(pixel_x, pixel_y, Color(0.f, 1.f, 0.2f));
    p = tick(std::move(p), e);
  }

  std::ofstream ostrm("projectile_trace.ppm");
  ostrm << CanvasUtil::to_ppm(c);
  return 0;
}