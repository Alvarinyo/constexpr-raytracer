#include <catch2/catch.hpp>
#include <iostream>
#include <numbers>

#include "../src/Math.hpp"
#include "../src/MatrixTransformations.hpp"
#include "../src/Shape.hpp"
#include "../src/Tuple.hpp"

using namespace TupleUtil;
using namespace MathUtil;
using namespace MatrixUtil;
using namespace ShadingUtil;

SCENARIO("The normal on a sphere at a point on the x axis") {
  GIVEN("s <- Sphere()") {
    constexpr Sphere s;
    WHEN("n <- s.normal_at(point(1, 0, 0))") {
      constexpr auto n = s.normal_at(point(1, 0, 0));
      THEN("n = vector(1, 0, 0)") { STATIC_REQUIRE(n == vector(1, 0, 0)); }
    }
  }
}

SCENARIO("The normal on a sphere at a point on the y axis") {
  GIVEN("s <- Sphere()") {
    constexpr Sphere s;
    WHEN("n <- s.normal_at(point(0, 1, 0))") {
      constexpr auto n = s.normal_at(point(0, 1, 0));
      THEN("n = vector(0, 1, 0)") { STATIC_REQUIRE(n == vector(0, 1, 0)); }
    }
  }
}

SCENARIO("The normal on a sphere at a point on the z axis") {
  GIVEN("s <- Sphere()") {
    constexpr Sphere s;
    WHEN("n <- s.normal_at(point(0, 0, 1))") {
      constexpr auto n = s.normal_at(point(0, 0, 1));
      THEN("n = vector(0, 0, 1)") { STATIC_REQUIRE(n == vector(0, 0, 1)); }
    }
  }
}

SCENARIO("The normal on a nonaxial point") {
  GIVEN("s <- Sphere()") {
    constexpr Sphere s;
    WHEN("n <- s.normal_at(point(√3/3, √3/3, √3/3))") {
      constexpr auto n =
          s.normal_at(point(sqrt(3.f) / 3, sqrt(3.f) / 3, sqrt(3.f) / 3));
      THEN("n = vector(√3/3, √3/3, √3/3)") {
        STATIC_REQUIRE(n ==
                       vector(sqrt(3.f) / 3, sqrt(3.f) / 3, sqrt(3.f) / 3));
      }
    }
  }
}

SCENARIO("The normal is a normalized vector") {
  GIVEN("s <- Sphere()") {
    constexpr Sphere s;
    WHEN("n <- s.normal_at(point(√3/3, √3/3, √3/3))") {
      constexpr auto n =
          s.normal_at(point(sqrt(3.f) / 3, sqrt(3.f) / 3, sqrt(3.f) / 3));
      THEN("n = vector(√3/3, √3/3, √3/3)") {
        STATIC_REQUIRE(n == normalize(vector(sqrt(3.f) / 3, sqrt(3.f) / 3,
                                             sqrt(3.f) / 3)));
      }
    }
  }
}

SCENARIO("Computing the normal on a translated sphere") {
  GIVEN("s <- Sphere()")
  AND_GIVEN("s.set_transform(translation(0, 1, 0))") {
    constexpr Sphere s(translation(0, 1, 0));
    WHEN("n <- s.normal_at(point(0, 1.70711f, 0.70711f))") {
      constexpr auto n = s.normal_at(point(0, 1.70711f, -0.70711f));
      THEN("n = vector(0, 1.70711f, 0.70711f)") {
        STATIC_REQUIRE(n == vector(0.f, 0.70711f, -0.70711f));
      }
    }
  }
}

SCENARIO("Computing the normal on a transformed sphere") {
  GIVEN("s <- Sphere()")
  AND_GIVEN("m <- scaling(1, 0.5, 1) * rotation_z(pi/5)")
  AND_GIVEN("s.set_transform(m)") {
    constexpr Sphere s(scaling(1, 0.5, 1) *
                       rotation_z(std::numbers::pi_v<float> / 5));
    WHEN("n <- s.normal_at(point(0, √2/2, √2/2))") {
      constexpr auto n = s.normal_at(point(0, sqrt(2.f) / 2, -sqrt(2.f) / 2));
      THEN("n = vector(0, 0.97014f, -0.24254f)") {
        STATIC_REQUIRE(n == vector(0.f, 0.97014f, -0.24254f));
      }
    }
  }
}

