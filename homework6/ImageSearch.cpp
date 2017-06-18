
/*CopyRight 2017 Mike Sosan 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: sosanma
 *
 * Created on April 12, 2017, 11:52 PM
 */

#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "PNG.h"
#include "Assert.h"

int getPixelIndex(int rowNum, int colNum, int NumberofCol) {
    return ((rowNum * 10 + colNum));
}


// draws a red box around any matches we find
void drawBox(PNG& png, int row, int col, int width, int height) {
    // Draw horizontal lines
    for (int i = 0; (i < width); i++) {
    png.setRed(row, col + i);
    png.setRed(row + height, col + i);
    }
    // Draw vertical lines
    for (int i = 0; (i < height); i++) {
    png.setRed(row + i, col);
    png.setRed(row + i, col + width);
    }
}

// adds the match to the row matches and col matches vectors
// also adds the rows plus height, and col plus width
void addToVec(std::vector<int> rowS, std::vector<int> colS, int row,
        int col, int w, int h) {
    rowS.push_back(row), rowS.push_back(row + h);
    colS.push_back(col), colS.push_back(col + w);
}


// second pass to see if the pixel is the same shade
bool isSameRGB(std::vector<int>& RGB, PNG image, int tol, int pixel) {
    bool isMatch = false;
    int pixelR, pixelG, pixelB;
    // int vals that represent the average RGB values from the vector
    int testR = RGB[0], testG = RGB[1], testB = RGB[2];
    // gets the image as a buffer so we can compare the pixel's RGBA
    const std::vector<unsigned char>& imgBuff = image.getBuffer();
    pixelR = imgBuff[pixel];
    pixelG = imgBuff[pixel + 1];
    pixelB = imgBuff[pixel + 2];
    // systematically check to see if the RGB
    // averages are in our tolereance range
    if (pixelR + tol >= testR || pixelR - tol <= testR) {
        if (pixelG + tol >= testG || pixelG - tol <= testG) {
            if (pixelB + tol >= testB || pixelB - tol <= testB) {
                // std::cout << "we've found a match!: " << std::endl;
                isMatch = true;
            }
        }
    }
    return isMatch;
}

const std::vector<int> avgBackPixels(int r, int c,
                                     PNG imageRegion, PNG mask) {
    const std::vector<unsigned char>& mBuffer = mask.getBuffer();
    const std::vector<unsigned char>& iBuff = imageRegion.getBuffer();
    int maskR, maskB, maskG, maskA, rAv, bAv, gAv;
    int backPixNum = 0, rSum = 0, bSum = 0, gSum = 0, mH = mask.getHeight(),
    mW = mask.getWidth();
    // Goes through the main image's pixels with the mask's row and height
    // we start at the current pixel that was passed in
    //  so we add r to the row and c to the col
    for (int row = r; row < r + mH; row++) {
       for (int col = c; col < c + mW; col++) {
            // we are using the buffer so we need to get
            // the pixel index to get the RGB values
            // std::cout << "In avgBackPix" << std::endl;
            int i = getPixelIndex(row, col, mH);
            // get the RGBA values
            maskR = mBuffer[i], maskB = mBuffer[i + 1];
            maskG = mBuffer[i + 2], maskA = mBuffer[i + 3];
            // checks to see if the Red value is the same as the blue and green.
            //  In otherwords if it's the background
            if (maskB == maskR && maskG == maskR && maskA != 0) {
                rSum += iBuff[i], bSum += iBuff[i + 1], gSum += iBuff[i + 2];
                // count the amount of black bacgroung pixels we have
                backPixNum++;
            }
        }
    }
    // std::cout << "avg Back pix finished: " << std::endl;
    // get the average of each RGB val and return it as a vector of ints
    rAv = (rSum / backPixNum);
    bAv = (bSum / backPixNum);
    gAv = (gSum / backPixNum);

    std::vector<int> RGBVec = {rAv, bAv, gAv};
    return RGBVec;
}

// calculate to see if our percent of matches is within our tolerance
bool isMaskMatch(int w, int h, int matchPercent, int numMatched) {
    int notMatched = (h * w) - numMatched;
    int netMatch = numMatched - notMatched;
    if (netMatch > (w * h * matchPercent) / 100) {
        return true;
    }
    return false;
}

