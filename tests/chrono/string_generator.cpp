#include "string_generator.hpp"


std::string generateRandomString(size_t length) {
    const std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+-=<>{}[]/|";
    std::string result;
    result.reserve(length);
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, characters.length() - 1);
    for (size_t i = 0; i < length; ++i) {
        result.push_back(characters[distribution(generator)]);
    }
    return result;
}