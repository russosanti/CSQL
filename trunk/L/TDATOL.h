#ifndef __TDATOL_H
#define __TDATOL_H

#define	MAX 100

typedef int Tclave;

typedef struct index_lib
{
	Tclave clave;
	char autor[42];
	char titulo[80];
};

typedef index_lib Tdato;
#endif


