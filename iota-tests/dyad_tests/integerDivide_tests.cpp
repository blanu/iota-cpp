//
// Created by Dr. Brandon Wiley on 4/18/25.
//

#include <string>
#include <catch2/catch_all.hpp>

#include "api.h"
#include <iostream>

TEST_CASE("integerDivide integer integer", "[dyad]")
{
  using namespace iota;

  REQUIRE(evalExpression({1, integerDivide, 1}) == 1);
  REQUIRE(evalExpression({2, integerDivide, 1}) == 2);
  REQUIRE(evalExpression({1, integerDivide, 2}) == 0);
}

TEST_CASE("integerDivide Word / Word - basic cases", "[dyad][integerDivide]")
{
  using namespace iota;

  REQUIRE(evalExpression({1, integerDivide, 1}) == 1);
  REQUIRE(evalExpression({2, integerDivide, 1}) == 2);
  REQUIRE(evalExpression({1, integerDivide, 2}) == 0);
  REQUIRE(evalExpression({10, integerDivide, 3}) == 3);
  REQUIRE(evalExpression({10, integerDivide, 5}) == 2);
  REQUIRE(evalExpression({100, integerDivide, 10}) == 10);
  REQUIRE(evalExpression({0, integerDivide, 1}) == 0);
  REQUIRE(evalExpression({0, integerDivide, 100}) == 0);
}

TEST_CASE("integerDivide Word / Word - negative operands", "[dyad][integerDivide]")
{
  using namespace iota;

  REQUIRE(evalExpression({-10, integerDivide, 3}) == -3);
  REQUIRE(evalExpression({10, integerDivide, -3}) == -3);
  REQUIRE(evalExpression({-10, integerDivide, -3}) == 3);
  REQUIRE(evalExpression({-1, integerDivide, 1}) == -1);
  REQUIRE(evalExpression({1, integerDivide, -1}) == -1);
  REQUIRE(evalExpression({-1, integerDivide, -1}) == 1);
}

TEST_CASE("integerDivide Word / Word - division by zero error", "[dyad][integerDivide]")
{
  using namespace iota;

  auto result = evalExpressionCppToIota({1, integerDivide, 0});
  REQUIRE(result.o == NounType::ERROR);

  auto result2 = evalExpressionCppToIota({100, integerDivide, 0});
  REQUIRE(result2.o == NounType::ERROR);
}

TEST_CASE("integerDivide Word / Word - at INT_MAX boundary", "[dyad][integerDivide]")
{
  using namespace iota;

  // INT_MAX / 1 = INT_MAX
  REQUIRE(evalExpression({2147483647, integerDivide, 1}) == 2147483647);

  // INT_MAX / 2 = 1073741823
  REQUIRE(evalExpression({2147483647, integerDivide, 2}) == 1073741823);

  // INT_MAX / INT_MAX = 1
  REQUIRE(evalExpression({2147483647, integerDivide, 2147483647}) == 1);
}

TEST_CASE("integerDivide Word / Word - at INT_MIN boundary", "[dyad][integerDivide]")
{
  using namespace iota;

  // INT_MIN / 1 = INT_MIN
  REQUIRE(evalExpression({INT_MIN, integerDivide, 1}) == INT_MIN);

  // INT_MIN / 2 = -1073741824
  REQUIRE(evalExpression({INT_MIN, integerDivide, 2}) == -1073741824);

  // INT_MIN / -1 overflows to WordArray (result would be 2^31)
  auto result = evalExpressionCppToIota({INT_MIN, integerDivide, -1});
  REQUIRE(result.t == StorageType::WORD_ARRAY);
  REQUIRE(result.o == NounType::INTEGER);
}

TEST_CASE("integerDivide WordArray / Word - result fits in Word", "[dyad][integerDivide]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // 10000000000 / 10 = 1000000000 (fits in Word)
  auto big = evalExpressionCppToIota({"10000000000"s, form, 0});
  auto result = evalExpression({big, integerDivide, 10});
  REQUIRE(std::holds_alternative<int>(result));
  REQUIRE(result == 1000000000);

  // 5000000000 / 5 = 1000000000
  auto big2 = evalExpressionCppToIota({"5000000000"s, form, 0});
  auto result2 = evalExpression({big2, integerDivide, 5});
  REQUIRE(std::holds_alternative<int>(result2));
  REQUIRE(result2 == 1000000000);
}

