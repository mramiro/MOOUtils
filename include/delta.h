/*
 * delta.h
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

#ifndef DELTA_H_
#define DELTA_H_

/* Calculates Deb's spread indicator from a set of non-dominated two-dimensional vectors
 *
 * ARGS: set of non-dominated vectors, set length, true pareto front, true front length
 * RTRN: the value of the calculated spread indicator  */
double spread(double **front, int frontlen,
		double **truefront, int truefrontlen);


/*** IMPORTANT NOTICE ****************************************************************
 * I include two diferent implementations of the Generalized Spread indicator.The
 * first one is mostly a porting to C of the algorithm implemented in Nebro and
 * Durillo's jMetal framework. This method is the same one that's used in Trautman,
 * Steuer and Mersmann's mco library for R. So I assume it's correct.
 * However, the definition of the indicator as presented in Zhou's original paper (1)
 * differs from said method. So I also include another implementation that, on my
 * personal opinion, is more faithfull to the original definition. Of course this
 * might be just a misunderstanding on my part, so take it with a grain of salt.
 * -M. Ramiro
 *
 * (1)[Zhou et al. Combining Model-based and Genetics-based Offspring Generation for
 * Multi-objective Optimization Using a Convergence Criterion. 2006]
 ************************************************************************************/

/* Calculates generalized spread indicator from a set of non-dominated vectors
 *
 * ARGS: set of non-dominated vectors, set length, true pareto front, true front length
 *       vectors length (number of objectives).
 * RTRN: the value of the generalized spread indicator  */
double generalized_spread(double **front, int frontlen,
		double **truefront, int truefrontlen, int vlen);


/* Calculates generalized spread indicator from a set of non-dominated vectors, as
 * described in Zhou's original paper.
 *
 * ARGS: set of non-dominated vectors, set length, true pareto front, true front length
 *       vectors length (number of objectives).
 * RTRN: the value of the generalized spread indicator  */
double generalized_spread_original(double **front, int frontlen,
		double **truefront, int truefrontlen, int vlen);


#endif /* DELTA_H_ */
