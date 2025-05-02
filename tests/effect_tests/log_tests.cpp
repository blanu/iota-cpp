//
// Created by Dr. Brandon Wiley on 4/18/25.
//

#include <string>
#include <catch2/catch_all.hpp>

#include "api.h"

#include "../../libraries/iota-cpp/src/effects/testing/testing_effects_register.h"
#include "effects/testing/log/log.h"

TEST_CASE("timestamp", "[effect]")
{
  using namespace iota;

  auto effects_register = TestingEffectsRegister();
  evalExpressionForEffects({nil, causes, timestamp}, &effects_register);
  Storage effects = effects_register.getEffectState();
  cppValue result = Object::to_cpp(effects);

  REQUIRE(std::holds_alternative<cppValues>(result));
  auto results = std::get<cppValues>(result);
  REQUIRE(results.size() == 3);

  cppValue value = results[1];
  REQUIRE(std::holds_alternative<cppValues>(value));

  auto values = std::get<cppValues>(value);
  REQUIRE(values.size() == 1);

  REQUIRE(std::holds_alternative<int>(values[0]));
  int timestamp = std::get<int>(values[0]);

  REQUIRE(timestamp > 0);
}

TEST_CASE("critical string, causes", "[effect]")
{
  using namespace iota;
  using namespace std::string_literals;

  auto effects_register = TestingEffectsRegister();
  evalExpressionForEffects({nil, causes, {"test"s, critical}}, &effects_register);
  Storage effects = effects_register.getEffectState();
  cppValue result = Object::to_cpp(effects);

  REQUIRE(result == a{"test"s});
}

TEST_CASE("warning string, because", "[effect]")
{
  using namespace iota;
  using namespace std::string_literals;

  auto effects_register = TestingEffectsRegister();
  evalExpressionForEffects({"test"s, warning, because, nil}, &effects_register);
  Storage effects = effects_register.getEffectState();
  cppValue result = Object::to_cpp(effects);

  REQUIRE(result == a{"test"s});
}

TEST_CASE("error string", "[effect]")
{
  using namespace iota;
  using namespace std::string_literals;

  auto effects_register = TestingEffectsRegister();
  evalExpressionForEffects({nil, causes, {"test"s, error}}, &effects_register);
  Storage effects = effects_register.getEffectState();
  cppValue result = Object::to_cpp(effects);

  REQUIRE(result == a{"test"s});
}

TEST_CASE("log level filtering", "[effect]")
{
  using namespace iota;
  using namespace std::string_literals;

  auto effects_register = TestingEffectsRegister();
  evalExpressionForEffects({nil, causes, {"test"s, trace}}, &effects_register);
  Storage effects = effects_register.getEffectState();
  cppValue result = Object::to_cpp(effects);

  REQUIRE(result == a{});
}

TEST_CASE("log level setting", "[effect]")
{
  using namespace iota;
  using namespace std::string_literals;

  auto effects_register = TestingEffectsRegister();
  evalExpressionForEffects({{}, causes, {Log::Levels::debug, level}, then, {"test"s, debug}}, &effects_register);
  Storage effects = effects_register.getEffectState();
  cppValue result = Object::to_cpp(effects);

  REQUIRE(result == a{"test"s});
}

TEST_CASE("log chaining", "[effect]")
{
  using namespace iota;
  using namespace std::string_literals;

  auto effects_register = TestingEffectsRegister();
  evalExpressionForEffects({{}, causes, {"test 1"s, warning}, then, {"test 2"s, warning}}, &effects_register);
  Storage effects = effects_register.getEffectState();
  cppValue result = Object::to_cpp(effects);

  REQUIRE(result == a{"test 1"s, "test 2"s});
}
