#include <iostream>

#include "../src/Tuple.hpp"

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
  Projectile p = {point(0.f, 1.f, 0.f), vector(1.f, 1.f, 0.f).normalized()};
  Environment e = {vector(0.f, -0.1f, 0.f), vector(-0.01f, 0.f, 0.f)};

  while (p.position.y > 0) {
    std::cout << "Position: " << to_string(p.position)
              << ", Velocity: " << to_string(p.velocity) << '\n';
    p = tick(std::move(p), e);
  }

  return 0;
}