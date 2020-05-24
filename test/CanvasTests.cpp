#include <catch2/catch.hpp>
#include <string_view>

#include "../src/Canvas.hpp"
#include "../src/Color.hpp"

SCENARIO("Colors are (red, green, blue) tuples") {
  GIVEN("c <- Color(-0.5, 0.4, 1.7)") {
    constexpr auto c = Color(-0.5f, 0.4f, 1.7f);
    THEN("c.red = -0.5") { STATIC_REQUIRE(c.red == -0.5f); }
    AND_THEN("c.green = 0.4") { STATIC_REQUIRE(c.green == 0.4f); }
    AND_THEN("c.blue = 1.7") { STATIC_REQUIRE(c.blue == 1.7f); }
  }
}

SCENARIO("Adding colors") {
  GIVEN("c1 <- Color(0.9, 0.6, 0.75)")
  AND_GIVEN("c2 <- Color(0.7, 0.1, 0.25)") {
    constexpr auto c1 = Color(0.9f, 0.6f, 0.75f);
    constexpr auto c2 = Color(0.7f, 0.1f, 0.25f);
    THEN("c1 + c2 = Color(1.6, 0.7, 1.0)") {
      STATIC_REQUIRE(c1 + c2 == Color(1.6f, 0.7f, 1.0f));
    }
  }
}

SCENARIO("Subtracting colors") {
  GIVEN("c1 <- Color(0.9, 0.6, 0.75)")
  AND_GIVEN("c2 <- Color(0.7, 0.1, 0.25)") {
    constexpr auto c1 = Color(0.9f, 0.6f, 0.75f);
    constexpr auto c2 = Color(0.7f, 0.1f, 0.25f);
    THEN("c1 - c2 =Color(0.2f, 0.5f, 0.5f)") {
      STATIC_REQUIRE(c1 - c2 == Color(0.2f, 0.5f, 0.5f));
    }
  }
}

SCENARIO("Multiplying a color by a scalar") {
  GIVEN("c1 <- Color(0.2f, 0.3f, 0.4f)") {
    constexpr auto c = Color(0.2f, 0.3f, 0.4f);
    THEN("c * 2 = Color(0.4, 0.6, 0.8)") {
      STATIC_REQUIRE(c * 2 == Color(0.4f, 0.6f, 0.8f));
    }
  }
}

SCENARIO("Multiplying colors") {
  GIVEN("c1 <- Color(1.0, 0.2, 0.4)")
  AND_GIVEN("c2 <- Color(0.9, 1.0, 0.1)") {
    constexpr auto c1 = Color(1.0f, 0.2f, 0.4f);
    constexpr auto c2 = Color(0.9f, 1.0f, 0.1f);
    THEN("c1 + c2 = Color(1.6, 0.7, 1.0)") {
      STATIC_REQUIRE(c1 * c2 == Color(0.9f, 0.2f, 0.04f));
    }
  }
}

SCENARIO("Creating a canvas") {
  GIVEN("c <- Canvas(10, 20)") {
    const Canvas c(10, 20);
    THEN("c.width() = 10")
    AND_THEN("c.height() = 20")
    AND_THEN("Every pixel of c is color(0, 0, 0)") {
      REQUIRE(c.width() == 10);
      REQUIRE(c.height() == 20);
      REQUIRE(std::all_of(
          c.pixels().begin(), c.pixels().end(), [](const auto& row) {
            return std::all_of(row.begin(), row.end(), [](const Color& color) {
              return color == Color(0, 0, 0);
            });
          }));
    }
  }
}

SCENARIO("Writing pixels to a canvas") {
  GIVEN("c <- Canvas(10, 20)")
  AND_GIVEN("red <- Color(1, 0, 0)") {
    const Canvas c(10, 20);
    const Color red(1.f, 0.f, 0.f);
    WHEN("c.write_pixel(2, 3, red)") {
      const auto c2 = [c = c, &red]() mutable {
        c.write_pixel(2, 3, red);
        return c;
      }();
      THEN("c.pixel_at(2, 3) = red") { REQUIRE(c2.pixel_at(2, 3) == red); }
    }
  }
}

