#include "Factor.h"

using namespace std;

int Factor::m_runningThreadCount = 0;
mutex Factor::m_threadMutex;

// Entry point for callers
// Hides some of the starting logic that callers don't need to know
list<ULL> Factor::CreateFactors(ULL maxValue)
{
    list<ULL> foundFactors = CreateFactorsRecursive(1, maxValue, 2);
    return foundFactors;
}

// Recursively look for all the factors of 2,3,5 up to a given max value
// Note:
//      When the previous call was a 2 factor we want to call 2,3,5 in this call
//      When the previous call was a 3 factor we want to call 3,5 in this call
//      When the previous call was a 5 factor we want to call 5 in this call
//      This accounts for duplicate calculations i.e. 1*2*3 holds the same result as 1*3*2. 
//      In this case we would ignore the 1*3*2 calculation since it is already in the list.
// Input: 
//      value: the last value
//      maxValue: the max value to end at supplied by the caller
//      lastLevel: the last factor that the recursive call was called with
// Returns: 
//      the sorted,non-duplicate list of factors
list<ULL> Factor::CreateFactorsRecursive(ULL value, ULL maxValue, int lastLevel)
{
    list<ULL> factorList;

    // If you find a factor greater than the max value then you are done
    if (value > maxValue)
    {
        return factorList;
    }

    // Add current value to the list
    factorList.push_back(value);
    
    // Do the recursive calls
    list<ULL> twoList, threeList, fiveList;
    future<list<ULL>> twoFutureList, threeFutureList, fiveFutureList;
    if (lastLevel == 2)
    {
        CreateFactorsRecursiveCall(value, 2, maxValue, &twoList, &twoFutureList);
    }

    if (lastLevel == 3 || lastLevel == 2)
    {
        CreateFactorsRecursiveCall(value, 3, maxValue, &threeList, &threeFutureList);
    }

    CreateFactorsRecursiveCall(value, 5, maxValue, &fiveList, &fiveFutureList);

    // The recursive calls can either return a list or a future due to async calls, resolve any futures
    if (twoFutureList.valid())
    {
        twoList = twoFutureList.get();
        m_threadMutex.lock();
        m_runningThreadCount--;
        m_threadMutex.unlock();
    }
    if (threeFutureList.valid())
    {
        threeList = threeFutureList.get();
        m_threadMutex.lock();
        m_runningThreadCount--;
        m_threadMutex.unlock();
    }
    if (fiveFutureList.valid())
    {
        fiveList = fiveFutureList.get();
        m_threadMutex.lock();
        m_runningThreadCount--;
        m_threadMutex.unlock();
    }

    // Merge separate calls into a master list
    factorList.merge(twoList);
    factorList.merge(threeList);
    factorList.merge(fiveList);

    // Return the master list
    return factorList;
}

// Determines if this call should be async or not and returns either a list or a future respectively
void Factor::CreateFactorsRecursiveCall(ULL value, int currentLevel, ULL maxValue, list<ULL> *factorList, future<list<ULL>> *futureFactorList)
{
    m_threadMutex.lock();
    if (m_runningThreadCount < MAX_RUNNING_THREADS)
    {
        m_runningThreadCount++;
        m_threadMutex.unlock();
        *futureFactorList = async(launch::async, &Factor::CreateFactorsRecursive, value * currentLevel, maxValue, currentLevel);
    }
    else
    {
        m_threadMutex.unlock();
        *factorList = CreateFactorsRecursive(value * currentLevel, maxValue, currentLevel);
    }
}