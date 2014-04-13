#include <stdio.h>
#include "parser.h"

void test(char s[], real v)
{
	real r = eval(s);
	if (r == v)
		puts("passed");
	else
		printf("failed %s = %g\n", s, r);
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
	test("14+10*(3-4)", 4);
	test("14+10*(1)", 24);
	test("14+10*(3-4)/(5+5)", 13);
	test("1+(2*10)*(3-4)-1", -20);
	test("1+(10-((9*2)))*(3-4)-8 + 3*2^3 - 20 + 5", 10);
	return 0;
}