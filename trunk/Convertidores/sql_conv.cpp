#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include"listas.h"
#include "TDATOLS.h"
#define maxcad 256


void sql_insercion(char cad[maxcad],tlista *l);
char Enter();
void clrbuf();
int val_balance(char cad[maxcad]);
void sql_insercion2(char *ptr,tlista *l);
//void insertarL(tlista *l,ptr);


int main(){
char culo[maxcad]="Nombre Cadena[40],Apellido Cadena[40],Edad Entero";
char cul[maxcad]="NOMBRE CADENA";
tlista l;

sql_insercion(culo,&l);
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
			sql_insercion2(aux,l);
			while((ptr=strtok(NULL,",")) != NULL){
				printf("go");
				strcpy(aux,ptr);
				sql_insercion2(aux,l);
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
int abre=0;
int cierra=0;

printf("%s",cad);
Enter();
if(strchr(cad,'(')!=NULL){  //Busco si hay o no parentesis
	 for(int i=0;i<=strlen(cad);i++){
		  if(cad[i]=='('){
				abre=abre+1;
		  }else{
				if(cad[i]==')'){
					 cierra=cierra+1;
				}
		  }
	 }
}
return(abre==cierra);
}


void sql_insercion2(char *ptr,tlista *l)
{
Tdato dato;

//strcpy(buffer,ptr);
ptr=strtok(ptr," ");
strcpy(dato.clave,ptr);
ptr=strtok(NULL," ");
strcpy(dato.tipo,ptr);
if(!lllena(l)){
//	linsertarfin(l,dato);
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
