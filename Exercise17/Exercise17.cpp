// Copyright (C) 2016 raodm@miamiOH.edu

// This program computes value for PI via numerical integration. It
// integrates function y = 4 / (1 + x * x), 0 <= x <= 1.

#include <mpi.h>
#include <iostream>
#include <cmath>

double
getArea(const int numRects, const int myRank, const double rectWidth) {
    const double startX = (myRank * numRects * rectWidth);
    double sum = 0;
    for (int i = 0; (i < numRects); i++) {
        double x = startX + (i * rectWidth);
        sum += 4.0 / (1.0 + x * x);
    }
    const double myPI = sum * rectWidth;
    return myPI;
}

double integrate(int& totalRects, const int myRank, const int numProcs) {
    // Send value of totalRects to all processes
    MPI_Bcast(&totalRects, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (totalRects == 0) {
        // Nothing to be done. Return -1.
        return -1;
    }
    // Compute number of rectangles each process some sum.
    const int myNumRects   = totalRects / numProcs;
    const double rectWidth = 1.0 / totalRects;
    double myPI    = getArea(myNumRects, myRank, rectWidth);
    // Send my area result back to process with rank 0 while adding
    // all the results from various processes.
    double pi = 0;
    MPI_Reduce(&myPI, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    return pi;
}

int main(int argc, char *argv[]) {
    int totalRects = -1, myRank = -1, numProcs = -1;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

    do {
        if (myRank == 0) {
            std::cout << "Enter the number of intervals (0 to quit): ";
            std::cin  >> totalRects;
        }
        const double pi = integrate(totalRects, myRank, numProcs);
        if ((totalRects > 0) && (myRank == 0)) {
            std::cout << "pi is approximately " << pi << ", Error is: "
                      << std::abs(pi - M_PI) << std::endl;
        }
    } while (totalRects > 0);
    // Done with the program
    return MPI_Finalize();
}

// End of source code
