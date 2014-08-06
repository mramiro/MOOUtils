/*
 * moutils.h
 *
 * Multiobjective optimization utilities and common functions used by the library
 *
 *  Created on: 27/06/2013
 *      Author: Miguel A. Ramiro <mike.longbow@gmail.com>
 *
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

#ifndef MOUTILS_H_
#define MOUTILS_H_


/* Filters out duplicate vectors from a set. newset must be freed upon use.
 *
 * ARGS: set of vectors, set length, vectors length, pointer to output array
 * RTRN: length of output array (newset) */
int remove_duplicates(double **set, int setlen, int vlen, double ***newset);


/* Determines if vector a dominates vector b (minimization of objectives)
 *
 * ARGS: vector a, vector b, number of objectives (length of vectors)
 * RTRN: 1 if a dominates b, 0 otherwise */
int dominates(double *a, double *b, int vlen);


/* Check if two equal-sized vectors are equal
 *
 * ARGS: vector a, vector b, length of vectors
 * RTRN: 1 if equal, 0 otherwise*/
int vectors_are_equal(double *A, double *B, int vlen);


/* Compares two vectors according to Pareto dominance (minimization of objectives)
 *
 * ARGS: vector a, vector b, number of objectives (length of vectors)
 * RTRN: -1 if a dominates b, 1 if b dominates a, 0 otherwise*/
int domination_cmp(double *a, double *b, int vlen);


/* Filter a set of vectors according to Pareto dominance (minimization of objectives)
 * Effectively sorts the set, placing any non-dominted vector first, and any non-dominated
 * vector last in the array. Returns the number of non-dominated vectors found.
 *
 * ARGS: set of vectors, set length, number of objectives (vector length)
 * RTRN: number of non-dominated vectors found, e.g. the index of the first dominated vector in set */
int pareto_filter(double **set, int setlen, int vlen);


/* Returns the euclidian distance between two vectors
 *
 * ARGS: vector a, vector b, vectors length
 * RTRN: the euclidian distance between a and b */
double eucdist(double *A, double *B, int vlen);


/* Returns the squared distance between two vectors
 *
 * ARGS: vector a, vector b, vectors length
 * RTRN: the squared euclidian distance between a and b */
double squared_dist(double *A, double *B, int vlen);


/* Returns the squared distance between a vector and the nearest vector to it in
 * a given set of non-dominated vectors
 *
 * ARGS: vector a, vector b, vectors length
 * RTRN: the squared distance between X and the nearest point in the front */
double dist_closed_point(double *X, int vlen, double **front, int frontlen);


/* Returns the squared distance between a vector and the nearest vector to it in
 * a given set of non-dominated vectors, only if the vectors are not equal
 *
 * ARGS: vector X, vector length, set of vectors, set length
 * RTRN: the squared distance between X and the nearest point in the front */
double dist_nearest_point(double *X, int vlen, double **front, int frontlen);


/**** NOTE *************************************************************************
 *  The following functions are used internally by the library and though it's
 *  perfectly possible to use them independently, I recommend against doing so.
 *  This is mosty because of memory management issues, since (given my laziness to
 *  come up with a better solution) most of them make use of the system's heap, and
 *  memory must be freed upon using any of them, to avoid any problem in the long
 *  run. If you're ok with this, by all means go ahead :)
 *  -M. Ramiro
 ***********************************************************************************/

/* Get the minimum values for each vector component of a given set of non-dominated
 * vectors. The memory used by the returned array must be freed upon use.
 *
 * ARGS: set of vectors, set length, vector length
 * RTRN: an array of size vlen with the minumum values for each vector component */
double *get_min_values(double **front, int frontlen, int vlen);


/* Get the maximum values for each vector component of a given set of non-dominated
 * vectors. The memory used by the returned array must be freed upon use.
 *
 * ARGS: set of vectors, set length, vector length
 * RTRN: an array of size vlen with the maximum values for each vector component */
double *get_max_values(double **front, int frontlen, int vlen);


/* Normalize a set of vectors using the minimum and maximum values for each vector
 * component. The memory used by the returned array must be freed upon use.
 *
 * ARGS: set of vectors, set length, vector length, vlen-sized array with minimum values,
 *       vlen-sized array with maximum values
 * RTRN: a matrix with the normalized front */
double **normalize_front(double **front, int frontlen, int vlen,
		double *min_values, double *max_values);


/* Get the extreme solutions from a given front.
 * The memory used by the returned array must be freed upon use.
 *
 * ARGS: set of vectors, set length, vector length, vector length
 * RTRN: a matrix (of vlen x vlen size) with the extreme vectors */
double **get_extreme_sols(double **front, int frontlen, int vlen);


/* Lexicographical comparision operator for two-dimensional vectors,
 * meant to be used by stdlib's qsort
 *
 * ARGS: pointer to vector a, pointer to vector b
 * RTRN: -1 if a < b, 1 if b > a, 0 otherwise */
int lexicographical_compare(const void *_a, const void *_b);

#endif /* COMMON_H_ */
