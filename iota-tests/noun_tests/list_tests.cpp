//
// Created by Dr. Brandon Wiley on 10/21/25.
//

#include <catch2/catch_all.hpp>
#include <cstdint>
#include <vector>

#include "nouns/list.h"
#include "nouns/integer.h"
#include "storage/storage.h"

TEST_CASE("ints list empty", "[list]")
{
    ints list = {};
    Storage storage = List::make(list);

    ints result = List::toInts(storage);
    REQUIRE(result == list);
}

TEST_CASE("ints list single element", "[list]")
{
    ints list = {42};
    Storage storage = List::make(list);

    ints result = List::toInts(storage);
    REQUIRE(result == list);
}

TEST_CASE("ints list multiple elements", "[list]")
{
    ints list = {1, 2, 3, 4, 5};
    Storage storage = List::make(list);

    ints result = List::toInts(storage);
    REQUIRE(result == list);
}

TEST_CASE("ints list negative values", "[list]")
{
    ints list = {-100, -50, -1, 0, 1, 50, 100};
    Storage storage = List::make(list);

    ints result = List::toInts(storage);
    REQUIRE(result == list);
}

TEST_CASE("ints list min/max values", "[list]")
{
    ints list = {INT_MIN, 0, INT_MAX};
    Storage storage = List::make(list);

    ints result = List::toInts(storage);
    REQUIRE(result == list);
}

TEST_CASE("ints list large", "[list]")
{
    ints list;
    for (int i = 0; i < 1000; i++)
    {
        list.push_back(i);
    }

    Storage storage = List::make(list);
    ints result = List::toInts(storage);
    REQUIRE(result == list);
}

TEST_CASE("uint64 list empty", "[list]")
{
    std::vector<uint64_t> list = {};
    Storage storage = List::make(list);

    std::vector<uint64_t> result = List::toUInt64s(storage);
    REQUIRE(result == list);
}

TEST_CASE("uint64 list single element", "[list]")
{
    std::vector<uint64_t> list = {42};
    Storage storage = List::make(list);

    std::vector<uint64_t> result = List::toUInt64s(storage);
    REQUIRE(result == list);
}

TEST_CASE("uint64 list all in int range", "[list]")
{
    // All values fit in int - should use WordArray
    std::vector<uint64_t> list = {0, 1, 100, 1000, static_cast<uint64_t>(INT_MAX)};
    Storage storage = List::make(list);

    // Should be stored as WordArray
    REQUIRE(std::holds_alternative<ints>(storage.i));

    std::vector<uint64_t> result = List::toUInt64s(storage);
    REQUIRE(result == list);
}

TEST_CASE("uint64 list some large", "[list]")
{
    // Some values don't fit in int - should use MixedArray
    std::vector<uint64_t> list = {1, UINT64_MAX, 100, 0x123456789ABCDEFULL};
    Storage storage = List::make(list);

    // Should be stored as MixedArray
    REQUIRE(std::holds_alternative<mixed>(storage.i));

    std::vector<uint64_t> result = List::toUInt64s(storage);
    REQUIRE(result == list);
}

TEST_CASE("uint64 list min/max", "[list]")
{
    std::vector<uint64_t> list = {0, UINT64_MAX};
    Storage storage = List::make(list);

    std::vector<uint64_t> result = List::toUInt64s(storage);
    REQUIRE(result == list);
}

TEST_CASE("uint64 list 32-bit boundaries", "[list]")
{
    std::vector<uint64_t> list = {
        0xFFFFFFFF,         // Max 32-bit
        0x100000000ULL,     // Min requiring 2 chunks
        0xFFFFFFFFFFFFFFFFULL // Max 64-bit
    };

    Storage storage = List::make(list);
    std::vector<uint64_t> result = List::toUInt64s(storage);
    REQUIRE(result == list);
}

TEST_CASE("uint64 list radio frequencies", "[list]")
{
    // Test radio frequency use case
    std::vector<uint64_t> frequencies = {
        300000000ULL,       // 3 MHz in centihertz
        1400000000ULL,      // 14 MHz
        2800000000ULL       // 28 MHz
    };

    Storage storage = List::make(frequencies);
    std::vector<uint64_t> result = List::toUInt64s(storage);
    REQUIRE(result == frequencies);
}

TEST_CASE("uint64 list power of two boundaries", "[list]")
{
    std::vector<uint64_t> list = {
        (1ULL << 31) - 1,
        (1ULL << 31),
        (1ULL << 31) + 1,
        (1ULL << 32) - 1,
        (1ULL << 32),
        (1ULL << 32) + 1,
        (1ULL << 63) - 1,
        (1ULL << 63),
        (1ULL << 63) + 1
    };

    Storage storage = List::make(list);
    std::vector<uint64_t> result = List::toUInt64s(storage);
    REQUIRE(result == list);
}

