//
// Created by Dr. Brandon Wiley on 4/8/25.
//

#include <catch2/catch_all.hpp>

#include "api.h"
#include "nouns/quoted_symbol.h"

TEST_CASE("transpose list", "[monad]")
{
  using namespace iota;

  REQUIRE(evalExpression({CppValues{CppValues{1, 2}, CppValues{3, 4}}, transpose}) == CppValues{CppValues{1, 3}, CppValues{2, 4}});
  REQUIRE(evalExpression({CppValues{CppValues{1.0f, 2.0f}, CppValues{3.0f, 4.0f}}, transpose}) == CppValues{CppValues{1.0f, 3.0f}, CppValues{2.0f, 4.0f}});
  auto result = evalExpression({CppValues{CppValues{1, 2.0f}, CppValues{3, 4.0f}}, transpose});
  auto correct = CppValues{CppValues{1, 3}, CppValues{2.0f, 4.0f}};
  REQUIRE(result == correct);
  // REQUIRE(evalExpression({CppValues{CppValues{1, 2.0f}, CppValues{3, 4.0f}}, transpose}) == CppValues{CppValues{1, 3}, CppValues{2.0f, 4.0f}});
}
