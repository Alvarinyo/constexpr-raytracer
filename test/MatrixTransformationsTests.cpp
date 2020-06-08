#include <catch2/catch.hpp>
#include <numbers>

#include "../src/MatrixTransformations.hpp"
#include "../src/Tuple.hpp"

SCENARIO("Multiplying by a translation matrix") {
  GIVEN("transform <- translation(5, -3, 2)")
  AND_GIVEN("p <- point(-3, 4, 5)") {
    constexpr auto transform = MatrixUtil::translation(5, -3, 2);
    constexpr auto p = point(-3, 4, 5);
    THEN("transform * p = point(2, 1, 7)") {
      STATIC_REQUIRE(transform * p == point(2, 1, 7));
    }
  }
}

SCENARIO("Multiplying by the inverse of a translation matrix") {
  GIVEN("transform <- translation(5, -3, 2)")
  AND_GIVEN("p <- point(-3, 4, 5)") {
    constexpr auto transform = MatrixUtil::translation(5, -3, 2);
    constexpr auto inv = MatrixUtil::inverse(transform);
    constexpr auto p = point(-3, 4, 5);
    THEN("inv * p = point(-8, 7, 3)") {
      STATIC_REQUIRE(inv * p == point(-8, 7, 3));
    }
  }
}

SCENARIO("Translation does not affect vectors") {
  GIVEN("transform <- translation(5, -3, 2)")
  AND_GIVEN("p <- point(-3, 4, 5)") {
    constexpr auto transform = MatrixUtil::translation(5, -3, 2);
    constexpr auto v = vector(-3, 4, 5);
    THEN("transform * p = point(2, 1, 7)") {
      STATIC_REQUIRE(transform * v == v);
    }
  }
}

SCENARIO("A scaling matrix applied to a point") {
  GIVEN("transform <- scaling(2, 3, 4)")
  AND_GIVEN("p <- point(-4, 6, 8)") {
    constexpr auto transform = MatrixUtil::scaling(2, 3, 4);
    constexpr auto p = point(-4, 6, 8);
    THEN("transform * p = point(-8, 18, 32)") {
      STATIC_REQUIRE(transform * p == point(-8, 18, 32));
    }
  }
}

SCENARIO("A scaling matrix applied to a vector") {
  GIVEN("transform <- scaling(2, 3, 4)")
  AND_GIVEN("v <- vector(-4, 6, 8)") {
    constexpr auto transform = MatrixUtil::scaling(2, 3, 4);
    constexpr auto v = vector(-4, 6, 8);
    THEN("transform * v = vector(-8, 18, 32)") {
      STATIC_REQUIRE(transform * v == vector(-8, 18, 32));
    }
  }
}

SCENARIO("Multiplying by the inverse of a scaling matrix") {
  GIVEN("transform <- scaling(2, 3, 4)")
  AND_GIVEN("inv <- inverse(transform)")
  AND_GIVEN("v <- vector(-4, 6, 8)") {
    constexpr auto transform = MatrixUtil::scaling(2, 3, 4);
    constexpr auto inv = MatrixUtil::inverse(transform);
    constexpr auto v = vector(-4, 6, 8);
    THEN("inv * v = vector(2, 2, 2)") {
      STATIC_REQUIRE(inv * v == vector(-2, 2, 2));
    }
  }
}

SCENARIO("Reflecting is scaling by a negative value") {
  GIVEN("transform <- scaling(-1, 1, 1)")
  AND_GIVEN("p <- point(2, 3, 4)") {
    constexpr auto transform = MatrixUtil::scaling(-1, 1, 1);
    constexpr auto p = point(2, 3, 4);
    THEN("transform * p = point(2, 3, 4)") {
      STATIC_REQUIRE(transform * p == point(-2, 3, 4));
    }
  }
}

SCENARIO("Rotating a point around the x axis") {
  GIVEN("p <- point(0, 1, 0)")
  AND_GIVEN("half_quarter <- rotation_x(pi/4)")
  AND_GIVEN("full_quarter <- rotation_x(pi/2)") {
    constexpr auto p = point(0, 1, 0);
    constexpr auto half_quarter =
        MatrixUtil::rotation_x(std::numbers::pi_v<float> / 4);
    constexpr auto full_quarter =
        MatrixUtil::rotation_x(std::numbers::pi_v<float> / 2);
    THEN("half_quarter * p = point(0, √2/2, √2/2)")
    AND_THEN("full_quarter * p = point(0, 1, 1)") {
      STATIC_REQUIRE(half_quarter * p ==
                     point(0, std::sqrt(2.f) / 2, std::sqrt(2.f) / 2));
      STATIC_REQUIRE(full_quarter * p == point(0, 0, 1));
    }
  }
}

