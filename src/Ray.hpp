#ifndef CONSTEXPR_RAYTRACER_RAY_HPP
#define CONSTEXPR_RAYTRACER_RAY_HPP
#include <array>
#include <concepts>
#include <optional>

#include "MatrixTransformations.hpp"
#include "Shape.hpp"
#include "StaticVector.hpp"
#include "Tuple.hpp"

struct Ray {
  Tuple origin;
  Tuple direction;
};

class Intersection {
 public:
  [[nodiscard]] constexpr Intersection() noexcept = default;

  [[nodiscard]] constexpr Intersection(float t, ShapeType object) noexcept
      : t_{t}, object_type_{object} {}

  [[nodiscard]] constexpr Intersection(float t, const Sphere& s) noexcept
      : t_{t}, object_type_{s.object_type} {}

  [[nodiscard]] constexpr float t() const noexcept { return t_; }

  [[nodiscard]] constexpr ShapeType object_type() const noexcept {
    return object_type_;
  }

  [[nodiscard]] friend constexpr bool operator==(
      const Intersection& lhs, const Intersection& rhs) noexcept {
    return lhs.t_ == rhs.t_ && lhs.object_type_ == rhs.object_type_;
  }

 private:
  float t_{0.f};
  ShapeType object_type_{ShapeType::Sphere};
};

namespace RayUtil {

namespace detail {

constexpr bool lower_nonnegative_intersection(
    const Intersection& lhs, const Intersection& rhs) noexcept {
  // Comparison between negative intersections is undefined
  if (lhs.t() < 0) return false;
  return lhs.t() < rhs.t();
}

}  // namespace detail

template <typename... Args>
requires(std::is_same_v<std::decay_t<Args>, Intersection>&&...)
    [[nodiscard]] constexpr auto intersections(Args&&... args) noexcept {
  auto result = std::array{std::forward<Args>(args)...};
  std::sort(result.begin(), result.end(),
            detail::lower_nonnegative_intersection);
  return result;
}

template <typename IntersectionList>
requires(std::is_same_v<typename IntersectionList::value_type, Intersection>)
    [[nodiscard]] constexpr std::optional<Intersection> hit(
        IntersectionList intersections) noexcept {
  assert(std::is_sorted(intersections.begin(), intersections.end(),
                        detail::lower_nonnegative_intersection));
  return intersections[0].t() < 0 ? std::nullopt
                                  : std::optional{intersections[0]};
}

[[nodiscard]] constexpr Ray transform(
    const Ray& ray, const MatrixUtil::Transformation& matrix) noexcept {
  return Ray{matrix * ray.origin, matrix * ray.direction};
}

[[nodiscard]] constexpr Tuple position(const Ray& ray, float t) noexcept {
  return ray.origin + ray.direction * t;
}

[[nodiscard]] constexpr auto intersect(const Ray& ray,
                                       const Sphere& sphere) noexcept
    -> StaticVector<Intersection, 2> {
  using namespace TupleUtil;
  using namespace MathUtil;

  const auto transformed_ray =
      transform(ray, MatrixUtil::inverse(sphere.transform));

  const auto sphere_to_ray = transformed_ray.origin - point(0, 0, 0);

  const auto a = dot(transformed_ray.direction, transformed_ray.direction);
  const auto b = 2 * dot(transformed_ray.direction, sphere_to_ray);
  const auto c = dot(sphere_to_ray, sphere_to_ray) - 1;

  const auto discriminant = b * b - 4 * a * c;
  if (discriminant < 0) return StaticVector<Intersection, 2>();

  return StaticVector<Intersection, 2>{
      Intersection((-b - sqrt(discriminant)) / (2 * a), ShapeType::Sphere),
      Intersection((-b + sqrt(discriminant)) / (2 * a), ShapeType::Sphere)};
}

}  // namespace RayUtil

#endif