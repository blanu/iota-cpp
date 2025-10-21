//
// Created by Dr. Brandon Wiley on [date]
//

#include <catch2/catch_all.hpp>
#include <cstdint>

#include "nouns/integer.h"
#include "storage/storage.h"

TEST_CASE("int to storage and back", "[integer]")
{
    int value = 42;
    Storage storage = Integer::make(value);

    // Should be a Word
    REQUIRE(std::holds_alternative<int>(storage.i));
    REQUIRE(std::get<int>(storage.i) == value);
}

TEST_CASE("int min/max values", "[integer]")
{
    Storage minStorage = Integer::make(INT_MIN);
    Storage maxStorage = Integer::make(INT_MAX);

    REQUIRE(std::holds_alternative<int>(minStorage.i));
    REQUIRE(std::holds_alternative<int>(maxStorage.i));
    REQUIRE(std::get<int>(minStorage.i) == INT_MIN);
    REQUIRE(std::get<int>(maxStorage.i) == INT_MAX);
}

TEST_CASE("uint64_t small value", "[integer]")
{
    uint64_t value = 42;
    Storage storage = Integer::make(value);

    uint64_t* result = Integer::toUInt64(storage);
    REQUIRE(result != nullptr);
    REQUIRE(*result == value);
    delete result;
}

TEST_CASE("uint64_t zero", "[integer]")
{
    uint64_t value = 0;
    Storage storage = Integer::make(value);

    uint64_t* result = Integer::toUInt64(storage);
    REQUIRE(result != nullptr);
    REQUIRE(*result == value);
    delete result;
}

TEST_CASE("uint64_t max int32", "[integer]")
{
    uint64_t value = INT_MAX;
    Storage storage = Integer::make(value);

    // Should be stored as Word
    REQUIRE(std::holds_alternative<int>(storage.i));

    uint64_t* result = Integer::toUInt64(storage);
    REQUIRE(result != nullptr);
    REQUIRE(*result == value);
    delete result;
}

TEST_CASE("uint64_t just above int32", "[integer]")
{
    uint64_t value = static_cast<uint64_t>(INT_MAX) + 1;
    Storage storage = Integer::make(value);

    // Should be stored as WordArray
    REQUIRE(std::holds_alternative<ints>(storage.i));

    uint64_t* result = Integer::toUInt64(storage);
    REQUIRE(result != nullptr);
    REQUIRE(*result == value);
    delete result;
}

TEST_CASE("uint64_t 32-bit boundary", "[integer]")
{
    uint64_t value = 0xFFFFFFFF; // Max 32-bit value
    Storage storage = Integer::make(value);

    uint64_t* result = Integer::toUInt64(storage);
    REQUIRE(result != nullptr);
    REQUIRE(*result == value);
    delete result;
}

TEST_CASE("uint64_t just above 32-bit", "[integer]")
{
    uint64_t value = 0x100000000ULL; // 2^32
    Storage storage = Integer::make(value);

    uint64_t* result = Integer::toUInt64(storage);
    REQUIRE(result != nullptr);
    REQUIRE(*result == value);
    delete result;
}

TEST_CASE("uint64_t max value", "[integer]")
{
    uint64_t value = UINT64_MAX;
    Storage storage = Integer::make(value);

    uint64_t* result = Integer::toUInt64(storage);
    REQUIRE(result != nullptr);
    REQUIRE(*result == value);
    delete result;
}

TEST_CASE("uint64_t various large values", "[integer]")
{
    uint64_t values[] = {
        0x123456789ABCDEFULL,
        0x8000000000000000ULL, // 2^63
        0xFFFFFFFFFFFFFFFEULL, // UINT64_MAX - 1
        0x0000000100000000ULL, // 2^32
        0x00000000FFFFFFFFULL  // 2^32 - 1
    };

    for (uint64_t value : values)
    {
        Storage storage = Integer::make(value);
        uint64_t* result = Integer::toUInt64(storage);
        REQUIRE(result != nullptr);
        REQUIRE(*result == value);
        delete result;
    }
}

TEST_CASE("uint64_t radio frequency use case", "[integer]")
{
    // Test radio frequencies in centihertz
    // 14 MHz = 1,400,000,000 centihertz
    uint64_t baseFreq = 1400000000ULL;
    uint64_t offset = 61; // 0.61 Hz in centihertz
    uint64_t frequency = baseFreq + offset;

    Storage storage = Integer::make(frequency);
    uint64_t* result = Integer::toUInt64(storage);
    REQUIRE(result != nullptr);
    REQUIRE(*result == frequency);
    delete result;
}

