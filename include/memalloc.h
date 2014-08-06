/*
 * memalloc.h
 *
 * Small (and somewhat raw) wrapper for memory management functions
 *
 *  Created on: 14/09/2012
 *      Author: Miguel A. Ramiro <mike.longbow@gmail.com>
 */

#ifndef MEMALLOC_H_
#define MEMALLOC_H_

int *new_vector_int(size_t size);

float *new_vector_float(size_t size);

double *new_vector_double(size_t size);

int **new_matrix_int(size_t size_y, size_t size_x);

float **new_matrix_float(size_t size_y, size_t size_x);

double **new_matrix_double(size_t size_y, size_t size_x);

void free_matrix(void **ptr, size_t size_y);

void free_vector(void *ptr);

#endif /* MEM_ALLOC_H_ */
