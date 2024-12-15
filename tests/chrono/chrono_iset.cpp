#include <iostream>
#include <chrono>
#include <vector>
#include <set>
#include "chrono_iset.hpp"
#include "demangle.hpp"


using namespace std;
using namespace chrono;

template<typename T, typename Container>
void chronoInsertSet(size_t elementCount) {
    Container set;
    auto start = high_resolution_clock::now();
    for (size_t i = 0; i < elementCount; ++i) {
        if constexpr (is_same_v<Container, ISet<T>>) {
            if constexpr (is_same_v<T, std::string>) {
                set.add(to_string(i));
            } else {
                set.add(i);
            }
        } else {
            if constexpr (is_same_v<T, std::string>) {
                set.insert(to_string(i));
            } else {
                set.insert(i);
            }
        }
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Insertion time for " << elementCount << " elements " << demangle(typeid(Container).name()) << ": "
         << duration.count() << " ms" << endl;
}

template<typename T, typename Container>
void chronoRemoveSet(size_t elementCount) {
    Container set;
    std::vector<T> elements;
    for (size_t i = 0; i < elementCount; ++i) {
        if constexpr (is_same_v<Container, ISet<T>>) {
            if constexpr (is_same_v<T, std::string>) {
                set.add(to_string(i));
                elements.push_back(to_string(i));
            } else {
                set.add(i);
                elements.push_back(i);
            }
        } else {
            if constexpr (is_same_v<T, std::string>) {
                set.insert(to_string(i));
                elements.push_back(to_string(i));
            } else {
                set.insert(i);
                elements.push_back(i);
            }
        }
    }
    auto start = high_resolution_clock::now();
    if constexpr (is_same_v<Container, ISet<T>>) {
        for (const auto &element: elements) {
            set.remove(element);
        }
    } else {
        for (const auto &element: elements) {
            set.erase(element);
        }
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Removal time for " << elementCount << " elements " << demangle(typeid(Container).name()) << ": "
         << duration.count() << " ms" << endl;
}

void chronoISet(size_t num_elements) {
    cout << "ISet tests for <int>:" << endl;
    chronoInsertSet<int, ISet<int>>(num_elements);
    chronoInsertSet<int, std::set<int>>(num_elements);
    chronoRemoveSet<int, ISet<int>>(num_elements);
    chronoRemoveSet<int, std::set<int>>(num_elements);
    cout << endl;

    cout << "ISet tests for <string>:" << endl;
    chronoInsertSet<string, ISet<string>>(num_elements);
    chronoInsertSet<string, std::set<string>>(num_elements);
    chronoRemoveSet<string, ISet<string>>(num_elements);
    chronoRemoveSet<string, std::set<string>>(num_elements);
    cout << endl;
}