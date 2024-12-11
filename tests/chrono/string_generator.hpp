#pragma once

#include <random>
#include <string>


using namespace std;

string generateRandomString(size_t length) {
    const string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+-=<>{}[]/|";
    string result;
    result.reserve(length);
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> distribution(0, characters.length() - 1);
    for (size_t i = 0; i < length; ++i) {
        result.push_back(characters[distribution(generator)]);
    }
    return result;
}