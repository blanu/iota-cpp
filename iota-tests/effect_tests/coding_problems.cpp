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

  REQUIRE(result == 6);
}
