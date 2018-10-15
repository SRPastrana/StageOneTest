# StageOneTest
C project for the stage one test for MobHealth Inc.

Note: This project was done using gcc on linux using eclipse. I don't have a Windows machine.

1. Refactor code - done look at f0700.c function name: 
signed int /*__cdecl */ f0700_refactor(const int max_count, int * const data, const int max_value, int* storage);

2. What strategy would you use to verify that your code is correct?
  A data baseline was generated using random numbers for a2. The data was written to a file to be use by the
  original algorithm (f0700.c) and by f0700_refactor.c.

3. Explain what the code is trying to accomplish intuitively
   The algorithm takes an array with data (a2) and arrange the data in a way that:
   1. Values with odd number indices in the array are greater than
      the previous element and the next element at least by max_value (a3).
   2. Values with even number indices in the array are smaller than
      the previous element and the next element at least by max_value (a3).
   3. The memory address of elements arranged in this configuration
      are stored in the pointer to array called storage (a4).
   4. The return value is max_count (a1) minus the times the algorithm is looking
      for a value that meet the criteria (greater or smaller depends on the index
      odd or even) in the inner loop. 
      
 More detail information is in the file f0700.c     
      
