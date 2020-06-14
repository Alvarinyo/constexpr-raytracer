#ifndef CONSTEXPR_RAYTRACER_SHAPE_HPP
#define CONSTEXPR_RAYTRACER_SHAPE_HPP

#include "MatrixTransformations.hpp"
#include "Tuple.hpp"

enum class ShapeType { Sphere };

struct Sphere {
  static constexpr ShapeType object_type{ShapeType::Sphere};
  MatrixUtil::Transformation transform{MatrixUtil::identity<4>()};
};

#endif