SCENARIO("Reflecting a vector approaching at 45º") {
  GIVEN("v <- vector(1, -1, 0)")
  AND_GIVEN("n <- vector(0, 1, 0)") {
    constexpr auto v = vector(1, -1, 0);
    constexpr auto n = vector(0, 1, 0);
    WHEN("r <- reflect(v, n)") {
      constexpr auto r = reflect(v, n);
      THEN("r = vector(1, 1, 0)") { STATIC_REQUIRE(r == vector(1, 1, 0)); }
    }
  }
}

SCENARIO("Reflecting a vector off a slanted surface") {
  GIVEN("v <- vector(0, -1, 0)")
  AND_GIVEN("n <- vector(√2/2, √2/2, 0)") {
    constexpr auto v = vector(0, -1, 0);
    constexpr auto n = vector(sqrt(2.f) / 2, sqrt(2.f) / 2, 0);
    WHEN("r <- reflect(v, n)") {
      constexpr auto r = reflect(v, n);
      THEN("r = vector(1, 0, 0)") { STATIC_REQUIRE(r == vector(1, 0, 0)); }
    }
  }
}

SCENARIO("A point light has a position and intensity") {
  GIVEN("intensity <- color(1, 1, 1)")
  AND_GIVEN("position <- point(0, 0, 0)") {
    constexpr Color intensity(1, 1, 1);
    constexpr auto position = point(0, 0, 0);
    WHEN("light <- point_light(position, intensity)") {
      constexpr PointLight light(position, intensity);
      THEN("light.position = position")
      AND_THEN("light.intensity = intensity") {
        STATIC_REQUIRE(light.position == position);
        STATIC_REQUIRE(light.intensity == intensity);
      }
    }
  }
}

SCENARIO("The default material") {
  GIVEN("m <- material()") {
    constexpr Material m;
    THEN("m.color = color(1, 1, 1)")
    AND_THEN("m.ambient = 0.1")
    AND_THEN("m.diffuse = 0.9")
    AND_THEN("m.specular = 0.9")
    AND_THEN("m.shininess = 200.0") {
      STATIC_REQUIRE(m.color == Color(1, 1, 1));
      STATIC_REQUIRE(m.ambient == 0.1f);
      STATIC_REQUIRE(m.diffuse == 0.9f);
      STATIC_REQUIRE(m.specular == 0.9f);
      STATIC_REQUIRE(m.shininess == 200.0f);
    }
  }
}

SCENARIO("A sphere has a default material") {
  GIVEN("s <- Sphere()") {
    constexpr Sphere s;
    WHEN("m <- s.material") {
      constexpr auto m = s.material;
      THEN("m = material()") { STATIC_REQUIRE(m == Material()); }
    }
  }
}

SCENARIO("A sphere may be assigned a material") {
  GIVEN("s <- Sphere()")
  AND_GIVEN("m <- Material()")
  AND_GIVEN("m.ambient <- 1") {
    constexpr Sphere s;
    constexpr Material m = []() {
      Material ret;
      ret.ambient = 1;
      return ret;
    }();
    WHEN("s.material <- m") {
      constexpr Sphere s2 = [s = s, &m]() mutable {
        s.material = m;
        return s;
      }();
      THEN("s.material = m") { STATIC_REQUIRE(s2.material == m); }
    }
  }
}

SCENARIO("Lighting with the eye between the light and the surface") {
  GIVEN("m <- material()")
  AND_GIVEN("position <- point(0, 0, 0)")
  AND_GIVEN("eyev <- vector(0, 0, -1)")
  AND_GIVEN("normalv <- vector(0, 0, -1)")
  AND_GIVEN("light <- point_light(point(0, 0, -10), color(1, 1, 1))") {
    constexpr Material m;
    constexpr auto position = point(0, 0, 0);

    constexpr auto eyev = vector(0, 0, -1);
    constexpr auto normalv = vector(0, 0, -1);
    constexpr PointLight light(point(0, 0, -10), Color(1, 1, 1));

    WHEN("result <- lighting(m, light, position, eyev, normalv)") {
      constexpr auto result = lighting(m, light, position, eyev, normalv);
      THEN("result = color(1.9f, 1.9f, 1.9f)") {
        STATIC_REQUIRE(result == Color(1.9f, 1.9f, 1.9f));
      }
    }
  }
}

