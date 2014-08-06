/*
 * mooutils_example.c
 *
 *  Created on: 2/08/2014
 *      Author: Miguel A. Ramiro <mike.longbow@gmail.com>
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "memalloc.h"
#include "delta.h"
#include "gamma.h"
#include "epsilon.h"
#include "moutils.h"

int read_set(FILE *input, int setlen, int nobj, double ***pset);

int main (int argc, char *argv[])
{
	double **pset, **tfront, **filtered_set, gd, sp, gs, ep;
	size_t psetlen, tfrontlen, fsetlen, nobj;
	FILE *input;
	char chr;

	const char* pset_file = "example_data.txt";
	const char* tfront_file = "example_truefront.txt";

	// Read true Pareto front from file
	nobj = 1;
	tfrontlen = 0;
	input = fopen(tfront_file, "r");
	do{
		chr = fgetc(input);
		if (chr == ' ')
			nobj++;
	}while(chr != '\n');
	rewind(input);
	do{
		chr = fgetc(input);
		if (chr == '\n')
			tfrontlen++;
	}while (feof(input) == 0);
	rewind(input);
	if (read_set(input, tfrontlen, nobj, &tfront) < 0)
	{
		fprintf(stderr, "Error reading %s", tfront_file);
		return(EXIT_FAILURE);
	}
	fclose(input);

	// Read set of obtained solutions from file
	input = fopen(pset_file, "r");
	psetlen = 0;
	do{
		chr = fgetc(input);
		if (chr == '\n')
			psetlen++;
	}while (feof(input) == 0);
	rewind(input);
	if (read_set(input, psetlen, nobj, &pset) < 0)
	{
		fprintf(stderr, "Error reading %s", pset_file);
		return(EXIT_FAILURE);
	}
	fclose(input);

	// Extract the reference set of non-dominated solutions from pset
	fsetlen = psetlen;
	fsetlen = pareto_filter(pset, psetlen, nobj);
	filtered_set = pset;

	// Perform calculations.
	// Note that epsilons is used here as an unary indicator, though it is originally meant to be
	// a binary one. The binary epsilon indicator is used to compare two reference sets against each
	// each and not a set against the true Pareto front, as is done here.
	gd = generational_distance(filtered_set, fsetlen, tfront, tfrontlen, nobj);
	sp = spread(filtered_set, fsetlen, tfront, tfrontlen);
	gs = generalized_spread(filtered_set, fsetlen, tfront, tfrontlen, nobj);
	ep = epsilon(filtered_set, fsetlen, tfront, tfrontlen, nobj, multiplicative_e);

	// Free memory used by arrays
	free_matrix((void**)tfront, tfrontlen);
	free_matrix((void**)pset, psetlen);

	// Print results
	printf( "I_GD: %2.4f\n"
			"I_S: %2.4f\n"
			"I_GS: %2.4f\n"
			"I_epsilon: %2.4f\n", gd, sp, gs, ep);

	return (EXIT_SUCCESS);
}

int read_set(FILE *input, int setlen, int nobj, double ***pset)
{
	size_t i, j, ctr;
	(*pset) = new_matrix_double(setlen, nobj);
	ctr = 0;
	for (i=0; i<setlen; i++)
	{
		for(j=0; j<nobj; j++)
		{
			if (fscanf(input, "%lf", &(*pset)[i][j]))
				ctr++;
			else
				return -1;
		}
	}
	return ctr;
}
