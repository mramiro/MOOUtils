/*
 * gamma.c
 *
 *  Generational Distance calculation.
 *
 *  Reference:
 *  [David A. Van Veldhuizen and Gary B. Lamont. Evolutionary
 *  computation and convergence to a Pareto front. 1998]
 *  [Kohkar et al. On the Performance of the Pareto Set Pursuing (PSP)
 *  Method for Mixed-Variable Multi-Objective Design Optimization. 2010]
 *
 *  Created on: 19/08/2013
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

#include "memalloc.h"
#include "moutils.h"

double generational_distance(double **front, int frontlen,
		double **truefront, int truefrontlen, int vlen)
{
	size_t i;
	double res, sum;
	double *min_values, *max_values;
	double **norm_front, **norm_truefront;

	// Normalize fronts
	min_values = get_min_values(truefront, truefrontlen, vlen);
	max_values = get_max_values(truefront, truefrontlen, vlen);
	norm_front = normalize_front(front, frontlen, vlen,
			min_values, max_values);
	norm_truefront = normalize_front(truefront, truefrontlen, vlen,
			min_values, max_values);

	/* Perform calculations. The generational distance accumulates the euclidian
	 * distances from every vector in the reference set to the nearest vector in
	 * the true Pareto front. Note that, according to all references, the distances
	 * aren't actually euclidian, but euclidian powered by 2, so we use simple
	 * squared distances here. */
	sum = 0;
	for (i = 0; i < frontlen; i++)
	{
		sum += dist_closed_point(norm_front[i], vlen, norm_truefront, truefrontlen);
	}
	res = (sqrt(sum))/frontlen;

	// Free used arrays
	free_matrix((void**)norm_front, frontlen);
	free_matrix((void**)norm_truefront, truefrontlen);
	free_vector(min_values);
	free_vector(max_values);

	return (res);
}

double inverted_generational_distance(double **front, int frontlen,
		double **truefront, int truefrontlen, int vlen)
{
	size_t i;
	double res, sum;
	double *min_values, *max_values;
	double **norm_front, **norm_truefront;

	// Normalize fronts
	min_values = get_min_values(truefront, truefrontlen, vlen);
	max_values = get_max_values(truefront, truefrontlen, vlen);
	norm_front = normalize_front(front, frontlen, vlen,
			min_values, max_values);
	norm_truefront = normalize_front(truefront, truefrontlen, vlen,
			min_values, max_values);

	/* Perform calculations. The inverted generational distance accumulates the
	 * euclidian distances from every vector in the true Pareto front to the nearest
	 * vector in the reference set. Note that, according to all references, the
	 * distances aren't actually euclidian, but euclidian powered by 2, so we use
	 * simple squared distances here. */
	sum = 0;
	for (i = 0; i < truefrontlen; i++)
	{
		sum += dist_closed_point(norm_truefront[i], vlen, norm_front, frontlen);
	}
	res = (sqrt(sum))/truefrontlen;

	// Free used arrays
	free_matrix((void**)norm_front, frontlen);
	free_matrix((void**)norm_truefront, truefrontlen);
	free_vector(min_values);
	free_vector(max_values);

	return (res);
}
