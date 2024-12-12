#include <iostream>
#include <chrono>
#include <vector>
#include <unordered_map>
#include "chrono_hash_table.hpp"


using namespace std;
using namespace chrono;

template<typename K, typename V>
void chronoInsertionHashTable(size_t elementCount) {
    HashTable<K, V> table;
    auto start = high_resolution_clock::now();
    for (size_t i = 0; i < elementCount; ++i) {
        if constexpr (std::is_same_v<K, std::string> && std::is_same_v<V, std::string>) {
            table.insert(to_string(i), to_string(i));
        } else if constexpr (std::is_same_v<K, std::string>) {
            table.insert(to_string(i), i);
        } else if constexpr (std::is_same_v<V, std::string>) {
            table.insert(i, to_string(i));
        } else {
            table.insert(i, i);
        }
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Insertion time for " << elementCount << " elements (HashTable): " << duration.count() << " ms" << endl;
}

template<typename K, typename V>
void chronoInsertionStdMap(size_t elementCount) {
    std::unordered_map<K, V> map;
    auto start = high_resolution_clock::now();
    for (size_t i = 0; i < elementCount; ++i) {
        if constexpr (std::is_same_v<K, std::string> && std::is_same_v<V, std::string>) {
            map[to_string(i)] = to_string(i);
        } else if constexpr (std::is_same_v<K, std::string>) {
            map[to_string(i)] = i;
        } else if constexpr (std::is_same_v<V, std::string>) {
            map[i] = to_string(i);
        } else {
            map[i] = i;
        }
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Insertion time for " << elementCount << " elements (std::unordered_map): " << duration.count() << " ms" << endl;
}

template<typename K, typename V>
void chronoGetHashTable(size_t elementCount) {
    HashTable<K, V> table;
    std::vector<K> keys;
    for (size_t i = 0; i < elementCount; ++i) {
        if constexpr (std::is_same_v<K, std::string> && std::is_same_v<V, std::string>) {
            table.insert(to_string(i), to_string(i));
            keys.push_back(to_string(i));
        } else if constexpr (std::is_same_v<K, std::string>) {
            table.insert(to_string(i), i);
            keys.push_back(to_string(i));
        } else if constexpr (std::is_same_v<V, std::string>) {
            table.insert(i, to_string(i));
            keys.push_back(i);
        } else {
            table.insert(i, i);
            keys.push_back(i);
        }
    }
    auto start = chrono::high_resolution_clock::now();
    for (const auto& key : keys) {
        table.get(key);
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Get time for " << elementCount << " elements (HashTable): " << duration.count() << " ms" << endl;
}

template<typename K, typename V>
void chronoGetStdMap(size_t elementCount) {
    std::unordered_map<K, V> map;
    std::vector<K> keys;
    for (size_t i = 0; i < elementCount; ++i) {
        if constexpr (std::is_same_v<K, std::string> && std::is_same_v<V, std::string>) {
            map[to_string(i)] = to_string(i);
            keys.push_back(to_string(i));
        } else if constexpr (std::is_same_v<K, std::string>) {
            map[to_string(i)] = i;
            keys.push_back(to_string(i));
        } else if constexpr (std::is_same_v<V, std::string>) {
            map[i] = to_string(i);
            keys.push_back(i);
        } else {
            map[i] = i;
            keys.push_back(i);
        }
    }
    auto start = chrono::high_resolution_clock::now();
    for (const auto& key : keys) {
        map.at(key); // Using at() for comparison with HashTable's get()
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Get time for " << elementCount << " elements (std::unordered_map): " << duration.count() << " ms" << endl;
}

template<typename K, typename V>
void chronoRemovalHashTable(size_t elementCount) {
    HashTable<K, V> table;
    std::vector<K> keys;
    for (size_t i = 0; i < elementCount; ++i) {
        if constexpr (std::is_same_v<K, std::string> && std::is_same_v<V, std::string>) {
            table.insert(to_string(i), to_string(i));
            keys.push_back(to_string(i));
        } else if constexpr (std::is_same_v<K, std::string>) {
            table.insert(to_string(i), i);
            keys.push_back(to_string(i));
        } else if constexpr (std::is_same_v<V, std::string>) {
            table.insert(i, to_string(i));
            keys.push_back(i);
        } else {
            table.insert(i, i);
            keys.push_back(i);
        }
    }
    auto start = chrono::high_resolution_clock::now();
    for (const auto& key : keys) {
        table.remove(key);
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Removal time for " << elementCount << " elements (HashTable): " << duration.count() << " ms" << endl;
}

template<typename K, typename V>
void chronoRemovalStdMap(size_t elementCount) {
    std::unordered_map<K, V> map;
    std::vector<K> keys;
    for (size_t i = 0; i < elementCount; ++i) {
        if constexpr (std::is_same_v<K, std::string> && std::is_same_v<V, std::string>) {
            map[to_string(i)] = to_string(i);
            keys.push_back(to_string(i));
        } else if constexpr (std::is_same_v<K, std::string>) {
            map[to_string(i)] = i;
            keys.push_back(to_string(i));
        } else if constexpr (std::is_same_v<V, std::string>) {
            map[i] = to_string(i);
            keys.push_back(i);
        } else {
            map[i] = i;
            keys.push_back(i);
        }
    }
    auto start = chrono::high_resolution_clock::now();
    for (const auto& key : keys) {
        map.erase(key);
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Removal time for " << elementCount << " elements (std::unordered_map): " << duration.count() << " ms" << endl;
}

void chronoHashTable(size_t num_elements) {
    cout << "Comparing HashTable and std::unordered_map for <int, int>:" << endl;
    chronoInsertionHashTable<int, int>(num_elements);
    chronoInsertionStdMap<int, int>(num_elements);
    chronoGetHashTable<int, int>(num_elements);
    chronoGetStdMap<int, int>(num_elements);
    chronoRemovalHashTable<int, int>(num_elements);
    chronoRemovalStdMap<int, int>(num_elements);
    cout << endl;

    cout << "Comparing HashTable and std::unordered_map for <int, string>:" << endl;
    chronoInsertionHashTable<int, string>(num_elements);
    chronoInsertionStdMap<int, string>(num_elements);
    chronoGetHashTable<int, string>(num_elements);
    chronoGetStdMap<int, string>(num_elements);
    chronoRemovalHashTable<int, string>(num_elements);
    chronoRemovalStdMap<int, string>(num_elements);
    cout << endl;

    cout << "Comparing HashTable and std::unordered_map for <string, int>:" << endl;
    chronoInsertionHashTable<string, int>(num_elements);
    chronoInsertionStdMap<string, int>(num_elements);
    chronoGetHashTable<string, int>(num_elements);
    chronoGetStdMap<string, int>(num_elements);
    chronoRemovalHashTable<string, int>(num_elements);
    chronoRemovalStdMap<string, int>(num_elements);
    cout << endl;

    cout << "Comparing HashTable and std::unordered_map for <string, string>:" << endl;
    chronoInsertionHashTable<string, string>(num_elements);
    chronoInsertionStdMap<string, string>(num_elements);
    chronoGetHashTable<string, string>(num_elements);
    chronoGetStdMap<string, string>(num_elements);
    chronoRemovalHashTable<string, string>(num_elements);
    chronoRemovalStdMap<string, string>(num_elements);
    cout << endl;
}