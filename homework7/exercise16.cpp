/** 
    An MPI program to compute factors of a number using 2 MPI processes:

    Rank 0: Operates as manager (performs I/O) 
    Rank 1: Operates as worker  (computes number of factors)

    Copyright (C) 2015 raodm@miamiOH.edu
*/

#include <mpi.h>
#include <iostream>
#include <fstream>
#include <string>

const int NUMBER_TAG  = 1;
const int FACTORS_TAG = 2;

const int MANAGER_RANK = 0;
const int WORKER_RANK  = 1;

// Prototype to keep compiler happy
int getFactorCount(const long long n);

void doWorkerTasks() {
    long long number;
    do {
        /* read number from the manager (rank == 0) */
        MPI_Recv(&number, 1, MPI_LONG_LONG_INT, MANAGER_RANK, NUMBER_TAG,
                 MPI_COMM_WORLD, NULL);
        if (number != -1) {
            int factors = getFactorCount(number);
            /* send number of factors back to the manager */
            MPI_Send(&factors, 1, MPI_INT, MANAGER_RANK, FACTORS_TAG,
                     MPI_COMM_WORLD);
        }
    } while (number != -1);
}

void doManagerTasks(const std::string& path) {
    std::ifstream data(path);
    if (!data.good()) {
        std::cout << "Unable to open " << path << " for input. "
                  << "Manager aborting.\n";
    } else {
        while (!data.eof()) {
            long long number;
            int factors;
            data >> number;
            // Send number to be converted to the worker
            MPI_Send(&number, 1, MPI_LONG_LONG_INT, WORKER_RANK, NUMBER_TAG,
                     MPI_COMM_WORLD);
            MPI_Recv(&factors, 1, MPI_INT, WORKER_RANK, FACTORS_TAG,
                     MPI_COMM_WORLD, NULL);
            // Print results
            std::cout << "Number " << number << " has " << factors
                      << " factors.\n";
        }
    }
    // send -1 to worker to inform worker to end processing
    long long number = -1;
    MPI_Send(&number, 1, MPI_LONG_LONG_INT, WORKER_RANK, NUMBER_TAG,
             MPI_COMM_WORLD);
}

//------------------------------------------------------------------
//          DO   NOT  MODIFY  CODE  BELOW  THIS  LINE
//------------------------------------------------------------------

/**
   This is a simple function that can be used to determine the number
   of factors for a given integer i.
*/
int getFactorCount(const long long n) {
    long long i = 0;
    int factorCount = 0;

    for (i = 1; (i <= n); i++) {
        if (!(n % i)) {
            factorCount++;
        }
    }
    return factorCount;
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size < 2) {
        std::cerr << "This program must be run with at least 2 processes!\n";
    } else if (argc != 2) {
        std::cerr << "Specify name of file to process\n";
    } else {
        int rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        if (rank == 0) {
            doManagerTasks(argv[1]);
        } else {
            doWorkerTasks();
        }
    }

    MPI_Finalize();
    return 0;
}

// End of source code.
