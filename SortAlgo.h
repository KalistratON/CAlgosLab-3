#pragma once

#include <algorithm>
#include <iterator>


template<typename T, typename Comp>
void InsertionSort (T* theFirst, T* theLast, Comp theComp)
{
    for (T* i = theFirst + 1; i < theLast; ++i) {
        T aValue = std::move (*i);
        T* j = i - 1;
        while (j >= theFirst && theComp (aValue, *j)) {
            *(j + 1) = std::move (*j);
            --j;
        }
        *(j + 1) = std::move (aValue);
    }
}

template<typename T, typename Comp>
T& GetPivot (T* theFirst, T* theMid, T* theLast, Comp theComp)
{
    if (theComp (*theMid, *theFirst)) {
        std::swap (*theFirst, *theMid);
    }

    if (theComp (*theLast, *theMid)) {
        std::swap (*theLast, *theMid);
    }

    if (theComp (*theLast, *theFirst))  {
        std::swap (*theLast, *theFirst);
    }
    return *theMid;
}

template<typename T, typename Comp>
T* Partition (T* theFirst, T* theLast, Comp theComp)
{
    int aSize = std::distance (theFirst, theLast);
    T aRefElement = GetPivot (theFirst, theFirst + aSize / 2, theLast - 1, theComp);

    T* aLeft = theFirst;
    T* aRight = theLast - 1;

    while (theComp (*aLeft, *aRight)) {
        while (theComp (*aLeft, aRefElement)) {
            ++aLeft;
        }

        while (theComp (aRefElement, *aRight)) {
            --aRight;
        }

        if (aLeft < aRight) {
            std::swap (*aLeft, *aRight);
        }
    }
    return aLeft;
}

template<typename T, typename Comp>
void QuickSort (T* theFirst, T* theLast, Comp theComp) 
{
    const int aTreshold = 10;
    int aSize = std::distance (theFirst, theLast);
    while (aSize > 1) {
        if (aSize <= aTreshold) {
            return InsertionSort (theFirst, theLast, theComp);
        }

        T* aMid = Partition (theFirst, theLast, theComp);
        if (std::distance (theFirst, aMid) < std::distance (aMid, theLast)) {
            QuickSort (theFirst, aMid, theComp);
            theFirst = aMid;
        } else {
            QuickSort (aMid, theLast, theComp);
            theLast = aMid;
        }
        aSize = std::distance (theFirst, theLast);
    }
}

template<typename T, typename Comp>
void ÑlassicQuickSort (T* theFirst, T* theLast, Comp theComp)
{
    while (std::distance (theFirst, theLast) > 1) {
        T* aMid = Partition (theFirst, theLast, theComp);
        if (std::distance (theFirst, aMid) < std::distance (aMid, theLast)) {
            ÑlassicQuickSort (theFirst, aMid, theComp);
            theFirst = aMid;
        } else {
            ÑlassicQuickSort (aMid, theLast, theComp);
            theLast = aMid;
        }
    }
}