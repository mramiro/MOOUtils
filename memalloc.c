/*
 * memalloc.c
 *
 *  Created on: 24/09/2012
 *      Author: Miguel A. Ramiro <mike.longbow@gmail.com>
 */

#include <stdlib.h>
#include <stdio.h>
#include "memalloc.h"

int *new_vector_int(size_t size)
{
	int * pRet = (int*)calloc(size, sizeof(int));
	if (!pRet)
	{
		perror("Out of memory when initializing int vector\n");
		exit(EXIT_FAILURE);
	}
	return pRet;
}

float *new_vector_float(size_t size)
{
	float * pRet = (float*)calloc(size, sizeof(float));
	if (!pRet)
	{
		perror("Out of memory when initializing float vector\n");
		exit(EXIT_FAILURE);
	}
	return pRet;
}

double *new_vector_double(size_t size)
{
	double * pRet = (double*)calloc(size, sizeof(double));
	if (!pRet)
	{
		perror("Out of memory when initializing double vector\n");
		exit(EXIT_FAILURE);
	}
	return pRet;
}

int **new_matrix_int(size_t size_y, size_t size_x)
{
	size_t i;
	int **retP;

	retP = (int**)calloc(size_y, sizeof(int*));
	if (!retP)
	{
		perror("Out of memory when initializing int matrix.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		for (i = 0; i < size_y; i++)
		{
			retP[i] = new_vector_int(size_x);
		}
	}

	return retP;
}

float **new_matrix_float(size_t size_y, size_t size_x)
{
	size_t i;
	float **retP;

	retP = (float**)calloc(size_y, sizeof(float*));
	if (!retP)
	{
		perror("Out of memory when initializing float matrix.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		for (i = 0; i < size_y; i++)
		{
			retP[i] = new_vector_float(size_x);
		}
	}

	return retP;
}

double **new_matrix_double(size_t size_y, size_t size_x)
{
	size_t i;
	double **retP;

	retP = (double**)calloc(size_y, sizeof(double*));
	if (!retP)
	{
		perror("Out of memory when initializing double matrix.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		for (i = 0; i < size_y; i++)
		{
			retP[i] = new_vector_double(size_x);
		}
	}

	return retP;
}

void free_matrix(void **ptr, size_t size_y)
{
	size_t i;
	for (i = 0; i < size_y; i++)
	{
		free(ptr[i]);
	}
	free(ptr);
}

void free_vector(void *ptr)
{
	free(ptr);
}
