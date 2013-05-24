/* ch13-strings.c --- demonstrate strcmp() vs. strcoll() */

#include <stdio.h>
#include <locale.h>
#include <string.h>

int main(void)
{
	setlocale(LC_ALL, "");

	printf("Result of strcmp(\"\\\"\", \"/\") is %d\n", strcmp("\"", "/"));
	printf("Result of strcoll(\"\\\"\", \"/\") is %d\n", strcoll("\"", "/"));
	exit(0);
}
