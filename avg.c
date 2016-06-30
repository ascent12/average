/*
 * iavg - arbitrary integer averaging function, without overflow or conversion
 *
 * Written in 2016 by Scott Anderson <scott@anderso.nz>
 */

#include <stdlib.h>

int iavg(int n, const int arr[static const n])
{
	int avg = 0;
	int rem[2] = {0, 0};
	int add[2] = {0, 0};

	for (int i = 0; i < n; ++i) {
		avg += arr[i] / n;

		int a = abs(arr[i] % n);
		int j = arr[i] < 0;

		if (rem[j] >= n - a) {
			rem[j] = a - (n - rem[j]);
			++add[j];
		} else {
			rem[j] += a;
		}
	}

	avg += add[0] - add[1];

	if (avg < 0 && rem[0] > rem[1])
		++avg;
	else if (avg > 0 && rem[0] < rem[1])
		--avg;

	return avg;
}