TEST_CASE("uint64_t power of two boundaries", "[integer]")
{
    // Test values near powers of 2
    for (int power = 32; power < 64; power++)
    {
        uint64_t base = 1ULL << power;

        uint64_t values[] = {
            base - 1,
            base,
            base + 1
        };

        for (uint64_t value : values)
        {
            Storage storage = Integer::make(value);
            uint64_t* result = Integer::toUInt64(storage);
            REQUIRE(result != nullptr);
            REQUIRE(*result == value);
            delete result;
        }
    }
}

TEST_CASE("uint64_t round trip with WordArray", "[integer]")
{
    // Test that large values requiring WordArray representation work correctly
    uint64_t values[] = {
        0x0000000100000000ULL,
        0x1234567890ABCDEFULL,
        0xFEDCBA9876543210ULL,
        0x8000000000000001ULL
    };

    for (uint64_t value : values)
    {
        Storage storage = Integer::make(value);

        // Verify it's stored as WordArray (since > INT_MAX)
        REQUIRE(std::holds_alternative<ints>(storage.i));

        uint64_t* result = Integer::toUInt64(storage);
        REQUIRE(result != nullptr);
        REQUIRE(*result == value);
        delete result;
    }
}

TEST_CASE("negative int cannot convert to uint64", "[integer]")
{
    int value = -42;
    Storage storage = Integer::make(value);

    uint64_t* result = Integer::toUInt64(storage);
    REQUIRE(result == nullptr); // Should return null for negative values
}

TEST_CASE("negative WordArray cannot convert to uint64", "[integer]")
{
    // Manually create a negative WordArray
    ints chunks = {1, 0x12345678}; // Sign bit = 1 (negative)
    Storage storage(NounType::INTEGER, StorageType::WORD_ARRAY, chunks);

    uint64_t* result = Integer::toUInt64(storage);
    REQUIRE(result == nullptr); // Should return null for negative values
}

TEST_CASE("empty WordArray returns null", "[integer]")
{
    ints chunks = {}; // Empty
    Storage storage(NounType::INTEGER, StorageType::WORD_ARRAY, chunks);

    uint64_t* result = Integer::toUInt64(storage);
    REQUIRE(result == nullptr);
}

TEST_CASE("WordArray with too many chunks returns null", "[integer]")
{
    // Create WordArray with 3 chunks (plus sign) = 4 elements total
    // This is too large for uint64_t (max 2 chunks)
    ints chunks = {0, static_cast<int>(0x12345678), static_cast<int>(0x9ABCDEF0), static_cast<int>(0x11111111)};
    Storage storage(NounType::INTEGER, StorageType::WORD_ARRAY, chunks);

    uint64_t* result = Integer::toUInt64(storage);
    REQUIRE(result == nullptr);
}

TEST_CASE("uint64_t bit pattern preservation", "[integer]")
{
    // Test that bit patterns are preserved, not numerical values
    // Use values where signed/unsigned interpretation differs significantly
    uint64_t value = 0x8000000012345678ULL;

    Storage storage = Integer::make(value);
    uint64_t* result = Integer::toUInt64(storage);
    REQUIRE(result != nullptr);
    REQUIRE(*result == value);

    // Verify exact bit pattern
    REQUIRE(std::holds_alternative<ints>(storage.i));
    const ints& chunks = std::get<ints>(storage.i);

    // Should have sign bit + 2 chunks
    REQUIRE(chunks.size() == 3);
    REQUIRE(chunks[0] == 0); // Sign bit (positive)

    // High 32 bits: 0x80000000 as signed int is -2147483648
    // But bit pattern should be preserved
    uint32_t high = static_cast<uint32_t>(chunks[1]);
    uint32_t low = static_cast<uint32_t>(chunks[2]);

    uint64_t reconstructed = (static_cast<uint64_t>(high) << 32) | low;
    REQUIRE(reconstructed == value);

    delete result;
}

TEST_CASE("invalid storage type returns null", "[integer]")
{
    // Create a Storage with a float (invalid for uint64 conversion)
    Storage storage(NounType::INTEGER, StorageType::FLOAT, 3.14f);

    uint64_t* result = Integer::toUInt64(storage);
    REQUIRE(result == nullptr); // Should return null for invalid storage type
}