SCENARIO("The inverse of an x-rotation rotates in the opposite direction") {
  GIVEN("p <- point(0, 1, 0)")
  AND_GIVEN("half_quarter <- rotation_x(pi/4)") {
    constexpr auto p = point(0, 1, 0);
    constexpr auto half_quarter =
        MatrixUtil::rotation_x(std::numbers::pi_v<float> / 4);
    constexpr auto inv = MatrixUtil::inverse(half_quarter);
    THEN("inv * p = point(0, √2/2, -√2/2)") {
      STATIC_REQUIRE(inv * p ==
                     point(0, std::sqrt(2.f) / 2, -std::sqrt(2.f) / 2));
    }
  }
}

SCENARIO("Rotating a point around the y axis") {
  GIVEN("p <- point(0, 0, 1)")
  AND_GIVEN("half_quarter <- rotation_y(pi/4)")
  AND_GIVEN("full_quarter <- rotation_y(pi/2)") {
    constexpr auto p = point(0, 0, 1);
    constexpr auto half_quarter =
        MatrixUtil::rotation_y(std::numbers::pi_v<float> / 4);
    constexpr auto full_quarter =
        MatrixUtil::rotation_y(std::numbers::pi_v<float> / 2);
    THEN("half_quarter * p = point(√2/2, 0, √2/2)")
    AND_THEN("full_quarter * p = point(1, 0, 0)") {
      STATIC_REQUIRE(half_quarter * p ==
                     point(std::sqrt(2.f) / 2, 0, std::sqrt(2.f) / 2));
      STATIC_REQUIRE(full_quarter * p == point(1, 0, 0));
    }
  }
}

SCENARIO("Rotating a point around the z axis") {
  GIVEN("p <- point(0, 1, 0)")
  AND_GIVEN("half_quarter <- rotation_z(pi/4)")
  AND_GIVEN("full_quarter <- rotation_z(pi/2)") {
    constexpr auto p = point(0, 1, 0);
    constexpr auto half_quarter =
        MatrixUtil::rotation_z(std::numbers::pi_v<float> / 4);
    constexpr auto full_quarter =
        MatrixUtil::rotation_z(std::numbers::pi_v<float> / 2);
    THEN("half_quarter * p = point(-√2/2, √2/2, 0)")
    AND_THEN("full_quarter * p = point(-1, 0, 0)") {
      STATIC_REQUIRE(half_quarter * p ==
                     point(-std::sqrt(2.f) / 2, std::sqrt(2.f) / 2, 0));
      STATIC_REQUIRE(full_quarter * p == point(-1, 0, 0));
    }
  }
}

SCENARIO("A shearing transformation moves x in proportion to y") {
  GIVEN("transform <- shearing(1, 0, 0, 0, 0, 0)")
  AND_GIVEN("p <- point(2, 3, 4)") {
    constexpr auto transform = MatrixUtil::shearing(1, 0, 0, 0, 0, 0);
    constexpr auto p = point(2, 3, 4);
    THEN("transform * p = point(5, 3, 4)") {
      STATIC_REQUIRE(transform * p == point(5, 3, 4));
    }
  }
}

SCENARIO("A shearing transformation moves x in proportion to z") {
  GIVEN("transform <- shearing(0, 1, 0, 0, 0, 0)")
  AND_GIVEN("p <- point(2, 3, 4)") {
    constexpr auto transform = MatrixUtil::shearing(0, 1, 0, 0, 0, 0);
    constexpr auto p = point(2, 3, 4);
    THEN("transform * p = point(6, 3, 4)") {
      STATIC_REQUIRE(transform * p == point(6, 3, 4));
    }
  }
}

SCENARIO("A shearing transformation moves y in proportion to x") {
  GIVEN("transform <- shearing(0, 0, 1, 0, 0, 0)")
  AND_GIVEN("p <- point(2, 3, 4)") {
    constexpr auto transform = MatrixUtil::shearing(0, 0, 1, 0, 0, 0);
    constexpr auto p = point(2, 3, 4);
    THEN("transform * p = point(2, 5, 4)") {
      STATIC_REQUIRE(transform * p == point(2, 5, 4));
    }
  }
}

