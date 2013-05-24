/* ch12-assert.c --- demonstrate assertions */

#include <stdio.h>
#include <assert.h>

/* lsearch --- return index in array of value, or -1 if not found */

int lsearch(int *array, size_t size, int value)
{
	size_t i;

	assert(array != NULL);
	assert(size > 0);
	for (i = 0; i < size; i++)
		if (array[i] == value)
			return i;

	assert(i == size);

	return -1;
}

/* main --- test out assertions */

int main(void)
{
#define NELEMS	4
	static int array[NELEMS] = { 1, 17, 42, 91 };
	int index;

	index = lsearch(array, NELEMS, 21);
	assert(index == -1);

	index = lsearch(array, NELEMS, 17);
	assert(index == 1);

	index = lsearch(NULL, NELEMS, 10);	/* won't return */

	printf("index = %d\n", index);

	return 0;
}
