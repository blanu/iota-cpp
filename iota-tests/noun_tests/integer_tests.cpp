//
// Created by Dr. Brandon Wiley on [date]
//

#include <catch2/catch_all.hpp>
#include <cstdint>

#include <transmission-cpp.h>
#include "nouns/integer.h"
#include "nouns/noun.h"
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

TEST_CASE("long small golden value conn", "[integer][conn]")
{
    Pipe pipe;
    int64_t value = 123456789012345LL; // 0x70488600DF79 in encoding

    // Expected bytes: type bytes + length (8) + 8 bytes
    std::vector<char> expected = {
        0x00, 0x00, 0x08, 0x00, 0x00, 0x70, 0x48, static_cast<char>(0x86),
        0x0D, static_cast<char>(0xDF), 0x79
    };

    pipe.getEndA().write(expected);
    maybe<Storage> decoded = Noun::from_conn(pipe.getEndB());
    REQUIRE(decoded.has_value());

    // For int64_t, we need to check if it fits in int or use WordArray
    // Since this value is larger than INT_MAX, it will be a WordArray
    REQUIRE(std::holds_alternative<ints>(decoded->i));

    // Test reverse direction
    Storage storage = Integer::make(static_cast<uint64_t>(value));
    Noun::to_conn(pipe.getEndA(), storage);

    std::vector<char> bytes = pipe.getEndB().read(expected.size());
    REQUIRE(bytes == expected);
}

TEST_CASE("radio frequency golden value conn", "[integer][conn]")
{
    Pipe pipe;
    uint64_t frequency = 1400000061ULL; // Encodes as 0x53724E3D

    // Expected bytes: type bytes + length (4) + 4 bytes
    std::vector<char> expected = {
        0x00, 0x00, 0x04, 0x53, 0x72, 0x4E, 0x3D
    };

    pipe.getEndA().write(expected);
    maybe<Storage> decoded = Noun::from_conn(pipe.getEndB());
    REQUIRE(decoded.has_value());

    uint64_t* result = Integer::toUInt64(*decoded);
    REQUIRE(result != nullptr);
    REQUIRE(*result == frequency);
    delete result;

    // Test reverse direction
    Storage storage = Integer::make(frequency);
    Noun::to_conn(pipe.getEndA(), storage);

    std::vector<char> bytes = pipe.getEndB().read(expected.size());
    REQUIRE(bytes == expected);
}

TEST_CASE("BigInteger small golden value conn", "[integer][conn][bigint]")
{
    Pipe pipe;
    uint64_t value = 123456789012345ULL;

    // Expected bytes: type bytes + length (8) + 8 bytes
    std::vector<char> expected = {
        0x00, 0x00, 0x08, 0x00, 0x00, 0x70, 0x48, static_cast<char>(0x86),
        0x0D, static_cast<char>(0xDF), 0x79
    };

    pipe.getEndA().write(expected);
    maybe<Storage> decoded = Noun::from_conn(pipe.getEndB());
    REQUIRE(decoded.has_value());

    // Verify the value can be converted to uint64
    uint64_t* result = Integer::toUInt64(*decoded);
    REQUIRE(result != nullptr);
    REQUIRE(*result == value);
    delete result;
}

TEST_CASE("BigInteger power of 2 golden value conn", "[integer][conn][bigint]")
{
    Pipe pipe;
    // 2^100 = 1267650600228229401496703205376

    // Expected bytes: type bytes + length (16) + 16 bytes
    std::vector<char> expected = {
        0x00, 0x00, 0x10,
        0x00, 0x00, 0x00, 0x10,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00
    };

    pipe.getEndA().write(expected);
    maybe<Storage> decoded = Noun::from_conn(pipe.getEndB());
    REQUIRE(decoded.has_value());

    // Verify it's a WordArray (too large for uint64)
    REQUIRE(std::holds_alternative<ints>(decoded->i));
}

TEST_CASE("BigInteger large golden value conn", "[integer][conn][bigint]")
{
    Pipe pipe;
    // 123456789012345678901234567890 = 0x18EE90FF6C373E0EE4E3F0AD2

    // Expected bytes: type bytes + length (16) + 16 bytes
    std::vector<char> expected = {
        0x00, 0x00, 0x10,
        0x00, 0x00, 0x00, 0x01, static_cast<char>(0x8E), static_cast<char>(0xE9),
        0x0F, static_cast<char>(0xF6), static_cast<char>(0xC3), 0x73,
        static_cast<char>(0xE0), static_cast<char>(0xEE), 0x4E,
        0x3F, 0x0A, static_cast<char>(0xD2)
    };

    pipe.getEndA().write(expected);
    maybe<Storage> decoded = Noun::from_conn(pipe.getEndB());
    REQUIRE(decoded.has_value());

    // Verify it's a WordArray (too large for uint64)
    REQUIRE(std::holds_alternative<ints>(decoded->i));
}

TEST_CASE("BigInteger negative golden value conn", "[integer][conn][bigint]")
{
    Pipe pipe;
    // -987654321098765432109876543210
    // Absolute value in hex: 0xC7748819DFFB62438D1C67EEA

    // Expected bytes: type bytes + length with sign (0x90) + 16 bytes
    std::vector<char> expected = {
        0x00, 0x00, static_cast<char>(0x90),
        0x00, 0x00, 0x00, 0x0C, 0x77,
        0x48, static_cast<char>(0x81), static_cast<char>(0x9D), static_cast<char>(0xFF),
        static_cast<char>(0xB6), 0x24, 0x38, static_cast<char>(0xD1),
        static_cast<char>(0xC6), 0x7E, static_cast<char>(0xEA)
    };

    pipe.getEndA().write(expected);
    maybe<Storage> decoded = Noun::from_conn(pipe.getEndB());
    REQUIRE(decoded.has_value());

    // Verify it's a WordArray (large negative number)
    REQUIRE(std::holds_alternative<ints>(decoded->i));

    // Verify sign bit is set (negative)
    const ints& chunks = std::get<ints>(decoded->i);
    REQUIRE(chunks.size() > 0);
    REQUIRE(chunks[0] == 1); // Sign bit = 1 for negative
}