SCENARIO("A shearing transformation moves y in proportion to z") {
  GIVEN("transform <- shearing(0, 0, 0, 1, 0, 0)")
  AND_GIVEN("p <- point(2, 3, 4)") {
    constexpr auto transform = MatrixUtil::shearing(0, 0, 0, 1, 0, 0);
    constexpr auto p = point(2, 3, 4);
    THEN("transform * p = point(2, 7, 4)") {
      STATIC_REQUIRE(transform * p == point(2, 7, 4));
    }
  }
}

SCENARIO("A shearing transformation moves z in proportion to x") {
  GIVEN("transform <- shearing(0, 0, 0, 0, 1, 0)")
  AND_GIVEN("p <- point(2, 3, 4)") {
    constexpr auto transform = MatrixUtil::shearing(0, 0, 0, 0, 1, 0);
    constexpr auto p = point(2, 3, 4);
    THEN("transform * p = point(2, 3, 6)") {
      STATIC_REQUIRE(transform * p == point(2, 3, 6));
    }
  }
}

SCENARIO("A shearing transformation moves z in proportion to y") {
  GIVEN("transform <- shearing(0, 0, 0, 0, 0, 1)")
  AND_GIVEN("p <- point(2, 3, 4)") {
    constexpr auto transform = MatrixUtil::shearing(0, 0, 0, 0, 0, 1);
    constexpr auto p = point(2, 3, 4);
    THEN("transform * p = point(2, 3, 7)") {
      STATIC_REQUIRE(transform * p == point(2, 3, 7));
    }
  }
}

SCENARIO("Individual transformations are applied in sequence") {
  GIVEN("p <- point(1, 0, 1)")
  AND_GIVEN("A <- rotation_x(pi/2)")
  AND_GIVEN("B <- scaling(5, 5, 5)")
  AND_GIVEN("C <- translation(10, 5, 7)") {
    constexpr auto p = point(1, 0, 1);
    constexpr auto A = MatrixUtil::rotation_x(std::numbers::pi_v<float> / 2);
    constexpr auto B = MatrixUtil::scaling(5, 5, 5);
    constexpr auto C = MatrixUtil::translation(10, 5, 7);
    // Apply rotation first
    WHEN("p2 <- A * p") {
      constexpr auto p2 = A * p;
      THEN("p2 = point(1, -1, 0)") { STATIC_REQUIRE(p2 == point(1, -1, 0)); }
      // Then apply scaling
      WHEN("p3 <- A * p") {
        constexpr auto p3 = B * p2;
        THEN("p3 = point(1, -1, 0)") { STATIC_REQUIRE(p3 == point(5, -5, 0)); }
        // Then apply translation
        WHEN("p4 <- A * p") {
          constexpr auto p4 = C * p3;
          THEN("p4 = point(15, 0, 7)") {
            STATIC_REQUIRE(p4 == point(15, 0, 7));
          }
        }
      }
    }
  }
}

SCENARIO("Chained transformations must be applied in reverse order") {
  GIVEN("p <- point(1, 0, 1)")
  AND_GIVEN("A <- rotation_x(pi/2)")
  AND_GIVEN("B <- scaling(5, 5, 5)")
  AND_GIVEN("C <- translation(10, 5, 7)") {
    constexpr auto p = point(1, 0, 1);
    constexpr auto A = MatrixUtil::rotation_x(std::numbers::pi_v<float> / 2);
    constexpr auto B = MatrixUtil::scaling(5, 5, 5);
    constexpr auto C = MatrixUtil::translation(10, 5, 7);
    WHEN("T <- C * B * A") {
      constexpr auto T = C * B * A;
      THEN("T * p = point(15, 0, 7") {
        STATIC_REQUIRE(T * p == point(15, 0, 7));
      }
    }
  }
}

SCENARIO("Using fluent API to perform chained transformations") {
  GIVEN("p <- point(1, 0, 1)") {
    constexpr auto p = point(1, 0, 1);
    WHEN("T <- rotation_x(pi/2).scaling(5, 5, 5).translation(10, 5, 7)") {
      constexpr auto T = MatrixUtil::rotation_x(std::numbers::pi_v<float> / 2)
                             .scaling(5, 5, 5)
                             .translation(10, 5, 7);
      THEN("T * p = point(15, 0, 7") {
        STATIC_REQUIRE(T * p == point(15, 0, 7));
      }
    }
  }
}