#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "ManejoArchivosNew.h"
#define maxSQL 1028


char Enter();
//*** Divide el string en cada parte sin tener en cuenta espacios, coma o parentesis ***//
//    e inserta cada instruccion en una lista 
int DividirStringEnPartes (char SQLString[],tlista *l)
{
  char cstr[maxSQL];
  char *p;

  strcpy (cstr, SQLString);

  p=strtok (cstr," ,()");
  while (p!=NULL)
  {
//	insertar_en_lista(p,l);   // Insertar la instruccion en una lista
	p=strtok(NULL," ,()");
  }

  return 0;
}

// Verifica si la instruccion SQL tiene los separadores balanceados
int val_balance(char cad[])
{
int abrep=0;
int cierrap=0;
int abrec=0;
int cierrac=0;
int abrel=0;
int cierral=0;


if(strchr(cad,'(')!=NULL){  //Busco si hay o no parentesis
	 for(int i=0;i<=strlen(cad);i++){
		switch(cad[i]){
			case '(':
				abrep=abrep+1;
			break;

			case ')':
				cierrap=cierrap+1;
			break;

			case '[':
				abrec=abrec+1;
			break;

			case ']':
				cierrac=cierrac+1;
			break;

			case '{':
				abrel=abrel+1;
			break;

			case '}':
				cierral=cierral+1;
			break;

			case '"':
				i=i+1;
				while(i!='\0' && cad[i]!='"'){
					i=i+1;
				}
			break;
		}
	 }
}
return(abrep==cierrap);
}
