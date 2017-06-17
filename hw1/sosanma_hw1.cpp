// Hw1
// Copyright 2017 Mike Sosan

#include <iostream>
#include <algorithm>
#include <string>
#include <cctype>

// swaps the digits with the letters in the string at the index passed in
void moveDigitsToIndex(std::string& str, int firstDigit, int indexToMove) {
    size_t count = 0;  // increments so we can swap chars appropriately
    // keeps swapping chars until we reach end of string
    if (firstDigit != -1) {
        for (size_t i = firstDigit; i < str.length(); i++) { 
            if ((indexToMove + count) < str.length()) {
                std::swap(str[indexToMove + count], str[i]);
                // swaps the values for correct placement
                for (size_t k = indexToMove + count+1; k < i; k++) { 
                    std:: swap(str[k], str[i]);
                }
                count++;
            }
        }
    }
}

// finds the index of the first index after we have put the digits at the end
int findFirstDigit(std::string& str) {
    for (size_t i = 0; i < str.length(); i++) {
        if (std::isdigit(str[i]))
            return i;
    }
    return -1;  // no digits found
}
// stores the current digit, 
// moves all the other values one spot over to the left, 
// then puts the digit at the end
void moveHelper(std::string& str, int index) {
    char thisDigit = str[index];
    for (size_t i = index; i < str.length(); i++) {
        str[i] = str[i+1];
    }
    str[str.length()-1] = thisDigit;
}
// loops through the string and calls the moveHelper method when we find a digit
void moveDigitsToEnd(std::string& str) {
    size_t count = 0;  // how many digits we found already
    for (size_t j = 0; j < str.length(); j++) {
        if (std::isdigit(str[count])) {
            moveHelper(str, count);
            count--;  // accounts for side by side digits
        }
        count++;
    }
}

bool checkValidString(std::string& str) {
    size_t num = 0;
    for (size_t j = 0; j < str.length(); j++) {
        if (std::isdigit(str[j])) {
            num++;
        }
    }
    if (num == str.length())  // is the string just digits?
        return false;  // is so, return false
    
    return true;
}

void gatherDigits(std::string& s, const size_t pos) {
    // Implement this method! You may introduce additional methods as
    // needed
    if (!checkValidString(s)) {
        return;
    }
    moveDigitsToEnd(s);
    moveDigitsToIndex(s, findFirstDigit(s), pos);
}


// --------------------------------------------------------------
//        DO  NOT  MODIFY  CODE  BELOW  THIS  LINE
// --------------------------------------------------------------

int main() {
    std::string str;
    int pos = 0;
    do {
        std::cout << "Enter gather position (-1 to quit) and string:\n";
        std::cin >> pos;
        if (pos != -1) {
            std::cin >> str;
            gatherDigits(str, pos);
            std::cout << "Gathered @ " << pos << ": " << str << std::endl;
        }
    } while (pos != -1);
    return 0;
}
