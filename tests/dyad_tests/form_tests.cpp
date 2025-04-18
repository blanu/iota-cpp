//
// Created by Dr. Brandon Wiley on 4/18/25.
//

#include <string>
#include <catch2/catch_all.hpp>

#include "api.h"

TEST_CASE("form ref", "[dyad]")
{
  using namespace iota;
  using namespace std::literals::string_literals; // This allows std::string literals using "value"s.

  REQUIRE(evalExpression({"-123"s, form, 1}) == -123);
  REQUIRE(evalExpression({"1.23"s, form, 1.0f}) == 1.23f);
  REQUIRE(evalExpression({"x"s, form, 'x'}) == 'x');
  REQUIRE(evalExpression({"string"s, form, ""s}) == "string"s);
  // FIXME - symbols
}

TEST_CASE("form integer", "[dyad]")
{
  using namespace iota;
  using namespace std::literals::string_literals; // This allows std::string literals using "value"s.

  REQUIRE(evalExpression({"0"s, form, 0}) == 0);
  REQUIRE(evalExpression({"1"s, form, 0}) == 1);
  REQUIRE(evalExpression({"-1"s, form, 0}) == -1);
}

TEST_CASE("form real", "[dyad]")
{
  using namespace iota;
  using namespace std::literals::string_literals; // This allows std::string literals using "value"s.

  REQUIRE(evalExpression({"0"s, form, 0.0f}) == 0.0f);
  REQUIRE(evalExpression({"1"s, form, 0.0f}) == 1.0f);
  REQUIRE(evalExpression({"-1"s, form, 0.0f}) == -1.0f);
  REQUIRE(evalExpression({"0.0"s, form, 0.0f}) == 0.0f);
  REQUIRE(evalExpression({"1.0"s, form, 0.0f}) == 1.0f);
  REQUIRE(evalExpression({"-1.0"s, form, 0.0f}) == -1.0f);
}

TEST_CASE("form list", "[dyad]")
{
  using namespace iota;
  using namespace std::literals::string_literals; // This allows std::string literals using "value"s.

  REQUIRE(evalExpression({"0"s, form, ints{0}}) == ints{0});
  REQUIRE(evalExpression({"0"s, form, floats{0.0f}}) == floats{0.0f});
  REQUIRE(evalExpression({"0"s, form, CppValues{0, 0.0f}}) == CppValues{0, 0.0f});
}

TEST_CASE("form character", "[dyad]")
{
  using namespace iota;
  using namespace std::literals::string_literals; // This allows std::string literals using "value"s.

  REQUIRE(evalExpression({"a"s, form, 'a'}) == 'a');
}

TEST_CASE("form string", "[dyad]")
{
  using namespace iota;
  using namespace std::literals::string_literals; // This allows std::string literals using "value"s.

  REQUIRE(evalExpression({"a"s, form, ""s}) == "a"s);
  REQUIRE(evalExpression({"ab"s, form, ""s}) == "ab"s);
}


// FIXME - symbol test case