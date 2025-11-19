//
// Created by Dr. Brandon Wiley on 11/16/25.
//

#include "IotaRepl.h"

#include <iostream>
#include <string>
#include <cctype>

#include "api.h"
#include "eval_register.h"
#include "nouns/integer.h"
#include "nouns/iota_string.h"

IotaRepl::IotaRepl()
{
    // Initialize the entire iota system
    EvalRegister::initialize();
}

void IotaRepl::run()
{
    std::cout << "iota REPL v0.1" << std::endl;
    std::cout << "Type an integer and press Enter (Ctrl+D or Ctrl+C to exit)" << std::endl;
    std::cout << std::endl;

    while (true)
    {
        // Read
        std::string input = read_line();

        // Check for EOF
        if (std::cin.eof())
        {
            std::cout << std::endl << "Goodbye!" << std::endl;
            break;
        }

        // Skip empty lines
        if (input.empty())
        {
            continue;
        }

        // Parse
        auto noun_opt = parse(input);
        if (!noun_opt)
        {
            print_error("Failed to parse input");
            continue;
        }

        // Eval
        auto result_opt = evalExpressionCppToIota({*noun_opt});
        print(result_opt);
    }
}

std::string IotaRepl::read_line()
{
    std::cout << "iota> " << std::flush;

    std::string line;
    if (std::getline(std::cin, line))
    {
        return line;
    }

    return "";
}

std::optional<cppValue> IotaRepl::parse(const std::string& input)
{
    // Trim whitespace
    size_t start = 0;
    size_t end = input.length();

    while (start < end && std::isspace(input[start]))
    {
        start++;
    }

    while (end > start && std::isspace(input[end - 1]))
    {
        end--;
    }

    if (start >= end)
    {
        return std::nullopt;
    }

    std::string trimmed = input.substr(start, end - start);

    // Try to parse as integer
    return parse_integer(trimmed);
}

std::optional<cppValue> IotaRepl::parse_integer(const std::string& input)
{
    // Check if all characters are digits (with optional leading minus/plus)
    size_t start_idx = 0;

    if (!input.empty() && (input[0] == '-' || input[0] == '+'))
    {
        start_idx = 1;

        if (input.length() == 1)
        {
            return std::nullopt;
        }
    }

    for (size_t i = start_idx; i < input.length(); i++)
    {
        if (!std::isdigit(input[i]))
        {
            return std::nullopt;
        }
    }

    // Use Integer::makeDecimal to parse integers of any size
    try
    {
        Storage storage = Integer::makeDecimal(input);

        // Check if parsing failed
        if (storage.o == NounType::ERROR)
        {
            return std::nullopt;
        }

        // Debug: print what we got
        std::cerr << "Parsed storage type: " << storage.t << ", noun type: " << storage.o << std::endl;
        if (std::holds_alternative<int>(storage.i))
        {
            std::cerr << "  Contains int: " << std::get<int>(storage.i) << std::endl;
        }
        else if (std::holds_alternative<ints>(storage.i))
        {
            const ints& chunks = std::get<ints>(storage.i);
            std::cerr << "  Contains " << chunks.size() << " chunks" << std::endl;
        }

        // Convert Storage to cppValue
        cppValue result = Object::to_cpp(storage);

        return result;
    }
    catch (...)
    {
        return std::nullopt;
    }
}

std::optional<cppValue> IotaRepl::eval(const cppValue& noun)
{
    try
    {
        cppValue result = evalNoun(noun);

        // Check if result is an error
        if (std::holds_alternative<Error>(result))
        {
            Error error = std::get<Error>(result);
            print_error("Evaluation error code: " + std::to_string(error.code));
            return std::nullopt;
        }

        return result;
    }
    catch (const std::exception& e)
    {
        print_error(std::string("Exception during evaluation: ") + e.what());
        return std::nullopt;
    }
    catch (...)
    {
        print_error("Unknown error during evaluation");
        return std::nullopt;
    }
}

void IotaRepl::print(const Storage& result)
{
    using namespace iota;

    Storage is = evalExpressionCppToIota({result, format});
    std::string s = IotaString::toString(is);
    std::cout << s << std::endl;
}

void IotaRepl::print_error(const std::string& message)
{
    std::cerr << "Error: " << message << std::endl;
}