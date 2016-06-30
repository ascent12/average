# Overview

Safely averaging integers in C has been known as a suprisingly difficult task to do.
The naive solution to averaging two integers is:
```C
(a + b) / 2
```
However, this statement can cause undefined behavior as `a + b` could cause signed overflow.
The next solution one might come up with is
```C
(a / 2) + (b / 2)
```
However, this will give the incorrect answer if both a and b are odd numbers, as integer
division will truncate `a / 2` and `b / 2` separately, and the answer will be 1 too small.
The correct answer is
```C
(a / 2) + (b / 2) + (a % 2 && b % 2)
```
which will add one to the result if both a and b are odd.

Another solution is to just convert a and b to larger integer types (or floating point),
to avoid overflow, and just do the naive solution.
However, this does not generalise to all integer types, as there may not be a larger
type to convert to, and floating point may not have to accuracy to calculate the result
accurately.

Now with the difficultly of averaging just two integers without overflow, I have written
a function will will average an arbitrary number of integers, without overflow on any
input or converting to a wider type, rounded towards zero.

This function has not been formally proven to be correct, but I'm fairly confident that
it works. If someone finds a situation where my function fails, I would love to know.

# Usage

To run the simple tests I wrote just run
```
make test
./test
```
Note that the tests require POSIX and GNU Make, but the averaging function itself is written entirely
with standard C.
