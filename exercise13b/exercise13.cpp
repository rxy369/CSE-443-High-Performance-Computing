// A simple program to generate a large set of random numbers and
// operate on them using different scheduling options.
//
// Copyright (C) raodm@miamiOH.edu

#include <omp.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <utility>

// A convenience typedef to hold a number and its number of prime factor
// counts
typedef std::pair<long, int> NumFactCount;

// Forward declaration (aka prototype) to keep compiler happy
bool isPrime(const long);
int getPrimeFactorCount(const long);

NumFactCount
findNumberWithMaxPrimeFactorCount(const std::vector<long>& numList) {
    // Can't set size of vector below until we know number of threads.
    std::vector<NumFactCount> maxFactCount;
    
#pragma omp parallel shared(numList, maxFactCount)
    {  // fork
#pragma omp critical
        if (omp_get_thread_num() == 0)
            maxFactCount.resize(omp_get_num_threads());  // Resize shared vector
// Wait for thread 0 to finish its task
#pragma omp barrier
        
        // Now compute the chunk of values this thread should work with. 
        // const int iterPerThr = numList.size() / omp_get_num_threads();
        const int thrId = omp_get_thread_num();
        // const int startIndex = thrId * iterPerThr;
        // int endIndex = startIndex + iterPerThr;
        // if (omp_get_num_threads() == thrId + 1) {
            // Handle case where numList.size() is not evenly divisible
            // by number of threads
            // endIndex = numList.size();
        // }
#pragma omp for schedule(runtime)
        for (size_t i = 0; (i < numList.size()); i++) {
            int primeFactCount = getPrimeFactorCount(numList[i]);
            if (maxFactCount[thrId].second < primeFactCount) {
                maxFactCount[thrId] = std::make_pair(numList[i],
                                                     primeFactCount);
            }  // if-statement
        }
    }  // join (waits for all threads to finish)
    
    // Find the maximum from the various threads.
    size_t max = 0;
    for (size_t i = 0; (i < maxFactCount.size()); i++) {
        if (maxFactCount[max].second < maxFactCount[i].second) {
            max = i;
        }
    }
    return maxFactCount[max];
}


// ----------------------------------------------------------------------
//     DO  NOT  MODIFY  CODE  BELOW  THIS  LINE
// ----------------------------------------------------------------------

int getPrimeFactorCount(const long number) {
    int count = 0;
    for (long factor = 1; (factor < number); factor++) {
        if ((number % factor == 0) && isPrime(factor)) {
            count++;
        }
    }
    return count;
}

bool isPrime(const long number) {
    int MaxFactor = sqrt(number) + 1;
    for (int factor = 2; (factor < MaxFactor); factor++) {
        if (number % factor == 0) {
            return false;
        }
    }
    return true;
}

long generator() {
    static int count = 0;
    unsigned int seed = 0;
    const long digits = (count++ % 4 > 1 ? 1000L : 10000000L);
    return rand_r(&seed) % digits;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Specify count of numbers to generate "
                  << "as command-line argument.\n";
        return 1;
    }
    // Generate vector with random numbers
    std::vector<long> numList(std::stoi(argv[1]));
    std::generate(numList.begin(), numList.end(), generator);
    std::sort(numList.begin(), numList.end());
    // Compute the largest prime number in the list.
    const NumFactCount bigPrime = findNumberWithMaxPrimeFactorCount(numList);
    // Print it.
    std::cout << "Number with most number of prime factors: "
          << bigPrime.first  << ", prime factor count = "
          << bigPrime.second << std::endl;
    return 0;
}

// End of source code.

