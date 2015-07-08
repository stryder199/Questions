#pragma once

#include <list>
#include <mutex>
#include <future>

#define MAX_RUNNING_THREADS 4
typedef unsigned long long ULL;

class Factor
{
public:
    static std::list<ULL> CreateFactors(ULL maxValue);
private:
    static std::list<ULL> CreateFactorsRecursive(ULL value, ULL maxValue, int lastLevel);
    static void Factor::CreateFactorsRecursiveCall(ULL value, ULL currentLevel, ULL maxValue, std::list<ULL> *factorList, std::future<std::list<ULL>> *futureFactorList);

    static int m_runningThreadCount;
    static std::mutex m_threadMutex;
};

