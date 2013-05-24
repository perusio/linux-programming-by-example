/* ch13-strfmon.c --- demonstrate strfmon() */

#include <stdio.h>
#include <locale.h>
#include <monetary.h>

int main(void)
{
	char buf[BUFSIZ];
	double val = 1234.567;

	setlocale(LC_ALL, "");
	strfmon(buf, sizeof buf, "You owe me %n (%i)\n", val, val);

	fputs(buf, stdout);
	return 0;
}
