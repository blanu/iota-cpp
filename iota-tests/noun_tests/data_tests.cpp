//
// Created by Dr. Brandon Wiley on 10/30/25.
//

#include <catch2/catch_all.hpp>
#include <cstdint>

#include <storage/storage.h>
#include <nouns/data.h>
#include <nouns/integer.h>

TEST_CASE("empty byte array", "[data]")
{
    std::vector<uint8_t> bytes = {};
    Storage storage = Data::make(bytes);

    REQUIRE(std::holds_alternative<ints>(storage.i));

    maybe<std::vector<uint8_t>> result = Data::toBytes(storage);
    REQUIRE(result.has_value());
    REQUIRE(result->empty());
}

TEST_CASE("single byte", "[data]")
{
    std::vector<uint8_t> bytes = {0x42};
    Storage storage = Data::make(bytes);

    maybe<std::vector<uint8_t>> result = Data::toBytes(storage);
    REQUIRE(result.has_value());
    REQUIRE(*result == bytes);
}

TEST_CASE("three bytes (example from spec)", "[data]")
{
    std::vector<uint8_t> bytes = {0xFF, 0xFF, 0xFF};
    Storage storage = Data::make(bytes);

    REQUIRE(std::holds_alternative<ints>(storage.i));
    const ints& is = std::get<ints>(storage.i);

    // First int is trim count (should be 1 for 3 bytes on 32-bit)
    REQUIRE(is[0] == 1);
    // Second int contains the 3 bytes packed, padded on right
    REQUIRE(static_cast<uint32_t>(is[1]) == 0xFFFFFF00);

    maybe<std::vector<uint8_t>> result = Data::toBytes(storage);
    REQUIRE(result.has_value());
    REQUIRE(*result == bytes);
}

TEST_CASE("four bytes (full word)", "[data]")
{
    std::vector<uint8_t> bytes = {0xDE, 0xAD, 0xBE, 0xEF};
    Storage storage = Data::make(bytes);

    REQUIRE(std::holds_alternative<ints>(storage.i));
    const ints& is = std::get<ints>(storage.i);

    // Trim count should be 0 (no trimming needed)
    REQUIRE(is[0] == 0);
    REQUIRE(static_cast<uint32_t>(is[1]) == 0xDEADBEEF);

    maybe<std::vector<uint8_t>> result = Data::toBytes(storage);
    REQUIRE(result.has_value());
    REQUIRE(*result == bytes);
}

TEST_CASE("five bytes", "[data]")
{
    std::vector<uint8_t> bytes = {0x01, 0x02, 0x03, 0x04, 0x05};
    Storage storage = Data::make(bytes);

    REQUIRE(std::holds_alternative<ints>(storage.i));
    const ints& is = std::get<ints>(storage.i);

    // Should have trim count of 3, two data words
    REQUIRE(is[0] == 3);
    REQUIRE(is.size() == 3);

    maybe<std::vector<uint8_t>> result = Data::toBytes(storage);
    REQUIRE(result.has_value());
    REQUIRE(*result == bytes);
}

TEST_CASE("eight bytes (two full words)", "[data]")
{
    std::vector<uint8_t> bytes = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};
    Storage storage = Data::make(bytes);

    REQUIRE(std::holds_alternative<ints>(storage.i));
    const ints& is = std::get<ints>(storage.i);

    REQUIRE(is[0] == 0); // No trimming
    REQUIRE(is.size() == 3); // Trim count + 2 words
    REQUIRE(static_cast<uint32_t>(is[1]) == 0x12345678);
    REQUIRE(static_cast<uint32_t>(is[2]) == 0x9ABCDEF0);

    maybe<std::vector<uint8_t>> result = Data::toBytes(storage);
    REQUIRE(result.has_value());
    REQUIRE(*result == bytes);
}

TEST_CASE("nine bytes", "[data]")
{
    std::vector<uint8_t> bytes = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09};
    Storage storage = Data::make(bytes);

    maybe<std::vector<uint8_t>> result = Data::toBytes(storage);
    REQUIRE(result.has_value());
    REQUIRE(*result == bytes);
}

