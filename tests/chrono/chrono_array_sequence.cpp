#include <iostream>
#include <chrono>
#include <vector>
#include "chrono_array_sequence.hpp"


using namespace std;
using namespace chrono;

void chronoAddIntAS(size_t num_elements) {
    ArraySequence<int> seq;
    vector<int> vec;

    auto start_seq = high_resolution_clock::now();
    for (size_t i = 0; i < num_elements; ++i) {
        seq.add(i);
    }
    auto end_seq = high_resolution_clock::now();
    auto duration_seq = duration_cast<microseconds>(end_seq - start_seq);

    auto start_vec = high_resolution_clock::now();
    for (size_t i = 0; i < num_elements; ++i) {
        vec.push_back(i);
    }
    auto end_vec = high_resolution_clock::now();
    auto duration_vec = duration_cast<microseconds>(end_vec - start_vec);

    cout << "Add " << num_elements << " elements:" << endl;
    cout << "  ArraySequence: " << duration_seq.count() << " ms" << endl;
    cout << "  vector:   " << duration_vec.count() << " ms" << endl;
    cout << endl;
}

void chronoGetIndexIntAS(size_t num_elements, size_t step) {
    ArraySequence<int> seq;
    vector<int> vec;
    for (size_t i = 0; i < num_elements; ++i) {
        seq.add(i);
        vec.push_back(i);
    }

    auto start_seq = high_resolution_clock::now();
    for (size_t i = 0; i < num_elements; i += num_elements / step) {
        volatile int temp = seq.get(i);
    }
    auto end_seq = high_resolution_clock::now();
    auto duration_seq = duration_cast<nanoseconds>(end_seq - start_seq);

    auto start_vec = high_resolution_clock::now();
    for (size_t i = 0; i < num_elements; i += num_elements / step) {
        volatile int temp = vec[i];
    }
    auto end_vec = high_resolution_clock::now();
    auto duration_vec = duration_cast<nanoseconds>(end_vec - start_vec);

    cout << "Get element by index (average over " << step << " accesses):" << endl;
    cout << "  ArraySequence: " << duration_seq.count() / step << " ns" << endl;
    cout << "  vector:   " << duration_vec.count() / step << " ns" << endl;
    cout << endl;
}

void chronoIterateIntAS(size_t num_elements) {
    ArraySequence<int> seq;
    vector<int> vec;
    for (size_t i = 0; i < num_elements; ++i) {
        seq.add(i);
        vec.push_back(i);
    }

    auto start_seq = high_resolution_clock::now();
    for(int val : seq){
        volatile int temp = val;
    }
    auto end_seq = high_resolution_clock::now();
    auto duration_seq = duration_cast<microseconds>(end_seq - start_seq);

    auto start_list = high_resolution_clock::now();
    for (int val : vec) {
        volatile int temp = val;
    }
    auto end_list = high_resolution_clock::now();
    auto duration_list = duration_cast<microseconds>(end_list - start_list);

    cout << "Iterate over " << num_elements << " elements:" << endl;
    cout << "  ArraySequence: " << duration_seq.count() << " ms" << endl;
    cout << "  vector:   " << duration_list.count() << " ms" << endl;
    cout << endl;
}

void chronoRemoveIntAS(size_t num_elements) {
    ArraySequence<int> seq;
    vector<int> vec;

    // Удаление с конца
    for (size_t i = 0; i < num_elements; ++i) {
        seq.add(i);
        vec.push_back(i);
    }

    auto start_seq_end = high_resolution_clock::now();
    for (size_t i = 0; i < num_elements / 2; ++i) {
        seq.remove(seq.getSize() - 1);
    }
    auto end_seq_end = high_resolution_clock::now();
    auto duration_seq_end = duration_cast<microseconds>(end_seq_end - start_seq_end);

    auto start_vec_end = high_resolution_clock::now();
    for (size_t i = 0; i < num_elements / 2; ++i) {
        vec.pop_back();
    }
    auto end_vec_end = high_resolution_clock::now();
    auto duration_vec_end = duration_cast<microseconds>(end_vec_end - start_vec_end);

    // Удаление из начала
    ArraySequence<int> seq2;
    vector<int> vec2;
    for (size_t i = 0; i < num_elements; ++i) {
        seq2.add(i);
        vec2.push_back(i);
    }
    auto start_seq_begin = high_resolution_clock::now();
    for (size_t i = 0; i < num_elements / 2; ++i) {
        seq2.remove(0);
    }
    auto end_seq_begin = high_resolution_clock::now();
    auto duration_seq_begin = duration_cast<microseconds>(end_seq_begin - start_seq_begin);

    auto start_vec_begin = high_resolution_clock::now();
    for (size_t i = 0; i < num_elements / 2; ++i) {
        vec2.erase(vec2.begin());
    }
    auto end_vec_begin = high_resolution_clock::now();
    auto duration_vec_begin = duration_cast<microseconds>(end_vec_begin - start_vec_begin);

    cout << "Remove " << num_elements / 2 << " elements:" << endl;
    cout << "  From the end:" << endl;
    cout << "    ArraySequence: " << duration_seq_end.count() << " ms" << endl;
    cout << "    vector:   " << duration_vec_end.count() << " ms" << endl;

    cout << "  From the beginning:" << endl;
    cout << "    ArraySequence: " << duration_seq_begin.count() << " ms" << endl;
    cout << "    vector:   " << duration_vec_begin.count() << " ms" << endl;
    cout << endl;
}

void chronoArraySequence(size_t num_elements, size_t step) {
    std::cout << "Performance tests for ArraySequence vs std::vector" << std::endl << std::endl;

    chronoAddIntAS(num_elements); // ms
    chronoGetIndexIntAS(num_elements, step); // ns
    chronoIterateIntAS(num_elements); // ms
    chronoRemoveIntAS(num_elements); // ms

}