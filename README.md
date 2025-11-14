# iota

iota is a small programming language.

It implements the operations from klong, which is a dialect of APL in the k family.

# The iota-cpp Project

The iota-cpp project is an implementation of the iota programming language in C++ that is portable across
Arduino-compatible microcontrollers and Linux-compatible microprocessors. It contains both a cross-platform core and
platform-specific extensions for Arduino and Linux.

## Dependencies:
- cmake, ninja
- arduino-cli (for iota-arduino and iota-arduino-protocol-server)
- A c++ compiler on your host system (for iota-stdio)
- If you want to test it on an Arduino, you need an Adafruit RP2350 Feather with HSTX at the moment.

The whole project and all build targets are built from the top-level project using cmake, using the usual invocation:
```aiignore
mkdir build
cd build
cmake ..
make
```

## The iota-cpp Library

The core of the iota-cpp project is the iota-cpp library. This both compiles as a static library for Linux and can be
imported as an Arduino library.

A core principle of iota is that it is portable. It is agnostic to platform-specific differences such as processor type,
machine word size, and endianness. It does require a compiler compatible with the C++17 standard, which is unfortunately
not available for all Arduino cores. Modern cores such as the RP2040/RP2350 and Teensy 4.0/4.1 support C++17.

## The iota-stdio Executable

The goal of iota-stdio is to give you a simple interface for Linux where you can pipe iota programs into this executable
and pipe the results of the computation back out. Right now, this is just an empty template for the code that will be
written later. The purpose it serves is to have a Linux target to compile against in order to ensure that the iota-cpp
libraries compiles on Linux.

## The iota-arduino Library

The iota-arduino library adds Arduino-specific functionality on top of iota-cpp. This code should be cross-platform to
any Arduino cores that support the C++17 standard. Right now, the main functionality this adds is serial input and
output. However, in the future this is where things like GPIO, I2C, and SPI interfaces will be added.

### The iota-arduino-protocol-server Example

Inside iota-arduino/examples is the iota-arduino-protocol-server program. If you run this on your Arduino, it will set
it up to read serialized iota programs through the Arduino's serial port, evaluate the programs, and write a serialized
version of the result of the computation back out of the serial port. This allows for a debugging feature that I call
"drive-by-wire". You can write programs on one machine (say your Linux computer) and then run them on an Arduino. This
is very handy for testing code and trying out different features of the language. There is a separate repository, sip
(Serial iota for Python), that has a full suite of unit tests, all written in python, that you can run on your Arduino
using iota-arduino-protocol-server and drive-by-wire.

## Features
- Beautiful code, written meticulously and with love in my heart
- Cross-platform between microcontrollers (Arduino) and microprocessors (Linux)
- Builds for all supported platforms, including cross-compiling, on your host machine with one build process (cmake)
- Contains no Rust code, has never been "entirely rewritten in Rust" as is the trend these days (this might be an anti-feature for some)
- Easily extensible to add new nouns and verbs

## Description

iota implements the following design paradigms:
- Object-oriented
- Protocol-oriented
- Functional
- Array
- Concatenative
- Effect-oriented

It is inspired by lots of language, but primarily:
- APL/K/J/Q
- Smalltalk
- Forth
- Haskell

### Audience

iota is a practical language for makers. It is designed to be used to quickly make and debug implementations of ideas.
Conceptually, it should be able to run everywhere, on everything. Programs should be easy to understand and easy to debug.
Low-level bookkeeping is handled by the language implementation so that the programmers can work on their applications
rather than memory management or fighting with the compiler to get something to type check.
It fits a niche similar to python but without the sometimes unacceptable performance hit.
It is interpreted, so it is agile when people using for changing needs and circumstances.

iota is a good language for creating innovative new concepts, such as art, music, games, and interactive systems that change constantly, such as home automation.
It is a language optimized for Do-It-Yourself projects.

While iota contains seem new ideas on programming language design, it is not intended to be a pure research language, but rather a general-purpose language for real-world projects.
It is multi-paradigm, but not in the sense of "there is more than one right way to do things", rather in the sense of cherry-picking certain ideas from each paradigm and using them
parsimoniously to best effect. It also aims to have a very minimal syntax with the majority of its expressive power coming from composition of its core features and the use of
abstractions such as high-order functions.

At this stage in the development, a concurrency API has not yet been introduced.

### Functions and Function Parameters

iota functions come in three varieties:
- Nilad - takes no parameters
- Monad - takes one parameter on the left
- Dyad - takes two parameters, one on the left and one on the right

