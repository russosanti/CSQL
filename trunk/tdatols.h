#ifndef __TDATOLS_H
#define __TDATOLS_H

#define	MAX 256

typedef char Tclave[MAX];

typedef struct datos
{
	Tclave clave;
	long pos;
	char flag;
};

typedef datos Tdato_IString;

#endif


