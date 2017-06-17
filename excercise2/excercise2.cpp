/* 
 * File:   excercise2.cpp
 * Author: sosanma
 *
 * Created on January 31, 2017, 3:21 PM
 * 
 * copyright (C) 2017 Mike Sosan
 */

// Change to suitable copy right message

#include <fstream>
#include <iostream>
#include <string>
#include <iterator>

int countVowels(std::string& str) {
    // Returns the number of vowels (one of the characters 'aeiouAEIOU')
    // in the supplied string
    const std::string vowels = "aeiouAEIOU";
    int count = 0;

    for (size_t i = 0; i < str.size(); i++) {
        if (vowels.find(str[i]) != std::string::npos) {
            count++;
        }
    }
    return count;
}

// --------[ Do not modify code below this line ]-----------------

void countVowels(const size_t size) {
    // Create a large string by repeating letters
    const std::string Letters = "abcdefghijklmnopqrstuvwxyz";
    std::string str(size, ' ');
    for (size_t i = 0; (i < size); i++) {
        str[i] = Letters[i % Letters.size()];
    }
    // Now call method to count vowels
    std::cout << "Vowels count: " << countVowels(str) << std::endl;
}

/** 
    Main method that acts as a unit test to call countVowles with
    different options based on command-line arguments.
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Specify necessary command-line arguments.\n";
        return 3;
    }
    if (argv[1] == std::string("--str")) {
        std::string str(argv[2]);
        std::cout << "Vowel count: " << countVowels(str) << std::endl;
    } else {
        const size_t size = std::stoi(argv[2]);
        countVowels(size);
    }
    return 0;
}

// End of source code
