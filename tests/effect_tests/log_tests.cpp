//
// Created by Dr. Brandon Wiley on 4/18/25.
//

#include <string>
#include <catch2/catch_all.hpp>

#include "api.h"

#include "effects/testing/log/log.h"

TEST_CASE("timestamp", "[effect]")
{
  using namespace iota;

  REQUIRE(evalExpression({timestamp}) == a{});
}

TEST_CASE("critical string, causes", "[effect]")
{
  using namespace iota;
  using namespace std::string_literals;

  REQUIRE(evalExpression({"test"s, critical}) == a{});
}

TEST_CASE("warning string, because", "[effect]")
{
  using namespace iota;
  using namespace std::string_literals;

  REQUIRE(evalExpression({"test"s, warning}) == a{});
}

TEST_CASE("error string", "[effect]")
{
  using namespace iota;
  using namespace std::string_literals;

  REQUIRE(evalExpression({"test"s, error}) == a{});
}

TEST_CASE("log level filtering", "[effect]")
{
  using namespace iota;
  using namespace std::string_literals;

  REQUIRE(evalExpression({"test"s, trace}) == a{});
}

TEST_CASE("log level setting", "[effect]")
{
  using namespace iota;
  using namespace std::string_literals;

  REQUIRE(evalExpression({Log::Levels::debug, level, then, "test"s, trace}) == a{});
}

TEST_CASE("log chaining", "[effect]")
{
  using namespace iota;
  using namespace std::string_literals;

  REQUIRE(evalExpression({"test 1"s, warning, then, Log::Levels::debug, level, then, "test 2"s, warning}) == a{});
}
