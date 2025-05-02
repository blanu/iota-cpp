//
// Created by Dr. Brandon Wiley on 4/16/25.
//

#include <string>
#include <catch2/catch_all.hpp>

#include "api.h"

TEST_CASE("divide integer integer", "[dyad]")
{
  using namespace iota;

  float f = 1.0f / 2.0f;
  REQUIRE(evalExpression({1, divide, 2}) == f);
  // FIXME, std::string equality
  // REQUIRE(evalExpression({1, divide, 0}) == CppValue(std::string(":undefined")));
}

TEST_CASE("divide integer real", "[dyad]")
{
  using namespace iota;

  float f = 1.0f / 2.0f;
  REQUIRE(evalExpression({1, divide, 2.0f}) == f);
  // FIXME, std::string equality
  // REQUIRE(evalExpression({1.0f, divide, 0.0f}) == CppValue(std::string(":undefined")));
}

TEST_CASE("divide real integer", "[dyad]")
{
  using namespace iota;

  float f = 1.0f / 2.0f;
  REQUIRE(evalExpression({1.0f, divide, 2}) == f);
  // FIXME, std::string equality
  // REQUIRE(evalExpression({1, divide, 0.0f}) == CppValue(std::string(":undefined")));
}

TEST_CASE("divide real real", "[dyad]")
{
  using namespace iota;

  float f = 1.0f / 2.0f;
  REQUIRE(evalExpression({1.0f, divide, 2.0f}) == f);
  // FIXME, std::string equality
  // REQUIRE(evalExpression({1, divide, 0.0f}) == CppValue(std::string(":undefined")));
}

TEST_CASE("divide integer list", "[dyad]")
{
  using namespace iota;

  REQUIRE(evalExpression({1, divide, {2, 4}}) == a{1.0f / 2.0f, 1.0f / 4.0f});
  // FIXME, std::string equality
  // REQUIRE(evalExpression({1, divide, 0.0f}) == CppValue(std::string(":undefined")));
  REQUIRE(evalExpression({1, divide, {2.0f, 4.0f}}) == a{1.0f / 2.0f, 1.0f / 4.0f});
  REQUIRE(evalExpression({1, divide, {2, 4.0f}}) == a{1.0f / 2.0f, 1.0f / 4.0f});
}

TEST_CASE("divide real list", "[dyad]")
{
  using namespace iota;

  REQUIRE(evalExpression({1.0f, divide, {2, 4}}) == a{1.0f / 2.0f, 1.0f / 4.0f});
  // FIXME, std::string equality
  // REQUIRE(evalExpression({1, divide, 0.0f}) == CppValue(std::string(":undefined")));
  REQUIRE(evalExpression({1.0f, divide, {2.0f, 4.0f}}) == a{1.0f / 2.0f, 1.0f / 4.0f});
  REQUIRE(evalExpression({1.0f, divide, {2, 4.0f}}) == a{1.0f / 2.0f, 1.0f / 4.0f});
}

TEST_CASE("divide list integer", "[dyad]")
{
  using namespace iota;

  REQUIRE(evalExpression({{2, 4}, divide, 1}) == a{2.0f, 4.0f});
  REQUIRE(evalExpression({{2.0f, 4.0f}, divide, 1}) == a{2.0f, 4.0f});
  REQUIRE(evalExpression({{2, 4.0f}, divide, 1}) == a{2.0f, 4.0f});
}

TEST_CASE("divide list real", "[dyad]")
{
  using namespace iota;

  REQUIRE(evalExpression({{2, 4}, divide, 1.0f}) == a{2.0f, 4.0f});
  REQUIRE(evalExpression({{2.0f, 4.0f}, divide, 1.0f}) == a{2.0f, 4.0f});
  REQUIRE(evalExpression({{2, 4.0f}, divide, 1.0f}) == a{2.0f, 4.0f});
}

TEST_CASE("divide list list", "[dyad]")
{
  using namespace iota;

  REQUIRE(evalExpression({{2, 4}, divide, {2, 4}}) == a{1.0f, 1.0f});
  REQUIRE(evalExpression({{2, 4}, divide, {2.0f, 4.0f}}) == a{1.0f, 1.0f});
  REQUIRE(evalExpression({{2, 4}, divide, {2, 4.0f}}) == a{1.0f, 1.0f});
  REQUIRE(evalExpression({{2.0f, 4.0f}, divide, {2, 4}}) == a{1.0f, 1.0f});
  REQUIRE(evalExpression({{2.0f, 4.0f}, divide, {2.0f, 4.0f}}) == a{1.0f, 1.0f});
  REQUIRE(evalExpression({{2.0f, 4.0f}, divide, {2.0f, 4.0f}}) == a{1.0f, 1.0f});
  REQUIRE(evalExpression({{2, 4.0f}, divide, {2, 4}}) == a{1.0f, 1.0f});
  REQUIRE(evalExpression({{2, 4.0f}, divide, {2.0f, 4.0f}}) == a{1.0f, 1.0f});
  REQUIRE(evalExpression({{2, 4.0f}, divide, {2, 4.0f}}) == a{1.0f, 1.0f});
}
