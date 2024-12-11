#include <cassert>
#include <iostream>
#include "test_sequence.hpp"


void testAddElementS() {
    Sequence<int> seq;
    seq.add(10);
    assert(("AddElement_size", seq.getSize() == 1));
    assert(("AddElement_value", seq.get(0) == 10));
}

void testAddMultipleElementsS() {
    Sequence<int> seq;
    seq.add(10);
    seq.add(20);
    seq.add(30);
    assert(("AddMultipleElements_size", seq.getSize() == 3));
    assert(("AddMultipleElements_value_0", seq.get(0) == 10));
    assert(("AddMultipleElements_value_1", seq.get(1) == 20));
    assert(("AddMultipleElements_value_2", seq.get(2) == 30));
}

void testRemoveElementS() {
    Sequence<int> seq;
    seq.add(10);
    seq.add(20);
    seq.add(30);
    seq.remove(1);
    assert(("RemoveElement_size", seq.getSize() == 2));
    assert(("RemoveElement_value_0", seq.get(0) == 10));
    assert(("RemoveElement_value_1", seq.get(1) == 30));
}

void testRemoveOutOfRangeS() {
    Sequence<int> seq;
    seq.add(10);
    seq.add(20);
    try {
        seq.remove(2);
        assert(("RemoveOutOfRange_remove", false));
    } catch (const std::out_of_range&) {
        assert(("RemoveOutOfRange_OK", true));
    }
}

void testGetOutOfRangeS() {
    Sequence<int> seq;
    seq.add(10);
    try {
        seq.get(1);
        assert(("GetOutOfRange_value", false));
    } catch (const std::out_of_range&) {
        assert(("GetOutOfRange_OK", true));
    }
}

void testCopyConstructorS() {
    Sequence<int> seq;
    seq.add(10);
    seq.add(20);
    Sequence<int> copy(seq);
    assert(("CopyConstructor_size", copy.getSize() == 2));
    assert(("CopyConstructor_value_0", copy.get(0) == 10));
    assert(("CopyConstructor_value_1", copy.get(1) == 20));
}

void testMoveConstructorS() {
    Sequence<int> seq;
    seq.add(10);
    seq.add(20);
    Sequence<int> moved(std::move(seq));
    assert(("MoveConstructor_size_0", moved.getSize() == 2));
    assert(("MoveConstructor_value_0", moved.get(0) == 10));
    assert(("MoveConstructor_value_1", moved.get(1) == 20));
    assert(("MoveConstructor_size_1", seq.getSize() == 0));
}

void testAssignmentOperatorS() {
    Sequence<int> seq;
    seq.add(10);
    seq.add(20);
    Sequence<int> copy;
    copy = seq;
    assert(("SelfAssignment_size", copy.getSize() == 2));
    assert(("SelfAssignment_value_0", copy.get(0) == 10));
    assert(("SelfAssignment_value_1", copy.get(1) == 20));
}

void testSelfAssignmentS() {
    Sequence<int> seq;
    seq.add(10);
    seq = seq;
    assert(("SelfAssignment_size", seq.getSize() == 1));
    assert(("SelfAssignment_value", seq.get(0) == 10));
}

void testEqualityOperatorS() {
    Sequence<int> seq1;
    seq1.add(10);
    seq1.add(20);

    Sequence<int> seq2;
    seq2.add(10);
    seq2.add(20);

    assert(("EqualityOperator", seq1 == seq2));
}

void testInequalityOperatorS() {
    Sequence<int> seq1;
    seq1.add(10);

    Sequence<int> seq2;
    seq2.add(20);

    assert(("InequalityOperator", seq1 != seq2));
}

void testResizeS() {
    Sequence<int> seq;
    for (int i = 0; i < 10; ++i) {
        seq.add(i);
    }
    assert(seq.getSize() == 10);
    for (int i = 0; i < 10; ++i) {
        assert(("Resize", seq.get(i) == i));
    }
}

void testSequence() {
    testAddElementS();
    testAddMultipleElementsS();
    testRemoveElementS();
    testRemoveOutOfRangeS();
    testGetOutOfRangeS();
    testCopyConstructorS();
    testMoveConstructorS();
    testAssignmentOperatorS();
    testSelfAssignmentS();
    testEqualityOperatorS();
    testInequalityOperatorS();
    testResizeS();

    std::cout << "All tests passed! (Sequence)" << std::endl;
}