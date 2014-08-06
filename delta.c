/*
 * delta.c
 *
 * Spread (delta) and Generalized Spread (I_GS) indicator calculation.
 *
 * Reference:
 * [Kalyanmoy Deb. A fast and elitist multiobjective genetic algorithm: NSGA-II. 2002]
 * [Zhou et al. Combining Model-based and Genetics-based Offspring Generation for
 * Multi-objective Optimization Using a Convergence Criterion. 2006]
 *
 *  Created on: 11/06/2013
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
#include <float.h>
#include <math.h>

#include "memalloc.h"
#include "moutils.h"
#include "delta.h"

double spread(double **front, int frontlen,
		double **truefront, int truefrontlen)
{
	size_t i;
	int vlen = 2;
	double df, dl, dbar, diversity, res;
	double *min_values, *max_values;
	double **norm_front, **norm_truefront;

	// Normalize fronts
	min_values = get_min_values(truefront, truefrontlen, vlen);
	max_values = get_max_values(truefront, truefrontlen, vlen);

	norm_front = normalize_front(front, frontlen, vlen,
			min_values, max_values);
	norm_truefront = normalize_front(truefront, truefrontlen, vlen,
			min_values, max_values);

	// Lexicographically sort fronts
	qsort(norm_front, frontlen, sizeof(norm_front[0]), &lexicographical_compare);
	qsort(norm_truefront, truefrontlen, sizeof(norm_truefront[0]), &lexicographical_compare);
	// Obtain the extreme distances
	df = eucdist(norm_front[0], norm_truefront[0], vlen);
	dl = eucdist(norm_front[frontlen-1], norm_truefront[truefrontlen-1], vlen);

	/* Perform calculations.
	 * First, the mean distance of all the euclidian distances between consecutive vectors
	 * in the reference set is calculated. */
	dbar = 0;
	for (i = 0; i < (frontlen-1); i++)
	{
		dbar += eucdist(norm_front[i], norm_front[i+1], vlen);
	}
	dbar = dbar / (frontlen-1);

	if (frontlen > 1)
	{
		/* The absolute differences between each vector in the reference set and the
		 * mean distance are accumulated and added to the extreme distances. */
		diversity = df + dl;
		for (i = 0; i < (frontlen-1); i++)
		{
			diversity += fabs(eucdist(norm_front[i], norm_front[i+1], vlen) - dbar);
		}
		/* The denominator of the final division represents the ideal distribution
		 * of all distances. */
		res = diversity / (df + dl + (frontlen-1)*dbar);
	}
	else
	{
		res = 1;
	}

	// Free used arrays
	free_matrix((void**)norm_front, frontlen);
	free_matrix((void**)norm_truefront, truefrontlen);
	free_vector(min_values);
	free_vector(max_values);

	return (res);
}

double generalized_spread(double **front, int frontlen, double **truefront, int truefrontlen, int nobj)
{
	size_t i;
	double sum, sum_extremis, dbar, res;
	double *min_values, *max_values;
	double **extreme_sols, **norm_front, **norm_truefront;

	min_values = get_min_values(truefront, truefrontlen, nobj);
	max_values = get_max_values(truefront, truefrontlen, nobj);

	norm_front = normalize_front(front, frontlen, nobj,
			min_values, max_values);
	norm_truefront = normalize_front(truefront, truefrontlen, nobj,
			min_values, max_values);

	extreme_sols = get_extreme_sols(norm_truefront, truefrontlen, nobj);

	dbar = 0;
	for (i = 0; i < frontlen; i++)
	{
		dbar += sqrt(dist_nearest_point(norm_front[i], nobj, norm_front, frontlen));
	}
	dbar = dbar / frontlen;

	sum_extremis = 0;
	for (i = 0; i < nobj; i++)
	{
		sum_extremis += sqrt(dist_closed_point(extreme_sols[i],
				nobj, norm_front, frontlen));
	}

	sum = 0;
//	for (i = 0; i < truefrontlen; i ++)
	for (i = 0; i < frontlen; i ++)
	{
		sum += fabs(sqrt(dist_nearest_point(norm_front[i], nobj,
				norm_front, frontlen)) - dbar);
//		sum += sqrt(dist_nearest_point(norm_front[i], nobj,
//						norm_front, frontlen)) - dbar;
	}

	res = (sum + sum_extremis)/(sum_extremis + frontlen*dbar);

	free_matrix((void**)norm_front, frontlen);
	free_matrix((void**)norm_truefront, truefrontlen);
	free_matrix((void**)extreme_sols, nobj);
	free_vector(min_values);
	free_vector(max_values);
	return (res);
}

double generalized_spread_original(double **front, int frontlen, double **truefront, int truefrontlen, int nobj)
{
	size_t i;
	double sum, sum_extremis, dbar, res;
	double *min_values, *max_values;
	double **extreme_sols, **norm_front, **norm_truefront;

	min_values = get_min_values(truefront, truefrontlen, nobj);
	max_values = get_max_values(truefront, truefrontlen, nobj);

	norm_front = normalize_front(front, frontlen, nobj,
			min_values, max_values);
	norm_truefront = normalize_front(truefront, truefrontlen, nobj,
			min_values, max_values);

	extreme_sols = get_extreme_sols(norm_truefront, truefrontlen, nobj);

	dbar = 0;
	for (i = 0; i < truefrontlen; i++)
	{
		dbar += dist_nearest_point(norm_truefront[i], nobj, norm_front, frontlen);
	}
	dbar = dbar / truefrontlen;

	sum_extremis = 0;
	for (i = 0; i < nobj; i++)
	{
		sum_extremis += dist_nearest_point(extreme_sols[i],
				nobj, norm_front, frontlen);
	}

	sum = 0;
	for (i = 0; i < truefrontlen; i ++)
//	for (i = 0; i < frontlen; i ++)
	{
		sum += fabs(dist_nearest_point(norm_truefront[i], nobj,
				norm_front, frontlen) - dbar);
//		sum += sqrt(dist_nearest_point(norm_front[i], nobj,
//						norm_front, frontlen)) - dbar;
	}

	res = (sum + sum_extremis)/(sum_extremis + truefrontlen*dbar);

	free_matrix((void**)norm_front, frontlen);
	free_matrix((void**)norm_truefront, truefrontlen);
	free_matrix((void**)extreme_sols, nobj);
	free_vector(min_values);
	free_vector(max_values);
	return (res);
}