TEST_CASE("integerDivide WordArray / Word - result stays WordArray", "[dyad][integerDivide]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // 10000000000 / 2 = 5000000000 (stays WordArray)
  auto big = evalExpressionCppToIota({"10000000000"s, form, 0});
  auto result = evalExpressionCppToIota({big, integerDivide, 2});
  REQUIRE(result.t == StorageType::WORD_ARRAY);
  REQUIRE(result.o == NounType::INTEGER);

  // 100000000000 / 10 = 10000000000
  auto big2 = evalExpressionCppToIota({"100000000000"s, form, 0});
  auto result2 = evalExpressionCppToIota({big2, integerDivide, 10});
  REQUIRE(result2.t == StorageType::WORD_ARRAY);
  REQUIRE(result2.o == NounType::INTEGER);
}

TEST_CASE("integerDivide WordArray / Word - result is zero", "[dyad][integerDivide]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // 100 (as WordArray) / 1000 = 0
  auto big = evalExpressionCppToIota({"100"s, form, 0});
  auto result = evalExpression({big, integerDivide, 1000});
  REQUIRE(std::holds_alternative<int>(result));
  REQUIRE(result == 0);
}

TEST_CASE("integerDivide Word / WordArray - result is zero", "[dyad][integerDivide]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // 100 / 10000000000 = 0
  auto big = evalExpressionCppToIota({"10000000000"s, form, 0});
  auto result = evalExpression({100, integerDivide, big});
  REQUIRE(std::holds_alternative<int>(result));
  REQUIRE(result == 0);

  // 1000000 / 10000000000 = 0
  auto result2 = evalExpression({1000000, integerDivide, big});
  REQUIRE(std::holds_alternative<int>(result2));
  REQUIRE(result2 == 0);
}

TEST_CASE("integerDivide Word / WordArray - result fits in Word", "[dyad][integerDivide]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // 10000000000 / 10000000000 = 1
  auto big_divisor = evalExpressionCppToIota({"10000000000"s, form, 0});
  auto big_dividend = evalExpressionCppToIota({"10000000000"s, form, 0});
  auto result = evalExpression({big_dividend, integerDivide, big_divisor});
  REQUIRE(std::holds_alternative<int>(result));
  REQUIRE(result == 1);

  // Also test: 2147483647 (max int) / large WordArray that equals it = 1
  auto big2 = evalExpressionCppToIota({"2147483647"s, form, 0});
  auto result2 = evalExpression({2147483647, integerDivide, big2});
  REQUIRE(std::holds_alternative<int>(result2));
  REQUIRE(result2 == 1);
}

TEST_CASE("integerDivide WordArray / WordArray - both positive", "[dyad][integerDivide]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // 15000000000 / 3000000000 = 5
  auto big1 = evalExpressionCppToIota({"15000000000"s, form, 0});
  auto big2 = evalExpressionCppToIota({"3000000000"s, form, 0});
  auto result = evalExpression({big1, integerDivide, big2});
  REQUIRE(std::holds_alternative<int>(result));
  REQUIRE(result == 5);

  // 10000000000 / 5000000000 = 2
  auto big3 = evalExpressionCppToIota({"10000000000"s, form, 0});
  auto big4 = evalExpressionCppToIota({"5000000000"s, form, 0});
  auto result2 = evalExpression({big3, integerDivide, big4});
  REQUIRE(std::holds_alternative<int>(result2));
  REQUIRE(result2 == 2);
}

TEST_CASE("integerDivide WordArray / WordArray - with negatives", "[dyad][integerDivide]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // -15000000000 / 3000000000 = -5
  auto big1 = evalExpressionCppToIota({"-15000000000"s, form, 0});
  auto big2 = evalExpressionCppToIota({"3000000000"s, form, 0});
  auto result = evalExpression({big1, integerDivide, big2});
  REQUIRE(std::holds_alternative<int>(result));
  REQUIRE(result == -5);

  // 15000000000 / -3000000000 = -5
  auto big3 = evalExpressionCppToIota({"15000000000"s, form, 0});
  auto big4 = evalExpressionCppToIota({"-3000000000"s, form, 0});
  auto result2 = evalExpression({big3, integerDivide, big4});
  REQUIRE(std::holds_alternative<int>(result2));
  REQUIRE(result2 == -5);

  // -15000000000 / -3000000000 = 5
  auto big5 = evalExpressionCppToIota({"-15000000000"s, form, 0});
  auto big6 = evalExpressionCppToIota({"-3000000000"s, form, 0});
  auto result3 = evalExpression({big5, integerDivide, big6});
  REQUIRE(std::holds_alternative<int>(result3));
  REQUIRE(result3 == 5);
}

