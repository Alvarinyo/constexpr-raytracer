#include <catch2/catch.hpp>

#include "../src/MatrixTransformations.hpp"
#include "../src/Ray.hpp"
#include "../src/Tuple.hpp"

using namespace TupleUtil;
using namespace RayUtil;
using namespace MatrixUtil;

SCENARIO("Creating and querying a ray") {
  GIVEN("origin <- point(1, 2, 3)")
  AND_GIVEN("direction <- vector(4, 5, 6)") {
    constexpr auto origin = point(1, 2, 3);
    constexpr auto direction = vector(4, 5, 6);
    WHEN("r <- ray(origin, direction)") {
      constexpr Ray r(origin, direction);
      THEN("r.origin = origin")
      AND_THEN("r.origin = origin") {
        STATIC_REQUIRE(r.origin == origin);
        STATIC_REQUIRE(r.direction == direction);
      }
    }
  }
}

SCENARIO("Comouting a point from a distance") {
  GIVEN("r <- ray(point(2, 3, 4), vector(1, 0, 0))") {
    constexpr Ray r(point(2, 3, 4), vector(1, 0, 0));
    THEN("position(r, 0) = point(2, 3, 4)")
    AND_THEN("position(r, 1) = point(3, 3, 4)")
    AND_THEN("position(r, -1) = point(1, 3, 4)")
    AND_THEN("position(r, 2.5) = point(4.5, 3, 4)") {
      STATIC_REQUIRE(position(r, 0) == point(2, 3, 4));
      STATIC_REQUIRE(position(r, 1) == point(3, 3, 4));
      STATIC_REQUIRE(position(r, -1) == point(1, 3, 4));
      STATIC_REQUIRE(position(r, 2.5) == point(4.5, 3, 4));
    }
  }
}

SCENARIO("A ray intersects a sphere at two points") {
  GIVEN("r <- ray(point(0, 0, -5), vector(0, 0, 1))")
  AND_GIVEN("s <- Sphere()") {
    constexpr Ray r(point(0, 0, -5), vector(0, 0, 1));
    constexpr Sphere s;
    WHEN("xs <- intersect(s, r)") {
      constexpr auto intersection = intersect(r, s);
      THEN("xs.count = 2")
      AND_THEN("xs[0] = 4.0")
      AND_THEN("xs[1] = 6.0") {
        STATIC_REQUIRE(intersection.has_value());
        STATIC_REQUIRE(intersection->size() == 2);
        STATIC_REQUIRE((*intersection)[0] ==
                       Intersection(4.0f, ShapeType::Sphere));
        STATIC_REQUIRE((*intersection)[1] ==
                       Intersection(6.0f, ShapeType::Sphere));
      }
    }
  }
}

SCENARIO("A ray intersects a sphere at a tangent") {
  GIVEN("r <- ray(point(0, 1, -5), vector(0, 0, 1))")
  AND_GIVEN("s <- Sphere()") {
    constexpr Ray r(point(0, 1, -5), vector(0, 0, 1));
    constexpr Sphere s;
    WHEN("xs <- intersect(s, r)") {
      constexpr auto intersection = intersect(r, s);
      THEN("xs.count = 2")
      AND_THEN("xs[0] = 5.0")
      AND_THEN("xs[1] = 5.0") {
        STATIC_REQUIRE(intersection.has_value());
        STATIC_REQUIRE(intersection->size() == 2);
        STATIC_REQUIRE((*intersection)[0] ==
                       Intersection(5.0f, ShapeType::Sphere));
        STATIC_REQUIRE((*intersection)[1] ==
                       Intersection(5.0f, ShapeType::Sphere));
      }
    }
  }
}

SCENARIO("A ray misses a sphere") {
  GIVEN("r <- ray(point(0, 2, -5), vector(0, 0, 1))")
  AND_GIVEN("s <- Sphere()") {
    constexpr Ray r(point(0, 2, -5), vector(0, 0, 1));
    constexpr Sphere s;
    WHEN("xs <- intersect(s, r)") {
      constexpr auto intersection = intersect(r, s);
      THEN("xs.count = 0") { STATIC_REQUIRE_FALSE(intersection.has_value()); }
    }
  }
}

SCENARIO("A ray originates inside a sphere") {
  GIVEN("r <- ray(point(0, 0, 0), vector(0, 0, 1))")
  AND_GIVEN("s <- Sphere()") {
    constexpr Ray r(point(0, 0, 0), vector(0, 0, 1));
    constexpr Sphere s;
    WHEN("xs <- intersect(s, r)") {
      constexpr auto intersection = intersect(r, s);
      THEN("xs.count = 2")
      AND_THEN("xs[0] = -1.0")
      AND_THEN("xs[1] = 1.0") {
        STATIC_REQUIRE(intersection.has_value());
        STATIC_REQUIRE(intersection->size() == 2);
        STATIC_REQUIRE((*intersection)[0] ==
                       Intersection(-1.0f, ShapeType::Sphere));
        STATIC_REQUIRE((*intersection)[1] ==
                       Intersection(1.0f, ShapeType::Sphere));
      }
    }
  }
}

