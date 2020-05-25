#include <catch2/catch.hpp>

#include "../src/Tuple.hpp"

SCENARIO("A tuple with w=1.0 is a point") {
  GIVEN("a <- tuple(4.3, -4.2, 3.1, 1.0)") {
    constexpr Tuple a(4.3f, -4.2f, 3.1f, 1.0f);
    THEN("[a.x, a.y, a.z, a.w] = [4.3, -4.2, 3.1, 1.0]") {
      STATIC_REQUIRE(a.x == 4.3f);
      STATIC_REQUIRE(a.y == -4.2f);
      STATIC_REQUIRE(a.z == 3.1f);
      STATIC_REQUIRE(a.w == 1.0f);
    }
    AND_THEN("a is a point") { STATIC_REQUIRE(is_point(a)); }
    AND_THEN("a is not a vector") { STATIC_REQUIRE_FALSE(is_vector(a)); }
  }
}

SCENARIO("A tuple with w=0 is a vector") {
  GIVEN("a <- tuple(4.3, -4.2, 3.1, 0.0)") {
    constexpr Tuple a(4.3f, -4.2f, 3.1f, 0.0f);
    THEN("[a.x, a.y, a.z, a.w] = [4.3, -4.2, 3.1, 0.0]") {
      STATIC_REQUIRE(a.x == 4.3f);
      STATIC_REQUIRE(a.y == -4.2f);
      STATIC_REQUIRE(a.z == 3.1f);
      STATIC_REQUIRE(a.w == 0.0f);
    }
    AND_THEN("a is not a point") { STATIC_REQUIRE_FALSE(is_point(a)); }
    AND_THEN("a is a vector") { STATIC_REQUIRE(is_vector(a)); }
  }
}

SCENARIO("point() creates tuples with w=1") {
  GIVEN("p <- point(4, -4, 3)") {
    constexpr auto p = point(4, -4, 3);
    THEN("p = tuple(4, -4, 3, 1)") { STATIC_REQUIRE(p == Tuple(4, -4, 3, 1)); }
  }
}

SCENARIO("vector() creates tuples with w=0") {
  GIVEN("p <- vector(4, -4, 3)") {
    constexpr auto p = vector(4, -4, 3);
    THEN("p = tuple(4, -4, 3, 0)") { STATIC_REQUIRE(p == Tuple(4, -4, 3, 0)); }
  }
}

SCENARIO("Adding two tuples") {
  GIVEN("a1 <- tuple(3, -2, 5, 1)")
  AND_GIVEN("a2 <- tuple(-2, 3, 1, 0)") {
    constexpr Tuple a1(3, -2, 5, 1);
    constexpr Tuple a2(-2, 3, 1, 0);
    THEN("a1 + a2 = tuple(1, 1, 6, 1)") {
      STATIC_REQUIRE(a1 + a2 == Tuple(1, 1, 6, 1));
    }
  }
  GIVEN("a1 <- vector(1, 2, 3)")
  AND_GIVEN("a2 <- vector(4, 5, 6)") {
    constexpr auto a1 = vector(1, 2, 3);
    constexpr auto a2 = vector(4, 5, 6);
    THEN("a1 + a2 is a vector") { STATIC_REQUIRE(is_vector(a1 + a2)); }
  }
  GIVEN("a1 <- vector(1, 2, 3)")
  AND_GIVEN("a2 <- point(4, 5, 6)") {
    constexpr auto a1 = vector(1, 2, 3);
    constexpr auto a2 = point(4, 5, 6);
    THEN("a1 + a2 is a point") { STATIC_REQUIRE(is_point(a1 + a2)); }
  }
  GIVEN("a1 <- point(1, 2, 3)")
  AND_GIVEN("a2 <- point(4, 5, 6)") {
    constexpr auto a1 = point(1, 2, 3);
    constexpr auto a2 = point(4, 5, 6);
    THEN("a1 + a2 is neither a point nor a vector") {
      STATIC_REQUIRE_FALSE(is_vector(a1 + a2));
      STATIC_REQUIRE_FALSE(is_point(a1 + a2));
    }
  }
}

SCENARIO("Subtracting two points") {
  GIVEN("p1 <- point(3, 2, 1)")
  AND_GIVEN("p2 <- point(5, 6, 7)") {
    constexpr auto p1 = point(3, 2, 1);
    constexpr auto p2 = point(5, 6, 7);
    THEN("p1 - p2 = vector(-2, 4, 6)") {
      STATIC_REQUIRE(p1 - p2 == vector(-2, -4, -6));
    }
  }
}

SCENARIO("Subtracting a vector from a point") {
  GIVEN("p <- point(3, 2, 1)")
  AND_GIVEN("v <- vector(5, 6, 7)") {
    constexpr auto p = point(3, 2, 1);
    constexpr auto v = vector(5, 6, 7);
    THEN("p - v = point(-2, 4, 6)") {
      STATIC_REQUIRE(p - v == point(-2, -4, -6));
    }
  }
}

SCENARIO("Subtracting two vectors") {
  GIVEN("v1 <- vector(3, 2, 1)")
  AND_GIVEN("v2 <- vector(5, 6, 7)") {
    constexpr auto v1 = vector(3, 2, 1);
    constexpr auto v2 = vector(5, 6, 7);
    THEN("v1 - v2 = vector(-2, 4, 6)") {
      STATIC_REQUIRE(v1 - v2 == vector(-2, -4, -6));
    }
  }
}

