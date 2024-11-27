#include "SortAlgo.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <algorithm>
#include <string>
#include <vector>
#include <numeric>


namespace {

template<typename T>
std::vector<T> CreateArray (size_t theSize)
{
    std::vector<T> anArr (theSize);
    std::iota (anArr.rbegin(), anArr.rend(), T());
    return anArr;
}

template<>
std::vector<int> CreateArray (size_t theSize)
{
    std::vector<int> anArr (theSize);
    std::iota (anArr.rbegin(), anArr.rend(), 0);
    return anArr;
}

template<>
std::vector<std::string> CreateArray (size_t theSize)
{
    std::string aStr = "a";
    std::vector<std::string> anArr (theSize);
    for (auto anIt = anArr.rbegin(); anIt != anArr.rend(); ++anIt) {
        *anIt = aStr;
        aStr += 'a';
    }
    return anArr;
}

}

TEST(SORT_ALGO, INSERT_SORT)
{
    const size_t aSize = 100;
    auto aStrArr = CreateArray<std::string> (aSize);
    auto anIntArr = CreateArray<int> (aSize);

    InsertionSort (aStrArr.data(), aStrArr.data() + aSize, std::less<std::string>());
    InsertionSort (anIntArr.data(), anIntArr.data() + aSize, std::less<int>());

    for (size_t i = 0; i < aSize - 1; ++i) {
        EXPECT_TRUE (!std::less<std::string>() (aStrArr[i + 1], aStrArr[i]));
        EXPECT_TRUE (!std::less<int>() (anIntArr[i + 1], anIntArr[i]));
    }
}

TEST(SORT_ALGO, C_QUICK_SORT)
{
    const size_t aSize = 100;
    auto aStrArr = CreateArray<std::string> (aSize);
    auto anIntArr = CreateArray<int> (aSize);

    ÑlassicQuickSort (aStrArr.data(), aStrArr.data() + aSize, std::less<std::string>());
    ÑlassicQuickSort (anIntArr.data(), anIntArr.data() + aSize, std::less<int>());

    for (size_t i = 0; i < aSize - 1; ++i) {
        EXPECT_TRUE (!std::less<std::string>() (aStrArr[i + 1], aStrArr[i]));
        EXPECT_TRUE (!std::less<int>() (anIntArr[i + 1], anIntArr[i]));
    }
}

TEST(SORT_ALGO, QUICK_SORT)
{
    const size_t aSize = 100;
    auto aStrArr = CreateArray<std::string> (aSize);
    auto anIntArr = CreateArray<int> (aSize);

    QuickSort (aStrArr.data(), aStrArr.data() + aSize, std::less<std::string>());
    QuickSort (anIntArr.data(), anIntArr.data() + aSize, std::less<int>());

    for (size_t i = 0; i < aSize - 1; ++i) {
        EXPECT_TRUE (!std::less<std::string>() (aStrArr[i + 1], aStrArr[i]));
        EXPECT_TRUE (!std::less<int>() (anIntArr[i + 1], anIntArr[i]));
    }
}


int main (int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    return RUN_ALL_TESTS();
}