TEST_CASE("all zeros", "[data]")
{
    std::vector<uint8_t> bytes = {0x00, 0x00, 0x00, 0x00, 0x00};
    Storage storage = Data::make(bytes);

    maybe<std::vector<uint8_t>> result = Data::toBytes(storage);
    REQUIRE(result.has_value());
    REQUIRE(*result == bytes);
}

TEST_CASE("all ones", "[data]")
{
    std::vector<uint8_t> bytes = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    Storage storage = Data::make(bytes);

    maybe<std::vector<uint8_t>> result = Data::toBytes(storage);
    REQUIRE(result.has_value());
    REQUIRE(*result == bytes);
}

TEST_CASE("alternating pattern", "[data]")
{
    std::vector<uint8_t> bytes = {0xAA, 0x55, 0xAA, 0x55, 0xAA};
    Storage storage = Data::make(bytes);

    maybe<std::vector<uint8_t>> result = Data::toBytes(storage);
    REQUIRE(result.has_value());
    REQUIRE(*result == bytes);
}

TEST_CASE("large byte array", "[data]")
{
    // 100 bytes
    std::vector<uint8_t> bytes;
    for (int i = 0; i < 100; i++) {
        bytes.push_back(static_cast<uint8_t>(i & 0xFF));
    }

    Storage storage = Data::make(bytes);

    maybe<std::vector<uint8_t>> result = Data::toBytes(storage);
    REQUIRE(result.has_value());
    REQUIRE(*result == bytes);
}

TEST_CASE("round trip various sizes", "[data]")
{
    for (int size = 1; size <= 20; size++) {
        std::vector<uint8_t> bytes;
        for (int i = 0; i < size; i++) {
            bytes.push_back(static_cast<uint8_t>((i * 17) & 0xFF));
        }

        Storage storage = Data::make(bytes);
        maybe<std::vector<uint8_t>> result = Data::toBytes(storage);

        REQUIRE(result.has_value());
        REQUIRE(*result == bytes);
    }
}

TEST_CASE("toBytes with non-data storage returns nullopt", "[data]")
{
    // Create an integer storage instead of data
    Storage storage = Integer::make(42);

    maybe<std::vector<uint8_t>> result = Data::toBytes(storage);
    REQUIRE_FALSE(result.has_value());
}

TEST_CASE("toBytes with invalid trim count returns nullopt", "[data]")
{
    // Manually create invalid data: trim count larger than possible
    ints chunks = {100, 0x12345678}; // Trim count of 100 is invalid
    Storage storage(NounType::DATA, StorageType::WORD_ARRAY, chunks);

    maybe<std::vector<uint8_t>> result = Data::toBytes(storage);
    REQUIRE_FALSE(result.has_value());
}

TEST_CASE("bit patterns preserved through round trip", "[data]")
{
    // Test that exact bit patterns are preserved
    std::vector<uint8_t> bytes = {0x80, 0x00, 0x00, 0x01, 0xFF, 0x7F};
    Storage storage = Data::make(bytes);

    maybe<std::vector<uint8_t>> result = Data::toBytes(storage);
    REQUIRE(result.has_value());

    for (size_t i = 0; i < bytes.size(); i++) {
        REQUIRE((*result)[i] == bytes[i]);
    }
}

TEST_CASE("sequential byte values", "[data]")
{
    std::vector<uint8_t> bytes = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
    Storage storage = Data::make(bytes);

    maybe<std::vector<uint8_t>> result = Data::toBytes(storage);
    REQUIRE(result.has_value());
    REQUIRE(*result == bytes);
}

TEST_CASE("reverse sequential byte values", "[data]")
{
    std::vector<uint8_t> bytes = {0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00};
    Storage storage = Data::make(bytes);

    maybe<std::vector<uint8_t>> result = Data::toBytes(storage);
    REQUIRE(result.has_value());
    REQUIRE(*result == bytes);
}

TEST_CASE("data type is set correctly", "[data]")
{
    std::vector<uint8_t> bytes = {0x12, 0x34, 0x56};
    Storage storage = Data::make(bytes);

    REQUIRE(storage.o == NounType::DATA);
}