// this checks to see how many mask 
// background pixels match with the main image's
// in other words, how many pixels match the background once we get an average
// r and c are the current pixel we're on
int maskOps(PNG mask, PNG image, int r, int c, int tol, int pix) {
    int amtMatched = 0;
    // gets a vector of 3 ints that represent the average RGB values
    std::vector<int> avgBackVecs = avgBackPixels(r, c, image, mask);
    // a bool to see if this pixel macthes the average background color
    bool same = isSameRGB(avgBackVecs, image, tol, pix);
    if (same == true) {
        amtMatched++;
    }
    return amtMatched;
}

// Checking to see if we are checking in a spot thats had a previous match
int isPixInMatch(int row, int col, std::vector<int> rows, 
                          std::vector<int> cols) {
    bool rowMatch = false;
    // std::cout << "In spotInMatch 1" << std::endl;
    // check to see if the current row is in the vector 
    // or if its greater and less than or equal to the rows value
    for (unsigned int i = 0; i < rows.size(); i++) {
        if (row == rows[i] || (row > rows[i] && row <= rows[i + 1])) {
            rowMatch = true;
        }
    }
    // if we do find a row match, now we want to check the coloumns
    // if the requirements are met, we return the col value at j+1
    if (rowMatch) {
        for (unsigned int j = 0; j < cols.size(); j++) {
            if (col == cols[j] || (col > cols[j] && col <= cols[j + 1])) {
                return cols[j + 1];
            }
        }
    }
    // if we dont find a match
    return -1;
}

void maskMoveAndCheck(PNG largeFile, PNG mask, int pixMatch, int tol,
        std::vector<int> rowMatch,  std::vector<int> colMatch) {
    int lgheight = largeFile.getHeight(), lgwidth = largeFile.getWidth();
    int mheight = mask.getHeight(), mwidth = mask.getWidth();
#pragma omp parallel for
    {
        for (int row = 0; row < lgheight; row++) {
            for (int col = 0; col < lgwidth; col++) {
                int isInMatch = isPixInMatch(row, col, rowMatch, colMatch);
                // if we have found a match
                if (isInMatch == -1) {
                    int numMatched = maskOps(mask, largeFile, row, col, tol,
                               getPixelIndex(row, col, lgwidth));
                    bool match = isMaskMatch(mwidth,
                                 mheight, pixMatch, numMatched);
                    if (match) {
                        addToVec(rowMatch, colMatch, row, col, mwidth, mheight);
                        col = col + mwidth - 1;
                    }
                } 
            }
        }
    }
}

void testMethod() {
    PNG img;
    img.load("Mammogram.png");
    const std::vector<unsigned char>& buffer = img.getBuffer();  
    const int index = getPixelIndex(10, 10, img.getWidth());
    std::cout << " red    =  "   << static_cast<int>(buffer[index])
              << " green  =  "  << static_cast<int>(buffer[index + 1])
              << " blue   =  "  << static_cast<int>(buffer[index + 2])
              << " Alpha  =  "  << static_cast<int>(buffer[index + 3])
              << std::endl;
}


int main(int argc, char** argv) {
    PNG mainImage, subImage; mainImage.load(argv[1]); subImage.load(argv[2]);
    // establish default tolerance and set it if given arguments
    int matchPercent = 75, tolerance = 32;
    if (argc > 4) {
            matchPercent = atoi(argv[5]); tolerance = atoi(argv[6]);
    }
    // put the row and col coordinates in their own vectors
    std::vector<int> rowMatchVals, colMatchVals;
    maskMoveAndCheck(mainImage, subImage,   matchPercent,
                     tolerance, rowMatchVals, colMatchVals);
    // draws a box for every successful match in rowMatch
#pragma omp parallel for
        {
        for (unsigned int i = 0; i < rowMatchVals.size() - 1; i += 2) {
#pragma omp critical
            { 
            drawBox(mainImage, rowMatchVals[i], colMatchVals[i],
                         subImage.getWidth(), subImage.getHeight());
            }
        }
    }
    // outputs all the coorodinates sub images that were matched  
    for (unsigned int i = 0; i < rowMatchVals.size(); i += 2) {
        std::cout << "sub-image matched at: " << rowMatchVals[i] 
                     << ", " <<rowMatchVals[i + 1] << ", " << colMatchVals[i] 
                     << ", " << colMatchVals[i + 1] << std::endl;
    }
    return 0;
}