SCENARIO("A sphere is behind a ray") {
  GIVEN("r <- ray(point(0, 0, 5), vector(0, 0, 1))")
  AND_GIVEN("s <- Sphere()") {
    constexpr Ray r(point(0, 0, 5), vector(0, 0, 1));
    constexpr Sphere s;
    WHEN("xs <- intersect(s, r)") {
      constexpr auto intersection = intersect(r, s);
      THEN("xs.count = 2")
      AND_THEN("xs[0] = -6.0")
      AND_THEN("xs[1] = -4.0") {
        STATIC_REQUIRE(intersection.has_value());
        STATIC_REQUIRE(intersection->size() == 2);
        STATIC_REQUIRE((*intersection)[0] ==
                       Intersection(-6.0f, ShapeType::Sphere));
        STATIC_REQUIRE((*intersection)[1] ==
                       Intersection(-4.0f, ShapeType::Sphere));
      }
    }
  }
}

SCENARIO("An intersection encapsulates t and object") {
  GIVEN("s <- sphere()") {
    constexpr Sphere s;
    WHEN(" i <- intersection(3.5, s)") {
      constexpr Intersection i(3.5f, s);
      THEN("i.t = 3.5")
      AND_THEN("i.object = sphere") {
        STATIC_REQUIRE(i.t() == 3.5f);
        STATIC_REQUIRE(i.object_type() == ShapeType::Sphere);
      }
    }
  }
}

SCENARIO("Aggregating intersections") {
  GIVEN("s <- sphere()")
  AND_GIVEN("i1 <- intersection(1, s)")
  AND_GIVEN("i2 <- intersection(2, s)") {
    constexpr Sphere s;
    constexpr Intersection i1(1.f, s);
    constexpr Intersection i2(2.f, s);

    WHEN("xs <- intersections(i1, i2)") {
      constexpr auto xs = intersections(i1, i2);
      THEN("xs.count = 2")
      AND_THEN("xs[0].t = 1")
      AND_THEN("xs[1].t = 2") {
        STATIC_REQUIRE(xs.size() == 2);
        STATIC_REQUIRE(xs[0].t() == 1);
        STATIC_REQUIRE(xs[1].t() == 2);
      }
    }
  }
}

SCENARIO("Intersect sets the object on the intersection") {
  GIVEN("r <- ray(point(0, 0, -5), vector(0, 0, 1)")
  AND_GIVEN("s <- sphere()") {
    constexpr Ray r(point(0, 0, -5), vector(0, 0, 1));
    constexpr Sphere s;
    WHEN("xs <- intersect(s, r)") {
      constexpr auto xs = intersect(r, s);
      THEN("xs.count = 2")
      AND_THEN("xs[0].object = s")
      AND_THEN("xs[1].object = s") {
        STATIC_REQUIRE(xs.has_value());
        STATIC_REQUIRE((*xs).size() == 2);
        STATIC_REQUIRE(
            std::all_of(xs->cbegin(), xs->cend(), [](const auto& intersection) {
              return intersection.object_type() == ShapeType::Sphere;
            }));
      }
    }
  }
}

SCENARIO("The hit, when all intersections have positive t") {
  GIVEN("s <- sphere()")
  AND_GIVEN(" i1 <- intersection(1, s)")
  AND_GIVEN(" i2 <- intersection(2, s)")
  AND_GIVEN(" xs <- intersections(i2, i1)") {
    constexpr Sphere s;
    constexpr Intersection i1(1.f, s);
    constexpr Intersection i2(2.f, s);
    constexpr auto xs = intersections(i2, i1);
    WHEN("i <- hit(xs)") {
      constexpr auto i = hit(xs);
      THEN("i = i1") {
        STATIC_REQUIRE(i.has_value());
        STATIC_REQUIRE(*i == i1);
      }
    }
  }
}

SCENARIO("The hit, when some intersections have negative t") {
  GIVEN("s <- sphere()")
  AND_GIVEN(" i1 <- intersection(-1, s)")
  AND_GIVEN(" i2 <- intersection(1, s)")
  AND_GIVEN(" xs <- intersections(i2, i1)") {
    constexpr Sphere s;
    constexpr Intersection i1(-1.f, s);
    constexpr Intersection i2(1.f, s);
    constexpr auto xs = intersections(i2, i1);
    WHEN("i <- hit(xs)") {
      constexpr auto i = hit(xs);
      THEN("i = i2") {
        STATIC_REQUIRE(i.has_value());
        STATIC_REQUIRE(*i == i2);
      }
    }
  }
}

SCENARIO("The hit, when all intersections have negative t") {
  GIVEN("s <- sphere()")
  AND_GIVEN(" i1 <- intersection(-2, s)")
  AND_GIVEN(" i2 <- intersection(-1, s)")
  AND_GIVEN(" xs <- intersections(i2, i1)") {
    constexpr Sphere s;
    constexpr Intersection i1(-2.f, s);
    constexpr Intersection i2(-1.f, s);
    constexpr auto xs = intersections(i2, i1);
    WHEN("i <- hit(xs)") {
      constexpr auto i = hit(xs);
      THEN("i = i2") { STATIC_REQUIRE_FALSE(i.has_value()); }
    }
  }
}

