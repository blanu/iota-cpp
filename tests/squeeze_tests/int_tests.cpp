//
// Created by Dr. Brandon Wiley on 7/3/25.
//

#include <catch2/catch_all.hpp>

#include "squeeze.h"
#include "storage/word.h"

TEST_CASE("squeeze int 0", "[int]")
{
  constexpr int input = 0;
  bytes data = squeeze_int(input);
  std::tuple<varint, bytes> result = expand_int(data);
  varint value = std::get<0>(result);
  bytes rest = std::get<1>(result);

  REQUIRE(std::holds_alternative<int>(value));

  if(std::holds_alternative<int>(value))
  {
    int output = std::get<int>(value);
    REQUIRE(input == output);
  }

  REQUIRE(rest.empty());
}

TEST_CASE("squeeze int 1", "[int]")
{
  constexpr int input = 1;
  bytes data = squeeze_int(input);
  std::tuple<varint, bytes> result = expand_int(data);
  varint value = std::get<0>(result);
  bytes rest = std::get<1>(result);

  REQUIRE(std::holds_alternative<int>(value));

  if(std::holds_alternative<int>(value))
  {
    int output = std::get<int>(value);
    REQUIRE(input == output);
  }

  REQUIRE(rest.empty());
}

TEST_CASE("squeeze int -1", "[int]")
{
  constexpr int input = -1;
  bytes data = squeeze_int(input);
  std::tuple<varint, bytes> result = expand_int(data);
  varint value = std::get<0>(result);
  bytes rest = std::get<1>(result);

  REQUIRE(std::holds_alternative<int>(value));

  if(std::holds_alternative<int>(value))
  {
    int output = std::get<int>(value);
    REQUIRE(input == output);
  }

  REQUIRE(rest.empty());
}

TEST_CASE("squeeze int 256", "[int]")
{
  constexpr int input = 256;
  bytes data = squeeze_int(input);
  std::tuple<varint, bytes> result = expand_int(data);
  varint value = std::get<0>(result);
  bytes rest = std::get<1>(result);

  REQUIRE(std::holds_alternative<int>(value));

  if(std::holds_alternative<int>(value))
  {
    int output = std::get<int>(value);
    REQUIRE(input == output);
  }

  REQUIRE(rest.empty());
}

TEST_CASE("squeeze int -256", "[int]")
{
  constexpr int input = -256;
  bytes data = squeeze_int(input);
  std::tuple<varint, bytes> result = expand_int(data);
  varint value = std::get<0>(result);
  bytes rest = std::get<1>(result);

  REQUIRE(std::holds_alternative<int>(value));

  if(std::holds_alternative<int>(value))
  {
    int output = std::get<int>(value);
    REQUIRE(input == output);
  }

  REQUIRE(rest.empty());
}