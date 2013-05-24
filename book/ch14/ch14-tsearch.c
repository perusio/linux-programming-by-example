/* ch14-tsearch.c --- demonstrate tree management */

#include <stdio.h>
#include <search.h>
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

/* print_emp --- print an employee structure during a tree walk */

void print_emp(const void *nodep, const VISIT which, const int depth)
{
	struct employee *e = *((struct employee **) nodep);

	switch (which) {
	case leaf:
	case postorder:
		printf("Depth: %d. Employee:\n", depth);
		printf("\t%s, %s\t%d\t%s\n", e->lastname, e->firstname,
			e->emp_id, ctime(& e->start_date));
		break;
	default:
		break;
	}
}

/* main --- demonstrate maintaining data in binary tree */

int main(void)
{
#define NPRES 10
	struct employee presidents[NPRES];
	int i, npres;
	char buf[BUFSIZ];
	void *root = NULL;

	/* Very simple code to read data: */
	for (npres = 0; npres < NPRES && fgets(buf, BUFSIZ, stdin) != NULL;
			npres++) {
		sscanf(buf, "%s %s %ld %ld\n",
			presidents[npres].lastname,
			presidents[npres].firstname,
			& presidents[npres].emp_id,
			& presidents[npres].start_date);
	}

	for (i = 0; i < npres; i++)
		(void) tsearch(& presidents[i], & root, emp_name_id_compare);

	twalk(root, print_emp);
	return 0;
}
