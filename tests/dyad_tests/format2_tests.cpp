//
// Created by Dr. Brandon Wiley on 4/18/25.
//

#include <string>
#include <catch2/catch_all.hpp>

#include "api.h"

TEST_CASE("format2 integer", "[dyad]")
{
  using namespace iota;
  using namespace std::literals::string_literals; // This allows std::string literals using "value"s.

  REQUIRE(evalExpression({0, format2, 0}) == "0"s);
  REQUIRE(evalExpression({0, format2, 1}) == "0"s);
  REQUIRE(evalExpression({0, format2, -1}) == "0"s);
  REQUIRE(evalExpression({0, format2, 2}) == "0 "s);
  REQUIRE(evalExpression({0, format2, -2}) == " 0"s);
  REQUIRE(evalExpression({0, format2, 3}) == "0  "s);
  REQUIRE(evalExpression({0, format2, -3}) == "  0"s);
}

TEST_CASE("format2 real", "[dyad]")
{
  using namespace iota;
  using namespace std::literals::string_literals; // This allows std::string literals using "value"s.

  REQUIRE(evalExpression({0.0f, format2, 0}) == "0.0"s);
  REQUIRE(evalExpression({0.0f, format2, 1}) == "0.0"s);
  REQUIRE(evalExpression({0.0f, format2, -1}) == "0.0"s);
  REQUIRE(evalExpression({0.0f, format2, 2}) == "0.0"s);
  REQUIRE(evalExpression({0.0f, format2, -2}) == "0.0"s);
  REQUIRE(evalExpression({0.0f, format2, 3}) == "0.0"s);
  REQUIRE(evalExpression({0.0f, format2, -3}) == "0.0"s);
  REQUIRE(evalExpression({0.0f, format2, 4}) == "0.0 "s);
  REQUIRE(evalExpression({0.0f, format2, -4}) == " 0.0"s);
  REQUIRE(evalExpression({0.0f, format2, 5}) == "0.0  "s);
  REQUIRE(evalExpression({0.0f, format2, -5}) == "  0.0"s);
}

