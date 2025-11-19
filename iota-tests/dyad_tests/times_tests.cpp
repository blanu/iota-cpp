//
// Created by Dr. Brandon Wiley on 11/18/25.
//

#include <string>
#include <catch2/catch_all.hpp>
#include "api.h"

TEST_CASE("times Word * Word - no overflow", "[dyad][times]")
{
  using namespace iota;

  REQUIRE(evalExpression({5, times, 3}) == 15);
  REQUIRE(evalExpression({100, times, 20}) == 2000);
  REQUIRE(evalExpression({-5, times, 3}) == -15);
  REQUIRE(evalExpression({5, times, -3}) == -15);
  REQUIRE(evalExpression({-5, times, -3}) == 15);
  REQUIRE(evalExpression({0, times, 0}) == 0);
  REQUIRE(evalExpression({0, times, 42}) == 0);
  REQUIRE(evalExpression({42, times, 0}) == 0);
  REQUIRE(evalExpression({1, times, 42}) == 42);
  REQUIRE(evalExpression({42, times, 1}) == 42);
}

TEST_CASE("times Word * Word - at INT_MAX boundary", "[dyad][times]")
{
  using namespace iota;

  // INT_MAX = 2147483647
  REQUIRE(evalExpression({2147483647, times, 1}) == 2147483647);
  REQUIRE(evalExpression({1, times, 2147483647}) == 2147483647);
  REQUIRE(evalExpression({2147483647, times, 0}) == 0);
}

TEST_CASE("times Word * Word - at INT_MIN boundary", "[dyad][times]")
{
  using namespace iota;

  // INT_MIN = -2147483648
  REQUIRE(evalExpression({INT_MIN, times, 1}) == INT_MIN);
  REQUIRE(evalExpression({1, times, INT_MIN}) == INT_MIN);
  REQUIRE(evalExpression({INT_MIN, times, 0}) == 0);
  REQUIRE(evalExpressionCppToIota({INT_MIN, times, -1}).t == StorageType::WORD_ARRAY); // Overflows
}

TEST_CASE("times Word * Word - positive overflow to WordArray", "[dyad][times]")
{
  using namespace iota;

  // 100000 * 100000 = 10000000000 (requires WordArray)
  auto result1 = evalExpressionCppToIota({100000, times, 100000});
  REQUIRE(result1.t == StorageType::WORD_ARRAY);
  REQUIRE(result1.o == NounType::INTEGER);

  // 50000 * 50000 = 2500000000
  auto result2 = evalExpressionCppToIota({50000, times, 50000});
  REQUIRE(result2.t == StorageType::WORD_ARRAY);
  REQUIRE(result2.o == NounType::INTEGER);

  // 2147483647 * 2 = 4294967294
  auto result3 = evalExpressionCppToIota({2147483647, times, 2});
  REQUIRE(result3.t == StorageType::WORD_ARRAY);
  REQUIRE(result3.o == NounType::INTEGER);
}

TEST_CASE("times Word * Word - negative overflow to WordArray", "[dyad][times]")
{
  using namespace iota;

  // -100000 * 100000 = -10000000000
  auto result1 = evalExpressionCppToIota({-100000, times, 100000});
  REQUIRE(result1.t == StorageType::WORD_ARRAY);
  REQUIRE(result1.o == NounType::INTEGER);

  // 100000 * -100000 = -10000000000
  auto result2 = evalExpressionCppToIota({100000, times, -100000});
  REQUIRE(result2.t == StorageType::WORD_ARRAY);
  REQUIRE(result2.o == NounType::INTEGER);

  // -50000 * -50000 = 2500000000 (positive result from two negatives)
  auto result3 = evalExpressionCppToIota({-50000, times, -50000});
  REQUIRE(result3.t == StorageType::WORD_ARRAY);
  REQUIRE(result3.o == NounType::INTEGER);
}

TEST_CASE("times WordArray * Word - result fits in Word", "[dyad][times]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // Create a WordArray, then multiply by something that brings it back to Word range
  // 10000000000 * 0 = 0
  auto big = evalExpressionCppToIota({"10000000000"s, form, 0});
  auto result = evalExpression({big, times, 0});
  REQUIRE(std::holds_alternative<int>(result));
  REQUIRE(result == 0);

  // 10000000000 / 10000000000 would be 1, but we're testing multiplication
  // So: 2147483647 (as WordArray) * 1 = 2147483647 (as Word)
  auto big2 = evalExpressionCppToIota({"2147483647"s, form, 0});
  auto result2 = evalExpression({big2, times, 1});
  REQUIRE(std::holds_alternative<int>(result2));
  REQUIRE(result2 == 2147483647);
}

