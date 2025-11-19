//
// Created by Dr. Brandon Wiley on 11/18/25.
//

#include <string>
#include <catch2/catch_all.hpp>
#include "api.h"

TEST_CASE("plus Word + Word - no overflow", "[dyad][plus]")
{
  using namespace iota;

  REQUIRE(evalExpression({5, plus, 3}) == 8);
  REQUIRE(evalExpression({100, plus, 200}) == 300);
  REQUIRE(evalExpression({-5, plus, 3}) == -2);
  REQUIRE(evalExpression({5, plus, -3}) == 2);
  REQUIRE(evalExpression({-5, plus, -3}) == -8);
  REQUIRE(evalExpression({0, plus, 0}) == 0);
  REQUIRE(evalExpression({0, plus, 42}) == 42);
  REQUIRE(evalExpression({42, plus, 0}) == 42);
}

TEST_CASE("plus Word + Word - at INT_MAX boundary", "[dyad][plus]")
{
  using namespace iota;

  // INT_MAX = 2147483647
  REQUIRE(evalExpression({2147483647, plus, 0}) == 2147483647);
  REQUIRE(evalExpression({2147483646, plus, 1}) == 2147483647);
  REQUIRE(evalExpression({1000000000, plus, 1147483647}) == 2147483647);
}

TEST_CASE("plus Word + Word - at INT_MIN boundary", "[dyad][plus]")
{
  using namespace iota;

  // INT_MIN = -2147483648
  REQUIRE(evalExpression({INT_MIN, plus, 0}) == INT_MIN);
  REQUIRE(evalExpression({INT_MIN + 1, plus, -1}) == INT_MIN);
  REQUIRE(evalExpression({-1000000000, plus, -1147483648}) == INT_MIN);
}

TEST_CASE("plus Word + Word - positive overflow to WordArray", "[dyad][plus]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // INT_MAX + 1 = 2147483648 (requires WordArray)
  auto result1 = evalExpression({2147483647, plus, 1});
  REQUIRE(std::holds_alternative<BigNumber>(result1));

  // INT_MAX + INT_MAX = 4294967294
  auto result2 = evalExpression({2147483647, plus, 2147483647});
  REQUIRE(std::holds_alternative<BigNumber>(result2));

  // Large positive + large positive
  auto result3 = evalExpression({1500000000, plus, 1500000000});
  REQUIRE(std::holds_alternative<BigNumber>(result3));
}

TEST_CASE("plus Word + Word - negative overflow to WordArray", "[dyad][plus]")
{
  using namespace iota;

  // INT_MIN + (-1) = -2147483649 (requires WordArray)
  auto result1 = evalExpression({INT_MIN, plus, -1});
  REQUIRE(std::holds_alternative<BigNumber>(result1));

  // INT_MIN + INT_MIN
  auto result2 = evalExpression({INT_MIN, plus, INT_MIN});
  REQUIRE(std::holds_alternative<BigNumber>(result2));

  // Large negative + large negative
  auto result3 = evalExpression({-1500000000, plus, -1500000000});
  REQUIRE(std::holds_alternative<BigNumber>(result3));
}

TEST_CASE("plus WordArray + Word - result fits in Word", "[dyad][plus]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // Create a WordArray, then add something that brings it back to Word range
  // 2147483648 + (-1) = 2147483647 (back to Word)
  auto big = evalExpressionCppToIota({"2147483648"s, form, 0});
  auto result = evalExpression({big, plus, -1});
  REQUIRE(std::holds_alternative<int>(result));
  REQUIRE(result == 2147483647);
}

TEST_CASE("plus WordArray + Word - result stays WordArray", "[dyad][plus]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // 2147483648 + 1 = 2147483649 (stays WordArray)
  auto big = evalExpression({"2147483648"s, form, 0});
  auto result = evalExpression({big, plus, 1});
  REQUIRE(std::holds_alternative<BigNumber>(result));

  // 5000000000 + 100 = 5000000100
  auto big2 = evalExpression({"5000000000"s, form, 0});
  auto result2 = evalExpression({big2, plus, 100});
  REQUIRE(std::holds_alternative<BigNumber>(result2));
}

TEST_CASE("plus Word + WordArray - result fits in Word", "[dyad][plus]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // Commutative test: -1 + 2147483648 = 2147483647
  auto big = evalExpressionCppToIota({"2147483648"s, form, 0});
  auto result = evalExpression({-1, plus, big});
  REQUIRE(std::holds_alternative<int>(result));
  REQUIRE(result == 2147483647);
}

TEST_CASE("plus Word + WordArray - result stays WordArray", "[dyad][plus]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // 100 + 5000000000 = 5000000100
  auto big = evalExpression({"5000000000"s, form, 0});
  auto result = evalExpression({100, plus, big});
  REQUIRE(std::holds_alternative<BigNumber>(result));
}