If more parameters are needed, a list can be used as a parameter (or two lists for a dyad). The use of a list
parameter also allows for variadic functions, optional parameters with default values, and a vareity of other function
calling styles that are normally done syntactically. The use of dictionary values as parameters allows for named
parameters.

Functions are separated into pure functions and effects. When we talk about functions, we are
talking about pure functions. However, effects are syntactically similar to functions, so much of what we can say about
calling functions and writing user-defined functions also applies to calling effects and writing user-defined effects.

Pure functions do not mutate values. Mutation of a value is an effect and so can only be done by calling an effect.
However, functions can pass around values that are handles to mutable state. Effects can mutate state and so can have
out parameters, but functions cannot.

Parameter naming is usually implicit. The left parameter is called "i" and the right parameter is called "x".

Binding of a function name to an implementation is done at call time using a dynamic dispatch table. The table
is specialized based on the types of the arguments.

All functions return one value. A list can be returned in order to return multiple values. List return values also allow
for optionals return values, error return values, and a variety of other common return types available in other
languages. Functions that do not want to return a value can return an empty list ("nil"). There are no true null values.

Functions are first-class values and can be used a function parameters. Anonymous functions are also supported.

### Type System

All typing is dynamic at runtime. Types are implicit. The main use of types is in the dynamic dispatch table for
function calls. You can call a function to get the type of a value at runtime. Types are first class values, although
there is not much runtime support for them yet other than obtaining the type of a value (including a type).

Functions first class values and so have a function type, but currently there is no introspection to find the type
signature of a function. In fact, functions can have multiple types signatures that are dynamically defined in the
dynamic dispatch table.

There are no traditional pointer types, but there are references types in the form of lenses.

There are no generic types or dependent types as these are not necessary in a dynamically typed system. There is no
type inferenc since all types are dynamic.

As there is no static typing, there is not such a big need for sum and product types, although they can be achieved
at runtime by using data structures such as lists and dictionaries.

Types are not classes. While there are objects (to be covered later), there are no classes. Types are not hierarchal and
there is no inheritance. Inheritance could be implemented using the dynamic dispatch table,
if so desired.

New types can be added by updating the dynamic dispatch table, although currently there are no runtime effects available
to enable this functionality.

#### Numeric Types

Integers are signed. There are two types of integers, machine word size (which depends on the platform) and "big ints",
which are arbitrary precision and used when the number is larger than the machine word size. Both types of integers
have the same interface and so can be used interchangeably.

Floating point numbers are supported using the floating point word size of the platform.

There are no specific numeric types based on different fix bit widths such as int8, float64, etc.

#### Text Types

Characters are machine word size. Strings are lists of characters and so are also machine word size. On a 32-bit
machine this would be considered UTF-32 encoding. UTF-8 strings can be obtained through conversion, but are not
used internally.

#### Constrained Types

Sometimes languages provide types that are semantically constrained. For instance, a boolean can only have two values
but it is not actually stored in a single bit (except perhaps in a bit array). Similarly, unsigned integers are
sometimes used not to get one extra bit of storage, but to ensure that a value cannot be negative. This are
constraints on the range of values representable by a number of the given type. This approach is not supported in iota
as it is a questionable design decision to confuse storage types and constraint types, although it is a very popular thing
to do historically

### Expressions

Evaluation is left-to-right and is eager unless the value is quoted. Quoted values are evaluated by the called function,
allowing for custom control structures such as loops and conditionals being implemented as functions. There is no
implicit lazy evaluation.

Monads are postfix operators and dyads are infix operators. (This distinction does not make sense to apply to Nilads).
Operator overloading is handled by the dynamic dispatch table. Overloading is done by the type of the arguments. Unlike
in some other APLs, iota does not allow one function to have multiple arities, but this can be achieved by using a list
parameter. There is no operator precedence, evaluation is left-to-right with grouping used to specify evaluation order.

All values are immutable. However, some values provided by calling effects are handles to effect state and can be used
with an effect to achieve mutation. In this sense, these values can be considered mutable since they are a reference
to mutable state. However, such values can only be mutated by effects and not be functions, so they are effectively
immutable when used inside of functions and mutable when used inside of effects.

Variables are implicitly named and bound for functions and cannot be reassigned. Traditional variables are available
through effects to store state inside a named handle.

Structuring and destructuring are not provided syntactically due to the lack of bound variables, but the programming
style is such that this feature is not as useful as in some other languages.

