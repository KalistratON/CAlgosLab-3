#include "Quick_sort.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <random>
#include <limits>
#include <numeric>
#include <fstream>

#include <nanobench.h>

#define ANKERL_NANOBENCH_IMPLEMENT


using namespace std;
using namespace chrono;

vector<int> GenerateReverseSortedVector(int theSize)
{
    vector<int> aVec (theSize);
    std::iota (aVec.rbegin(), aVec.rend(), 0);
    return aVec;
}

double InsertionSortTest (vector<int> vec)
{
    auto start = high_resolution_clock::now();
    InsertionSort (vec.data(), vec.data() + vec.size(), less<int>());
    auto end = high_resolution_clock::now();
    return duration<double>(end - start).count();
}

double QuickSortTest (vector<int> vec)
{
    auto start = high_resolution_clock::now();
    QuickSort (vec.data(), vec.data() + vec.size(), less<int>());
    auto end = high_resolution_clock::now();
    return duration<double>(end - start).count();
}

void save_results_to_csv (const vector<int>& sizes,
    const vector<double>& rev_is,
    const vector<double>& rev_qs)
{
    ofstream file("F:\\Pet-Projects\\CAlgos\\labaratory_work_3\\results.csv");
    if (!file.is_open()) {
        cerr << "Cann't open results.csv\n";
        return;
    }

    file << "size,InsertionSort,QuickSort\n";
    for (size_t i = 0; i < sizes.size(); ++i) {
        file << sizes[i] << "," << rev_is[i] << "," << rev_qs[i] << "\n";
    }
    return file.close();
}

void chrono_tests()
{
    vector<int> array_sizes;
    vector<double> reverse_insertion_sort_times;
    vector<double> reverse_quick_sort_times;

    int tries = 25000;
    double time = 0.0;
    vector<int> vec;

    for(int i = 2; i <= 100; i += 1) {
        array_sizes.push_back (i);
    }

    for (int size : array_sizes) {
        vec = GenerateReverseSortedVector(size);

        time = 0;
        for (int i = 0; i < tries; ++i) {
            time += QuickSortTest (vec);;
        }
        reverse_quick_sort_times.push_back(time / tries);

        time = 0;
        for (int i = 0; i < tries; ++i) {
            time += InsertionSortTest (vec);
        }
        reverse_insertion_sort_times.push_back (time / tries);
    }
    save_results_to_csv (array_sizes, reverse_insertion_sort_times, reverse_quick_sort_times);
}

#if 0
void nanobench_test()
{
    vector<int> array_sizes;
    vector<double> reverse_insertion_sort_times;
    vector<double> reverse_quick_sort_times;

    vector<int> vec;
    int warmups = 1000, epochs = 10000;

    ankerl::nanobench::Bench bench;

    for (int i = 2; i <= 60; i += 1) {
        array_sizes.push_back(i);
    }

    for (int size : array_sizes)
    {
        vec = GenerateReverseSortedVector(size);

        bench = ankerl::nanobench::Bench().warmup(warmups).minEpochIterations(epochs);
        bench.run("Reverse array | Quick sort", [&]() { QuickSortTest (vec); });
        reverse_quick_sort_times.push_back(bench.results().front().median (ankerl::nanobench::Result::Measure::elapsed));

        bench = ankerl::nanobench::Bench().warmup(warmups).minEpochIterations(epochs);
        bench.run("Reverse array | Insertion sort", [&]() { InsertionSortTest (vec); });
        reverse_insertion_sort_times.push_back(bench.results().front().median (ankerl::nanobench::Result::Measure::elapsed));
    }
    save_results_to_csv (array_sizes, reverse_insertion_sort_times, reverse_quick_sort_times);

}
#endif

int main()
{
    chrono_tests();
    return 0;
}
