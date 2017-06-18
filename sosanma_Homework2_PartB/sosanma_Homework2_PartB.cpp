// Copyright 2017 Mike Sosan 

#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <cmath>
#include <set>
#include <string>

inline int testInline(int a, int b) {
    return a < b;
}

int main(int argc, char *argv[]) {
    // creates a vector full of random ints from 0 - 100 
    std::string temp = argv[1];
    std::vector<int> list(450000, rand() % 100); 
        if (temp == "lambda") {
            for (int i = 0; i < 1500; i++) {
                std:: sort(list.begin(), list.end(), 
                        [] (int a, int b) {return a < b;});
            }
            std:: cout << "Done!" << std::endl;
        } else if (temp == "inline") {
            for (int i = 0; i < 1500; i++) {
                std:: sort(list.begin(), list.end(), testInline);
            }
            std:: cout << "Done!" << std::endl;
        }
    return 0;
}

