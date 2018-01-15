/*
 * iavg - arbitrary integer averaging function, without overflow or conversion
 *
 * Written in 2016 by Scott Anderson <scott@anderso.nz>
 */

#include <stdlib.h>

/**
 * Averages an array of integers.
 *
 * Averages an array of integers, without overflow or conversion to a larger type.
 * It is equivalent to the sum of the array, divided by the array's length (rounded towards zero).
 * 
 * @param n Number of array elements. Must be greater than zero.
 * @param arr A pointer to an array of n integers. Must be non-null.
 * @return The mean of the array's elements. 
 */
int iavg(int n, const int arr[static const n])
{
	int avg = 0;

	/* A buffer of values that are lost to integer truncation.
	 * It should always be in the closed interval (-n, n).
	 */
	int error = 0;

	for (int i = 0; i < n; ++i) {
		error += arr[i] % n;
		avg += (arr[i] / n) + (error / n);
		error %= n;
	}

	// Fix some overcompensation for error
	if (avg < 0 && error > 0)
		++avg;
	else if (avg > 0 && error < 0)
		--avg;

	return avg;
}