TEST_CASE("format2 list", "[dyad]")
{
  using namespace iota;
  using namespace std::literals::string_literals; // This allows std::string literals using "value"s.

  // FIXME - :undefined results
  // REQUIRE(evalExpression({a{}, format2, 0}) == ":undefined"s);

  REQUIRE(evalExpression({{0}, format2, 0}) == a{"0"s});
  REQUIRE(evalExpression({{0}, format2, 1}) == a{"0"s});
  REQUIRE(evalExpression({{0}, format2, -1}) == a{"0"s});
  REQUIRE(evalExpression({{0}, format2, 2}) == a{"0 "s});
  REQUIRE(evalExpression({{0}, format2, -2}) == a{" 0"s});
  REQUIRE(evalExpression({{0}, format2, 3}) == a{"0  "s});
  REQUIRE(evalExpression({{0}, format2, -3}) == a{"  0"s});

  REQUIRE(evalExpression({{0}, format2, 0.0f}) == a{"0"s});
  REQUIRE(evalExpression({{0}, format2, 1.0f}) == a{"0"s});
  REQUIRE(evalExpression({{0}, format2, -1.0f}) == a{"0"s});
  REQUIRE(evalExpression({{0}, format2, 2.0f}) == a{"0 "s});
  REQUIRE(evalExpression({{0}, format2, -2.0f}) == a{" 0"s});
  REQUIRE(evalExpression({{0}, format2, 3.0f}) == a{"0  "s});
  REQUIRE(evalExpression({{0}, format2, -3.0f}) == a{"  0"s});

  REQUIRE(evalExpression({{0}, format2, 0.5f}) == a{"0"s});
  REQUIRE(evalExpression({{0}, format2, 1.5f}) == a{"0"s});
  REQUIRE(evalExpression({{0}, format2, -1.5f}) == a{"0"s});
  REQUIRE(evalExpression({{0}, format2, 2.5f}) == a{"0 "s});
  REQUIRE(evalExpression({{0}, format2, -2.5f}) == a{" 0"s});
  REQUIRE(evalExpression({{0}, format2, 3.5f}) == a{"0  "s});
  REQUIRE(evalExpression({{0}, format2, -3.5f}) == a{"  0"s});

  REQUIRE(evalExpression({{0.0f}, format2, 0}) == a{"0.0"s});
  REQUIRE(evalExpression({{0.0f}, format2, 1}) == a{"0.0"s});
  REQUIRE(evalExpression({{0.0f}, format2, -1}) == a{"0.0"s});
  REQUIRE(evalExpression({{0.0f}, format2, 2}) == a{"0.0"s});
  REQUIRE(evalExpression({{0.0f}, format2, -2}) == a{"0.0"s});
  REQUIRE(evalExpression({{0.0f}, format2, 3}) == a{"0.0"s});
  REQUIRE(evalExpression({{0.0f}, format2, -3}) == a{"0.0"s});
  REQUIRE(evalExpression({{0.0f}, format2, 4}) == a{"0.0 "s});
  REQUIRE(evalExpression({{0.0f}, format2, -4}) == a{" 0.0"s});
  REQUIRE(evalExpression({{0.0f}, format2, 5}) == a{"0.0  "s});
  REQUIRE(evalExpression({{0.0f}, format2, -5}) == a{"  0.0"s});

  REQUIRE(evalExpression({{0.0f}, format2, 0.0f}) == a{"0.0"s});
  REQUIRE(evalExpression({{0.0f}, format2, 1.0f}) == a{"0.0"s});
  REQUIRE(evalExpression({{0.0f}, format2, -1.0f}) == a{"0.0"s});
  REQUIRE(evalExpression({{0.0f}, format2, 2.0f}) == a{"0.0"s});
  REQUIRE(evalExpression({{0.0f}, format2, -2.0f}) == a{"0.0"s});
  REQUIRE(evalExpression({{0.0f}, format2, 3.0f}) == a{"0.0"s});
  REQUIRE(evalExpression({{0.0f}, format2, -3.0f}) == a{"0.0"s});
  REQUIRE(evalExpression({{0.0f}, format2, 4.0f}) == a{"0.0 "s});
  REQUIRE(evalExpression({{0.0f}, format2, -4.0f}) == a{" 0.0"s});
  REQUIRE(evalExpression({{0.0f}, format2, 5.0f}) == a{"0.0  "s});
  REQUIRE(evalExpression({{0.0f}, format2, -5.0f}) == a{"  0.0"s});

  REQUIRE(evalExpression({{0.0f}, format2, 0.5f}) == a{"0.00000"s});
  REQUIRE(evalExpression({{0.0f}, format2, -0.5f}) == a{"0.00000"s});
  REQUIRE(evalExpression({{0.0f}, format2, 1.5f}) == a{"0.00000"s});
  REQUIRE(evalExpression({{0.0f}, format2, -1.5f}) == a{"0.00000"s});
  REQUIRE(evalExpression({{0.0f}, format2, 2.5f}) == a{" 0.00000"s});
  REQUIRE(evalExpression({{0.0f}, format2, -2.5f}) == a{" 0.00000"s});
  REQUIRE(evalExpression({{0.0f}, format2, 3.5f}) == a{"  0.00000"s});
  REQUIRE(evalExpression({{0.0f}, format2, -3.5f}) == a{"  0.00000"s});

  REQUIRE(evalExpression({{0.0f, 1}, format2, 0}) == a{"0.0"s, "1"s});
  REQUIRE(evalExpression({{0.0f, 1}, format2, 1}) == a{"0.0"s, "1"s});
  REQUIRE(evalExpression({{0.0f, 1}, format2, -1}) == a{"0.0"s, "1"s});
  REQUIRE(evalExpression({{0.0f, 1}, format2, 2}) == a{"0.0"s, "1 "s});
  REQUIRE(evalExpression({{0.0f, 1}, format2, -2}) == a{"0.0"s, " 1"s});
  REQUIRE(evalExpression({{0.0f, 1}, format2, 3}) == a{"0.0"s, "1  "s});
  REQUIRE(evalExpression({{0.0f, 1}, format2, -3}) == a{"0.0"s, "  1"s});
  REQUIRE(evalExpression({{0.0f, 1}, format2, 4}) == a{"0.0 "s, "1   "s});
  REQUIRE(evalExpression({{0.0f, 1}, format2, -4}) == a{" 0.0"s, "   1"s});
  REQUIRE(evalExpression({{0.0f, 1}, format2, 5}) == a{"0.0  "s, "1    "s});
  REQUIRE(evalExpression({{0.0f, 1}, format2, -5}) == a{"  0.0"s, "    1"s});

  REQUIRE(evalExpression({{0.0f, 1}, format2, 0.0f}) == a{"0.0"s, "1"s});
  REQUIRE(evalExpression({{0.0f, 1}, format2, 1.0f}) == a{"0.0"s, "1"s});
  REQUIRE(evalExpression({{0.0f, 1}, format2, -1.0f}) == a{"0.0"s, "1"s});
  REQUIRE(evalExpression({{0.0f, 1}, format2, 2.0f}) == a{"0.0"s, "1 "s});
  REQUIRE(evalExpression({{0.0f, 1}, format2, -2.0f}) == a{"0.0"s, " 1"s});
  REQUIRE(evalExpression({{0.0f, 1}, format2, 3.0f}) == a{"0.0"s, "1  "s});
  REQUIRE(evalExpression({{0.0f, 1}, format2, -3.0f}) == a{"0.0"s, "  1"s});
  REQUIRE(evalExpression({{0.0f, 1}, format2, 4.0f}) == a{"0.0 "s, "1   "s});
  REQUIRE(evalExpression({{0.0f, 1}, format2, -4.0f}) == a{" 0.0"s, "   1"s});
  REQUIRE(evalExpression({{0.0f, 1}, format2, 5.0f}) == a{"0.0  "s, "1    "s});
  REQUIRE(evalExpression({{0.0f, 1}, format2, -5.0f}) == a{"  0.0"s, "    1"s});

  REQUIRE(evalExpression({{0.0f, 1}, format2, 0.5f}) == a{"0.00000"s, "1"s});
  REQUIRE(evalExpression({{0.0f, 1}, format2, -0.5f}) == a{"0.00000"s, "1"s});
  REQUIRE(evalExpression({{0.0f, 1}, format2, 1.5f}) == a{"0.00000"s, "1"s});
  REQUIRE(evalExpression({{0.0f, 1}, format2, -1.5f}) == a{"0.00000"s, "1"s});
  REQUIRE(evalExpression({{0.0f, 1}, format2, 2.5f}) == a{" 0.00000"s, "1 "s});
  REQUIRE(evalExpression({{0.0f, 1}, format2, -2.5f}) == a{" 0.00000"s, " 1"s});
  REQUIRE(evalExpression({{0.0f, 1}, format2, 3.5f}) == a{"  0.00000"s, "1  "s});
  REQUIRE(evalExpression({{0.0f, 1}, format2, -3.5f}) == a{"  0.00000"s, "  1"s});
}

