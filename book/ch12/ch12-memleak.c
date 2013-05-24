/* ch12-memleak.c --- demonstrate memory leaks with setjmp()/longjmp(). */

#include <stdio.h>
#include <malloc.h>		/* for definition of ptrdiff_t on GLIBC */
#include <setjmp.h>
#include <unistd.h>

jmp_buf env;

void f1(void), f2(void);

/* main --- leak memory with setjmp() and longjmp() */

int main(void)
{
	char *start_break;
	char *current_break;
	ptrdiff_t diff;

	start_break = sbrk((ptrdiff_t) 0);

	if (setjmp(env) == 0)		/* first time */
		printf("setjmp called\n");

	current_break = sbrk((ptrdiff_t) 0);

	diff = current_break - start_break;
	printf("memsize = %ld\n", (long) diff);

	f1();

	return 0;
}

/* f1 --- allocate some memory, make a nested call */

void f1(void)
{
	char *p = malloc(1024);

	f2();
}

/* f2 --- allocate some memory, make longjmp */

void f2(void)
{
	char *p = malloc(1024);

	longjmp(env, 1);
}
