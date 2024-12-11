#include <iostream>
#include <chrono>
#include <list>
#include "chrono_list_sequence.hpp"


using namespace std;
using namespace chrono;

void chronoAddIntLS(size_t num_elements) {
    ListSequence<int> seq;
    list<int> llist;

    auto start_seq = high_resolution_clock::now();
    for (size_t i = 0; i < num_elements; ++i) {
        seq.add(i);
    }
    auto end_seq = high_resolution_clock::now();
    auto duration_seq = duration_cast<microseconds>(end_seq - start_seq);

    auto start_vec = high_resolution_clock::now();
    for (size_t i = 0; i < num_elements; ++i) {
        llist.push_back(i);
    }
    auto end_vec = high_resolution_clock::now();
    auto duration_vec = duration_cast<microseconds>(end_vec - start_vec);

    cout << "Add " << num_elements << " elements:" << endl;
    cout << "  ListSequence: " << duration_seq.count() << " ms" << endl;
    cout << "  list:   " << duration_vec.count() << " ms" << endl;
    cout << endl;
}

void chronoGetIndexIntLS(size_t num_elements, size_t step) {
    ListSequence<int> seq;
    list<int> llist;
    for (size_t i = 0; i < num_elements; ++i) {
        seq.add(i);
        llist.push_back(i);
    }

    auto start_seq = high_resolution_clock::now();
    for (size_t i = 0; i < num_elements; i += num_elements / step) {
        volatile int temp = seq.get(i);
    }
    auto end_seq = high_resolution_clock::now();
    auto duration_seq = duration_cast<nanoseconds>(end_seq - start_seq);

    auto start_vec = high_resolution_clock::now();
    for (size_t i = 0; i < num_elements; i += num_elements / step) {
        auto it = llist.begin();
        advance(it, i);
        volatile int temp = *it;
    }
    auto end_vec = high_resolution_clock::now();
    auto duration_vec = duration_cast<nanoseconds>(end_vec - start_vec);

    cout << "Get element by index (average over " << step << " accesses):" << endl;
    cout << "  ListSequence: " << duration_seq.count() / step << " ns" << endl;
    cout << "  list:   " << duration_vec.count() / step << " ns" << endl;
    cout << endl;
}

void chronoIterateIntLS(size_t num_elements) {
    ListSequence<int> seq;
    list<int> llist;
    for (size_t i = 0; i < num_elements; ++i) {
        seq.add(i);
        llist.push_back(i);
    }

    auto start_seq = high_resolution_clock::now();
    for(int val : seq){
        volatile int temp = val;
    }
    auto end_seq = high_resolution_clock::now();
    auto duration_seq = duration_cast<microseconds>(end_seq - start_seq);

    auto start_list = high_resolution_clock::now();
    for (int val : llist) {
        volatile int temp = val;
    }
    auto end_list = high_resolution_clock::now();
    auto duration_list = duration_cast<microseconds>(end_list - start_list);

    cout << "Iterate over " << num_elements << " elements:" << endl;
    cout << "  ListSequence: " << duration_seq.count() << " ms" << endl;
    cout << "  list:   " << duration_list.count() << " ms" << endl;
    cout << endl;
}

void chronoRemoveIntLS(size_t num_elements) {
    ListSequence<int> seq;
    list<int> llist;

    // Удаление с конца
    for (size_t i = 0; i < num_elements; ++i) {
        seq.add(i);
        llist.push_back(i);
    }

    auto start_seq_end = high_resolution_clock::now();
    for (size_t i = 0; i < num_elements / 2; ++i) {
        seq.remove(seq.getSize() - 1);
    }
    auto end_seq_end = high_resolution_clock::now();
    auto duration_seq_end = duration_cast<microseconds>(end_seq_end - start_seq_end);

    auto start_vec_end = high_resolution_clock::now();
    for (size_t i = 0; i < num_elements / 2; ++i) {
        llist.pop_back();
    }
    auto end_vec_end = high_resolution_clock::now();
    auto duration_vec_end = duration_cast<microseconds>(end_vec_end - start_vec_end);

    // Удаление из начала
    ListSequence<int> seq2;
    list<int> llist2;
    for (size_t i = 0; i < num_elements; ++i) {
        seq2.add(i);
        llist2.push_back(i);
    }
    auto start_seq_begin = high_resolution_clock::now();
    for (size_t i = 0; i < num_elements / 2; ++i) {
        seq2.remove(0);
    }
    auto end_seq_begin = high_resolution_clock::now();
    auto duration_seq_begin = duration_cast<microseconds>(end_seq_begin - start_seq_begin);

    auto start_vec_begin = high_resolution_clock::now();
    for (size_t i = 0; i < num_elements / 2; ++i) {
        llist2.erase(llist2.begin());
    }
    auto end_vec_begin = high_resolution_clock::now();
    auto duration_vec_begin = duration_cast<microseconds>(end_vec_begin - start_vec_begin);

    cout << "Remove " << num_elements / 2 << " elements:" << endl;
    cout << "  From the end:" << endl;
    cout << "    ListSequence: " << duration_seq_end.count() << " ms" << endl;
    cout << "    list:   " << duration_vec_end.count() << " ms" << endl;

    cout << "  From the beginning:" << endl;
    cout << "    ListSequence: " << duration_seq_begin.count() << " ms" << endl;
    cout << "    list:   " << duration_vec_begin.count() << " ms" << endl;
    cout << endl;
}

void chronoListSequence(size_t num_elements, size_t step) {
    std::cout << "Performance tests for ListSequence vs std::vector" << std::endl << std::endl;

    chronoAddIntLS(num_elements); // ms
    chronoGetIndexIntLS(num_elements, step); // ns
    chronoIterateIntLS(num_elements); // ms
    chronoRemoveIntLS(num_elements); // ms

}