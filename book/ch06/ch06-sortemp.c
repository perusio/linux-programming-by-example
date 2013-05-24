/* ch06-sortemp.c --- Demonstrate qsort() with two comparison functions. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct employee {
	char lastname[30];
	char firstname[30];
	long emp_id;
	time_t start_date;
};

/* emp_name_id_compare --- compare by name, then by ID */

int emp_name_id_compare(const void *e1p, const void *e2p)
{
	const struct employee *e1, *e2;
	int last, first;

	e1 = (const struct employee *) e1p;
	e2 = (const struct employee *) e2p;

	if ((last = strcmp(e1->lastname, e2->lastname)) != 0)
		return last;

	/* same last name, check first name */
	if ((first = strcmp(e1->firstname, e2->firstname)) != 0)
		return first;

	/* same first name, check ID numbers */
	if (e1->emp_id < e2->emp_id)
		return -1;
	else if (e1->emp_id == e2->emp_id)
		return 0;
	else
		return 1;

}

/* emp_seniority_compare --- compare by seniority */

int emp_seniority_compare(const void *e1p, const void *e2p)
{
	const struct employee *e1, *e2;
	double diff;

	e1 = (const struct employee *) e1p;
	e2 = (const struct employee *) e2p;

	diff = difftime(e1->start_date, e2->start_date);
	if (diff < 0.0)
		return -1;
	else if (diff > 0.0)
		return 1;
	else
		return 0;
}

/* main --- demonstrate sorting */

int main(void)
{
#define NPRES 10
	struct employee presidents[NPRES];
	int i, npres;
	char buf[BUFSIZ];

	/* Very simple code to read data: */
	for (npres = 0; npres < NPRES && fgets(buf, BUFSIZ, stdin) != NULL;
			npres++) {
		sscanf(buf, "%s %s %ld %ld\n",
			presidents[npres].lastname,
			presidents[npres].firstname,
			& presidents[npres].emp_id,
			& presidents[npres].start_date);
	}

	/* npres is now number of actual lines read. */

	/* First, sort by name */
	qsort(presidents, npres, sizeof(struct employee), emp_name_id_compare);

	/* Print output */
	printf("Sorted by name:\n");
	for (i = 0; i < npres; i++)
		printf("\t%s %s\t%d\t%s", 
			presidents[i].lastname,
			presidents[i].firstname,
			presidents[i].emp_id,
			ctime(& presidents[i].start_date));

	/* Now, sort by seniority */
	qsort(presidents, npres, sizeof(struct employee), emp_seniority_compare);

	/* And print again */
	printf("Sorted by seniority:\n");
	for (i = 0; i < npres; i++)
		printf("\t%s %s\t%d\t%s", 
			presidents[i].lastname,
			presidents[i].firstname,
			presidents[i].emp_id,
			ctime(& presidents[i].start_date));
}
