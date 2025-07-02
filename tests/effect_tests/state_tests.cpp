//
// Created by Dr. Brandon Wiley on 5/4/25.
//

#include <string>
#include <catch2/catch_all.hpp>

#include "api.h"

#include "../../libraries/iota-cpp/src/effects/testing/testing_effects_provider.h"
#include "nouns/lens.h"

TEST_CASE("state get", "[effect]")
{
  using namespace iota;
  using namespace std::string_literals;

  REQUIRE(evalExpression({get, atom}) == "empty"s);
}

TEST_CASE("state put get", "[effect]")
{
  using namespace iota;
  using namespace std::string_literals;

  REQUIRE(evalExpression({1, put, then, get, atom}) == 1);
}
