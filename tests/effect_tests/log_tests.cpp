//
// Created by Dr. Brandon Wiley on 4/18/25.
//

#include <string>
#include <catch2/catch_all.hpp>

#include "api.h"

#include "../../libraries/iota-cpp/src/effects/testing/testing_effects_register.h"
#include "effects/testing/log/log.h"

TEST_CASE("critical string", "[effect]")
{
  using namespace iota;
  using namespace std::string_literals;

  auto effects_register = TestingEffectsRegister();
  evalExpressionForEffects({ints{}, cause, CppValues{"test"s, critical}}, &effects_register);
  Storage effects = effects_register.getEffectState();
  cppValue result = Object::to_cpp(effects);

  REQUIRE(result == CppValues{"test"s});
}

TEST_CASE("warning string", "[effect]")
{
  using namespace iota;
  using namespace std::string_literals;

  auto effects_register = TestingEffectsRegister();
  evalExpressionForEffects({ints{}, cause, CppValues{"test"s, warning}}, &effects_register);
  Storage effects = effects_register.getEffectState();
  cppValue result = Object::to_cpp(effects);

  REQUIRE(result == CppValues{"test"s});
}

TEST_CASE("error string", "[effect]")
{
  using namespace iota;
  using namespace std::string_literals;

  auto effects_register = TestingEffectsRegister();
  evalExpressionForEffects({ints{}, cause, CppValues{"test"s, error}}, &effects_register);
  Storage effects = effects_register.getEffectState();
  cppValue result = Object::to_cpp(effects);

  REQUIRE(result == CppValues{"test"s});
}

TEST_CASE("log level filtering", "[effect]")
{
  using namespace iota;
  using namespace std::string_literals;

  auto effects_register = TestingEffectsRegister();
  evalExpressionForEffects({ints{}, cause, CppValues{"test"s, trace}}, &effects_register);
  Storage effects = effects_register.getEffectState();
  cppValue result = Object::to_cpp(effects);

  REQUIRE(result == CppValues{});
}

TEST_CASE("log level setting", "[effect]")
{
  using namespace iota;
  using namespace std::string_literals;

  auto effects_register = TestingEffectsRegister();
  evalExpressionForEffects({ints{}, cause, CppValues{Log::Levels::debug, level}, then, CppValues{"test"s, debug}}, &effects_register);
  Storage effects = effects_register.getEffectState();
  cppValue result = Object::to_cpp(effects);

  REQUIRE(result == CppValues{"test"s});
}