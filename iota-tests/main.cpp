//
// Created by Dr. Brandon Wiley on 3/23/25.
//

#define CATCH_CONFIG_RUNNER
#include <catch2/catch_all.hpp>

#include "eval_register.h"
#include "effects/effects_provider.h"
#include "effects/testing/testing_effects_provider.h"

static TestingEffectsProvider *provider = nullptr;

int main(const int argc, char** argv)
{
  EvalRegister::initialize();
  provider = new TestingEffectsProvider();

  EvalRegister::registerEffectsProvider(*provider);

  const int result = Catch::Session().run(argc, argv);

  delete provider;

  return result;
}
