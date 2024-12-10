#pragma once

#include <stdexcept>
#include "array_sequence.hpp"
#include "list_sequence.hpp"
#include "hash_table_iterators.hpp"


template<typename K, typename V>
struct HashNode {
    K key;
    V value;
    bool isOccupied;

    HashNode() : isOccupied(false) {}
    HashNode(const K& k, const V& v) : key(k), value(v), isOccupied(true) {}
};

template<typename K, typename V>
class HashTable {
private:
    template<typename KI, typename VI> friend class HashTableIterator;
    template<typename KI, typename VI> friend class ConstHashTableIterator;

    static constexpr double P = 2.0;  // Пороговое значение для сжатия
    static constexpr double Q = 1.5;  // Коэффициент расширения/сжатия

    ArraySequence<ListSequence<HashNode<K,V>>> table;  // Основная таблица с цепочками
    size_t elementCount;
    size_t capacity;

    // Определение базовой хеш-функции
    size_t getHashCode(const K& key) const {
        return std::hash<K>{}(key);
    }

    // Получение индекса в таблице
    size_t getIndex(const K& key) const {
        return getHashCode(key) % capacity;
    }

    // Перестройка таблицы
    void rebuild(size_t newCapacity) {
        ArraySequence<ListSequence<HashNode<K,V>>> newTable(newCapacity);
        for (size_t i = 0; i < newCapacity; ++i) {
            newTable.add(ListSequence<HashNode<K,V>>()); // Исправлено: создание ListSequence
        }

        for (size_t i = 0; i < capacity; ++i) {
            for (size_t j = 0; j < table.get(i).getSize(); ++j) {
                const auto& node = table.get(i).get(j);
                if (node.isOccupied) {
                    size_t newIndex = getHashCode(node.key) % newCapacity;
                    newTable.get(newIndex).add(node);
                }
            }
        }
        table = std::move(newTable);
        capacity = newCapacity;
    }

    void checkAndResize() {
        if (elementCount == capacity) {
            rebuild(static_cast<size_t>(capacity * Q));
        }
        else if (elementCount <= capacity / P && capacity > 4) {
            rebuild(static_cast<size_t>(capacity / Q));
        }
    }

public:
    explicit HashTable(size_t initialCapacity = 4)
            : elementCount(0), capacity(initialCapacity), table(initialCapacity) { // Инициализация ArraySequence с capacity
        for (size_t i = 0; i < capacity; ++i) {
            table.add(ListSequence<HashNode<K,V>>());
        }
    }

    void insert(const K& key, const V& value) {
        size_t index = getIndex(key);
        ListSequence<HashNode<K, V>>& bucket = table.get(index); // Получаем ссылку на ListSequence

        // Проверяем, существует ли уже такой ключ
        for (size_t i = 0; i < bucket.getSize(); ++i) {
            if (bucket.get(i).isOccupied && bucket.get(i).key == key) {
                bucket.get(i).value = value;
                return;
            }
        }

        bucket.add(HashNode<K, V>(key, value));
        ++elementCount;
        checkAndResize();
    }

    const V& get(const K& key) const { // Добавлен const для метода
        size_t index = getIndex(key);
        const ListSequence<HashNode<K, V>>& bucket = table.get(index);
        for (size_t i = 0; i < bucket.getSize(); ++i) {
            if (bucket.get(i).isOccupied && bucket.get(i).key == key) {
                return bucket.get(i).value;
            }
        }
        throw std::runtime_error("Key not found");
    }

    void remove(const K& key) {
        size_t index = getIndex(key);
        ListSequence<HashNode<K, V>>& bucket = table.get(index); // Получаем ссылку на ListSequence

        for (size_t i = 0; i < bucket.getSize(); ++i) {
            if (bucket.get(i).isOccupied && bucket.get(i).key == key) {
                bucket.get(i).isOccupied = false;
                --elementCount;
                checkAndResize();
                return;
            }
        }
        throw std::runtime_error("Key not found");
    }

    [[nodiscard]] size_t size() const {
        return elementCount;
    }

    bool contains(const K& key) const {
        size_t index = getIndex(key);
        const ListSequence<HashNode<K, V>>& bucket = table.get(index); // Получаем константную ссылку

        for (size_t i = 0; i < bucket.getSize(); ++i) {
            if (bucket.get(i).isOccupied && bucket.get(i).key == key) { // Проверка на равенство ключей
                return true;
            }
        }
        return false;
    }

    using iterator = HashTableIterator<K, V>;
    using const_iterator = ConstHashTableIterator<K, V>;

    iterator begin() {
        return iterator(this);
    }

    iterator end() {
        return iterator(this, capacity, 0);
    }

    const_iterator begin() const {
        return const_iterator(this);
    }

    const_iterator end() const {
        return const_iterator(this, capacity, 0);
    }

    [[maybe_unused]] const_iterator cbegin() const {
        return const_iterator(this);
    }

    [[maybe_unused]] const_iterator cend() const {
        return const_iterator(this, capacity, 0);
    }
};