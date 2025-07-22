//
// Created by Dr. Brandon Wiley on 5/4/25.
//

#include "state.h"

#include "../../../api.h"
#include "../../../nouns/error.h"

#include <storage/storage.h>
#include <storage/word.h>
#include <storage/word_array.h>

void State::initialize(EffectsProvider* effects_register)
{
  state = std::nullopt;
}

// Monads
Storage State::get_impl()
{
  if(state)
  {
    return *state;
  }
  else
  {
    return Word::make(EMPTY, NounType::ERROR);
  }
}

// Dyads
Storage State::put_impl(const Storage& i)
{
  state = i;

  return WordArray::nil();
}

Storage State::modify_impl(const Storage& i)
{
  if(state)
  {
    Storage result = eval({*state, i});
    state = result;
    return result;
  }
  else
  {
    Storage result = eval({WordArray::nil(), i});
    state = result;
    return result;
  }

}

Storage State::getEffectState()
{
  if(state)
  {
    return *state;
  }
  else
  {
    return WordArray::nil();
  }
}

maybe<Storage> State::state;
