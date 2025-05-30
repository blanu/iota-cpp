//
// Created by Dr. Brandon Wiley on 4/7/25.
//

#include <catch2/catch_all.hpp>

#include "api.h"

TEST_CASE("enumerate integer", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({5, enumerate}) == a{1, 2, 3, 4, 5});
}
