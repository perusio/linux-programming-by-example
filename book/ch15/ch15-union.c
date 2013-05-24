/* ch15-union.c --- brief demo of union usage. */

#include <stdio.h>

int main(void)
{
	union i_f {
		int i;
		float f;
	} u;

	u.f = 12.34;	/* Assign a floating point value */
	printf("%f also looks like %#x\n", u.f, u.i);
	exit(0);
}
