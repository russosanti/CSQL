#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main()
{
char g[42];
char h[80];
int a,b,c;

a=sizeof(int);
b=sizeof(g);
c=sizeof(h);
printf("%d\n",a);
printf("%d\n",b);
printf("%d\n",c);
a=a+b+c;
printf("%d\n",a);
}