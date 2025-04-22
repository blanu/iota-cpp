//
// Created by Dr. Brandon Wiley on 4/18/25.
//

#include <string>
#include <catch2/catch_all.hpp>

#include "api.h"

#include "../../libraries/iota-cpp/src/effects/testing/testing_effects_register.h"

TEST_CASE("log string", "[effect]")
{
  using namespace iota;
  using namespace std::string_literals;

  auto effects_register = TestingEffectsRegister();
  evalExpressionForEffects({ints{}, cause, CppValues{"test"s, info}}, &effects_register);
  Storage effects = effects_register.getEffectState();
  cppValue result = Object::to_cpp(effects);
  REQUIRE(result == CppValues{"test"s});
}