TEST_CASE("plus WordArray + WordArray - both same sign positive", "[dyad][plus]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // 5000000000 + 3000000000 = 8000000000
  auto big1 = evalExpression({"5000000000"s, form, 0});
  auto big2 = evalExpression({"3000000000"s, form, 0});
  auto result = evalExpression({big1, plus, big2});
  REQUIRE(std::holds_alternative<BigNumber>(result));
}

TEST_CASE("plus WordArray + WordArray - both same sign negative", "[dyad][plus]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // -5000000000 + (-3000000000) = -8000000000
  auto big1 = evalExpression({"-5000000000"s, form, 0});
  auto big2 = evalExpression({"-3000000000"s, form, 0});
  auto result = evalExpression({big1, plus, big2});
  REQUIRE(std::holds_alternative<BigNumber>(result));
}

TEST_CASE("plus WordArray + WordArray - different signs, result positive", "[dyad][plus]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // 5000000000 + (-3000000000) = 2000000000
  auto big1 = evalExpressionCppToIota({"5000000000"s, form, 0});
  auto big2 = evalExpressionCppToIota({"-3000000000"s, form, 0});
  auto result = evalExpression({big1, plus, big2});
  REQUIRE(std::holds_alternative<int>(result));
  REQUIRE(result == 2000000000);
}

TEST_CASE("plus WordArray + WordArray - different signs, result negative", "[dyad][plus]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // -5000000000 + 3000000000 = -2000000000
  auto big1 = evalExpressionCppToIota({"-5000000000"s, form, 0});
  auto big2 = evalExpressionCppToIota({"3000000000"s, form, 0});
  auto result = evalExpression({big1, plus, big2});
  REQUIRE(std::holds_alternative<int>(result));
  REQUIRE(result == -2000000000);
}

TEST_CASE("plus WordArray + WordArray - different signs, result zero", "[dyad][plus]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // 5000000000 + (-5000000000) = 0
  auto big1 = evalExpression({"5000000000"s, form, 0});
  auto big2 = evalExpression({"-5000000000"s, form, 0});
  auto result = evalExpression({big1, plus, big2});
  REQUIRE(std::holds_alternative<int>(result));
  REQUIRE(result == 0);
}

TEST_CASE("plus WordArray + WordArray - very large numbers", "[dyad][plus]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // 999999999999999999 + 1 = 1000000000000000000
  auto big1 = evalExpression({"999999999999999999"s, form, 0});
  auto result = evalExpression({big1, plus, 1});
  REQUIRE(std::holds_alternative<BigNumber>(result));

  // Two very large numbers
  auto big2 = evalExpression({"123456789012345678901234567890"s, form, 0});
  auto big3 = evalExpression({"987654321098765432109876543210"s, form, 0});
  auto result2 = evalExpression({big2, plus, big3});
  REQUIRE(std::holds_alternative<BigNumber>(result2));
}

TEST_CASE("plus - negative WordArray + positive Word crossing zero", "[dyad][plus]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // -2147483649 + 2147483649 = 0
  auto big = evalExpression({"-2147483649"s, form, 0});
  auto result = evalExpression({big, plus, 2147483649});
  REQUIRE(std::holds_alternative<int>(result));
  REQUIRE(result == 0);
}

TEST_CASE("plus - associativity with mixed types", "[dyad][plus]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // (Word + Word_overflow) + Word should equal Word + (Word_overflow + Word)
  auto big = evalExpression({2147483647, plus, 1}); // WordArray
  auto result1 = evalExpression({big, plus, 1});

  auto result2 = evalExpression({2147483647, plus, 2});

  REQUIRE(std::holds_alternative<BigNumber>(result1));
  REQUIRE(std::holds_alternative<BigNumber>(result2));
}

TEST_CASE("plus - zero identity with WordArray", "[dyad][plus]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  auto big = evalExpression({"9876543210"s, form, 0});

  auto result1 = evalExpression({big, plus, 0});
  REQUIRE(std::holds_alternative<BigNumber>(result1));

  auto result2 = evalExpression({0, plus, big});
  REQUIRE(std::holds_alternative<BigNumber>(result2));
}

TEST_CASE("plus - multiple precision chunks", "[dyad][plus]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // Numbers that require multiple 32-bit chunks (or whatever int size)
  // 2^40 = 1099511627776
  auto big1 = evalExpression({"1099511627776"s, form, 0});
  auto big2 = evalExpression({"1099511627776"s, form, 0});
  auto result = evalExpression({big1, plus, big2});
  REQUIRE(std::holds_alternative<BigNumber>(result));

  // Result should be 2^41 = 2199023255552
}