SCENARIO("The hit is always the lowest nonnegative intersection") {
  GIVEN("s <- sphere()")
  AND_GIVEN(" i1 <- intersection(5, s)")
  AND_GIVEN(" i2 <- intersection(7, s)")
  AND_GIVEN(" i1 <- intersection(-3, s)")
  AND_GIVEN(" i2 <- intersection(2, s)")
  AND_GIVEN(" xs <- intersections(i, i2, i3, i4)") {
    constexpr Sphere s;
    constexpr Intersection i1(5.f, s);
    constexpr Intersection i2(7.f, s);
    constexpr Intersection i3(-3.f, s);
    constexpr Intersection i4(2.f, s);
    constexpr auto xs = intersections(i1, i2, i3, i4);
    WHEN("i <- hit(xs)") {
      constexpr auto i = hit(xs);
      THEN("i = i2") {
        STATIC_REQUIRE(i.has_value());
        STATIC_REQUIRE(*i == i4);
      }
    }
  }
}

SCENARIO("Translating a ray") {
  GIVEN("r <- ray(point(1, 2, 3), vector(0, 1, 0))")
  AND_GIVEN("m <- translation(3, 4, 5)") {
    constexpr Ray r(point(1, 2, 3), vector(0, 1, 0));
    constexpr auto m = translation(3, 4, 5);
    WHEN("r2 <- transform(r, m)") {
      constexpr auto r2 = transform(r, m);
      THEN("r2.origin = point(4, 6, 8)")
      AND_THEN("r2.direction = vector(0, 1, 0)") {
        STATIC_REQUIRE(r2.origin == point(4, 6, 8));
        STATIC_REQUIRE(r2.direction == vector(0, 1, 0));
      }
    }
  }
}

SCENARIO("Scaling a ray") {
  GIVEN("r <- ray(point(1, 2, 3), vector(0, 1, 0))")
  AND_GIVEN("m <- scaling(2, 3, 4)") {
    constexpr Ray r(point(1, 2, 3), vector(0, 1, 0));
    constexpr auto m = scaling(2, 3, 4);
    WHEN("r2 <- transform(r, m)") {
      constexpr auto r2 = transform(r, m);
      THEN("r2.origin = point(2, 6, 12)")
      AND_THEN("r2.direction = vector(0, 3, 0)") {
        STATIC_REQUIRE(r2.origin == point(2, 6, 12));
        STATIC_REQUIRE(r2.direction == vector(0, 3, 0));
      }
    }
  }
}

SCENARIO("A sphere's default transformation") {
  GIVEN("s <- Sphere()") {
    constexpr Sphere s;
    THEN("s.transform = indentity_matrix") {
      STATIC_REQUIRE(s.transform == identity<4>());
    }
  }
}

SCENARIO("Changing a sphere's transformation") {
  GIVEN("s <- Sphere()")
  AND_GIVEN("t <- translation(2, 3, 4)") {
    constexpr Sphere s;
    constexpr auto t = translation(2, 3, 4);
    WHEN("s.set_transform(t)") {
      constexpr auto s2 = [s_ = s, t]() mutable {
        s_.transform = t;
        return s_;
      }();
      THEN("s.transform = t") { STATIC_REQUIRE(s2.transform == t); }
    }
  }
}

SCENARIO("Intersecting a scaled sphere with a ray") {
  GIVEN("r <- ray(point(0, 0, -5), vector(0, 0, 1))")
  AND_GIVEN("s <- Sphere()") {
    constexpr Ray r(point(0, 0, -5), vector(0, 0, 1));
    constexpr Sphere s;
    WHEN("s.set_transform(scaling(2, 2, 2))")
    AND_WHEN("xs <- intersect(r, s)") {
      constexpr auto s2 = [s_ = s]() mutable {
        s_.transform = scaling(2, 2, 2);
        return s_;
      }();
      constexpr auto xs = intersect(r, s2);

      THEN("xs.count = 2")
      AND_THEN("xs[0].t = 3")
      AND_THEN("xs[1].t = 7") {
        STATIC_REQUIRE(xs.has_value());
        STATIC_REQUIRE((*xs)[0].t() == 3);
        STATIC_REQUIRE((*xs)[1].t() == 7);
      }
    }
  }
}

SCENARIO("Intersecting a translated sphere with a ray") {
  GIVEN("r <- ray(point(0, 0, -5), vector(0, 0, 1))")
  AND_GIVEN("s <- Sphere()") {
    constexpr Ray r(point(0, 0, -5), vector(0, 0, 1));
    constexpr Sphere s;
    WHEN("s.set_transform(translation(5, 0, 0))")
    AND_WHEN("xs <- intersect(r, s)") {
      constexpr auto s2 = [s_ = s]() mutable {
        s_.transform = translation(5, 0, 0);
        return s_;
      }();
      constexpr auto xs = intersect(r, s2);

      THEN("xs.count = 0") { STATIC_REQUIRE_FALSE(xs.has_value()); }
    }
  }
}
