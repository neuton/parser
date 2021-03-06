#include <stdio.h>
#include "parser.h"

void tests(char s[], char sx[], real x[], real v)
{
	real r = evals(s, sx, x);
	if (v!=v)
	{
		if (r!=r)
			puts("passed");
		else
			printf("failed %s = %g\n", s, r);
	}
	else
	if (r == v)
		puts("passed");
	else
		printf("failed %s = %g\n", s, r);
}

void test(char s[], real v)
{
	tests(s, "", NULL, v);
}

int main()
{
	test("0" "0", 0);
	test("0.0", 0);
	test("-0.0", 0);
	test("1 + 1", 2);
	test("12.345", 12.345);
	test("-12,345", -12.345);
	test("14+10", 24);
	test("(14+10)*(3-4)", -24);
	test("(((14/10)))", 1.4);
	puts("-----------------------------");
	test("1+2*3", 7);
	test("14+10*(3-4)", 4);
	test("14+10*(1)", 24);
	test("14+10*(3-4)/(5+5)", 13);
	test("1+(2*10)*(3-4)-1", -20);
	test("1+(10-((9*2)))*(3-4)-8 + 3*2^3 - 20 + 5", 10);
	puts("-----------------------------");
	real x[] = {1, 2, 3, 4, 5};
	tests("x + y", "xy", x, 3);
	tests("x + yz", "xyzabc%^&", x, 7);
	tests("(x+y)/z + 2w", "xyzw", x, 9);
	puts("-----------------------------");
	test("((((1", 1);
	test("1 +J 1", 0./0.);
	return 0;
}