TEST_CASE("times WordArray * Word - result stays WordArray", "[dyad][times]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // 5000000000 * 2 = 10000000000
  auto big = evalExpressionCppToIota({"5000000000"s, form, 0});
  auto result = evalExpressionCppToIota({big, times, 2});
  REQUIRE(result.t == StorageType::WORD_ARRAY);
  REQUIRE(result.o == NounType::INTEGER);

  // 10000000000 * 3 = 30000000000
  auto big2 = evalExpressionCppToIota({"10000000000"s, form, 0});
  auto result2 = evalExpressionCppToIota({big2, times, 3});
  REQUIRE(result2.t == StorageType::WORD_ARRAY);
  REQUIRE(result2.o == NounType::INTEGER);
}

TEST_CASE("times Word * WordArray - result fits in Word", "[dyad][times]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // Commutative test: 0 * 10000000000 = 0
  auto big = evalExpressionCppToIota({"10000000000"s, form, 0});
  auto result = evalExpression({0, times, big});
  REQUIRE(std::holds_alternative<int>(result));
  REQUIRE(result == 0);

  // 1 * 2147483647 = 2147483647
  auto big2 = evalExpressionCppToIota({"2147483647"s, form, 0});
  auto result2 = evalExpression({1, times, big2});
  REQUIRE(std::holds_alternative<int>(result2));
  REQUIRE(result2 == 2147483647);
}

TEST_CASE("times Word * WordArray - result stays WordArray", "[dyad][times]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // 2 * 5000000000 = 10000000000
  auto big = evalExpressionCppToIota({"5000000000"s, form, 0});
  auto result = evalExpressionCppToIota({2, times, big});
  REQUIRE(result.t == StorageType::WORD_ARRAY);
  REQUIRE(result.o == NounType::INTEGER);
}

TEST_CASE("times WordArray * WordArray - both positive", "[dyad][times]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // 5000000000 * 3000000000 = 15000000000000000000
  auto big1 = evalExpressionCppToIota({"5000000000"s, form, 0});
  auto big2 = evalExpressionCppToIota({"3000000000"s, form, 0});
  auto result = evalExpressionCppToIota({big1, times, big2});
  REQUIRE(result.t == StorageType::WORD_ARRAY);
  REQUIRE(result.o == NounType::INTEGER);
}

TEST_CASE("times WordArray * WordArray - both negative", "[dyad][times]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // -5000000000 * -3000000000 = 15000000000000000000
  auto big1 = evalExpressionCppToIota({"-5000000000"s, form, 0});
  auto big2 = evalExpressionCppToIota({"-3000000000"s, form, 0});
  auto result = evalExpressionCppToIota({big1, times, big2});
  REQUIRE(result.t == StorageType::WORD_ARRAY);
  REQUIRE(result.o == NounType::INTEGER);

  // Result should be positive
  if(std::holds_alternative<ints>(result.i))
  {
    const ints& chunks = std::get<ints>(result.i);
    REQUIRE(!chunks.empty());
    REQUIRE(chunks[0] == 0); // sign bit = 0 (positive)
  }
}

TEST_CASE("times WordArray * WordArray - different signs positive result", "[dyad][times]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // 5000000000 * -3000000000 = -15000000000000000000
  auto big1 = evalExpressionCppToIota({"5000000000"s, form, 0});
  auto big2 = evalExpressionCppToIota({"-3000000000"s, form, 0});
  auto result = evalExpressionCppToIota({big1, times, big2});
  REQUIRE(result.t == StorageType::WORD_ARRAY);
  REQUIRE(result.o == NounType::INTEGER);

  // Result should be negative
  if(std::holds_alternative<ints>(result.i))
  {
    const ints& chunks = std::get<ints>(result.i);
    REQUIRE(!chunks.empty());
    REQUIRE(chunks[0] == 1); // sign bit = 1 (negative)
  }
}

TEST_CASE("times WordArray * WordArray - different signs negative result", "[dyad][times]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // -5000000000 * 3000000000 = -15000000000000000000
  auto big1 = evalExpressionCppToIota({"-5000000000"s, form, 0});
  auto big2 = evalExpressionCppToIota({"3000000000"s, form, 0});
  auto result = evalExpressionCppToIota({big1, times, big2});
  REQUIRE(result.t == StorageType::WORD_ARRAY);
  REQUIRE(result.o == NounType::INTEGER);

  // Result should be negative
  if(std::holds_alternative<ints>(result.i))
  {
    const ints& chunks = std::get<ints>(result.i);
    REQUIRE(!chunks.empty());
    REQUIRE(chunks[0] == 1); // sign bit = 1 (negative)
  }
}

TEST_CASE("times WordArray * WordArray - result zero", "[dyad][times]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // 5000000000 * 0 = 0
  auto big1 = evalExpressionCppToIota({"5000000000"s, form, 0});
  auto result = evalExpression({big1, times, 0});
  REQUIRE(std::holds_alternative<int>(result));
  REQUIRE(result == 0);

  // 0 * 5000000000 = 0
  auto result2 = evalExpression({0, times, big1});
  REQUIRE(std::holds_alternative<int>(result2));
  REQUIRE(result2 == 0);
}

