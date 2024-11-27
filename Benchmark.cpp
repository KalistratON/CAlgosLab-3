#include "SortAlgo.h"

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

void SaveResults (const vector<int>& theSizes,
    const vector<double>& theRevIS,
    const vector<double>& theRevQS)
{
    ofstream aFile("F:\\Pet-Projects\\CAlgos\\labaratory_work_3\\results.csv");
    if (!aFile.is_open()) {
        cerr << "Cann't open results.csv\n";
        return;
    }

    aFile << "size,InsertionSort,QuickSort\n";
    for (size_t i = 0; i < theSizes.size(); ++i) {
        aFile << theSizes[i] << "," << theRevIS[i] << "," << theRevQS[i] << "\n";
    }
    return aFile.close();
}

void ChronoTests()
{
    const int aSizeCount = 100;
    vector<int> aSizeArray (aSizeCount);
    std::iota (aSizeArray.begin(), aSizeArray.end(), 2);

    vector<double> aQSTimes;
    vector<double> anISTimes;

    double aTime = 0.0;
    int aTryCount = 25000;
    std::for_each (aSizeArray.begin(), aSizeArray.end(), [&](int theSize) {
        vector<int> anArr = GenerateReverseSortedVector (theSize);
        for (int i = 0; i < aTryCount; ++i) {
            aTime += QuickSortTest (anArr);;
        }
        aQSTimes.push_back(aTime / aTryCount);

        aTime = 0.0;
        for (int i = 0; i < aTryCount; ++i) {
            aTime += InsertionSortTest (anArr);
        }
        anISTimes.push_back (aTime / aTryCount);

        aTime = 0.0;
    });
    SaveResults (aSizeArray, anISTimes, aQSTimes);
}

#if 0
void nanobench_test()
{
    vector<int> aSizeArray;
    vector<double> anISTimes;
    vector<double> aQSTimes;

    vector<int> vec;
    int warmups = 1000, epochs = 10000;

    ankerl::nanobench::Bench bench;

    for (int i = 2; i <= 60; i += 1) {
        aSizeArray.push_back(i);
    }

    for (int size : aSizeArray)
    {
        vec = GenerateReverseSortedVector(size);

        bench = ankerl::nanobench::Bench().warmup(warmups).minEpochIterations(epochs);
        bench.run("Reverse array | Quick sort", [&]() { QuickSortTest (vec); });
        aQSTimes.push_back(bench.results().front().median (ankerl::nanobench::Result::Measure::elapsed));

        bench = ankerl::nanobench::Bench().warmup(warmups).minEpochIterations(epochs);
        bench.run("Reverse array | Insertion sort", [&]() { InsertionSortTest (vec); });
        anISTimes.push_back(bench.results().front().median (ankerl::nanobench::Result::Measure::elapsed));
    }
    SaveResults (aSizeArray, anISTimes, aQSTimes);

}
#endif

int main()
{
    ChronoTests();
    return 0;
}
