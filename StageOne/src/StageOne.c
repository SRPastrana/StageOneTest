/*
 ============================================================================
 Name        : StageOne.c
 Author      : SergioR
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "f0700.h"
#include "utils.h"

// Set this switch to see the performance of the original algorithm
//
// #define USE_ORIGINAL

// constant values for array's sizes and values
#define ARRAY_A2_SIZE 1408
#define ARRAY_A2_VALUE 4095
#define ARRAY_A4_SIZE 116

// store data in file to have a baseline
const char* a2_data = "/home/sergio/Test/a2.bin";

/* Purpose: Initialize data for the first time and stored in a file
 * for later use to have a baseline to compare results
 *
 * param a1 - pointer to an integer correspond to the max count
 * param a2 - pointer to an array of integers to store the data
 * param a3 - pointer to an integer correspond to the max value to compare
 * param a4 - pointer to an array of integers to initialized to zeros
 *
 * return operation status, 0 = sucess, negative number = failure
 */
int Initialize(int* a1, int* a2, int* a3, int* a4 )
{
  int index;
  int r;
  int flip;
  int write_a2;
  int read_a2;

  if(a1 == NULL || a2 == NULL || a3 == NULL || a4 == NULL)
  {
    printf("Invalid data to initialize\n");
    return -1;
  }

  // initialize max count (a1) and max value (a3)
  *a1 = 64;
  *a3 = 2;

  // a4 is initialized with zeros
  for(index = 0; index < ARRAY_A4_SIZE; ++index)
  {
    a4[index] = 0;
  }

  // read data from file
  read_a2 = ReadBinaryData(a2_data, a2, ARRAY_A2_SIZE);

  if(read_a2 == 0 )
  {
    printf("Read binary files status ok\n");
    return 0;
  }

  // There is no data file. Generate random numbers for a2
  //

  srand(time(0));

  for(index = 0; index < ARRAY_A2_SIZE; ++index)
  {
    r = rand() % (ARRAY_A2_VALUE+1);
    flip = (( rand() % (ARRAY_A2_VALUE+1)) > 3*ARRAY_A2_SIZE/2);
    if(flip > 0)
    {
      r *= -1;
    }

    a2[index] = r;
  }

  // Write data to disk for the next time
  write_a2 = WriteBinaryData(a2_data, a2, ARRAY_A2_SIZE);

  if(write_a2 == 0 )
  {
    printf("Write file status ok\n");
    return 0;
  }

  return -1;
}

int main(void)
{
  puts("Stage 1 Test");

  // variable declaration
  int a1;
  int a2[ARRAY_A2_SIZE];
  int a3;
  int a4[ARRAY_A4_SIZE];
  int result;
  int i;

  // Fill variables with data
  Initialize(&a1, a2, &a3, a4);

  // call f0700 refactor
#ifdef USE_ORIGINAL
  result = f0700(a1, a2, a3, a4);
#else
  result = f0700_refactor(a1, a2, a3, a4);
#endif

  if(result == -1)
  {
    return EXIT_FAILURE;
  }

  // display results - f0700_refactor store the results in a4 (memory address), the original data
  // a2 is also show for reference. a4 only contain address up to [results - 1]
  // The algorithm configure a2 data in a4 in the following way
  // if the index is odd the value is greater than the previous value and the next value
  // at least by max value (a3).
  // if the index is even the value is smaller than the previous value and the next value
  // at least by max value (a3).
  for(i = 0; i < result; ++i)
  {
    int x = *(int*)(a4[i]);
    printf("a4[%d] = %d \t a2[%d] = %d\n", i,x,i,a2[i]);
  }

  printf("result = %d\n", result);


  return EXIT_SUCCESS;
}
