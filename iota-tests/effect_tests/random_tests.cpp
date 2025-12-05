//
// Created by Dr. Brandon Wiley on 4/24/25.
//

#include <string>
#include <catch2/catch_all.hpp>

#include "api.h"

TEST_CASE("random", "[effect]")
{
  using namespace iota;
  using namespace std::string_literals;

  REQUIRE(evalExpression({iota::random, iota::floor}) == 0); // For the TESTING random number generator, a static seed is used, so we will always get the same number. A different test is required for production.
}

TEST_CASE("roll", "[effect]")
{
  using namespace iota;
  using namespace std::string_literals;

  REQUIRE(evalExpression({10, roll, negate}) == -8); // For the TESTING random number generator, a static seed is used, so we will always get the same number. A different test is required for production.
}

TEST_CASE("rolls", "[effect]")
{
  using namespace iota;
  using namespace std::string_literals;

  REQUIRE(evalExpression({10, rolls, 2, negate}) == a{-5, -4}); // For the TESTING random number generator, a static seed is used, so we will always get the same number. A different test is required for production.
}

TEST_CASE("deal", "[effect]")
{
  using namespace iota;
  using namespace std::string_literals;

  REQUIRE(evalExpression({{1, 2, 3}, deal, 0, negate}) == a{-1, -1, -3}); // For the TESTING random number generator, a static seed is used, so we will always get the same number. A different test is required for production.
}