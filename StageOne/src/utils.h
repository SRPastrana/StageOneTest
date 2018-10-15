/*
 * utils.h
 *
 *  Created on: Oct 13, 2018
 *      Author: sergio
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <stdlib.h>

int WriteBinaryData(const char* file_name, int* dataptr, size_t size);
int ReadBinaryData(const char* file_name, int* dataptr, size_t size);

#endif /* UTILS_H_ */
