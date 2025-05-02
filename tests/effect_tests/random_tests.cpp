//
// Created by Dr. Brandon Wiley on 4/24/25.
//

#include <string>
#include <catch2/catch_all.hpp>

#include "api.h"

#include "../../libraries/iota-cpp/src/effects/testing/testing_effects_register.h"

TEST_CASE("roll", "[effect]")
{
  using namespace iota;
  using namespace std::string_literals;

  auto effects_register = TestingEffectsRegister();
  cppValue result = evalExpressionWithEffects({{10, roll}, bind, negate}, &effects_register);

  REQUIRE(result == -9); // For the TESTING random number generator, a static seed is used, so we will always get the same number. A different test is required for production.
}

TEST_CASE("rolls", "[effect]")
{
  using namespace iota;
  using namespace std::string_literals;

  auto effects_register = TestingEffectsRegister();
  cppValue result = evalExpressionWithEffects({{10, rolls, 2}, bind, negate}, &effects_register);

  REQUIRE(result == a{-9, -3}); // For the TESTING random number generator, a static seed is used, so we will always get the same number. A different test is required for production.
}

TEST_CASE("deal", "[effect]")
{
  using namespace iota;
  using namespace std::string_literals;

  auto effects_register = TestingEffectsRegister();
  cppValue result = evalExpressionWithEffects({{{1, 2, 3}, deal, 0}, bind, negate}, &effects_register);

  REQUIRE(result == a{-1, -1, -3}); // For the TESTING random number generator, a static seed is used, so we will always get the same number. A different test is required for production.
}