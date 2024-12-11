#include <iostream>
#include <cassert>
#include "func_iset.hpp"


void testAddIS() {
    ISet<int> iset;
    iset.add(1);
    iset.add(2);

    assert(("Add_value_0", iset.contains(1)));
    assert(("Add_value_1", iset.contains(2)));
}

void testAddDuplicateElementIS() {
    ISet<int> iset;
    iset.add(1);
    assert(("AddDuplicateElement_size_0", iset.size() == 1));
    iset.add(1);
    assert(("AddDuplicateElement_size_1", iset.size() == 1));
    iset.remove(1);
    assert(("AddDuplicateElement_size_2", iset.size() == 0));
}

void testRemoveIS() {
    ISet<int> iset;
    iset.add(1);
    iset.add(2);

    iset.remove(1);
    assert(("Remove_value_0", iset.contains(1) == false));
    assert(("Remove_value_1", iset.contains(2)));
}

void testRemoveNonexistentElementIS() {
    ISet<int> iset;
    iset.add(1);

    try {
        iset.remove(2);
        assert(("RemoveNonexistentElement_value", false));
    } catch (const std::runtime_error&) {
        assert(("RemoveNonexistentElement_OK", true));
    }
}

void testContainsIS() {
    ISet<int> iset;
    iset.add(1);
    iset.add(2);

    assert(("Contains_value_0", iset.contains(1)));
    assert(("Contains_value_1", iset.contains(2)));
    assert(("Contains_value_2", iset.contains(3) == false));
}

void testSizeIS() {
    ISet<int> iset;
    assert(("Size_0", iset.size() == 0));

    iset.add(1);
    assert(("Size_1", iset.size() == 1));

    iset.add(2);
    assert(("Size_2", iset.size() == 2));

    iset.remove(1);
    assert(("Size_3", iset.size() == 1));
}

void testIteratorsIS() {
    ISet<int> iset;
    iset.add(1);
    iset.add(2);
    iset.add(3);

    int count = 0;
    for (auto it = iset.begin(); it != iset.end(); ++it) {
        ++count;
    }
    assert(("Iterators_counter_0", count == 3));

    count = 0;
    for (auto it = iset.cbegin(); it != iset.cend(); ++it) {
        ++count;
    }
    assert(("Iterators_counter_1", count == 3));
}

void testISet() {
    testAddIS();
    testAddDuplicateElementIS();
    testRemoveIS();
    testRemoveNonexistentElementIS();
    testContainsIS();
    testSizeIS();
    testIteratorsIS();

    std::cout << "All tests passed! (ISet)" << std::endl;
}