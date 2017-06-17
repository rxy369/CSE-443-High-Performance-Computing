// Copyright (C) 2016 raodm@miamiOH.edu

/** A program to compute factors of a given list of numbers in
    parallel using OpenMP
*/

#include <omp.h>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>


// A shortcut to refer to a vector of integers
using IntVec = std::vector<int>;
using StringVec = std::vector<std::string>;

bool prime(int num) {
    for (int i = 2; i < (std::sqrt(num) + 1); i++) {
        if (num%i == 0 && i != num) {
            return false;
        }
    }
    return true;
}

bool primeFactorable(int num) {
    for (int i = 2; i < (std::sqrt(num) + 1); i++) {
        if (num%i == 0) {
            if (prime(i)) {
                int temp = (num)/i;
                if (prime(temp)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool factorial(int num) {
    if (num == 0)
        return 1;
    int a = 1;
    int b = 1;
    while (a < num) {
        b *= ++a; 
    }
    return (b == num);
}

bool palindromic(const int num) {
    int a = num, b = 0;
    while (a > 0) {
        b = (b*10 + a%10);
        a /= 10; 
    }
    return (b == num);
}

std::string runFunctions(int i) {
    std::string curVal = std::to_string(i);
    std::string s = curVal + ": ";
    if (prime(i)) 
        s +=  "is prime,";
    else 
        s += "not prime,";
    if (primeFactorable(i)) 
        s += " is Factorable,";
    else 
        s += " not Factorable,";

    if (factorial(i)) 
        s += " is factorial,";
    else 
        s += " not factorial,";

    if (palindromic(i)) 
        s += " is palindromic\n";
    else 
        s += " not palindromic\n";
    
    return s;
}
//---------------------------------------------------------------------
//    DO   NOT   MODIFY   CODE   BELOW   THIS   LINE
//---------------------------------------------------------------------

// Returns the number of factors for a given number.
int getFactorCount(int num) {
    int factCount     = 0;
    for (int fact = 1; (fact <= num); fact++) {
        if (num % fact == 0) {
            factCount++;
        }
    }
    return factCount;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Error" << std::cout;
    }
    int ia = std::stoi(argv[1]), ib = std::stoi(argv[2]);
    IntVec numList(ib+1 - ia);
    StringVec strings(ib+1 - ia);
    std::iota(numList.begin(), numList.end(), ia);
    #pragma omp parallel shared(numList, strings)
    {
        const int iterPerThr = numList.size() / omp_get_num_threads();
        const int startIndex = omp_get_thread_num() * iterPerThr;
        int endIndex = startIndex + iterPerThr;
        if (omp_get_thread_num() == omp_get_num_threads()-1) {
            endIndex = numList.size();
        }

        
        // #pragma omp for
        for (int i = startIndex; i < endIndex; i++) {
            strings[i] = runFunctions(numList[i]);
        }
    }
    for (size_t i = 0; i < strings.size(); i++) {
        std::cout << strings[i];
    }
    return 0;
}