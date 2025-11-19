//
// Created by Dr. Brandon Wiley on 11/16/25.
//

#ifndef IOTAREPL_H
#define IOTAREPL_H

#include <string>
#include <optional>

#include "api.h"

class IotaRepl
{
  public:
    IotaRepl();
    ~IotaRepl() = default;

    // Main REPL loop
    void run();

  private:
    // Display the prompt and get user input
    std::string read_line();

    // Parse input string into a cppValue object
    // Returns nullopt if parsing fails
    std::optional<cppValue> parse(const std::string& input);

    // Evaluate the cppValue using evalNoun
    std::optional<cppValue> eval(const cppValue& noun);

    // Print the result
    void print(const Storage& result);

    // Print error message
    void print_error(const std::string& message);

    // Parse an integer literal
    std::optional<cppValue> parse_integer(const std::string& input);
};

#endif //IOTAREPL_H