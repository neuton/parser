#include "parser.h"

#include <stddef.h>
#include <math.h>

static short prio(char op)
{
	if ((op=='+')||(op=='-')) return 1;
	else if ((op=='*')||(op=='/')) return 2;
	else if (op=='^') return 3;
}

static real evals_(char s[], char sx[], real x[], unsigned* ishift, real init_r, char init_a, short p)
{
	real r=init_r, n=0, k;
	unsigned d=0, j, i=0;
	char a=init_a, c=s[0];
	if (!c) return NAN;
	while (1)
	{
		if (c==' ');
		else if ((c>='0')&&(c<='9'))
		{
			if (d>0) n+=(real)(c-'0')/(d*=10);
			else n=n*10+(real)(c-'0');
		}
		else if ((c=='.')||(c==','))
			d=1;
		else if (c=='(')
			{ i++; n=evals_(s+i, sx, x, &i, 0, '+', 0); }
		else if ((c=='s')&&(s[i+1]=='i')&&(s[i+2]=='n')&&(s[i+3]=='('))
			{ i+=4; n=sin(evals_(s+i, sx, x, &i, 0, '+', 0)); }
		else if ((c=='c')&&(s[i+1]=='o')&&(s[i+2]=='s')&&(s[i+3]=='('))
			{ i+=4; n=cos(evals_(s+i, sx, x, &i, 0, '+', 0)); }
		else if ((c=='t')&&(s[i+1]=='g')&&(s[i+2]=='('))
			{ i+=3; n=tan(evals_(s+i, sx, x, &i, 0, '+', 0)); }
		else if ((c=='l')&&(s[i+1]=='n')&&(s[i+2]=='('))
			{ i+=3; n=log(evals_(s+i, sx, x, &i, 0, '+', 0)); }
		else if ((c=='e')&&(s[i+1]=='x')&&(s[i+2]=='p')&&(s[i+3]=='('))
			{ i+=4; n=exp(evals_(s+i, sx, x, &i, 0, '+', 0)); }
		else if ((c=='p')&&(s[i+1]=='i'))
			{ i++; n=M_PI; }
		else if (c=='e')
			n=M_E;
		else if (c=='!')
			for (k=n-1; k>1; k--) n*=k;
		else
		{
			for (j=0; sx[j]&&c!=sx[j]; j++);
			if (sx[j])
				n=n==0?x[j]:n*x[j];
			else
			{
				if (((c=='+')||(c=='-')||(c=='/')||(c=='*')||(c=='^'))&&(prio(c)>prio(a)))
					{ i++; n=evals_(s+i, sx, x, &i, n, c, prio(a)); c=s[i]; }
				if (a=='+') r+=n;
				else if (a=='-') r-=n;
				else if (a=='*') r*=n;
				else if (a=='/') r/=n;
				else if (a=='^') r=pow(r, n);
				if ((!c)||(c==')'))
					{ *ishift+=i; return r; }
				else if ((c=='+')||(c=='-')||(c=='/')||(c=='*')||(c=='^'))
					{ if (prio(c)<=p) { *ishift+=i; return r; } a=c; }
				else
					{ *ishift+=i; return NAN; }
				n=0.; d=0;
			}
		}
		c=s[++i];
	}
}

extern real evals(char s[], char sx[], real x[])
{
	unsigned i=0;
	return evals_(s, sx, x, &i, 0, '+', 0);
}

extern real eval(char s[])
{
	return evals(s, "", NULL);
}