SCENARIO(
    "Lighting with the eye between the light and the surface, eye offset 45º") {
  GIVEN("m <- material()")
  AND_GIVEN("position <- point(0, 0, 0)")
  AND_GIVEN("eyev <- vector(0, √2/2, -√2/2)")
  AND_GIVEN("normalv <- vector(0, 0, -1)")
  AND_GIVEN("light <- point_light(point(0, 0, -10), color(1, 1, 1))") {
    constexpr Material m;
    constexpr auto position = point(0, 0, 0);

    constexpr auto eyev = vector(0, sqrt(2.f) / 2, -sqrt(2.f) / 2);
    constexpr auto normalv = vector(0, 0, -1);
    constexpr PointLight light(point(0, 0, -10), Color(1, 1, 1));

    WHEN("result <- lighting(m, light, position, eyev, normalv)") {
      constexpr auto result = lighting(m, light, position, eyev, normalv);
      THEN("result = color(1.0f, 1.0f, 1.0f)") {
        STATIC_REQUIRE(result == Color(1.0f, 1.0f, 1.0f));
      }
    }
  }
}

SCENARIO("Lighting with eye opposite surface, light offset 45º") {
  GIVEN("m <- material()")
  AND_GIVEN("position <- point(0, 0, 0)")
  AND_GIVEN("eyev <- vector(0, 0, -1)")
  AND_GIVEN("normalv <- vector(0, 0, -1)")
  AND_GIVEN("light <- point_light(point(0, 10, -10), color(1, 1, 1))") {
    constexpr Material m;
    constexpr auto position = point(0, 0, 0);

    constexpr auto eyev = vector(0, 0, -1);
    constexpr auto normalv = vector(0, 0, -1);
    constexpr PointLight light(point(0, 10, -10), Color(1, 1, 1));

    WHEN("result <- lighting(m, light, position, eyev, normalv)") {
      constexpr auto result = lighting(m, light, position, eyev, normalv);
      THEN("result = color(0.7364f, 0.7364f, 0.7364f)") {
        STATIC_REQUIRE(result == Color(0.7364f, 0.7364f, 0.7364f));
      }
    }
  }
}

#define constexpr const
SCENARIO("Lighting with eye in the path of the reflection vector") {
  GIVEN("m <- material()")
  AND_GIVEN("position <- point(0, 0, 0)")
  AND_GIVEN("eyev <- vector(0, -√2/2, -√2/2)")
  AND_GIVEN("normalv <- vector(0, 0, -1)")
  AND_GIVEN("light <- point_light(point(0, 10, -10), color(1, 1, 1))") {
    constexpr Material m;
    constexpr auto position = point(0, 0, 0);

    constexpr auto eyev = vector(0, -sqrt(2.f) / 2, -sqrt(2.f) / 2);
    constexpr auto normalv = vector(0, 0, -1);
    constexpr PointLight light(point(0, 10, -10), Color(1, 1, 1));

    WHEN("result <- lighting(m, light, position, eyev, normalv)") {
      constexpr auto result = lighting(m, light, position, eyev, normalv);
      THEN("result = color(1.6364f, 1.6364f, 1.6364f)") {
        std::cout << result.red << " " << result.green << " " << result.blue
                  << "\n";
        REQUIRE(result == Color(1.6364f, 1.6364f, 1.6364f));
      }
    }
  }
}

SCENARIO("Lighting with the light behind the surface") {
  GIVEN("m <- material()")
  AND_GIVEN("position <- point(0, 0, 0)")
  AND_GIVEN("eyev <- vector(0, 0, -1)")
  AND_GIVEN("normalv <- vector(0, 0, -1)")
  AND_GIVEN("light <- point_light(point(0, 0, -10), color(1, 1, 1))") {
    constexpr Material m;
    constexpr auto position = point(0, 0, 0);

    constexpr auto eyev = vector(0, 0, -1);
    constexpr auto normalv = vector(0, 0, -1);
    constexpr PointLight light(point(0, 0, 10), Color(1, 1, 1));

    WHEN("result <- lighting(m, light, position, eyev, normalv)") {
      constexpr auto result = lighting(m, light, position, eyev, normalv);
      THEN("result = color(0.1f, 0.1f, 0.1f)") {
        REQUIRE(result == Color(0.1f, 0.1f, 0.1f));
      }
    }
  }
}
