/*
 * epsilon.c
 *
 * Epsilon indicator, both additive and multiplicative versions, based on the
 * original implementation by Eckart Zitzler.
 *
 * Reference:
 * [E. Zitzler, E. Thiele, L. Laummanns, M., Fonseca, C., and Grunert da Fonseca.
 * Performance Assesment of Multiobjective Optimizers: An Analysis and Review. 2003]
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

#include <stdlib.h>
#include <stdio.h>
#include <float.h>

#include "epsilon.h"

double epsilon(double **A, int Alen, double **B, int Blen, int vlen, epsilon_t method)
{
	size_t i, j, k;
    double  eps, eps_j = 0.0, eps_k=0.0, eps_temp;

    if (method == 0)
	  eps = DBL_MIN;
	else
	  eps= 0;

	for (i = 0; i < Alen; i++)
	{
		for (j = 0; j < Blen; j++)
		{
			for (k = 0; k < vlen; k++)
			{
				switch (method)
				{
					case additive_e:
						eps_temp = B[j][k] - A[i][k];
						break;
					case multiplicative_e:
						if ( (A[i][k] < 0 && B[j][k] > 0) ||
								(A[i][k] > 0 && B[j][k] < 0) ||
								(A[i][k] == 0 || B[j][k] == 0) )
						{
							perror("MOOUtils: Error in data.");
							exit(EXIT_FAILURE);
						}
						eps_temp = B[j][k] / A[i][k];
						break;
					default:
						perror("MOOUtils: Invalid option.");
						exit(EXIT_FAILURE);
				}
				if (k == 0)
					eps_k = eps_temp;
				else if (eps_k < eps_temp)
					eps_k = eps_temp;
			}
	        if (j == 0)
	          eps_j = eps_k;
	        else if (eps_j > eps_k)
	          eps_j = eps_k;
		}
		if (i == 0)
			eps = eps_j;
		else if (eps < eps_j)
		eps = eps_j;
	}
	return eps;
}

double additive_epsilon(double **A, int Alen, double **B, int Blen, int vlen)
{
	return epsilon(A, Alen, B, Blen, vlen, additive_e);
}

double multiplicative_epsilon(double **A, int Alen, double **B, int Blen, int vlen)
{
	return epsilon(A, Alen, B, Blen, vlen, multiplicative_e);
}
