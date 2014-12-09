#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include "listas.h"
#include "TDATOLS.h"
#define maxcad 1028


void sql_insercion(char cad[maxcad],tlista *l);
char Enter();
void clrbuf();
int val_balance(char cad[maxcad]);
void insertar_en_lista(char *ptr,tlista *l);
void mostrarlista(tlista *l);
//void insertarL(tlista *l,ptr);


int maintain(){
char culo[maxcad]="Nombre Cadena[40],Apellido Cadena[40],Edad Entero";
char cul[maxcad]="()*(Nombre)}]* {}[][{]}(Cadena)";
tlista l;

lcrear(&l);

sql_insercion(culo,&l);
Enter();
//clrscr();
mostrarlista(&l);
Enter();
return(0);
}




void sql_insercion(char cad[maxcad],tlista *l)
{
char *ptr;
char *aux=" ";

if(stricmp(cad,"/0")==0){
	 printf("La cadena pasada esta vacia");
}else{
	if(val_balance(cad)){
		printf("Sintaxis correcta");
		if(strchr(cad,',')!= NULL){
			ptr=strtok(cad,",");
			strcpy(aux,ptr);
			insertar_en_lista(aux,l);
			while((ptr=strtok(NULL,",")) != NULL){
				printf("go");
				strcpy(aux,ptr);
				insertar_en_lista(aux,l);
			}
		}else{
			printf("Faltan los caracteres separadores");
		}
	 }else{
		  printf("Sintaxis incorrecta");
	 }
}

}

int val_balance(char cad[maxcad])
{
int abrep=0;
int cierrap=0;
int abrec=0;
int cierrac=0;
int abrel=0;
int cierral=0;

printf("%s",cad);
Enter();
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

			case'*':
				i=i+1;
				while(i!='\0' && cad[i]!='*'){
					i=i+1;
				}
			break;
		}
	 }
}
return(abrep==cierrap);
}

//inserta una cadena en la lista
void insertar_en_lista(char *ptr,tlista *l)
{
Tdato dato;

strcpy(dato.clave,ptr);
if(!lllena(l)){
	strcpy(dato.clave,ptr);
	linsertarfin(l,dato);
}else{
	printf("La memoria esta llena, sera implosible agragar los campos solicitados");
}
}

//Pre{...}//
char Enter()
{
char E;
fflush(stdin);
clrbuf();
do
  {
	printf("\nPresione Enter Para Continuar\n");
	scanf("%c",&E);
  }
  while(E!='\n');
return(E);
}
//Pos{Valida el keypress del enter}//
/*--------------------------------------*/


//Pre{...}//
void clrbuf()
{
char a;
while (kbhit() != 0){
			a=getch();
		}
}
//Pos{Borra el buffer del getch}//


//muestra la clve (string) de la lista
void mostrarlista(tlista *l)
{
Tdato x;

if(!lvacia(l)){
	lppio(l);
	linfo(l,&x);
	printf("%s",x.clave);
	lsig(l);
	while(!lfin(l)){
		linfo(l,&x);
		printf("%s",x.clave);
		lsig(l);
	}
}
}
