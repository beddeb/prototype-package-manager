#pragma once

template<typename K, typename V>
class HashTable;

template<typename K, typename V>
class HashTableIterator {
private:
    HashTable<K, V>* hash_table;
    size_t bucket_index;
    size_t node_index;

    void findNextValid() {
        while (bucket_index < hash_table->capacity) {
            while (node_index < hash_table->table.get(bucket_index).getSize()) {
                if (hash_table->table.get(bucket_index).get(node_index).isOccupied) {
                    return;
                }
                ++node_index;
            }
            ++bucket_index;
            node_index = 0;
        }
    }

public:
    static HashTableIterator end(HashTable<K, V>* table) {
        return HashTableIterator(table, table->capacity, 0);
    }

    using value_type = const K&;

    explicit HashTableIterator(HashTable<K, V>* table, size_t bucket = 0, size_t node = 0)
            : hash_table(table), bucket_index(bucket), node_index(node) {
        if (!hash_table) {
            throw std::runtime_error("HashTable is NULL");
        }
        findNextValid();
    }

    value_type operator*() const {
        if (bucket_index >= hash_table->capacity) {
            throw std::runtime_error("Iterator is out of range");
        }
        return hash_table->table.get(bucket_index).get(node_index).key;
    }

    HashTableIterator& operator++() {
        ++node_index;
        findNextValid();
        return *this;
    }

    HashTableIterator operator++(int) {
        HashTableIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    bool operator==(const HashTableIterator& other) const {
        return hash_table == other.hash_table &&
               bucket_index == other.bucket_index &&
               node_index == other.node_index;
    }

    bool operator!=(const HashTableIterator& other) const {
        return !(*this == other);
    }
};

template<typename K, typename V>
class ConstHashTableIterator {
private:
    const HashTable<K, V>* hash_table;
    size_t bucket_index;
    size_t node_index;

    void findNextValid() {
        while (bucket_index < hash_table->capacity) {
            while (node_index < hash_table->table.get(bucket_index).getSize()) {
                if (hash_table->table.get(bucket_index).get(node_index).isOccupied) {
                    return;
                }
                ++node_index;
            }
            ++bucket_index;
            node_index = 0;
        }
    }

public:
    static ConstHashTableIterator end(const HashTable<K, V>* table) {
        return ConstHashTableIterator(table, table->capacity, 0);
    }

    using value_type = const K&;

    explicit ConstHashTableIterator(const HashTable<K, V>* table, size_t bucket = 0, size_t node = 0)
            : hash_table(table), bucket_index(bucket), node_index(node) {
        if (!hash_table) {
            throw std::runtime_error("HashTable is NULL");
        }
        findNextValid();
    }

    value_type operator*() const {
        if (bucket_index >= hash_table->capacity) {
            throw std::runtime_error("Iterator is out of range");
        }
        return hash_table->table.get(bucket_index).get(node_index).key;
    }

    ConstHashTableIterator& operator++() {
        ++node_index;
        findNextValid();
        return *this;
    }

    ConstHashTableIterator operator++(int) {
        ConstHashTableIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    bool operator==(const ConstHashTableIterator& other) const {
        return hash_table == other.hash_table &&
               bucket_index == other.bucket_index &&
               node_index == other.node_index;
    }

    bool operator!=(const ConstHashTableIterator& other) const {
        return !(*this == other);
    }
};