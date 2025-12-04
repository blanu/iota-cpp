//
// Created by Dr. Brandon Wiley on 12/3/25.
//

#include <catch2/catch_all.hpp>

#include <string>

#include "api.h"

TEST_CASE("split string character", "[dyad]")
{
  using namespace std::literals::string_literals;
  using namespace iota;
  using iota::split;

  auto result = evalExpression({"abc def"s, split, ' '});
  REQUIRE(result == a{"abc"s, "def"s});
}