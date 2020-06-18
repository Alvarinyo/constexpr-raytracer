#ifndef CONSTEXPR_RAYTRACER_SHADING_HPP

struct PointLight {
  Tuple position;
  Color intensity;

  [[nodiscard]] constexpr PointLight(Tuple position_, Color intensity_) noexcept
      : position(std ::move(position_)), intensity(std::move(intensity_)) {}
};

struct Material {
  Color color{1.f, 1.f, 1.f};
  float ambient{0.1f};
  float diffuse{0.9f};
  float specular{0.9f};
  float shininess{200.0f};

  [[nodiscard]] constexpr friend bool operator==(const Material& lhs,
                                                 const Material& rhs) noexcept {
    return lhs.color == rhs.color && lhs.ambient == rhs.ambient &&
           lhs.diffuse == rhs.diffuse && lhs.specular == rhs.specular &&
           lhs.shininess == rhs.shininess;
  }
};

namespace ShadingUtil {

/*
  Calculates the lighting at a point of a surface using the Phong Reflection
  Model
*/
[[nodiscard]] constexpr Color lighting(Material material, PointLight light,
                                       Tuple point, Tuple eye_vector,
                                       Tuple normal_vector) noexcept {
  const Color effective_color = material.color * light.intensity;
  const Tuple light_vector = TupleUtil::normalize(light.position - point);
  const Color ambient = effective_color * material.ambient;
  const float light_dot_normal = TupleUtil::dot(light_vector, normal_vector);

  const auto [diffuse, specular] = [&]() -> std::pair<Color, Color> {
    if (light_dot_normal < 0)
      return {ColorUtil::black(), ColorUtil::black()};
    else {
      const Color diffuse_ =
          effective_color * material.diffuse * light_dot_normal;

      const Tuple reflect_vector =
          TupleUtil::reflect(-light_vector, normal_vector);
      const float reflect_dot_eye = TupleUtil::dot(reflect_vector, eye_vector);

      const Color specular_ = [&]() -> Color {
        if (reflect_dot_eye <= 0)
          return ColorUtil::black();
        else {
          const auto factor = std::pow(reflect_dot_eye, material.shininess);
          return light.intensity * material.specular * factor;
        }
      }();

      return {diffuse_, specular_};
    }
  }();

  return ambient + diffuse + specular;
}

}  // namespace ShadingUtil

#define CONSTEXPR_RAYTRACER_SHADING_HPP
#endif