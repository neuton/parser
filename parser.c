#include "parser.h"

#include <stddef.h>
//#include <stdbool.h>
#include <math.h>

/*int processstring(char s[], bool doshift)
{
    int i=0, c=0;
    void shiftstring(int k)
    {
         int n=0;
         while (s[n++]); n++;
         while ((--n)>=k) s[n]=s[n-1];
    }
    void processstring1()
    {
         bool t=false;
         int a=0;
         do
               if (s[i]=='(') { i++; processstring1(); }
               else if (s[i]==')') { if (t) { if (doshift) { shiftstring(a); s[a]='('; i++; shiftstring(i); s[i]=')'; i++; } c+=2; } return; }
               else if ((a>0)&&((s[i]=='*')||(s[i]=='/')||(s[i]=='^'))) t=true;
               else if ((s[i]=='-')||(s[i]=='+')||s[i]==0) { if (t) { if (doshift) { shiftstring(a); s[a]='('; i++; shiftstring(i); s[i]=')'; i++; } c+=2; t=false; } a=i+1; }
         while (s[i++]);
    }
    void processstring2()
    {
         bool t=false;
         int a=0;
         do
               if (s[i]=='(') { i++; processstring2(); }
               else if (s[i]==')') { if (t) { if (doshift) { shiftstring(a); s[a]='('; i++; shiftstring(i); s[i]=')'; i++; } c+=2; } return; }
               else if ((s[i]=='^')&&(a>0)) t=true;
               else if ((s[i]=='-')||(s[i]=='+')||(s[i]=='*')||(s[i]=='/')||s[i]==0)
               { if (t) { if (doshift) { shiftstring(a); s[a]='('; i++; shiftstring(i); s[i]=')'; i++; } c+=2; t=false; } a=i+1; if ((s[i]=='-')||(s[i]=='+')) a=0; }
         while (s[i++]);
    }
    while (s[i++]) if ((s[i]=='(')&&(((s[i-1]>='0')&&(s[i-1]<':'))||(s[i-1]=='x'))) { if (doshift) { shiftstring(i); s[i]='*'; i++; } c++; } i=0;
    processstring1(); i=0;
    processstring2();
	return c;
}*/

static real evals_(char s[], char sx[], real x[], unsigned* ishift)
{
	real r=0, n=0, k;
	unsigned d=0, j, i=0;
	char a='+', c=s[0];
	if (!c) return NAN;
	while (1)
	{
		if ((c>='0')&&(c<='9'))
		{
			if (d>0) n+=(real)(c-'0')/(d*=10);
			else n=n*10+(real)(c-'0');
		}
		/*else if (s[i]=='y')
		{
			for (t=0; (s[++i]>='0')&&(s[i]<='9'); t=t*10+s[i]-'0');
			i--;
			n=n==0?y[t]:n*y[t];
		}*/
		else if ((c=='.')||(c==','))
			d=1;
		else if (c=='(')
			{ i++; n=evals_(s+i, sx, x, &i); }
		else if ((c=='s')&&(s[i+1]=='i')&&(s[i+2]=='n')&&(s[i+3]=='('))
			{ i+=4; n=sin(evals_(s+i, sx, x, &i)); }
		else if ((c=='c')&&(s[i+1]=='o')&&(s[i+2]=='s')&&(s[i+3]=='('))
			{ i+=4; n=cos(evals_(s+i, sx, x, &i)); }
		else if ((c=='t')&&(s[i+1]=='g')&&(s[i+2]=='('))
			{ i+=3; n=tan(evals_(s+i, sx, x, &i)); }
		else if ((c=='l')&&(s[i+1]=='n')&&(s[i+2]=='('))
			{ i+=3; n=log(evals_(s+i, sx, x, &i)); }
		else if ((c=='e')&&(s[i+1]=='x')&&(s[i+2]=='p')&&(s[i+3]=='('))
			{ i+=4; n=exp(evals_(s+i, sx, x, &i)); }
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
				switch (a)
				{
					case '+': r+=n; break;
					case '-': r-=n; break;
					case '*': r*=n; break;
					case '/': r/=n; break;
					case '^': r=pow(r, n);
				}
				//printf("%f ", r);
				if ((!c)||(c==')'))
					{ *ishift+=i; return r; }
				else if ((c=='+')||(c=='-')||(c=='/')||(c=='*')||(c=='^'))
					a=c;
				else if (c!=' ')
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
	return evals_(s, sx, x, &i);
}

extern real eval(char s[])
{
	return evals(s, "", NULL);
}
