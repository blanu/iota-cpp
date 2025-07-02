//
// Created by Dr. Brandon Wiley on 3/23/25.
//

#define CATCH_CONFIG_RUNNER
#include <catch2/catch_all.hpp>

#include "eval_register.h"
#include "effects/effects_provider.h"
#include "effects/testing/testing_effects_provider.h"

int main(int argc, char** argv)
{
  EvalRegister::initialize();
  EffectsProvider provider = TestingEffectsProvider();

  EvalRegister::registerEffectsProvider(provider);

  const int result = Catch::Session().run(argc, argv);

  return result;
}