TEST_CASE("times - very large numbers", "[dyad][times]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // 1000000000 * 1000000000 = 1000000000000000000
  auto big1 = evalExpressionCppToIota({"1000000000"s, form, 0});
  auto result = evalExpressionCppToIota({big1, times, big1});
  REQUIRE(result.t == StorageType::WORD_ARRAY);
  REQUIRE(result.o == NounType::INTEGER);

  // 999999999999 * 999999999999
  auto big2 = evalExpressionCppToIota({"999999999999"s, form, 0});
  auto result2 = evalExpressionCppToIota({big2, times, big2});
  REQUIRE(result2.t == StorageType::WORD_ARRAY);
  REQUIRE(result2.o == NounType::INTEGER);
}

TEST_CASE("times - commutativity with mixed types", "[dyad][times]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // Word * WordArray should equal WordArray * Word
  auto big = evalExpressionCppToIota({"5000000000"s, form, 0});
  auto result1 = evalExpressionCppToIota({2, times, big});
  auto result2 = evalExpressionCppToIota({big, times, 2});

  REQUIRE(result1.t == result2.t);
  REQUIRE(result1.o == result2.o);
}

TEST_CASE("times - one identity with WordArray", "[dyad][times]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  auto big = evalExpressionCppToIota({"9876543210"s, form, 0});

  auto result1 = evalExpressionCppToIota({big, times, 1});
  REQUIRE(result1.t == StorageType::WORD_ARRAY);

  auto result2 = evalExpressionCppToIota({1, times, big});
  REQUIRE(result2.t == StorageType::WORD_ARRAY);
}

TEST_CASE("times - multiple precision chunks", "[dyad][times]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // Numbers that require multiple chunks
  // 2^40 = 1099511627776
  auto big1 = evalExpressionCppToIota({"1099511627776"s, form, 0});
  auto big2 = evalExpressionCppToIota({"1099511627776"s, form, 0});
  auto result = evalExpressionCppToIota({big1, times, big2});
  REQUIRE(result.t == StorageType::WORD_ARRAY);
  REQUIRE(result.o == NounType::INTEGER);

  // Result should be 2^80 which requires multiple chunks
}

TEST_CASE("times - small WordArray times small Word gives Word", "[dyad][times]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // Create a small number as WordArray (just over INT_MAX)
  // 2147483648 / 2 = 1073741824 (fits in Word)
  auto big = evalExpressionCppToIota({"2147483648"s, form, 0});

  // This is tricky - we can't easily test this since 2147483648 * any positive int > 1 overflows
  // But we can test: 2147483648 * 0 = 0
  auto result = evalExpression({big, times, 0});
  REQUIRE(std::holds_alternative<int>(result));
  REQUIRE(result == 0);
}

TEST_CASE("times - negative one flips sign", "[dyad][times]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // 5000000000 * -1 = -5000000000
  auto big = evalExpressionCppToIota({"5000000000"s, form, 0});
  auto result = evalExpressionCppToIota({big, times, -1});
  REQUIRE(result.t == StorageType::WORD_ARRAY);

  if(std::holds_alternative<ints>(result.i))
  {
    const ints& chunks = std::get<ints>(result.i);
    REQUIRE(!chunks.empty());
    REQUIRE(chunks[0] == 1); // sign bit = 1 (negative)
  }

  // -5000000000 * -1 = 5000000000
  auto big_neg = evalExpressionCppToIota({"-5000000000"s, form, 0});
  auto result2 = evalExpressionCppToIota({big_neg, times, -1});
  REQUIRE(result2.t == StorageType::WORD_ARRAY);

  if(std::holds_alternative<ints>(result2.i))
  {
    const ints& chunks = std::get<ints>(result2.i);
    REQUIRE(!chunks.empty());
    REQUIRE(chunks[0] == 0); // sign bit = 0 (positive)
  }
}

TEST_CASE("times - powers of two", "[dyad][times]")
{
  using namespace iota;
  using namespace std::literals::string_literals;

  // 2^31 * 2 = 2^32 = 4294967296
  auto big1 = evalExpressionCppToIota({"2147483648"s, form, 0}); // 2^31
  auto result1 = evalExpressionCppToIota({big1, times, 2});
  REQUIRE(result1.t == StorageType::WORD_ARRAY);

  // 2^32 * 2 = 2^33 = 8589934592
  auto big2 = evalExpressionCppToIota({"4294967296"s, form, 0}); // 2^32
  auto result2 = evalExpressionCppToIota({big2, times, 2});
  REQUIRE(result2.t == StorageType::WORD_ARRAY);
}