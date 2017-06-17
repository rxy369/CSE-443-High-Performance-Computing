/** 
    An MPI program to compute factors of a number using 2 MPI processes:

    Rank 0: Operates as manager (performs I/O) 
    Rank 1: Operates as worker  (computes number of factors)

    Copyright (C) 2015 raodm@miamiOH.edu edited: Mike Sosan
*/

#include <mpi.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const int NUMBER_TAG  = 1;
const int FACTORS_TAG = 2;

const int MANAGER_RANK = 0;
const int WORKER_RANK  = 1;

// Prototype to keep compiler happy
int getFactorCount(const long long n);

void doWorkerTasks() {
    long long nums[2];
    int factors[2];
    do {
        /* read number from the manager (rank == 0) */
        MPI_Recv(&nums, 2, MPI_LONG_LONG_INT, MANAGER_RANK, NUMBER_TAG,
                 MPI_COMM_WORLD, NULL);
        if (nums[0] != -1 && nums[1] != -1) {
            factors[0] = (getFactorCount(nums[0]));
            factors[1] = (getFactorCount(nums[1]));
            /* send number of factors back to the manager */
            MPI_Send(&factors, 2, MPI_INT, MANAGER_RANK, FACTORS_TAG,
                     MPI_COMM_WORLD);
        }
    } while ((nums[0] != -1) && (nums[1] != -1));
}

void doManagerTasks(const std::string& path) {
    std::ifstream data(path);
    if (!data.good()) {
        std::cout << "Unable to open numbers.txt for input. "
                  << "Manager aborting.\n";
    } else {
        long long nums[2];
        while ((data >> nums[0] >> nums[1])) {
            int factors[2];
            // Send number to be converted to the worker
            MPI_Send(&nums, 2, MPI_LONG_LONG_INT, WORKER_RANK, NUMBER_TAG,
                     MPI_COMM_WORLD);
            MPI_Recv(&factors, 2, MPI_INT, WORKER_RANK, FACTORS_TAG,
                     MPI_COMM_WORLD, NULL);
            // Print results
            std::cout << "Number " << nums[0] << 
                    " has " << factors[0] << " factors" <<
                    " and Number " << nums[1] << 
                    " has " << factors[1] << " factors.\n";
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