TEST_CASE("format2 character", "[dyad]")
{
  using namespace iota;
  using namespace std::literals::string_literals; // This allows std::string literals using "value"s.

  // FIXME - :undefined results
  // REQUIRE(evalExpression({a{}, format2, 0}) == ":undefined"s);

  REQUIRE(evalExpression({'a', format2, 0}) == "a"s);
  REQUIRE(evalExpression({'a', format2, 1}) == "a"s);
  REQUIRE(evalExpression({'a', format2, 2}) == "a "s);
  REQUIRE(evalExpression({'a', format2, -2}) == " a"s);
  REQUIRE(evalExpression({'a', format2, 0.0f}) == "a"s);
  REQUIRE(evalExpression({'a', format2, 1.0f}) == "a"s);
  REQUIRE(evalExpression({'a', format2, -1.0f}) == "a"s);
  REQUIRE(evalExpression({'a', format2, 2.0f}) == "a "s);
  REQUIRE(evalExpression({'a', format2, -2.0f}) == " a"s);
  REQUIRE(evalExpression({'a', format2, 2.5f}) == "a "s);
  REQUIRE(evalExpression({'a', format2, -2.5f}) == " a"s);
}

TEST_CASE("format2 string", "[dyad]")
{
  using namespace iota;
  using namespace std::literals::string_literals; // This allows std::string literals using "value"s.

  // FIXME - :undefined results
  // REQUIRE(evalExpression({a{}, format2, 0}) == ":undefined"s);

  REQUIRE(evalExpression({"abc", format2, 0}) == "abc"s);
  REQUIRE(evalExpression({"abc", format2, 1}) == "abc"s);
  REQUIRE(evalExpression({"abc", format2, -1}) == "abc"s);
  REQUIRE(evalExpression({"abc", format2, 2}) == "abc"s);
  REQUIRE(evalExpression({"abc", format2, -2}) == "abc"s);
  REQUIRE(evalExpression({"abc", format2, 3}) == "abc"s);
  REQUIRE(evalExpression({"abc", format2, -3}) == "abc"s);
  REQUIRE(evalExpression({"abc", format2, 4}) == "abc "s);
  REQUIRE(evalExpression({"abc", format2, -4}) == " abc"s);
  REQUIRE(evalExpression({"abc", format2, 0.0f}) == "abc"s);
  REQUIRE(evalExpression({"abc", format2, 1.0f}) == "abc"s);
  REQUIRE(evalExpression({"abc", format2, -1.0f}) == "abc"s);
  REQUIRE(evalExpression({"abc", format2, 2.0f}) == "abc"s);
  REQUIRE(evalExpression({"abc", format2, -2.0f}) == "abc"s);
  REQUIRE(evalExpression({"abc", format2, 3.0f}) == "abc"s);
  REQUIRE(evalExpression({"abc", format2, -3.0f}) == "abc"s);
  REQUIRE(evalExpression({"abc", format2, 4.0f}) == "abc "s);
  REQUIRE(evalExpression({"abc", format2, -4.0f}) == " abc"s);
  REQUIRE(evalExpression({"abc", format2, 4.5f}) == "abc "s);
  REQUIRE(evalExpression({"abc", format2, -4.5f}) == " abc"s);
}

// FIXME - symbols