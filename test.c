/*
 * iavg - arbitrary integer averaging function, without overflow or conversion
 *
 * Written in 2016 by Scott Anderson <scott@anderso.nz>
 */

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int iavg(int n, const int arr[static const n]);

double davg(int n, const int arr[static const n])
{
	double a = 0.0;

	for (int i = 0; i < n; ++i) {
		a += arr[i];
	}

	return a / n;
}

#define GRE "\033[32m"
#define RED "\033[31m"
#define CLR "\033[0m"

int test(int line, int n, const int arr[static const n])
{
	double fa = trunc(davg(n, arr));
	int ia = iavg(n, arr);

	if (fa == -0.0)
		fa = 0.0;

	printf("%d:\t%s"CLR": Expected %.0f, got %d\n",
			line, fa != ia ? RED"FAIL" : GRE"SUCC",
			fa, ia);

	return fa != ia;
}

#define test(...) _test(((int []){__VA_ARGS__}))
#define _test(arr) (test)(__LINE__, sizeof(arr)/sizeof(int), (arr))

int main()
{
#if 1
	int n = 0;

	n += test(INT_MAX, INT_MAX - 2);
	n += test(INT_MAX, INT_MAX - 1);
	n += test(INT_MIN, INT_MIN + 2);
	n += test(INT_MIN, INT_MIN + 1);
	n += test(INT_MAX, INT_MIN);
	n += test(INT_MAX, INT_MIN + 1);
	n += test(0, 999, 999999);
	n += test(0, 2, 4);
	n += test(0, 3, 6);
	n += test(0, 0, 2, 4);
	n += test(0, 0, 3, 6);
	n += test(0, 0, 2, 4, 4);
	n += test(-4, -2);
	n += test(0, -4, -2);
	n += test(0, 0, -4, -2);
	n += test(0, 0, -2, -4, -4);
	n += test(0, 0, -2, -4);
	n += test(4, 4, -4, -4);
	n += test(4, 4, 0, -4, -4);
	n += test(0, 0, 0, 0, 0, 0, 0, 8);
	n += test(0, 0, -2, -4, 6, 6);
	n += test(1, 2, 3, 4, 5, 6, 7, 8, 9 ,10);
	n += test(99, 0, 0, 0, 0, -100);
	n += test(1, 0, 0, -3);
	n += test(1);
	n += test(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 1);
	n += test(1, -4);
	n += test(-1, 4);
	n += test(1, 0, 0, -4);
	n += test(1, 0, 0, 0, -4);
	n += test(1, -1, -2, -1, -1, -1);
	n += test(-1, 1, 2, 1, 1, 1);
	n += test(1, -2);
	n += test(259483898, 1237343351, 1458536042, -203793151, 643797739,
			-1971218779, -4983519, -1410846899, 1651314371);
	n += test(-626385293, 1592999523, 378367764);
	n += test(-297795952, 592762855, 472900259, -1229229426, -1765257246,
			-1928201177, -1910083561);

	printf("Failed %d tests\n", n);

	return n != 0;
#endif

#if 0
	srand48(time(NULL));

	for (int i = 0; i < 100000; ++i) {
		static int arr[10000];
		int n = lrand48() % 10000 + 1;

		for (int j = 0; j < n; ++j) {
			arr[j] = mrand48();
		}

		int avg = iavg(n, arr);
		double dav = trunc(davg(n, arr));

		if (avg != dav) {
			printf("%d %.0f\n", avg, dav);
			for (int j = 0; j < n; ++j) {
				printf("%d\n", arr[j]);
			}
			break;
		}
	}
#endif
}
