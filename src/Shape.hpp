#ifndef CONSTEXPR_RAYTRACER_SHAPE_HPP
#define CONSTEXPR_RAYTRACER_SHAPE_HPP

#include <cmath>
#include <tuple>

#include "Color.hpp"
#include "MatrixTransformations.hpp"
#include "Shading.hpp"
#include "Tuple.hpp"

enum class ShapeType { Sphere };

struct Sphere {
  static constexpr ShapeType object_type{ShapeType::Sphere};
  MatrixUtil::Transformation transform{MatrixUtil::identity<4>()};
  Material material{};

  [[nodiscard]] constexpr Tuple normal_at(
      const Tuple& world_point) const noexcept {
    const auto object_point = MatrixUtil::inverse(transform) * world_point;
    const auto object_normal = object_point - TupleUtil::point(0, 0, 0);
    auto world_normal =
        MatrixUtil::transpose(MatrixUtil::inverse(transform)) * object_normal;
    world_normal.w = 0;
    return TupleUtil::normalize(world_normal);
  }
};

#endif