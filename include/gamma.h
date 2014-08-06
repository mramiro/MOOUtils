/*
 * gamma.h
 *
 *  Created on: 19/08/2013
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

#ifndef GAMMA_H_
#define GAMMA_H_

/* Calculates the generational distance indicator for a set of non-dominated vectors
 *
 * ARGS: set of non-dominated vectors, set length, true pareto front, true front length,
 *       vector length (number of objectives).
 * RTRN: the value of the calculated generational distance indicator  */
double generational_distance(double **front, int frontlen,
		double **truefront, int truefrontlen, int vlen);

/* Calculates the inverted generational distance indicator for a set of non-dominated vectors
 *
 * ARGS: set of non-dominated vectors, set length, true pareto front, true front length,
 *       vector length (number of objectives).
 * RTRN: the value of the inverted generational distance indicator  */
double inverted_generational_distance(double **front, int frontlen,
		double **truefront, int truefrontlen, int vlen);

#endif /* GAMMA_H_ */
