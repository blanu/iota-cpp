#ifndef ERROR_H_
#define ERROR_H_

#include "../storage/storage.h"

#define BAD_INDEX_TYPE 0
#define BAD_INITIALIZATION 1
#define BAD_STORAGE 2
#define BAD_OPERATION 3
#define EMPTY 4
#define INVALID_ARGUMENT 5
#define INVALID_ADVERB_ARGUMENT 6
#define OUT_OF_BOUNDS 7
#define SHAPE_MISMATCH 8
#define TEST_ERROR 9
#define UNSUPPORTED_OBJECT 10
#define UNSUPPORTED_SUBJECT 11
#define UNKNOWN_KEY 12
#define UNEQUAL_ARRAY_LENGTHS 13
#define DIVISION_BY_ZERO 14
#define MAXIMUM_ITERATIONS 15

class Error
{
  public:
    static constexpr int bad_index_type = BAD_INDEX_TYPE;
    static constexpr int bad_initialization = BAD_INITIALIZATION;
    static constexpr int bad_storage = BAD_STORAGE;
    static constexpr int bad_operation = BAD_OPERATION;
    static constexpr int empty = EMPTY;
    static constexpr int invalid_argument = INVALID_ARGUMENT;
    static constexpr int invalid_adverb_argument = INVALID_ADVERB_ARGUMENT;
    static constexpr int out_of_bounds = OUT_OF_BOUNDS;
    static constexpr int shape_mismatch = SHAPE_MISMATCH;
    static constexpr int test_error = TEST_ERROR;
    static constexpr int unsupported_object = UNSUPPORTED_OBJECT;
    static constexpr int unsupported_subject = UNSUPPORTED_SUBJECT;
    static constexpr int unknown_key = UNKNOWN_KEY;
    static constexpr int unequal_array_lengths = UNEQUAL_ARRAY_LENGTHS;
    static constexpr int division_by_zero = DIVISION_BY_ZERO;
    static constexpr int maximum_iterations = MAXIMUM_ITERATIONS;

    static Storage make(int i);

    int code;

    bool operator==(const Error& rhs) const
    {
      return code == rhs.code; // Compare member variables
    }

    [[nodiscard]] std::string string() const;
};

template<>
struct std::hash<Error>
{
  std::size_t operator()(const Error& i) const noexcept
  {
    return std::hash<int>()(i.code);
  }
};

#endif