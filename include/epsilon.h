/*
 * epsilon.h
 *
 *  Created on: 10/09/2013
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

#ifndef EPSILON_H_
#define EPSILON_H_

typedef enum
{
	additive_e,
	multiplicative_e
}epsilon_t;

/* Calculates the epsilon binary indicator from two sets of non-dominated vectors
 *
 * ARGS: set A, set A length, set B, set B length, vectors length (number of objectives),
 *       method: multiplicative or additive (see enum declaration on top)
 * RTRN: the value of the calculated epsilon indicator  */
double epsilon(double **A, int Alen, double **B, int Blen, int vlen, epsilon_t method);

double additive_epsilon(double **A, int Alen, double **B, int Blen, int vlen);

double multiplicative_epsilon(double **A, int Alen, double **B, int Blen, int vlen);

#endif /* EPSILON_H_ */
