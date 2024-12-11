#include <iostream>
#include <chrono>
#include <vector>
#include "chrono_iset.hpp"


using namespace std;
using namespace chrono;

template<typename T>
void chronoInsertISet(size_t elementCount) {
    ISet<T> set;
    auto start = high_resolution_clock::now();
    for (size_t i = 0; i < elementCount; ++i) {
        if constexpr (is_same_v<T, std::string>) {
            set.add(to_string(i));
        } else {
            set.add(i);
        }
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Insertion time for " << elementCount << " elements: " << duration.count() << " ms" << endl;
}

template<typename T>
void chronoRemoveISet(size_t elementCount) {
    ISet<T> set;
    std::vector<T> elements;
    for (size_t i = 0; i < elementCount; ++i) {
        if constexpr (is_same_v<T, std::string>) {
            set.add(to_string(i));
            elements.push_back(to_string(i));
        } else {
            set.add(i);
            elements.push_back(i);
        }
    }
    auto start = high_resolution_clock::now();
    for (const auto& element : elements) {
        set.remove(element);
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Removal time for " << elementCount << " elements: " << duration.count() << " ms" << endl;
}

void chronoISet(size_t num_elements) {
    cout << "ISet tests for <int>:" << endl;
    chronoInsertISet<int>(num_elements);
    chronoRemoveISet<int>(num_elements);
    cout << endl;

    cout << "ISet tests for <string>:" << endl;
    chronoInsertISet<string>(num_elements);
    chronoRemoveISet<string>(num_elements);
    cout << endl;
}