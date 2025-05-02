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
  Storage effectResult = evalExpressionWithEffects({{10, roll}, bind, negate}, &effects_register);
  cppValue result = Object::to_cpp(effectResult);

  REQUIRE(std::holds_alternative<int>(result));
  int integer = std::get<int>(result);
  
  REQUIRE(integer == -7); // For the TESTING random number generator, a static seed is used, so we will always get the same number. A different test is required for production.
}
