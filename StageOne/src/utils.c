/*
 * utils.c
 *
 *  Created on: Oct 13, 2018
 *      Author: sergio
 */

#include "utils.h"


/* Purpose: Write an array of integers to a file in binary format
 * param file_name - file name for the data
 * param dataptr - pointer to a array of integers
 * param size - data array size
 * return operation status. 0 success, negative number fail
 */
int WriteBinaryData(const char* file_name, int* dataptr, size_t size)
{
  if(file_name == NULL || dataptr == NULL || size <= 0)
  {
    return -1;
  }

  FILE* file_desc = fopen(file_name, "wb");
  if(file_desc == NULL)
  {
    return -1;
  }

  size_t result = fwrite(dataptr,sizeof(int),size,file_desc);

  result -= size;
  fclose(file_desc);

  return result;
}

/* Purpose: Read a binary file and put the file content in a array of integers
 * param file_name - file name for the data
 * param dataptr - pointer to a array of integers
 * param size - data array size
 * return operation status. 0 success, negative number fail
 */
int ReadBinaryData(const char* file_name, int* dataptr, size_t size)
{
  if(file_name == NULL || dataptr == NULL || size <= 0)
  {
    return -1;
  }

  FILE* file_desc = fopen(file_name, "rb");
  if(file_desc == NULL)
  {
    return -1;
  }

  size_t result = fread(dataptr,sizeof(int),size,file_desc);
  result -= size;
  fclose(file_desc);

  return result;
}
