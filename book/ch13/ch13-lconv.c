/* ch13-lconv.c --- show some of the components of the struct lconv */

#include <stdio.h>
#include <limits.h>
#include <locale.h>

int main(void)
{
	struct lconv l;
	int i;

	setlocale(LC_ALL, "");
	l = *localeconv();

	printf("decimal_point = [%s]\n", l.decimal_point);
	printf("thousands_sep = [%s]\n", l.thousands_sep);

	for (i = 0; l.grouping[i] != 0 && l.grouping[i] != CHAR_MAX; i++)
		printf("grouping[%d] = [%d]\n", i, l.grouping[i]);

	printf("int_curr_symbol = [%s]\n", l.int_curr_symbol);
	printf("currency_symbol = [%s]\n", l.currency_symbol);
	printf("mon_decimal_point = [%s]\n", l.mon_decimal_point);
	printf("mon_thousands_sep = [%s]\n", l.mon_thousands_sep);
	printf("positive_sign = [%s]\n", l.positive_sign);
	printf("negative_sign = [%s]\n", l.negative_sign);
}
