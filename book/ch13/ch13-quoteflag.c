/* ch13-quoteflag.c --- demonstrate printf's quote flag */

#include <stdio.h>
#include <locale.h>

int main(void)
{
	setlocale(LC_ALL, "");		/* Have to do this, or it won't work */
	printf("%'d\n", 1234567);
	return 0;
}