SCENARIO("Constructing the PPM header") {
  GIVEN("c <- Canvas(5, 3)") {
    const Canvas c(5, 3);
    WHEN("ppm <- c.to_ppm()") {
      const std::string ppm = c.to_ppm();

      THEN(R"(lines 1-3 of ppm are: 
            """
            P3
            5 3
            255
            """)") {
        const std::string ppm_header("P3\n5 3\n255");
        REQUIRE(std::equal(ppm_header.begin(), ppm_header.end(), ppm.begin()));
      }
    }
  }
}

SCENARIO("Constructing the PPM pixel data") {
  GIVEN("c <- Canvas(5, 3)")
  AND_GIVEN("c1 <- Color(1.5f, 0.f, 0.f)")
  AND_GIVEN("c2 <- Color(0.f, 0.5f, 0.f)")
  AND_GIVEN("c3 <- Color(-0.5f, 0.f, 1.f)") {
    Canvas c(5, 3);
    const Color c1(1.5f, 0.f, 0.f);
    const Color c2(0.f, 0.5f, 0.f);
    const Color c3(-0.5f, 0.f, 1.f);
    WHEN("c.write_pixel(0, 0, c1)")
    AND_WHEN("c.write_pixel(2, 1, c1)")
    AND_WHEN("c.write_pixel(4, 2, c1)")
    AND_WHEN("ppm <- c.to_ppm()") {
      c.write_pixel(0, 0, c1);
      c.write_pixel(2, 1, c2);
      c.write_pixel(4, 2, c3);
      const std::string ppm = c.to_ppm();

      THEN(R"(lines 4-6 of ppm are: 
            """
            255 0 0 0 0 0 0 0 0 0 0 0 0 0 0
            0 0 0 0 0 0 0 128 0 0 0 0 0 0 0
            0 0 0 0 0 0 0 0 0 0 0 0 0 0 255
            """
            )") {
        const std::string expected_payload(
            "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
            "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n"
            "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n");

        REQUIRE(c.ppm_payload() == expected_payload);
        REQUIRE(ppm == c.ppm_header() + expected_payload);
      }
    }
  }
}

SCENARIO("Splitting long lines in PPM files") {
  GIVEN("c <- Canvas(10, 2)") {
    Canvas c(10, 2);
    WHEN("Every pixel of c is set to Color(1, 0.8, 0.6)")
    AND_WHEN("ppm <- c.to_ppm()") {
      for (auto& row : c.pixels()) {
        for (auto& color : row) {
          color = Color(1.f, 0.8f, 0.6f);
        }
      }
      const std::string ppm = c.to_ppm();
      THEN(R"(lines 4-7 of ppm are: 
            """
            255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204
            153 255 204 153 255 204 153 255 204 153 255 204 153
            255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204
            153 255 204 153 255 204 153 255 204 153 255 204 153
            """
            )") {
        const std::string expected_payload(
            "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 "
            "204\n"
            "153 255 204 153 255 204 153 255 204 153 255 204 153\n"
            "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 "
            "204\n"
            "153 255 204 153 255 204 153 255 204 153 255 204 153\n");

        REQUIRE(c.ppm_payload() == expected_payload);
        REQUIRE(ppm == c.ppm_header() + expected_payload);
      }
    }
  }
}

SCENARIO("PPM files are terminated by a newline character") {
  GIVEN("c <- Canvas(5, 3)") {
    const Canvas c(5, 3);
    WHEN("ppm <- c.to_ppm()") {
      const std::string ppm = c.to_ppm();
      THEN("ppm ends with a newline character") { REQUIRE(ppm.back() == '\n'); }
    }
  }
}