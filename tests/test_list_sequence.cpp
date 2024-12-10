#include <cassert>
#include <iostream>
#include "test_list_sequence.hpp"


void testAddElementLS() {
    ListSequence<int> seq;
    seq.add(10);
    assert(("AddElement_size", seq.getSize() == 1));
    assert(("AddElement_value", seq.get(0) == 10));
}

void testAddMultipleElementsLS() {
    ListSequence<int> seq;
    seq.add(10);
    seq.add(20);
    seq.add(30);
    assert(("AddMultipleElements_size_0", seq.getSize() == 3));
    assert(("AddMultipleElements_value_0", seq.get(0) == 10));
    assert(("AddMultipleElements_value_1", seq.get(1) == 20));
    assert(("AddMultipleElements_value_2", seq.get(2) == 30));
}

void testRemoveElementLS() {
    ListSequence<int> seq;
    seq.add(10);
    seq.add(20);
    seq.add(30);
    seq.remove(1);
    assert(("RemoveElement_size", seq.getSize() == 2));
    assert(("RemoveElement_value_0", seq.get(0) == 10));
    assert(("RemoveElement_value_1", seq.get(1) == 30));
}

void testRemoveOutOfRangeLS() {
    ListSequence<int> seq;
    seq.add(10);
    seq.add(20);
    try {
        seq.remove(2);
        assert(("RemoveOutOfRange_remove", false));
    } catch (const std::out_of_range&) {
        assert(("RemoveOutOfRange_OK", true));
    }
}

void testGetOutOfRangeLS() {
    ListSequence<int> seq;
    seq.add(10);
    try {
        seq.get(1);
        assert(("GetOutOfRange_value", false));
    } catch (const std::out_of_range&) {
        assert(("GetOutOfRange_OK", true));
    }
}

void testCopyConstructorLS() {
    ListSequence<int> seq;
    seq.add(10);
    seq.add(20);
    ListSequence<int> copy(seq);
    assert(("CopyConstructor_size", copy.getSize() == 2));
    assert(("CopyConstructor_value_0", copy.get(0) == 10));
    assert(("CopyConstructor_value_1", copy.get(1) == 20));
}

void testMoveConstructorLS() {
    ListSequence<int> seq;
    seq.add(10);
    seq.add(20);
    ListSequence<int> moved(std::move(seq));
    assert(("MoveConstructor_size_0", moved.getSize() == 2));
    assert(("MoveConstructor_value_0", moved.get(0) == 10));
    assert(("MoveConstructor_value_1", moved.get(1) == 20));
    assert(("MoveConstructor_size_1", seq.getSize() == 0));
}

void testAssignmentOperatorLS() {
    ListSequence<int> seq;
    seq.add(10);
    seq.add(20);
    ListSequence<int> copy;
    copy = seq;
    assert(("AssignmentOperator_size", copy.getSize() == 2));
    assert(("AssignmentOperator_value_0", copy.get(0) == 10));
    assert(("AssignmentOperator_value_1", copy.get(1) == 20));
}

void testSelfAssignmentLS() {
    ListSequence<int> seq;
    seq.add(10);
    seq = seq;
    assert(("SelfAssignment_size", seq.getSize() == 1));
    assert(("SelfAssignment_value", seq.get(0) == 10));
}

void testEqualityOperatorLS() {
    ListSequence<int> seq1;
    seq1.add(10);
    seq1.add(20);

    ListSequence<int> seq2;
    seq2.add(10);
    seq2.add(20);

    assert(("EqualityOperator", seq1 == seq2));
}

void testInequalityOperatorLS() {
    ListSequence<int> seq1;
    seq1.add(10);

    ListSequence<int> seq2;
    seq2.add(20);

    assert(("InequalityOperator", seq1 != seq2));
}

void testClearLS() {
    ListSequence<int> seq;
    seq.add(10);
    seq.add(20);
    seq.clear();
    assert(("Clear", seq.getSize() == 0));
}

void testResizeLS() {
    ListSequence<int> seq;
    for (int i = 0; i < 10; ++i) {
        seq.add(i);
    }
    assert(("Resize_size", seq.getSize() == 10));
    for (int i = 0; i < 10; ++i) {
        assert(("Resize_value", seq.get(i) == i));
    }
}

void testListSequence() {
    testAddElementLS();
    testAddMultipleElementsLS();
    testRemoveElementLS();
    testRemoveOutOfRangeLS();
    testGetOutOfRangeLS();
    testCopyConstructorLS();
    testMoveConstructorLS();
    testAssignmentOperatorLS();
    testSelfAssignmentLS();
    testEqualityOperatorLS();
    testInequalityOperatorLS();
    testClearLS();
    testResizeLS();

    std::cout << "All tests passed! (ListSequence)" << std::endl;
}
