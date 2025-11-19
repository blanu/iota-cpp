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

  REQUIRE(evalExpression({"0"s, form, {0}}) == a{0});
  REQUIRE(evalExpression({"0"s, form, {0.0f}}) == a{0.0f});
  REQUIRE(evalExpression({"0"s, form, {0, 0.0f}}) == a{0, 0.0f});
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

TEST_CASE("form integer - 32-bit boundaries", "[dyad]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // INT_MAX fits in int
  REQUIRE(evalExpression({"2147483647"s, form, 0}) == 2147483647);

  // INT_MIN requires BigNumber (can't write as literal)
  auto min_result = evalExpression({"-2147483648"s, form, 0});
  REQUIRE(std::holds_alternative<BigNumber>(min_result));
}

TEST_CASE("form integer - just beyond 32-bit (BigNumber)", "[dyad]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // 2^31 = 2147483648 (one more than INT_MAX)
  auto result1 = evalExpression({"2147483648"s, form, 0});
  REQUIRE(std::holds_alternative<BigNumber>(result1));

  // -2^31 - 1 = -2147483649 (one less than INT_MIN)
  auto result2 = evalExpression({"-2147483649"s, form, 0});
  REQUIRE(std::holds_alternative<BigNumber>(result2));
}

TEST_CASE("form integer - 33-bit values", "[dyad]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // 2^33 = 8589934592
  auto result = evalExpression({"8589934592"s, form, 0});
  REQUIRE(std::holds_alternative<BigNumber>(result));
}

TEST_CASE("form integer - 64-bit values", "[dyad]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // 2^63 - 1 (max signed 64-bit)
  auto result1 = evalExpression({"9223372036854775807"s, form, 0});
  REQUIRE(std::holds_alternative<BigNumber>(result1));

  // 2^64 - 1 (max unsigned 64-bit)
  auto result2 = evalExpression({"18446744073709551615"s, form, 0});
  REQUIRE(std::holds_alternative<BigNumber>(result2));
}

TEST_CASE("form integer - very large values", "[dyad]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // The example from the original issue: 29 digits
  auto result = evalExpression({"10101010101010101001010101010"s, form, 0});
  REQUIRE(std::holds_alternative<BigNumber>(result));
}
