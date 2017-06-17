// Copyright (C) 2017 raodm@miamiOH.edu

#include <iostream>
#include <string>

/* The following #define compiler directive is used to define a named
   constant to replace magic numbers (like 1000000) in the source code
   with more meaningful terms.  This named constant is used in the
   main() function to determine the number of times an experimental
   code fragement is invoked.  The experiment is repeated a large
   number of times so that the overall runtime is at an acceptable (in
   10s of seconds) value so that the timing measurement is more
   reliable and less noisy.
*/
const int REPETITIONS = 500000000;

/* 
   This program was developed to explore the effect of manually
   unrolling a loop.  Loop unrolling is a standard programming
   technique that is used to minimize the number of control hazards
   (that arise due to branching in loops) in looping constructs by
   simply repeating the body of the loop several times. as shown in the
   example below:

   for (int i = 0; (i < 1000); i++) {
       // Body doing some operation with i
   }

   unrolled loop:

   for (int i = 0; (i < 1000); i += 5) {
       // Body doing some operation with i
       // Body doing some operation with i + 1
       // Body doing some operation with i + 2
       // Body doing some operation with i + 3
       // Body doing some operation with i + 4
   }

   This program includes two functions namely standard and unroll.  The
   standard method contains the default set of nested for-loops to
   perform the matrix operation. unrolled contains the unrolled for
   loop.  The main() function must be modified to call one of these two
   functions in order to compare their effectiveness.

   Both standard and unrolled methods perform exactly the same
   operation.  The functions perform a standard 3-D transformation
   (specified in matrix m) to a given point (v on the x, y, and z
   planes) resulting in a new point (r) via the following matrix
   multiplication operation

   r = v * m;

   where

   \param[in] m Is a 4x4 matrix that is setup to do a graphics
   operation (such as: translation, rotation, scale, etc.)

   \param[in] v The a 1x4 array containing the x, y, and z value for
   a given point.

   \param[out] r A 1x4 array that will contain the result of applying
   the transformation (m) to the specified point (v).
*/


/* This is the standard version of the function that multiplies vector
   V by a 4x4 tranform matrix m 
*/
void standard(const int m[][4], const int v[], int r[]) {
    int i, j;
    for (i = 0; i < 4; i++) {
        r[i] = 0;
        for (j = 0; j < 4; j++) {
            r[i] += m[j][i] * v[j];
        }
    }
}

/* This is the completely unrolled version of the function that
   multiplies vector v by a 4x4 tranform matrix m */
void unrolled(const int m[][4], const int v[], int r[]) {
    r[0] = m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2] + m[3][0] * v[3];
    r[1] = m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2] + m[3][1] * v[3];
    r[2] = m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2] + m[3][2] * v[3];
    r[3] = m[0][3] * v[0] + m[1][3] * v[1] + m[2][3] * v[2] + m[3][3] * v[3];
}

int main(int argc, char *argv[]) {
    const int m[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, 
                         {0, 0, 0, 0}};
    int r[4];
    long result = 0;
  
    if ((argc > 1) && (argv[1] == std::string("unrolled"))) {
        for (int count = 0; (count < REPETITIONS); count++) {
            int v[4] = {count, count, count, 0};
            unrolled(m, v, r);
            result += v[count & 3];
        }
        std::cout << "unrolled() method result = " << result << std::endl;
    } else {
        for (int count = 0; (count < REPETITIONS); count++) {
            int v[4] = {count, count, count, 0};
            standard(m, v, r);
            result += v[count & 3];
        }
        std::cout << "Standard() method result = " << result << std::endl;
    }
    return 0;
}

// End of source code
