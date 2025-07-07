//
// Created by Dr. Brandon Wiley on 7/3/25.
//

#include <catch2/catch_all.hpp>

#include "squeeze.h"
#include "storage/iota_float.h"

TEST_CASE("squeeze float 0.0", "[float]")
{
  constexpr float input = 0.0;
  const bytes data = squeeze_floating(input);
  maybe<floating> result = expand_floating(data);

  REQUIRE(result);
  if(result)
  {
    const floating fd = *result;

    REQUIRE(std::holds_alternative<double>(fd));

    const double d = std::get<double>(fd);
    const auto f = static_cast<float>(d);
    REQUIRE(f == input);
  }
}

TEST_CASE("squeeze float 1.0", "[float]")
{
  constexpr float input = 1.0;
  const bytes data = squeeze_floating(input);
  maybe<floating> result = expand_floating(data);

  REQUIRE(result);
  if(result)
  {
    const floating fd = *result;

    REQUIRE(std::holds_alternative<float>(fd));

    const float f = std::get<float>(fd);
    REQUIRE(f == input);
  }
}

TEST_CASE("squeeze double 1.0", "[double]")
{
  constexpr double input = 1.0;
  const bytes data = squeeze_floating(input);
  maybe<floating> result = expand_floating(data);

  REQUIRE(result);
  if(result)
  {
    const floating fd = *result;

    REQUIRE(std::holds_alternative<double>(fd));

    const double d = std::get<double>(fd);
    REQUIRE(d == input);
  }
}

TEST_CASE("squeeze float -1.0", "[float]")
{
  constexpr float input = -1.0;
  const bytes data = squeeze_floating(input);
  maybe<floating> result = expand_floating(data);

  REQUIRE(result);
  if(result)
  {
    const floating fd = *result;

    REQUIRE(std::holds_alternative<float>(fd));

    const float f = std::get<float>(fd);
    REQUIRE(f == input);
  }
}