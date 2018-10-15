/*
 * f0700.c
 *
 *  Created on: Oct 13, 2018
 *      Author: sergio
 */

#include "f0700.h"

#include <stdio.h>
#include <stdlib.h>


#ifdef USE_ORIGINAL

signed int /*__cdecl */ f0700(int a1, int *a2, int a3, int *a4)
{
   // Pre-Condition:
   //    a1: possible input value = [64, 128, 256]
   //    a2: is an int[1408] array
   //        possible input value for each element = [-4095 ... 4095]
   //    a3: possible input value = [2, 3, 4, 5, 6]
   //    a4: is an int[116] array
   //        possible input value for each element = [0]
   //
   // Post-Condition:
   //    a1: value shouldn't change
   //    a2: value shouldn't change
   //    a3: value shouldn't changed
   //    a4: value can changed


  int *v4;
  int v5;
  int v6;
  int v7;
  int o1;
  int v9;
  int *v10;
  int v11;
  int v12;
  int v13;
  int v14;
  int v15;
  int a2a;

   v4 = a2;
   v5 = a1;
   v6 = 0;
   v7 = a2[a1];
   v14 = a2[a1 - 1];
   o1 = 0;
   v9 = -1;
   a2[a1 - 1] = 10000;
   v15 = v7;
   a2[a1] = -10000;
   a2a = 0;

   if (a1 > 0)
   {
      v10 = a4;
      do
      {
         v11 = (int)&v4[v6++];
         *v10 = v11;
         v12 = (int)&v4[v6];
         if (v9 * (*(int *)v11 - *(int *)v12) < a3)
         {
            do
            {
               if (v9 * *(int *)v12 > v9 * *(int *)*v10)
                  *v10 = v12;
               v13 = *(int *)(v12 + sizeof(int));
               v12 += sizeof(int);
               ++v6;
            } while (v9 * (*(int_64_type *)*v10 - v13) < a3);
            v5 = a1;
         }
         ++v10;
         v9 = -v9;
         o1 = a2a++ + 1;
      } while (v6 < v5);
   }
   if (o1 % 2)
      --o1;
   v4[v5 - 1] = v14;
   v4[v5] = v15;
   return o1;
}

result = f0700(a1, a2, a3, a4);
#else

signed int /*__cdecl */ f0700_refactor(const int max_count, int * const data, const int max_value, int* storage)
{
  // Pre-Condition:
  //    max_count: possible input value = [64, 128, 256]
  //    data: is an int[1408] array
  //        possible input value for each element = [-4095 ... 4095]
  //    max_value: possible input value = [2, 3, 4, 5, 6]
  //    storage: is an int[116] array
  //        possible input value for each element = [0]
  //
  // Post-Condition:
  //    max_count: value shouldn't change
  //    data: value shouldn't change
  //    max_value: value shouldn't changed
  //    storage: value can changed
  //
  // Purpose:
  //    Takes an array with data and arrange the data in a way that:
  //    1. Values with odd number indices in the array are greater than
  //    the previous element and the next element at least by max_value.
  //    2. Values with even number indices in the array are smaller than
  //    the previous element and the next element at least by max_value.
  //    3. The memory address of elements arranged in this configuration
  //    are stored in the pointer to array called storage.
  //    4. The return value is max_count minus the times the algorithm is looking
  //    for a value that meet the criteria (greater or smaller depends on the index
  //    odd or even) in the inner loop.

  // variable declaration
  int counter;
  int toogle_sign;
  int current;  // using this variable to make the code more readable. No need to dereference storage
  int next;
  int last_minus_one;
  int last;
  int result;

  // validate pointers
  if(data == NULL || storage == NULL)
  {
    printf("Invalid data\n");
    return -1;
  }

  // variable definition
  counter = 0;
  result = 0;
  toogle_sign = -1;

  // keep values corresponding to data for max_count and max_count-1
  last = data[max_count];
  last_minus_one = data[max_count - 1];

  // set the data values corresponding to max_count and max_count -1 to special values
  // to force exit when reach max_count and avoid to go further the length of the
  // storage array. The inner loop on some conditions increment counter but the only the outer loop
  // perform a check for a value less than max_count.
  data[max_count - 1] = 10000;
  data[max_count] = -10000;

  // loop until counter reaches max count
  while (counter < max_count)
  {
    *storage = (int)&data[counter]; // pointer contains data element address
    current = data[counter++]; // update current
    next = data[counter];      // update next

    // loop until we find a value that is greater or less (depends of the index odd or even) than the
    // next element by at least max value.
    while (toogle_sign * (current - next) < max_value)
    {
      if (toogle_sign * next > toogle_sign * current)
      {
        current = next; // replace current value with next
        *storage = (int)&data[counter]; // replace value in the array. The pointer keeps updating the
      }                                 // same element until condition is meet
      next = data[++counter]; // advance next value
    }
    toogle_sign = -toogle_sign; // switch sign for the next index
    ++result; // increment result
    ++storage; // move pointer to next location
  }

  if (result % 2)
    --result;

  // restore original values
  data[max_count - 1] = last_minus_one;
  data[max_count] = last;

  return result;
}

#endif
