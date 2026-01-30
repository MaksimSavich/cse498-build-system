#include <catch2/catch_test_macros.hpp>

#include "math_utils.hpp"

TEST_CASE("add function", "[add]") {
  SECTION("adds two positive numbers") { REQUIRE(add(2, 3) == 5); }

  SECTION("adds negative numbers") { REQUIRE(add(-2, -3) == -5); }

  SECTION("adds zero") { REQUIRE(add(0, 5) == 5); }
}

TEST_CASE("multiply function", "[multiply]") {
  SECTION("multiplies two positive numbers") { REQUIRE(multiply(2, 3) == 6); }

  SECTION("multiplies by zero") { REQUIRE(multiply(5, 0) == 0); }

  SECTION("multiplies negative numbers") { REQUIRE(multiply(-2, 3) == -6); }
}

TEST_CASE("factorial function", "[factorial]") {
  SECTION("factorial of 0 is 1") { REQUIRE(factorial(0) == 1); }

  SECTION("factorial of 5 is 120") { REQUIRE(factorial(5) == 120); }

  SECTION("factorial of 1 is 1") { REQUIRE(factorial(1) == 1); }
}