Variable scope is lexical and implicit. Shadowing is commonplace due to the reuse of implicitly named variables.

The equivalent of "this" or "self" in iota is "i", which represents the left argument and also "the value being acted
upon".

There are no public/private access controls. All values and their fields are public. However, effects can have internal
state that can be either public or private as provided by the effect's API.

### Flow Control

iota primarily uses expressions. Statements can be achieved through effects. Most control flow is handled through
expressions and functions using a functional approach. All of the usual loops and conditionals are supported through
higher-order functions, as well as functional approaches to control flow such as map and reduce functions.

There are no specific control flow keywords such as "break" and "continue". There is no "goto", but you could probably
make one yourself if you really wanted to, using higher-order functions.

There are no exceptions per se, rather functions can return error values. However, there is some built-in handling of
the evaluation of errors in expressions. When an error is the parameter to a function, the function will not be
evaluated and instead the error will be propagated.

Nondeterminism is not purely functional and so requires the use of effects. Similarly, anything related to time, so as
adding a delay, requires the use of an effect.

### Concurrency

There is not yet a concurrency API, but the pure functional nature of the language with immutable values designed to be
compatible with both concurrency and parallelism.

### Metaprogramming

There is not yet support for metaprogramming, but the fully dynamic nature of the language makes it ideal for any sort of
metaprogramming, including many techniques that are not available in statically typed, compiled languages.

### Syntax

iota does not have syntax in the traditional sense. It is embedded in an implementation language and so uses the syntax
of the implementation language to construct programs, along with some helper code to make this process more convenient.
This implementation is in C++ and so uses C++ syntax.

An iota program is an expression, which is a list of values, some of which are function symbols. An expression starts
with a Nilad function, Nilad effect, or value. Following that is zero or one Monad or Dyad functions or Monad or Dyad
effects. After a Dyad function or effect another value is expected. After that, another Monad or Dyad, and so on.
These expressions are concatenated together to form a program, with the output of the left subexpression being the input
of the right subexpression. Ultimately, the expression yields a single value (possibly a list) and may yield side
effects, depending on if effects were used.

There are also two types of grouping. One type of grouping, for instance "()" in C++, is used to choose the order of
evaluation of subexpressions. Quoting, for instance "{}" in C++ refrains from evaluation of a subexpression altogether
so that the called function can decide how to handle it.

### Effects

There are three fundamental types of things in iota: values, functions, and effects. Values store data or references to
data (including functions and effects and handles to state inside of effects). Functions are pure, taking 0, 1, or 2
values (some of which may be lists) as input parameters and outputting one value without mutating the input parameters.
Effects are syntactically similar to functions, but are semantically completely different. Effects are methods on
objects. They can do literally anything to the objects they represent. This includes mutating state, nondeterminism, and
I/O with the world outside the program. Their resemblance to functions is merely syntactic. Functions can only be
composed out of other functions (and values). Effects can be composed out of other effects, as well as functions and
values.

## Discussion

Let's discuss some of the design paradigms iota implements and how they are implemented in the language.

### Object-oriented

iota effects are objects. They are inspired by Smalltalk objects. They have free reign, but only with their internal
domain (which can include the world outside the program).

### Functional

iota functions are pure. They take immutable values as input parameters and return a single value. They are not allowed
to mutate their input parameters. They are first-class values and can be used as function parameters (as are effects).
Functional approaches are provided for solving problems such as map and reduce for flow control.

### Protocol-oriented

The dynamic dispatch table provides a way to have values of different types conform to the same interface. For instance,
both machine word integers and "big ints" provide the same interface and so can be used interchangeably.

### Array

iota provides functions for working with arrays based on the Klong dialect of APL. A full suite of array-oriented
functions derived from APL's approach to problem solving are provided. iota specifically specializes arrays of machine
word integers and arrays of floats to optimize performance for common computing tasks, avoiding the overhead of "boxed"
types. Throuh the protocol-oriented implementation, specialized high-performance functions can be use interchangeably
with generic functions that work on a broader range of data types, freeing the programming from low-level bookkeeping
without sacrificing performance on performance-critical operations.

### Concatenative

The left-to-right evaluation of expressions allows for the composition of programs through the contasenation of
subexpressions containing a mixture of values, functions, and effects.

### Effect-oriented

Functions and effects are separated with completely different semantics. Computation is done with functions, while
a variety of pragmatic necessities are encapsulated by effects, such as nondeterminism, mutable state, time, and I/O.