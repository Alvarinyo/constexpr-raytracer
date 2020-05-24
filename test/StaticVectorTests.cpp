#include <algorithm>
#include <catch2/catch.hpp>

#include "../src/StaticVector.hpp"

TEST_CASE("creating StaticVector") {
  constexpr StaticVector<int, 100> v = {5, 7, 9};

  STATIC_REQUIRE(v[0] == 5);
  STATIC_REQUIRE(v[1] == 7);
  STATIC_REQUIRE(v[2] == 9);
  STATIC_REQUIRE(v.back() == 9);
  STATIC_REQUIRE(v.size() == 3);
  STATIC_REQUIRE(v.capacity() == 100);

  SECTION("other constructors of StaticVector") {
    constexpr StaticVector<int, 100> v2(3);
    STATIC_REQUIRE(v2.size() == 3);
    STATIC_REQUIRE(std::equal(v2.begin(), v2.end(), std::begin({0, 0, 0})));
  }

  SECTION("pushing values to StaticVector") {
    constexpr auto v2 = [v = v]() mutable {
      v.push_back(11);
      v.push_back(13);
      return v;
    }();
    STATIC_REQUIRE(std::equal(v.begin(), v.end(), v2.begin()));
    STATIC_REQUIRE(v2[3] == 11);
    STATIC_REQUIRE(v2[4] == 13);
    STATIC_REQUIRE(v2.back() == v2[4]);
    STATIC_REQUIRE(v2.size() == 5);
  }

  SECTION("popping values from StaticVector") {
    constexpr auto v2 = [v = v]() mutable {
      v.pop_back();
      v.pop_back();
      return v;
    }();
    STATIC_REQUIRE(std::equal(v2.begin(), v2.end(), v.begin()));
    STATIC_REQUIRE(v2.size() == 1);
  }

  SECTION("pushing and popping values from StaticVector") {
    constexpr auto v2 = [v = v]() mutable {
      v.pop_back();
      v.push_back(50);
      v.push_back(60);
      v.pop_back();
      return v;
    }();
    STATIC_REQUIRE(v2[0] == 5);
    STATIC_REQUIRE(v2[1] == 7);
    STATIC_REQUIRE(v2[2] == 50);
    STATIC_REQUIRE(v2.size() == 3);
  }
}