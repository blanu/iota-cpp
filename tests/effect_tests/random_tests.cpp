//
// Created by Dr. Brandon Wiley on 4/24/25.
//

#include <string>
#include <catch2/catch_all.hpp>

#include "api.h"

#include "../../libraries/iota-cpp/src/effects/testing/testing_effects_register.h"
#include "effects/testing/log/log.h"

TEST_CASE("roll", "[effect]")
{
  using namespace iota;
  using namespace std::string_literals;

  auto effects_register = TestingEffectsRegister();
  evalExpressionForEffects({CppValues{}, cause, CppValues{10, roll}}, &effects_register);
  Storage effects = effects_register.getEffectState();
  cppValue result = Object::to_cpp(effects);

  REQUIRE(std::holds_alternative<int>(result));
  int integer = std::get<int>(result);
  
  REQUIRE(integer > 0);
  REQUIRE(integer <= 10);
}
