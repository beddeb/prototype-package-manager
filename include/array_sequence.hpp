#pragma once

#include <stdexcept>
#include <utility>
#include "sequence.hpp"


template<typename T>
class ArraySequence : public Sequence<T> {
private:
    T* data;

public:
    explicit ArraySequence(size_t size = 0) : Sequence<T>(size), data(new T[size]) {}

    ArraySequence(const ArraySequence& other) : Sequence<T>(other.getSize()) {
        data = new T[Sequence<T>::capacity];
        for (size_t i = 0; i < Sequence<T>::size; ++i) {
            data[i] = other.data[i];
        }
    }

    ArraySequence(ArraySequence&& other) noexcept : Sequence<T>(other.getSize()) {
        data = other.data;
        other.data = nullptr;
    }

    ~ArraySequence() {
        delete[] data;
    }

    void add(const T& element) override {
        if (Sequence<T>::size == Sequence<T>::capacity) {
            Sequence<T>::resize();
            T* newData = new T[Sequence<T>::capacity];
            for (size_t i = 0; i < Sequence<T>::size; ++i) {
                newData[i] = std::move(data[i]);
            }
            delete[] data;
            data = newData;
        }
        data[Sequence<T>::size++] = element;
    }

    void remove(size_t index) override {
        if (index >= Sequence<T>::size) {
            throw std::out_of_range("Index out of range");
        }
        for (size_t i = index; i < Sequence<T>::size - 1; ++i) {
            data[i] = std::move(data[i + 1]);
        }
        --Sequence<T>::size;
    }

    T& get(size_t index) override {
        if (index >= Sequence<T>::size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& get(size_t index) const override {
        if (index >= Sequence<T>::size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    ArraySequence& operator=(const ArraySequence& other) {
        if (this != &other) {
            Sequence<T>::size = other.Sequence<T>::size;
            delete[] data;
            data = new T[Sequence<T>::capacity];
            for (size_t i = 0; i < Sequence<T>::size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    ArraySequence& operator=(ArraySequence&& other) noexcept {
        if (this != &other) {
            std::swap(data, other.data);
            Sequence<T>::size = other.Sequence<T>::size;
        }
        return *this;
    }

    Iterator<T> begin() {
        return Iterator<T>(data);
    }

    Iterator<T> end() {
        return Iterator<T>(data + Sequence<T>::size);
    }

    ConstIterator<T> begin() const {
        return ConstIterator<T>(data);
    }

    ConstIterator<T> end() const {
        return ConstIterator<T>(data + Sequence<T>::size);
    }

    ConstIterator<T> cbegin() const {
        return ConstIterator<T>(data);
    }

    ConstIterator<T> cend() const {
        return ConstIterator<T>(data + Sequence<T>::size);
    }
};