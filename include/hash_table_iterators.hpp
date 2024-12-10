#pragma once

template<typename K, typename V>
class HashTable;

template<typename K, typename V>
class HashTableIterator {
private:
    HashTable<K, V>* hashTable;
    size_t bucketIndex;
    size_t nodeIndex;

    void findNextValid() {
        while (bucketIndex < hashTable->capacity) {
            while (nodeIndex < hashTable->table.get(bucketIndex).getSize()) {
                if (hashTable->table.get(bucketIndex).get(nodeIndex).isOccupied) {
                    return;
                }
                ++nodeIndex;
            }
            ++bucketIndex;
            nodeIndex = 0;
        }
    }

public:
    using value_type = const K&;

    explicit HashTableIterator(HashTable<K, V>* table, size_t bucket = 0, size_t node = 0)
            : hashTable(table), bucketIndex(bucket), nodeIndex(node) {
        if (hashTable) {
            findNextValid();
        }
    }

    value_type operator*() const {
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
                    return;
                }
                ++nodeIndex;
            }
            ++bucketIndex;
            nodeIndex = 0;
        }
    }

public:
    using value_type = const K&;

    explicit ConstHashTableIterator(const HashTable<K, V>* table, size_t bucket = 0, size_t node = 0)
            : hashTable(table), bucketIndex(bucket), nodeIndex(node) {
        if (hashTable) {
            findNextValid();
        }
    }

    value_type operator*() const {
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
        return hashTable == other.hashTable &&
               bucketIndex == other.bucketIndex &&
               nodeIndex == other.nodeIndex;
    }

    bool operator!=(const ConstHashTableIterator& other) const {
        return !(*this == other);
    }
};