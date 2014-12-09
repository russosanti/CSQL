#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>               // PROBLEMA AL GUARDAR CADA REGISTRO.
#include <sys\stat.h>
#include "lista.h"
//#include "listas.h"
#include "TDATOL.H"
//#include "TDATOLS.H"

struct reg_libro{
	int nro_libro;
	char autor[42];
	char titulo[80];
};

void Cargar(tlista *l_lib);
void cargar_libros(tlista *l);
void ModificarLibros();
void listar_libros(tlista *l);
void showpos(FILE *stream);
char Enter();
char Salir();
void clrbuf();
void Grabar(tlista *l_lib);

int main()
{
FILE *index_principal;
FILE *libros;
tlista l_lib;
int opc,error;

lcrear(&l_lib);
error=0;

Cargar(&l_lib);
clrscr();
while(opc != 99){
	printf("\n\t\t¿Que desea Hacer?\n\n");
	printf("\t\t1.Alta de libros\n");
	printf("\t\t2.Baja de libros\n");
	printf("\t\t3.Modif de libros\n");
	printf("\t\t4.Listar libros por numero ascendente\n");
	printf("\t\t5.Listar autores por nombre\n");
	printf("\t\t6.Listar por titulo\n");
	printf("\t\t7.Buscar libros de un autor\n");
	printf("\t\t8.Buscar libros de un titulo\n");
	printf("\t\t9.\n");
	printf("\t\t10.\n");
	printf("\n\t\t99.Salir\n");
	printf("\n\t\OPCIÓN: ");
	scanf("%d", &opc);
	fflush(stdin);
	clrbuf();
	printf("\n\n");
	switch(opc){
		case 1:         //Carga de libros
			cargar_libros(&l_lib);
		break;

		/*case 2:
			if(lvacia(&l)){
				printf("La lista se encuentra vacía.\n\n");
			}else{
				printf("La lista ya tiene elementos ingresados.\n\n");
			}break;
	  */

		case 3:
			//ModificarLibro();
			break;

		case 4:        // Listar los libros en forma ascendente
			listar_libros(&l_lib);
			break;
		/*
		case 5:        // mostrar los valores en forma descendente
			if(!lvacia(&l))
				{
				lppio(&l);
				lant(&l);
				linfo(&l,&num);
				printf("%d ",num.clave);
				while(!lfin(&l))
					{
					lant(&l);
					linfo(&l,&num);
					printf("%d ",num.clave);
					}
				}
			break;

		case 6:        // mostrar el primer elemento de la lista
			if(!lvacia(&l))
				{
				lppio(&l);
				linfo(&l,&num);
				printf("%d ",num.clave);
				}
			else
				printf("La lista se encuentra vacía.\n\n");
			break;

		case 7:        // mostrar el último elemento de la lista
			if(!lvacia(&l))
				{
				lppio(&l);
				lant(&l);
				linfo(&l,&num);
				printf("%d ",num.clave);
				}
			else
				printf("La lista se encuentra vacía.\n\n");
			break;

		case 8:        // mostrar el siguiente elemento en la lista
			if(!lvacia(&l))
				{
				lsig(&l);
				linfo(&l,&num);
				printf("%d ",num.clave);
				}
			else
				printf("La lista se encuentra vacía.\n\n");
			break;

		case 9:        // modificar el elemento en la lista
			if(!lvacia(&l))
				{
				linfo(&l,&num);
				printf("\n\t\tModificar %d por el valor: ", num.clave);
				scanf("%d",&num.clave);
				lmodificar(&l,num);
				linfo(&l,&num);
				printf("%d ",num.clave);
				}
			else
				printf("La lista se encuentra vacía.\n\n");
			break;

		case 10:
			clrscr();
			printf("Ingrese el valor que desea buscar en la lista: ");
			scanf("%d", &num.clave);
		 //	printf("El valor %d se encuentra %d veces en la lista\n\n", busca,buscar(busca,cabeza, cabeza));
			lbuscar(&l,num.clave,&existe);
			if(existe == 1)
				printf("\nEl valor %d buscado se encuentra en la lista\n", num.clave);
			else
				printf("\nEl valor %d buscado no se encuentra en la lista\n", num.clave);
			break;
		*/
		case 99:
			Grabar(&l_lib);
			exit(1);

		default:
			printf("Error, el comando no es válido\n");
			break;
		}
		clrscr();
	}
}


// Cargar indice ppal en memoria

