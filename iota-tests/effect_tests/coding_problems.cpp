//
// Created by Dr. Brandon Wiley on 12/2/2025.
//

#include <map>
#include <string>
#include <catch2/catch_all.hpp>
#include <catch2/catch_test_macros.hpp>
#include <fstream>
#include <sstream>
#include "api.h"
#include "effects/testing/testing_effects_provider.h"
#include "effects/testing/state/testing_state.h"

extern TestingEffectsProvider provider;

std::string read_file(const std::string& filepath) {
  std::ifstream file(filepath);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open file: " + filepath);
  }
  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

TEST_CASE("AoC_2025_1_1 simple", "[AoC]")
{
  using namespace iota;
  using iota::split;
  using iota::each;
  using iota::first;
  using iota::drop;
  using iota::form;
  using iota::equal;
  using iota::scanOverNeutral;
  using iota::times;
  using iota::minus;
  using iota::plus;
  using iota::over;
  using iota::remainder;
  using iota::x;

  std::string input = R"(L68
L30
R48
L5
R60
L55
L1
L99
R14
L82)";

  auto lines = evalExpressionCppToIota({input, split, '\n'});
  auto directions = evalExpressionCppToIota({lines, each, e(first, equal, 'R', times, 2, minus, 1)});
  auto magnitudes = evalExpressionCppToIota({lines, each, e(drop, 1, form, 0)});
  auto numbers = evalExpressionCppToIota({directions, times, magnitudes});
  auto positions = evalExpressionCppToIota({numbers, scanOverNeutral, e(plus, x, remainder, 100, plus, 100, remainder, 100), 50, drop, 1});
  auto zeros = evalExpressionCppToIota({positions, equal, 0});
  auto result = evalExpression({zeros, over, plus});

  if (std::holds_alternative<std::string>(result)) {
    std::string result_str = std::get<std::string>(result);
    printf("%s\n", result_str.c_str());
  }

  REQUIRE(result == 3);
}

TEST_CASE("AoC_2025_1_1 full", "[AoC]")
{
  using namespace iota;
  using iota::split;
  using iota::each;
  using iota::first;
  using iota::drop;
  using iota::form;
  using iota::equal;
  using iota::scanOverNeutral;
  using iota::times;
  using iota::minus;
  using iota::plus;
  using iota::over;
  using iota::remainder;

  std::string input = read_file(TEST_DATA_DIR "/AoC_2025_1_1.txt");
  auto lines = evalExpressionCppToIota({input, split, '\n'});
  auto directions = evalExpressionCppToIota({lines, each, e(first, equal, 'R', times, 2, minus, 1)});
  auto magnitudes = evalExpressionCppToIota({lines, each, e(drop, 1, form, 0)});
  auto numbers = evalExpressionCppToIota({directions, times, magnitudes});
  auto positions = evalExpressionCppToIota({numbers, scanOverNeutral, e(plus, x, remainder, 100, plus, 100, remainder, 100), 50, drop, 1});
  auto zeros = evalExpressionCppToIota({positions, equal, 0});
  auto result = evalExpression({zeros, over, plus});

  if (std::holds_alternative<std::string>(result))
  {
    std::string result_str = std::get<std::string>(result);
    printf("%s\n", result_str.c_str());
  }
  else if(std::holds_alternative<int>(result))
  {
    int result_int = std::get<int>(result);
    printf("%d\n", result_int);
  }
}

TEST_CASE("AoC_2025_1_2 simple", "[AoC]")
{
  using namespace iota;
  using iota::split;
  using iota::each;
  using iota::first;
  using iota::drop;
  using iota::form;
  using iota::equal;
  using iota::scanOverNeutral;
  using iota::times;
  using iota::minus;
  using iota::plus;
  using iota::over;
  using iota::remainder;
  using iota::x;
  using iota::expand;
  using iota::join;

  std::string input = R"(L68
L30
R48
L5
R60
L55
L1
L99
R14
L82)";

  auto lines = evalExpressionCppToIota({input, split, '\n'});
  auto directions = evalExpressionCppToIota({lines, each, e(first, equal, 'R', times, 2, minus, 1)});
  auto magnitudes = evalExpressionCppToIota({lines, each, e(drop, 1, form, 0, expand, plus, 1)});
  auto numbers = evalExpressionCppToIota({directions, times, magnitudes, over, join});
  auto positions = evalExpressionCppToIota({numbers, scanOverNeutral, e(plus, x, remainder, 100, plus, 100, remainder, 100), 50, drop, 1});
  auto zeros = evalExpressionCppToIota({positions, equal, 0});
  auto result = evalExpression({zeros, over, plus});

  if (std::holds_alternative<std::string>(result)) {
    std::string result_str = std::get<std::string>(result);
    printf("%s\n", result_str.c_str());
  }

  REQUIRE(result == 6);
}

