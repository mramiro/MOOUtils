/*
 * moutils.c
 *
 *  Created on: 27/06/2013
 *      Author: Miguel A. Ramiro <mike.longbow@gmail.com>
 *  Copyright (c) 2014 Miguel A. Ramiro
 *
 *  This file is part of MOOUtils.
 *
 *  MOOUtils is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  MOOUtils is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with MOOUtils.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <math.h>
#include <float.h>

#include "memalloc.h"
#include "moutils.h"

void swap_points(double **a, double **b)
{
	double *tmp = *a;
	*a = *b;
	*b = tmp;
}

int remove_duplicates(double **set, int setlen, int vlen, double ***newset)
{
	size_t i, j;
	int unique[setlen];

	for (i = 0; i < setlen; i++)
		unique[i] = 1;

	for (i = 0; i < (setlen-1); i++)
	{
		for (j = i; j < setlen; j++)
		{
			if ((i != j) && (unique[i] || unique[j]))
			{
				if (vectors_are_equal(set[i], set[j], vlen))
					unique[j] = 0;
			}
		}
	}

	int ctr = 0;
	for (i = 0; i < setlen; i++)
	{
		if (unique[i])
			ctr++;
	}
	(*newset) = new_matrix_double(ctr, vlen);
	ctr = 0;
	for (i = 0; i < setlen; i++)
	{
		if (unique[i])
		{
			for (j = 0; j < vlen; j++)
				(*newset)[ctr][j] = set[i][j];
			ctr++;
		}
	}
	return ctr;
}

int dominates(double *a, double *b, int vlen)
{
	int i, better_in_any;

	better_in_any = 0;
	for (i = 0; i < vlen && a[i] <= b[i]; i++)
		if (a[i] < b[i])
			better_in_any = 1;

	return ((i >= vlen) && better_in_any);
}

int domination_cmp(double *a, double *b, int vlen)
{
	if (dominates(a,b,vlen))
		return -1;
	else if (dominates(b,a,vlen))
		return 1;
	return 0;
}

int pareto_filter(double **set, int setlen, int vlen)
{
    int  i, j, n;

	n = setlen;
	i = 0;
	while (i < n)
	{
		j = i + 1;
		while (j < n)
		{
			if (dominates(set[i], set[j], vlen))
			{
				/* remove vector 'j' */
				n--;
				swap_points(&set[j], &set[n]);
			}
			else if (dominates(set[j], set[i], vlen))
			{
				/* remove vector 'i'; ensure that the vector copied to index 'i'
				 is considered in the next outer loop (thus, decrement i) */
				n--;
				swap_points(&set[j], &set[n]);
				i--;
				break;
			}
			else
				j++;
		}
		i++;
	}
	return n;
}

int vectors_are_equal(double *A, double *B, int vlen)
{
	int i;
	for (i = 0; i < vlen; i++)
	{
		if (A[i] != B[i])
			return 0;
	}
	return 1;
}

double eucdist(double *A, double *B, int vlen)
{
	return sqrt(squared_dist(A, B, vlen));
}

double squared_dist(double *A, double *B, int vlen)
{
	int i;
	double diff, sum;
	sum = 0;
	for (i = 0; i < vlen; i++)
	{
		diff = A[i] - B[i];
		sum += pow(diff, 2.0);
	}
	return sum;
}

double dist_closed_point(double *X, int vlen, double **front, int frontlen)
{
	int i;
	double dist, mindist;
	mindist = DBL_MAX;
	for (i = 0; i < frontlen; i++)
	{
		dist = squared_dist(X, front[i], vlen);
		if (dist < mindist)
			mindist = dist;
	}
	return mindist;
}

double dist_nearest_point(double *X, int vlen, double **front, int frontlen)
{
	int i;
	double dist, mindist;
	mindist = DBL_MAX;
	for (i = 0; i < frontlen; i++)
	{
		if (!vectors_are_equal(X, front[i], vlen))
		{
			dist = squared_dist(X, front[i], vlen);
			if (dist < mindist)
				mindist = dist;
		}
	}
	return mindist;

}

double *get_min_values(double **front, int frontlen, int vlen)
{
	size_t i, j;
	double *min_values = malloc(sizeof(double)*vlen);
	for (i = 0; i < vlen; i++)
		min_values[i] = DBL_MAX;
	for (i = 0; i < frontlen; i++)
	{
		for (j = 0; j < vlen; j++)
		{
			if (front[i][j] < min_values[j])
			{
				min_values[j] = front[i][j];
			}
		}
	}
	return min_values;
}

double *get_max_values(double **front, int frontlen, int vlen)
{
	size_t i, j;
	double *max_values = malloc(sizeof(double)*vlen);
	for (i = 0; i < vlen; i++)
		max_values[i] = 0;
	for (i = 0; i < frontlen; i++)
	{
		for (j = 0; j < vlen; j++)
		{
			if (front[i][j] > max_values[j])
			{
				max_values[j] = front[i][j];
			}
		}
	}
	return max_values;
}

double **normalize_front(double **front, int frontlen, int vlen,
		double *min_values, double *max_values)
{
	size_t i, j;
	double **normalized_front = new_matrix_double(frontlen, vlen);
	for (i = 0; i < frontlen; i++)
	{
		for (j = 0; j < vlen; j++)
		{
			normalized_front[i][j] = (front[i][j] - min_values[j]) /
					(max_values[j] - min_values[j]);
		}
	}
	return (normalized_front);
}

double **get_extreme_sols(double **front, int frontlen, int vlen)
{
	size_t i, j;
	double max_fit[vlen], cur_fit;
	double **extreme_sols = new_matrix_double(vlen, vlen);
	int positions[vlen];
	for (i = 0; i < vlen; i++)
	{
		max_fit[i] = 0;
	}
	for (i = 0; i < frontlen; i++)
	{
		for (j = 0; j < vlen; j++)
		{
			cur_fit = front[i][j];
			if (cur_fit > max_fit[j])
			{
				max_fit[j] = cur_fit;
				positions[j] = i;
			}
		}
	}
	for (i = 0; i < vlen; i++)
	{
		for (j = 0; j < vlen; j++)
		{
			extreme_sols[i][j] = front[positions[i]][j];
		}
	}
	return (extreme_sols);
}

//This ordering is only used in Spread, wich is exclusive for bi-objective problems
static int _vlen = 2;
int lexicographical_compare(const void *_a, const void *_b)
{
	const double *a = *(const double**)_a;
	const double *b = *(const double**)_b;

	int index = 0;
	while (index < _vlen && a[index] == b[index])
	{
		index++;
	}
	if (a[index] < b[index])
	{
		return -1;
	}
	if (a[index] > b[index])
	{
		return 1;
	}
	return 0;
}