TEST_CASE("integerDivide WordArray / WordArray - result is WordArray", "[dyad][integerDivide]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // Very large dividend / small divisor
  // 100000000000000000 / 2 = 50000000000000000
  auto big1 = evalExpressionCppToIota({"100000000000000000"s, form, 0});
  auto result = evalExpressionCppToIota({big1, integerDivide, 2});
  REQUIRE(result.t == StorageType::WORD_ARRAY);
  REQUIRE(result.o == NounType::INTEGER);
}

TEST_CASE("integerDivide WordArray / WordArray - equal values", "[dyad][integerDivide]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // 9876543210 / 9876543210 = 1
  auto big = evalExpressionCppToIota({"9876543210"s, form, 0});
  auto result = evalExpression({big, integerDivide, big});
  REQUIRE(std::holds_alternative<int>(result));
  REQUIRE(result == 1);
}

TEST_CASE("integerDivide - repeated division by 10 (for decimal conversion)", "[dyad][integerDivide]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // Test the pattern used for decimal string conversion
  // 12345 / 10 = 1234
  auto big = evalExpressionCppToIota({"12345"s, form, 0});
  auto result1 = evalExpression({big, integerDivide, 10});
  REQUIRE(std::holds_alternative<int>(result1));
  REQUIRE(result1 == 1234);

  // 1234 / 10 = 123
  auto result2 = evalExpression({result1, integerDivide, 10});
  REQUIRE(std::holds_alternative<int>(result2));
  REQUIRE(result2 == 123);

  // 123 / 10 = 12
  auto result3 = evalExpression({result2, integerDivide, 10});
  REQUIRE(std::holds_alternative<int>(result3));
  REQUIRE(result3 == 12);

  // 12 / 10 = 1
  auto result4 = evalExpression({result3, integerDivide, 10});
  REQUIRE(std::holds_alternative<int>(result4));
  REQUIRE(result4 == 1);

  // 1 / 10 = 0
  auto result5 = evalExpression({result4, integerDivide, 10});
  REQUIRE(std::holds_alternative<int>(result5));
  REQUIRE(result5 == 0);
}

TEST_CASE("integerDivide - large number divided by 10", "[dyad][integerDivide]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // 10000000000 / 10 = 1000000000
  auto big = evalExpressionCppToIota({"10000000000"s, form, 0});
  auto result = evalExpression({big, integerDivide, 10});

  std::cout << "result variant index: " << result.index() << std::endl;
  if(std::holds_alternative<Storage>(result)) {
    Storage s = std::get<Storage>(result);
    std::cout << "Storage t=" << s.t << " o=" << s.o << std::endl;
    if(std::holds_alternative<ints>(s.i)) {
      ints chunks = std::get<ints>(s.i);
      std::cout << "WordArray chunks: ";
      for(int c : chunks) std::cout << c << " ";
      std::cout << std::endl;
    }
  }

  REQUIRE(std::holds_alternative<int>(result));
  REQUIRE(result == 1000000000);
}

TEST_CASE("integerDivide WordArray / Word - negative dividend", "[dyad][integerDivide]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // -10000000000 / 10 = -1000000000
  auto big = evalExpressionCppToIota({"-10000000000"s, form, 0});
  auto result = evalExpression({big, integerDivide, 10});
  REQUIRE(std::holds_alternative<int>(result));
  REQUIRE(result == -1000000000);
}

TEST_CASE("integerDivide - dividend smaller than divisor", "[dyad][integerDivide]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // 5 / 10 = 0
  REQUIRE(evalExpression({5, integerDivide, 10}) == 0);

  // 1000000000 / 10000000000 = 0
  auto big = evalExpressionCppToIota({"10000000000"s, form, 0});
  auto result = evalExpression({1000000000, integerDivide, big});

  std::cout << "result variant index: " << result.index() << std::endl;
  if(std::holds_alternative<int>(result)) {
    std::cout << "int value: " << std::get<int>(result) << std::endl;
  } else if(std::holds_alternative<BigNumber>(result)) {
    BigNumber bn = std::get<BigNumber>(result);
    char* str = bn.toString();
    std::cout << "BigNumber value: " << (str ? str : "null") << std::endl;
  }

  REQUIRE(std::holds_alternative<int>(result));
  REQUIRE(result == 0);
}

TEST_CASE("integerDivide - division by one", "[dyad][integerDivide]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // Any number / 1 = itself
  REQUIRE(evalExpression({42, integerDivide, 1}) == 42);
  REQUIRE(evalExpression({-42, integerDivide, 1}) == -42);

  auto big = evalExpressionCppToIota({"9876543210"s, form, 0});
  auto result = evalExpressionCppToIota({big, integerDivide, 1});
  REQUIRE(result.t == StorageType::WORD_ARRAY);
  REQUIRE(result.o == NounType::INTEGER);
}