void Cargar(tlista *l_lib)
{
FILE *libros;
struct reg_libro reg;
index_lib dato;

if((libros = fopen("LIBROS.TXT", "r")) == NULL)
{
	fprintf(stderr, "Cannot open input file.\n");
	Enter();
}else{
	//fseek(libros,0,SEEK_SET);
	fread(&reg, sizeof(reg), 1, libros);
	if(!feof(libros)){
		while(!feof(libros)){
			if(!lllena(l_lib)){
				dato.clave=reg.nro_libro;
				strcpy(dato.autor,reg.autor);
				strcpy(dato.titulo,reg.titulo);
				linsertarorden(l_lib,dato,'a');
				printf("%d  %s  %s\n",dato.clave,dato.autor,dato.titulo);
				fread(&reg, sizeof(reg), 1, libros);
			}else{
				printf("Muchos registros cargados en el archivo");
				exit(0);
			}
		}
	}else{
		printf("La base de datos esta vacia, procure ingresar datos antes de operar\n\n");
		Enter();
	}
	fclose(libros);
}
//BUCKUP
}


// Rutina para cargar libros
void cargar_libros(tlista *l)
{
char control;
FILE *libros;
struct reg_libro a;
struct reg_libro reg;
index_lib dato;
struct stat statbuf;
control='s';

if(!lvacia(l)){
	lult(l);
	linfo(l,&dato);
	dato.clave=dato.clave+1;
}else{
	dato.clave=1;
}

while(control=='s' || control=='S'){
	printf("AUTOR: ");
	gets(dato.autor);
	printf("TITULO: ");
	gets(dato.titulo);
	linsertarorden(l,dato,'a');
	control=Salir();
	dato.clave=dato.clave+1;
}
//graba los archivos
}


//Modificar Libros
void ModificarLibro()
{
FILE *libros;
FILE *stream;
	if ((libros = fopen("LIBROS.TXT", "a+")) == NULL){
		fprintf(stderr, "Cannot open output file.\n");
			//return 1;
	}

	fpos_t filepos;

	/* save the file pointer position */
	fgetpos(stream, &filepos);

	/* write some data to the file */
	//fwrite(&texto,sizeof(texto),1,stream);

	/* show the current file position */
	showpos(stream);

	/* set a new file position, display it */
	filepos=0;
	if (fsetpos(stream, &filepos) == 0){
		showpos(stream);
		fwrite("This is a zest",sizeof("This is a zest"),1,stream);
	}else{
		fprintf(stderr, "Error setting file pointer.\n");
		exit(1);
	}
}



void listar_libros(tlista *l)
{
index_lib dato;

if(!lvacia(l)){
	printf("Nro lib     titulo              autor\n\n");
	lppio(l);
	linfo(l,&dato);
	printf("%d      %s                %s\n",dato.clave,dato.autor,dato.titulo);
	lsig(l);
	while(!lfin(l)){
		linfo(l,&dato);
		printf("%d      %s                %s\n",dato.clave,dato.autor,dato.titulo);
		lsig(l);
	}
}else{
	printf("No hay datos ingresados en la base de datos\n");
	Enter();
	clrscr();
}
Enter();
}



void showpos(FILE *stream)

{
	fpos_t pos;

	/* display the current file pointer
		position of a stream */
	fgetpos(stream, &pos);
	printf("File position: %ld\n", pos);
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

char Salir()
{
char X;
printf("\nQuiere seguir ingresando libros?: \n S = Si       N = No \n");
do
  {
	scanf("%c",&X);
	fflush(stdin);
	clrbuf();
  }
while (X!='S' && X!='s' && X!='N' && X!='n');
clrscr();
return(X);
}

//Pre{...}//
void clrbuf()
{
char a;
while (kbhit() != 0){
			a=getch();
		}
}
//Pos{Borra el buffer del getch}//



void Grabar(tlista *l_lib)
{
FILE *libros;
index_lib dato;
struct reg_libro reg;

if ((libros = fopen("LIBROS.TXT", "a+")) == NULL){
	fprintf(stderr, "Cannot open output file.\n");
	printf("Problemas al grabar el archivo\n");
	Enter();
}else{
	fseek(libros, 0, SEEK_SET);
	if(!lvacia(l_lib)){
		lppio(l_lib);
		linfo(l_lib,&dato);
		reg.nro_libro=dato.clave;
		strcpy(reg.autor,dato.autor);
		strcpy(reg.titulo,dato.titulo);
		printf("%d  %s  %s\n",reg.nro_libro,reg.autor,reg.titulo);
		fwrite(&reg, sizeof(reg), 1, libros);
		lsig(l_lib);
		while(!lfin(l_lib)){
			linfo(l_lib,&dato);
			reg.nro_libro=dato.clave;
			strcpy(reg.autor,dato.autor);
			strcpy(reg.titulo,dato.titulo);
			printf("%d  %s  %s\n",reg.nro_libro,reg.autor,reg.titulo);
			fwrite(&reg, sizeof(reg), 1, libros);
			lsig(l_lib);
		}
	}else{
		printf("OBSERVACION: LA BASE DE DATOS ESTA VACIA");
	}
}
fclose(libros);
}


//----------------------------------------//






