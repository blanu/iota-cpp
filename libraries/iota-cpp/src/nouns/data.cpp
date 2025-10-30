//
// Created by Dr. Brandon Wiley on 10/29/25.
//

#include "data.h"

#include <storage/storage.h>
#include <storage/word_array.h>

#include "nouns/noun.h"

void Data::initialize()
{

}

Storage Data::make(std::vector<uint8_t> bs)
{
  if(bs.empty())
  {
    return WordArray::make({}, NounType::DATA);
  }

  int wordCount = static_cast<int>(bs.size() / sizeof(int));
  const int leftover = static_cast<int>(bs.size() % sizeof(int));
  int trimCount = 0;

  if(leftover != 0)
  {
    trimCount = static_cast<int>(sizeof(int)) - leftover;
    ++wordCount;
  }

  auto is = ints(wordCount + 1);
  is[0] = trimCount;

  int working = 0;
  int wordIndex = 1;

  for(int byteIndex = 0; byteIndex < static_cast<int>(bs.size()); ++byteIndex)
  {
    int bytePos = byteIndex % sizeof(int);
    working = (working << 8) | bs[byteIndex];

    if(bytePos == sizeof(int) - 1)
    {
      is[wordIndex++] = working;
      working = 0;
    }
  }

  // Handle final partial word
  if(leftover != 0)
  {
    // Shift remaining bytes to fill the word (pad with zeros on right)
    working = working << (8 * trimCount);
    is[wordIndex] = working;
  }

  return WordArray::make(is, NounType::DATA);
}

maybe<std::vector<uint8_t>> Data::toBytes(const Storage& i)
{
  if(std::holds_alternative<ints>(i.i))
  {
    auto iis = std::get<ints>(i.i);
    if(iis.empty())
    {
      return std::vector<uint8_t>();
    }

    int trimCount = iis[0];
    // Skip the first int (trim count), process the rest
    int byteCount = (static_cast<int>(iis.size()) - 1) * sizeof(int) - trimCount;

    if(byteCount < 0)
    {
      return std::nullopt;
    }

    if(byteCount == 0)
    {
      return std::vector<uint8_t>();
    }

    std::vector<uint8_t> result;
    result.reserve(byteCount);

    // Start from index 1 (skip trim count)
    for(int wordIdx = 1; wordIdx < static_cast<int>(iis.size()); ++wordIdx)
    {
      int integer = iis[wordIdx];
      // Extract bytes from most significant to least significant
      for(int offset = sizeof(int) - 1; offset >= 0; --offset)
      {
        uint8_t b = static_cast<uint8_t>((integer >> (offset * 8)) & 0xFF);
        result.push_back(b);
      }
    }

    result.resize(byteCount);
    return result;
  }

  return std::nullopt;
}