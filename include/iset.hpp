#pragma once

#include "hash_table.hpp"


template<typename T>
class ISet {
private:
    HashTable<T, void*> table;

public:
    static constexpr size_t default_capacity = 4; // capacity по умолчанию

    explicit ISet(size_t initialCapacity = default_capacity) : table(initialCapacity) {}

    void add(const T& element) {
//        if (table.contains(element)) {
//            throw std::runtime_error("Element existed");
//        }
//        table.insert(element, nullptr);
        try {
            table.insert(element, nullptr);
        } catch (std::runtime_error& e) {
            throw std::runtime_error("Error adding element: " + std::string(e.what()));
        }
    }

    void remove(const T& element) {
//        if (table.contains(element)) {
//            table.remove(element);
//            return;
//        }
//        throw std::runtime_error("Element not found");
        try {
            table.remove(element);
        } catch (std::runtime_error& e) {
            throw std::runtime_error("Error removing element: " + std::string(e.what()));
        }
    }

    bool contains(const T& element) const {
        return table.contains(element);
    }

    [[nodiscard]] size_t size() const {
        return table.size();
    }

    using iterator = typename HashTable<T, void*>::iterator;
    using const_iterator = typename HashTable<T, void*>::const_iterator;

    iterator begin() {
        return table.begin();
    }

    iterator end() {
        return table.end();
    }

    const_iterator begin() const {
        return table.begin();
    }

    const_iterator end() const {
        return table.end();
    }

    const_iterator cbegin() const {
        return table.cbegin();
    }

    const_iterator cend() const {
        return table.cend();
    }
};