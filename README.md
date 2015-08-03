# Drako's DI Container

[![Join the chat at https://gitter.im/Drako/ddic](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/Drako/ddic?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

This is a light weight DI (Dependency Injection) Container written in C++11.
It does not rely on external dependencies and avoids the use of macros.

## Requirements

 * A recent C++ compiler with more or less complete C++11 support (GCC and Clang are good bets, MSVC >= 2013 should also work)
 * CMake >= 3.1

## Unit Tests

*ddic* comes with unit tests based on Google Test (gtest) and Google Mock (gmock).
For simplicity the versions of gtest and gmock I used, are bundled with ddic.
The library itself has no other external dependencies.

The unit tests are disabled by default, but can be enabled running CMake like this:

```bash
# enable unit tests
cmake -DWITH_TESTS=ON <source dir>
# build and run the tests like this
cmake --target test --config <Debug|Release> --build <build dir>
```