TEST_CASE("AoC_2025_1_2 full", "[AoC]")
{
  using namespace iota;
  using iota::split;
  using iota::each;
  using iota::first;
  using iota::drop;
  using iota::form;
  using iota::equal;
  using iota::scanOverNeutral;
  using iota::times;
  using iota::minus;
  using iota::plus;
  using iota::over;
  using iota::remainder;

  std::string input = read_file(TEST_DATA_DIR "/AoC_2025_1_1.txt"); // Same input as the last puzzle
  auto lines = evalExpressionCppToIota({input, split, '\n'});
  auto directions = evalExpressionCppToIota({lines, each, e(first, equal, 'R', times, 2, minus, 1)});
  auto magnitudes = evalExpressionCppToIota({lines, each, e(drop, 1, form, 0, expand, plus, 1)});
  auto sublists= evalExpressionCppToIota({directions, times, magnitudes});
  auto numbers = evalExpressionCppToIota({sublists, over, join});
  auto positions = evalExpressionCppToIota({numbers, scanOverNeutral, e(plus, x, remainder, 100, plus, 100, remainder, 100), 50, drop, 1});
  auto zeros = evalExpressionCppToIota({positions, equal, 0});
  auto result = evalExpression({zeros, over, plus});

  if (std::holds_alternative<std::string>(result))
  {
    std::string result_str = std::get<std::string>(result);
    printf("%s\n", result_str.c_str());
  }
  else if(std::holds_alternative<int>(result))
  {
    int result_int = std::get<int>(result);
    printf("%d\n", result_int);
  }
}

TEST_CASE("AoC_2025_2_1 simple", "[AoC]")
{
  using namespace iota;
  using iota::split;
  using iota::each;
  using iota::form;
  using iota::index;
  using iota::enumerate;
  using iota::reverse;
  using iota::transpose;
  using iota::over;
  using iota::join;
  using iota::match;
  using iota::expand;

  std::string input = "11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124";

  auto textRanges = evalExpressionCppToIota({input, split, ','});
  auto ranges = evalExpressionCppToIota({textRanges, each, e(split, '-', each, e(form, 0))});
  auto offsets = evalExpressionCppToIota({ranges, each, first});
  auto spans = evalExpressionCppToIota({ranges, each, e(reverse, over, minus)});
  auto enumerations = evalExpressionCppToIota({spans, each, e(plus, 1, enumerate, minus, 1)});
  auto numbers = evalExpressionCppToIota({{offsets, enumerations}, transpose, each, e(over, plus), over, join});
  auto ids = evalExpressionCppToIota({numbers, each, format});
  auto sizes = evalExpressionCppToIota({ids, each, e(size, integerDivide, 2)});
  auto parts = evalExpressionCppToIota({{ids, sizes}, transpose, each, e(over, split)});
  auto isBad = evalExpressionCppToIota({parts, each, e(over, match), expand});
  auto badNumbers = evalExpressionCppToIota({numbers, index, isBad});
  auto result = evalExpression({badNumbers, over, plus});
  REQUIRE(result == 1227775554);
}

TEST_CASE("AoC_2025_2_1 full", "[AoC]")
{
  using namespace iota;
  using iota::each;
  using iota::format;
  using iota::form;
  using iota::i;
  using iota::match;
  using iota::minus;
  using iota::over;
  using iota::plus;
  using iota::size;
  using iota::split;
  using iota::take;
  using iota::times;

  std::string input = read_file(TEST_DATA_DIR "/AoC_2025_2_1.txt"); // Same input as the last puzzle

  auto inputSize = evalExpressionCppToIota({input, size, minus, 1});
  auto trimmed = evalExpressionCppToIota({input, take, inputSize});
  auto ranges = evalExpressionCppToIota({trimmed, split, ',', each, e(split, '-', each, e(form, 0), range)});
  auto sums = evalExpressionCppToIota({
    ranges, each, e( // each range
      each, e( // each number in the range
      format, split, 0.5f, // split textual representation of the number in half
      over, match, // are both halves the same?
      times, i // if so, keep the number, otherwise set it to 0
      ),
      over, plus
    )
  });
  auto result = evalExpression({sums, over, plus});

  if(std::holds_alternative<int>(result))
  {
    printf("%d\n", std::get<int>(result));
  }
  else if(std::holds_alternative<BigNumber>(result))
  {
    BigNumber result_bn = std::get<BigNumber>(result);
    printf("%s\n", result_bn.toString());
  }
  else if (std::holds_alternative<std::string>(result))
  {
    std::string result_str = std::get<std::string>(result);
    printf("%s\n", result_str.c_str());
  }
}