TEST_CASE("uint64 list mixed sizes optimization", "[list]")
{
    // Test that small list uses WordArray
    std::vector<uint64_t> smallList = {1, 2, 3};
    Storage smallStorage = List::make(smallList);
    REQUIRE(std::holds_alternative<ints>(smallStorage.i));

    // Test that large list uses MixedArray
    std::vector<uint64_t> largeList = {1, UINT64_MAX, 3};
    Storage largeStorage = List::make(largeList);
    REQUIRE(std::holds_alternative<mixed>(largeStorage.i));

    // Both should convert back correctly
    std::vector<uint64_t> smallResult = List::toUInt64s(smallStorage);
    std::vector<uint64_t> largeResult = List::toUInt64s(largeStorage);

    REQUIRE(smallResult == smallList);
    REQUIRE(largeResult == largeList);
}

TEST_CASE("uint64 list large list", "[list]")
{
    std::vector<uint64_t> list;
    for (uint64_t i = 0; i < 1000; i++)
    {
        list.push_back(i * 1000000000ULL);
    }

    Storage storage = List::make(list);
    std::vector<uint64_t> result = List::toUInt64s(storage);
    REQUIRE(result == list);
}

TEST_CASE("uint64 list bit patterns", "[list]")
{
    // Test values with specific bit patterns
    std::vector<uint64_t> list = {
        0x0000000000000000ULL,
        0xFFFFFFFFFFFFFFFFULL,
        0x5555555555555555ULL,
        0xAAAAAAAAAAAAAAAAULL,
        0x0F0F0F0F0F0F0F0FULL,
        0xF0F0F0F0F0F0F0F0ULL
    };

    Storage storage = List::make(list);
    std::vector<uint64_t> result = List::toUInt64s(storage);
    REQUIRE(result == list);
}

TEST_CASE("toInts with wrong noun type returns empty", "[list]")
{
    // Create a Storage that's not a LIST
    Storage storage = Integer::make(42);

    ints result = List::toInts(storage);
    REQUIRE(result.empty());
}

TEST_CASE("toUInt64s with wrong noun type returns empty", "[list]")
{
    // Create a Storage that's not a LIST
    Storage storage = Integer::make(42);

    std::vector<uint64_t> result = List::toUInt64s(storage);
    REQUIRE(result.empty());
}

TEST_CASE("toInts with invalid storage type returns empty", "[list]")
{
    // Create a Storage with floats (invalid for int list)
    floats float_array = {1.0f, 2.0f, 3.0f};
    Storage storage(NounType::LIST, StorageType::FLOAT_ARRAY, float_array);

    ints result = List::toInts(storage);
    REQUIRE(result.empty());
}

TEST_CASE("toUInt64s with invalid storage type returns empty", "[list]")
{
    // Create a Storage with floats (invalid for uint64 list)
    floats float_array = {1.0f, 2.0f, 3.0f};
    Storage storage(NounType::LIST, StorageType::FLOAT_ARRAY, float_array);

    std::vector<uint64_t> result = List::toUInt64s(storage);
    REQUIRE(result.empty());
}

TEST_CASE("toUInt64s with negative values returns empty", "[list]")
{
    // Create a WordArray with negative values
    ints list = {1, -42, 3};
    Storage storage(NounType::LIST, StorageType::WORD_ARRAY, list);

    std::vector<uint64_t> result = List::toUInt64s(storage);
    REQUIRE(result.empty());
}

TEST_CASE("toInts from MixedArray", "[list]")
{
    // Create a MixedArray of small integers
    mixed mix = {
        Integer::make(1),
        Integer::make(2),
        Integer::make(3)
    };
    Storage storage(NounType::LIST, StorageType::MIXED_ARRAY, mix);

    ints result = List::toInts(storage);
    ints expected = {1, 2, 3};
    REQUIRE(result == expected);
}

TEST_CASE("toUInt64s from MixedArray", "[list]")
{
    // Create a MixedArray of uint64 values
    mixed mix = {
        Integer::make(static_cast<uint64_t>(1)),
        Integer::make(static_cast<uint64_t>(UINT64_MAX)),
        Integer::make(static_cast<uint64_t>(100))
    };
    Storage storage(NounType::LIST, StorageType::MIXED_ARRAY, mix);

    std::vector<uint64_t> result = List::toUInt64s(storage);
    std::vector<uint64_t> expected = {1, UINT64_MAX, 100};
    REQUIRE(result == expected);
}

TEST_CASE("toInts from MixedArray with non-int returns empty", "[list]")
{
    // Create a MixedArray with a value that can't fit in int
    mixed mix = {
        Integer::make(1),
        Integer::make(static_cast<uint64_t>(UINT64_MAX)), // Too large for int
        Integer::make(3)
    };
    Storage storage(NounType::LIST, StorageType::MIXED_ARRAY, mix);

    ints result = List::toInts(storage);
    REQUIRE(result.empty());
}