SCENARIO("Subtracting a vector from the zero vector") {
  GIVEN("zero <- vector(0, 0, 0)")
  AND_GIVEN("v <- vector(1, -2, 3)") {
    constexpr auto zero = vector(0, 0, 0);
    constexpr auto v = vector(1, -2, 3);
    THEN("zero - v = vector(-1, 2, -3)") {
      STATIC_REQUIRE(zero - v == vector(-1, 2, -3));
    }
  }
}

SCENARIO("Negating a tuple") {
  GIVEN("a <- tuple(1, -2, 3, -4)") {
    constexpr auto a = Tuple(1, -2, 3, -4);
    constexpr auto b = -a;
    THEN("-a = tuple(-1, 2, -3, 4)") {
      STATIC_REQUIRE(b == Tuple(-1, 2, -3, 4));
    }
  }
}

SCENARIO("Multiplying a tuple by an escalar") {
  GIVEN("a <- tuple(1, -2, 3, -4)") {
    constexpr auto a = Tuple(1, -2, 3, -4);
    THEN("a * 3.5 = tuple(3.5, -7, 10.5, -14)") {
      STATIC_REQUIRE(a * 3.5 == Tuple(3.5, -7, 10.5, -14));
    }
  }
}

SCENARIO("Multiplying a tuple by a fraction") {
  GIVEN("a <- tuple(1, -2, 3, -4)") {
    constexpr auto a = Tuple(1, -2, 3, -4);
    THEN("a * 0.5 = tuple(0.5, -1, 1.5, -2)") {
      STATIC_REQUIRE(a * 0.5 == Tuple(0.5, -1, 1.5, -2));
    }
  }
}

SCENARIO("Dividing a tuple by an escalar") {
  GIVEN("a <- tuple(1, -2, 3, -4)") {
    constexpr auto a = Tuple(1, -2, 3, -4);
    THEN("a / 2 = tuple(0.5, -1, 1.5, -2)") {
      STATIC_REQUIRE(a / 2 == Tuple(0.5, -1, 1.5, -2));
    }
  }
}

SCENARIO("Computing the magnitude of vectors") {
  GIVEN("v <- vector(1, 0, 0)") {
    constexpr auto v = vector(1, 0, 0);
    THEN("v.magnitude() = 1") { STATIC_REQUIRE(magnitude(v) == 1); }
  }
  GIVEN("v <- vector(0, 1, 0)") {
    constexpr auto v = vector(0, 1, 0);
    THEN("v.magnitude() = 1") { STATIC_REQUIRE(magnitude(v) == 1); }
  }
  GIVEN("v <- vector(0, 0, 1)") {
    constexpr auto v = vector(0, 0, 1);
    THEN("v.magnitude() = 1") { STATIC_REQUIRE(magnitude(v) == 1); }
  }
  GIVEN("v <- vector(1, 2, 3)") {
    constexpr auto v = vector(1, 2, 3);
    THEN("v.magnitude() = sqrt(14)") {
      STATIC_REQUIRE(magnitude(v) == std::sqrt(14.0f));
    }
  }
  GIVEN("v <- vector(-1, -2, -3)") {
    constexpr auto v = vector(-1, -2, -3);
    THEN("v.magnitude() = sqrt(14)") {
      STATIC_REQUIRE(magnitude(v) == std::sqrt(14.0f));
    }
  }
}

SCENARIO("Normalizing some vectors") {
  GIVEN("v <- vector(4, 0, 0)") {
    constexpr auto v = vector(4, 0, 0);
    THEN("v.normalize() = vector(1, 0, 0)") {
      STATIC_REQUIRE(normalize(v) == vector(1, 0, 0));
    }
  }
  GIVEN("v <- vector(1, 2, 3)") {
    constexpr auto v = vector(1, 2, 3);
    THEN("v.normalize() = aproximately vector(0.26726, 0.53452, 0.80178)") {
      STATIC_REQUIRE(normalize(v) == vector(0.26726f, 0.53452f, 0.80178f));
    }
  }
  GIVEN("v <- vector(1, 2, 3)") {
    constexpr auto v = vector(1, 2, 3);
    WHEN("norm <- v.get_normalized()") {
      constexpr auto norm = normalize(v);
      THEN("norm = aproximately vector(0.26726, 0.53452, 0.80178)") {
        STATIC_REQUIRE(aprox_equal(magnitude(norm), 1.0f, 0.00001f));
      }
    }
  }
}

SCENARIO("The dot product of two tuples") {
  GIVEN("a <- vector(1, 2, 3)")
  AND_GIVEN("b <- vector(2, 3, 4))") {
    constexpr auto a = vector(1, 2, 3);
    constexpr auto b = vector(2, 3, 4);
    THEN("dot(a, b) = 20") { STATIC_REQUIRE(dot(a, b) == 20); }
  }
}

SCENARIO("The cross product of two vectors") {
  GIVEN("a <- vector(1, 2, 3")
  AND_GIVEN("b <- vector(2, 3, 4)") {
    constexpr auto a = vector(1, 2, 3);
    constexpr auto b = vector(2, 3, 4);
    THEN("cross(a, b) = vector(-1, 2, -1)") {
      STATIC_REQUIRE(cross(a, b) == vector(-1, 2, -1));
    }
    AND_THEN("cross(b, a) = vector(1, -2, 1)") {
      STATIC_REQUIRE(cross(b, a) == vector(1, -2, 1));
    }
  }
}