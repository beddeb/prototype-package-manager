#pragma once

template<typename K, typename V>
class HashTable;

template<typename K, typename V>
class HashTableIterator {
private:
    HashTable<K, V>* hashTable;
    size_t bucketIndex;
    size_t nodeIndex;

    // Метод поиска следующего валидного элемента (с учетом того, что итератор может "выйти" за границу)
    void findNextValid() {
        while (bucketIndex < hashTable->capacity) {
            while (nodeIndex < hashTable->table.get(bucketIndex).getSize()) {
                if (hashTable->table.get(bucketIndex).get(nodeIndex).isOccupied) {
                    return;  // Нашли валидный элемент, выходим
                }
                ++nodeIndex;
            }
            ++bucketIndex;
            nodeIndex = 0; // Начинаем с начала следующей цепочки
        }
        // Если дошли до конца, bucketIndex будет равен hashTable->capacity
    }

public:
    using value_type = const K&;

    explicit HashTableIterator(HashTable<K, V>* table, size_t bucket = 0, size_t node = 0)
            : hashTable(table), bucketIndex(bucket), nodeIndex(node) {
        if (hashTable) {
            findNextValid(); // Находим первый валидный элемент при создании
        }
    }

    value_type operator*() const {
        // Проверка, что итератор валиден (не указывает за пределы хеш-таблицы)
        if(bucketIndex >= hashTable->capacity) {
            throw std::runtime_error("Iterator is out of range");
        }
        return hashTable->table.get(bucketIndex).get(nodeIndex).key;
    }

    HashTableIterator& operator++() {
        if (hashTable) {
            ++nodeIndex;
            findNextValid();
        }
        return *this;
    }

    HashTableIterator operator++(int) {
        HashTableIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    bool operator==(const HashTableIterator& other) const {
        // Сравниваем итераторы, учитывая что end итератор будет валидным
        return hashTable == other.hashTable &&
               bucketIndex == other.bucketIndex &&
               nodeIndex == other.nodeIndex;
    }

    bool operator!=(const HashTableIterator& other) const {
        return !(*this == other);
    }
};

template<typename K, typename V>
class ConstHashTableIterator {
private:
    const HashTable<K, V>* hashTable;
    size_t bucketIndex;
    size_t nodeIndex;

    void findNextValid() {
        while (bucketIndex < hashTable->capacity) {
            while (nodeIndex < hashTable->table.get(bucketIndex).getSize()) {
                if (hashTable->table.get(bucketIndex).get(nodeIndex).isOccupied) {
                    return;  // Нашли валидный элемент, выходим
                }
                ++nodeIndex;
            }
            ++bucketIndex;
            nodeIndex = 0; // Начинаем с начала следующей цепочки
        }
        // Если дошли до конца, bucketIndex будет равен hashTable->capacity
    }

public:
    using value_type = const K&;

    explicit ConstHashTableIterator(const HashTable<K, V>* table, size_t bucket = 0, size_t node = 0)
            : hashTable(table), bucketIndex(bucket), nodeIndex(node) {
        if (hashTable) {
            findNextValid(); // Находим первый валидный элемент при создании
        }
    }

    value_type operator*() const {
        // Проверка, что итератор валиден (не указывает за пределы хеш-таблицы)
        if(bucketIndex >= hashTable->capacity) {
            throw std::runtime_error("Iterator is out of range");
        }
        return hashTable->table.get(bucketIndex).get(nodeIndex).key;
    }

    ConstHashTableIterator& operator++() {
        if (hashTable) {
            ++nodeIndex;
            findNextValid();
        }
        return *this;
    }

    ConstHashTableIterator operator++(int) {
        ConstHashTableIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    bool operator==(const ConstHashTableIterator& other) const {
        // Сравниваем итераторы, учитывая что end итератор будет валидным
        return hashTable == other.hashTable &&
               bucketIndex == other.bucketIndex &&
               nodeIndex == other.nodeIndex;
    }

    bool operator!=(const ConstHashTableIterator& other) const {
        return !(*this == other);
    }
};