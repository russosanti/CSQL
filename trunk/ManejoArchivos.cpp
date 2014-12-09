#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
#include <string> 
#include "LISTAINDEX.h"		// clave numerica
#include "tdatoindex.h"
#include "listas.h"			// clabe alfanumerica
#include "tdatols.h"

typedef struct prod {
	int cod;
	char descrip[256];
	float precio;
	int stock;
	char flag;
}Producto;

// Estructura generica
typedef struct arch_gen {
	int cod;			// Código 
	char flag;				// Condicion que indica si el registro fue dado de baja o no
}Archivo;

// Estructura de Libros
typedef struct libro {
	int cod;				// Código interno de la biblioteca (ISSN) que se le asignó al libro el ingresar al sistema.-
	char flag;				// Condicion que indica si el registro fue dado de baja o no
	char cod_tema[MAX];		// Código interno con el que la biblioteca distingue cada tema.-
	char titulo[100];		// Título completo del libro.-
	char cod_autor[MAX];	// Codigo de autor
	char ubicacion[10];		// Ubicacion dentro de la biblioteca
}Libros;

// Estructura de Temas
typedef struct tema {
	char cod[MAX];			// Código interno con el que la biblioteca distingue cada tema.-
	char flag;				// Condicion que indica si el registro fue dado de baja o no
}Temas;

// Estructura de Prestamos
typedef struct prestamo {
	int cod;				// Codigo del prestamo
	char flag;
	int cod_socio;			// Codigo del socio
	int cod_libro;			// Código interno de la biblioteca (ISSN) que se le asignó al libro el ingresar al sistema.-
}Prestamos;

// Estructura de Autores
typedef struct autor {
	char cod[MAX];			// Nombre del autor
	char flag;				// Condicion que indica si el registro fue dado de baja o no
}Autores;

// Estructura de Socios
typedef struct socio {
	int cod;				// Codigo del socio
	char flag;
	char nombreyapellido[100];	// Nombre y apellido del socio
	long dni;				// DNI del socio
	char direccion[100];	// Dirección del socio.
}Socios;


typedef struct indice{
	int cod;
	char flag;
	long pos;
}Index;
 
typedef struct indice_alfa{
	char cod[MAX];
	char flag;
	long pos;
}IndexS;


void backup(char nom1[128],int longreg,char nom2[128]);
void BackUpArchivo(char nom[128],int longreg);
void cargarindice(tlista *l, char nom[128]);
void cargarindice_s(tlista_s *l, char nom[128]);
int crear_archivos(char nom1[128],char nom2[128]);
int crear_archivo(char nom[128]);
char Enter();
void clrbuf();
int abrir(char nombre[36]);
int cargar_Libros(char nom[128], tlista *l, tlista_s *l_tema, tlista_s *l_autor);
int cargar_Temas(char nom[128],tlista_s *l);
int cargar_Autores(char nom[128],tlista_s *l);
int cargar_Socios(char nom[128],tlista *l);
int cargar_Prestamos(char nom[128], tlista *l, tlista *l_socio, tlista *l_libro);
void borrarindice(tlista *l);
void borrarindice_s(tlista_s *l);
void LibroALista(tlista *l, char nom[128]);
void TemaALista(tlista_s *l, char nom[128]);
void PrestamoALista(tlista *l, char nom[128]);
void AutorALista(tlista_s *l, char nom[128]);
void SocioALista(tlista *l, char nom[128]);
void grabarindice(tlista *l, char nom[128]);
void grabarindice_s(tlista_s *l, char nom[128]);
void mostrarindice(tlista *l);
void mostrarindice_s(tlista_s *l);

char nom_arch_Libros[128];
char nom_arch_Temas[128];
char nom_arch_Prestamos[128];
char nom_arch_Autores[128];
char nom_arch_Socios[128];
char nom_indice_Libros[128];
char nom_indice_Temas[128];
char nom_indice_Prestamos[128];
char nom_indice_Autores[128];
char nom_indice_Socios[128];


int main()
{
	int opc = 0;
	tlista indice_Libros;
	tlista_s indice_Temas;
	tlista indice_Prestamos;
	tlista_s indice_Autores;
	tlista indice_Socios;

	strcpy(nom_arch_Libros,"Libros");
	strcpy(nom_arch_Temas,"Temas");
	strcpy(nom_arch_Prestamos,"Prestamos");
	strcpy(nom_arch_Autores,"Autores");
	strcpy(nom_arch_Socios,"Socios");
	strcpy(nom_indice_Libros,"Libros_idx");
	strcpy(nom_indice_Temas,"Temas_idx");
	strcpy(nom_indice_Prestamos,"Prestamos_idx");
	strcpy(nom_indice_Autores,"Autores_idx");
	strcpy(nom_indice_Socios,"Socios_idx");
	

	// Realiza los backups de los archivos e índices
/*	backup(nom_arch_Libros,sizeof(Libros),nom_indice_Libros);		// backup Libros e indice
	backup(nom_arch_Temas,sizeof(Temas),nom_indice_Temas);		// backup Temas e indice asociado
	backup(nom_arch_Prestamos,sizeof(Prestamos),nom_indice_Prestamos); // backup Prestamos e indice asociado
	backup(nom_arch_Autores,sizeof(Autores),nom_indice_Autores); // backup Autores e indice asociado
	backup(nom_arch_Socios,sizeof(Socios),nom_indice_Socios);		// backup Socios e indice asociado
*/
	lcrear_inx(&indice_Libros);
	if(abrir(nom_indice_Libros)){
		cargarindice(&indice_Libros,nom_indice_Libros); //carga el indice
	}else{
		printf("Error al abrir los archivos, intente crearlos nuevamente");
		Enter();
	}
	lcrear(&indice_Temas);
	if(abrir(nom_indice_Temas)){
		cargarindice_s(&indice_Temas,nom_indice_Temas); //carga el indice
	}else{
		printf("Error al abrir los archivos, intente crearlos nuevamente");
		Enter();
	}
	lcrear_inx(&indice_Prestamos);
	if(abrir(nom_indice_Prestamos)){
		cargarindice(&indice_Prestamos,nom_indice_Prestamos); //carga el indice
	}else{
		printf("Error al abrir los archivos, intente crearlos nuevamente");
		Enter();
	}
	lcrear(&indice_Autores);
	if(abrir(nom_indice_Autores)){
		cargarindice_s(&indice_Autores,nom_indice_Autores); //carga el indice
	}else{
		printf("Error al abrir los archivos, intente crearlos nuevamente");
		Enter();
	}
	lcrear_inx(&indice_Socios);
	if(abrir(nom_indice_Socios)){
		cargarindice(&indice_Socios,nom_indice_Socios); //carga el indice
	}else{
		printf("Error al abrir los archivos, intente crearlos nuevamente");
		Enter();
	}


	while(opc != 99){
		system("cls");
		printf("\n\t\t¿Que desea Hacer?\n\n");
		printf("\t\t1.Crear Archivos\n");
		printf("\t\t21.Cargar Libros\n");
		printf("\t\t22.Cargar Temas\n");
		printf("\t\t23.Cargar Autores\n");
		printf("\t\t24.Cargar Socios\n");
		printf("\t\t25.Cargar Prestamos\n");
		printf("\t\t31.Crear Indice Libros\n");
		printf("\t\t32.Crear Indice Temas\n");
		printf("\t\t33.Crear Indice Autores\n");
		printf("\t\t34.Crear Indice Socios\n");
		printf("\t\t35.Crear Indice Prestamos\n");
		printf("\t\t4.Backup\n");
		printf("\t\t51.Mostrar Indice Libros\n");
		printf("\t\t52.Mostrar Indice Temas\n");
		printf("\t\t53.Mostrar Indice Autores\n");
		printf("\t\t54.Mostrar Indice Socios\n");
		printf("\t\t55.Mostrar Indice Prestamos\n");
		printf("\n\t\t99.Salir\n");
		printf("\n\t\OPCIÓN: ");
		scanf("%d", &opc);
		fflush(stdin);
		printf("\n\n");
		switch(opc){
			
			case 1:	// crea los archivos e índices
				crear_archivo(nom_arch_Libros);	
				crear_archivo(nom_indice_Libros);	
				crear_archivo(nom_arch_Temas);		
				crear_archivo(nom_indice_Temas);		
				crear_archivo(nom_arch_Prestamos); 
				crear_archivo(nom_indice_Prestamos); 
				crear_archivo(nom_arch_Autores); 
				crear_archivo(nom_indice_Autores); 
				crear_archivo(nom_arch_Socios);	
				crear_archivo(nom_indice_Socios);	
			break;

			case 21:
				
				if(abrir(nom_arch_Libros)){
					if(cargar_Libros(nom_arch_Libros,&indice_Libros,&indice_Temas,&indice_Autores)){//carga el archivo Libros
						borrarindice(&indice_Libros);
						LibroALista(&indice_Libros,nom_arch_Libros);
						grabarindice(&indice_Libros,nom_indice_Libros);
					}
				}else{
					printf("Error al abrir los archivos, intente crearlos nuevamente");
					Enter();
				}
			break;
			
			case 22:
				
				if(abrir(nom_arch_Temas)){
					if(cargar_Temas(nom_arch_Temas,&indice_Temas)){//carga el archivo Temas
						borrarindice_s(&indice_Temas);
						TemaALista(&indice_Temas,nom_arch_Temas);
						grabarindice_s(&indice_Temas,nom_indice_Temas);
					}
				}else{
					printf("Error al abrir los archivos, intente crearlos nuevamente");
					Enter();
				}
			break;
			
			case 23:
				
				if(abrir(nom_arch_Autores)){
					if(cargar_Autores(nom_arch_Autores,&indice_Autores)){//carga el archivo Autores
						borrarindice_s(&indice_Autores);
						AutorALista(&indice_Autores,nom_arch_Autores);
						grabarindice_s(&indice_Autores,nom_indice_Autores);
					}
				}else{
					printf("Error al abrir los archivos, intente crearlos nuevamente");
					Enter();
				}
			break;
			
			case 24:
				
				if(abrir(nom_arch_Socios)){
					if(cargar_Socios(nom_arch_Socios,&indice_Socios)){//carga el archivo Socios
						borrarindice(&indice_Socios);
						SocioALista(&indice_Socios,nom_arch_Socios);
						grabarindice(&indice_Socios,nom_indice_Socios);
					}
				}else{
					printf("Error al abrir los archivos, intente crearlos nuevamente");
					Enter();
				}
			break;
			
			case 25:
				
				if(abrir(nom_arch_Prestamos)){
					if(cargar_Prestamos(nom_arch_Prestamos,&indice_Prestamos,&indice_Socios,&indice_Libros)){//carga el archivo Prestamos
						borrarindice(&indice_Prestamos);
						PrestamoALista(&indice_Prestamos,nom_arch_Prestamos);
						grabarindice(&indice_Prestamos,nom_indice_Prestamos);
					}
				}else{
					printf("Error al abrir los archivos, intente crearlos nuevamente");
					Enter();
				}
			break;
			
			case 31:
				if(abrir(nom_arch_Libros) && abrir(nom_indice_Libros)){
					borrarindice(&indice_Libros);
					LibroALista(&indice_Libros,nom_arch_Libros);
					grabarindice(&indice_Libros,nom_indice_Libros);
				}else{
					printf("Error al abrir los archivos, intente crearlos nuevamente");
					Enter();
				}
			break;

			case 32:
				if(abrir(nom_arch_Temas) && abrir(nom_indice_Temas)){
					borrarindice_s(&indice_Temas);
					TemaALista(&indice_Temas,nom_arch_Temas);
					grabarindice_s(&indice_Temas,nom_indice_Temas);
				}else{
					printf("Error al abrir los archivos, intente crearlos nuevamente");
					Enter();
				}
			break;

			case 33:
				if(abrir(nom_arch_Autores) && abrir(nom_indice_Autores)){
					borrarindice_s(&indice_Autores);
					AutorALista(&indice_Autores,nom_arch_Autores);
					grabarindice_s(&indice_Autores,nom_indice_Autores);
				}else{
					printf("Error al abrir los archivos, intente crearlos nuevamente");
					Enter();
				}
			break;

			case 34:
				if(abrir(nom_arch_Socios) && abrir(nom_indice_Socios)){
					borrarindice(&indice_Socios);
					SocioALista(&indice_Socios,nom_arch_Socios);
					grabarindice(&indice_Socios,nom_indice_Socios);
				}else{
					printf("Error al abrir los archivos, intente crearlos nuevamente");
					Enter();
				}
			break;

			case 35:
				if(abrir(nom_arch_Prestamos) && abrir(nom_indice_Prestamos)){
					borrarindice(&indice_Prestamos);
					PrestamoALista(&indice_Prestamos,nom_arch_Prestamos);
					grabarindice(&indice_Prestamos,nom_indice_Prestamos);
				}else{
					printf("Error al abrir los archivos, intente crearlos nuevamente");
					Enter();
				}
			break;


			case 4:
				// Realiza los backups de los archivos e índices
				backup(nom_arch_Libros,sizeof(Libros),nom_indice_Libros);		// backup Libros e indice
				backup(nom_arch_Temas,sizeof(Temas),nom_indice_Temas);		// backup Temas e indice asociado
				backup(nom_arch_Prestamos,sizeof(Prestamos),nom_indice_Prestamos); // backup Prestamos e indice asociado
				backup(nom_arch_Autores,sizeof(Autores),nom_indice_Autores); // backup Autores e indice asociado
				backup(nom_arch_Socios,sizeof(Socios),nom_indice_Socios);		// backup Socios e indice asociado
			break;

			case 51:
				mostrarindice(&indice_Libros);
				Enter();
			break;

			case 52:
				mostrarindice_s(&indice_Temas);
				Enter();
			break;

			case 53:
				mostrarindice_s(&indice_Autores);
				Enter();
			break;

			case 54:
				mostrarindice(&indice_Socios);
				Enter();
			break;

			case 55:
				mostrarindice(&indice_Prestamos);
				Enter();
			break;
		}
	}
	return(0);
}
//--------------------------------------------------------------------

//Pregunta si se quiere realizar un backup
void backup(char nom1[128],int longreg,char nom2[128])
{
	char resp = 'S';
	printf("Quiere hacer un backup de %s?\n",nom1);
	printf("Esto puede durar unos minutos\n");
	printf(" S (Si)   N (No)   :\n");
	scanf("%c",&resp);
	system("cls");
	while(resp != 's' && resp != 'S' && resp != 'n' && resp != 'N'){
		printf("Ingrese 'S' si quiere realizar un backup o 'N' si no desea\n");
		scanf("%c",&resp);
	}

	if(resp=='s' || resp=='S'){
		printf("Aguarde mientras se realiza el backup de %s...",nom1);
		Enter();
		BackUpArchivo(nom1,longreg);			// backup archivo ppal
		if ((stricmp(nom2,"Temas") == 0) || (stricmp(nom2,"Autores") == 0)){
			BackUpArchivo(nom2,sizeof(IndexS));		// backup archivo indice del ppal
		}else{
			BackUpArchivo(nom2,sizeof(Index));		// backup archivo indice del ppal
		}
	}else{
		printf("Si quiere realizar el backup puede seleccionarlo desde el menu");
		Enter();
		system("cls");
	}
}
//--------------------------------------------------------------------

//Copia el achivo pasado por nom a su backup
void BackUpArchivo(char nom[128],int longreg)
{
	char * x;
  // asigna memoria para contener el registro
	x = (char*) malloc (longreg);
	if (x == NULL) {fputs ("Memory error",stderr); exit (2);}

	FILE *F;
	FILE *FBK;
	char bak[262];
	strcpy(bak,nom);
	strcat(bak,"_BKUP");

	if((F = fopen(nom, "rb+")) == NULL){
		printf("El archivo %s original no puede abrirse para el backup\nAsegurese que este creado",nom);
		Enter();
	}else{
		if((FBK = fopen(bak, "wb")) == NULL){
			printf("El archivo %s para backup no pudo ser creado\nIntente nuevamente mas tarde",bak);
			fclose(F);
			Enter();
		}else{
			fseek(F,0L,0);
			fseek(FBK,0L,0);
			fread(&x,sizeof(x),1,F);
			while(!feof(F)){
				fwrite(&x,sizeof(x),1,FBK);
				fread(&x,sizeof(x),1,F);
			}
			fclose(F);
			fclose(FBK);
		}
	}
	system("cls");
}

//Carga el indice numerico del archivo a la lista
void cargarindice(tlista *l, char nom[128])
{
	FILE *INDEX;
	Index d;
	Tdatoindex ind;
	long pos = 0;
	
	if((INDEX = fopen(nom, "rb+")) == NULL){
		printf("Pruebe crear el archivo primero");
		Enter();
	}else{
		fseek(INDEX,0L,0);
		fread(&d,sizeof(d),1,INDEX);
		while(!feof(INDEX)){
			ind.clave = d.cod;
			ind.pos = d.pos;
			ind.flag = d.flag;
			linsertarorden_inx(l,ind,'a');
			pos = pos + sizeof(d);
			fread(&d,sizeof(d),1,INDEX);
		}
	}
	fclose(INDEX);
}
//Carga el indice Tipo String del archivo a la Lista String
void cargarindice_s(tlista_s *l, char nom[128])
{
	FILE *INDEX;
	IndexS d;
	Tdato_IString ind;
	long pos = 0;
	
	if((INDEX = fopen(nom, "rb+")) == NULL){
		printf("Pruebe crear el archivo primero");
		Enter();
	}else{
		fseek(INDEX,0L,0);
		fread(&d,sizeof(d),1,INDEX);
		while(!feof(INDEX)){
			strcpy(ind.clave,d.cod);
			ind.pos = d.pos;
			ind.flag = d.flag;
			linsertarorden(l,ind,'a');
			pos = pos + sizeof(d);
			fread(&d,sizeof(d),1,INDEX);
		}
	}
	fclose(INDEX);
}
//--------------------------------------------------------------------

//Crea el archivo para trabajar en caso que no este creado
int crear_archivo(char nom[128])
{
	FILE *ARCH;
	if((ARCH = fopen(nom, "rb+")) == NULL){
		if((ARCH = fopen(nom, "wb+")) == NULL){
			printf("Error al crear el archivo %s", nom);
			Enter();
			exit(0);
		}else{
			fclose(ARCH);
		}
	}else{
		printf("El archivo %s ya existe", nom);
		Enter();
	}
	return(0);
}


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


//Pre{...}//
void clrbuf()
{
char a;
while (kbhit() != 0){
			a=getch();
		}
}

//Se fija si puede abrir el archivo
int abrir(char nombre[36])
{
	FILE *F;
	if((F = fopen(nombre, "rb+")) == NULL){
		printf("Pruebe crear el archivo primero");
		Enter();
		return(0);
	}else{
		return(1);
	}
	fclose(F);
}
//--------------------------------------------------------------------

//Carga el archivo Libros con datos
int cargar_Libros(char nom[128], tlista *l, tlista_s *l_tema, tlista_s *l_autor)
{
	FILE *ARCHIVO;
	Libros arch;
	int existe;
	fpos_t pos;
	Tdatoindex ind;
	
	if((ARCHIVO = fopen(nom, "rb+")) == NULL){
		printf("Pruebe crear el archivo primero");
		Enter();
		return(0);
	}else{
		system("cls");
		fseek(ARCHIVO,0L,SEEK_END);
		printf("Codigo (Salir 0): ");
		scanf("%d",&arch.cod);
		fflush(stdin);
		while(arch.cod != 0){
			lbuscar_inx(l,arch.cod,&existe);
			if (!existe){
				printf("Codigo Tema: ");
				gets(arch.cod_tema);
				fflush(stdin);				
				// Validar que el tema ingresado es valido
				lbuscar(l_tema,arch.cod_tema,&existe);
				if (!existe){
					printf("El tema '%s' ingresado no existe en la base.\nIngrese uno valido\n",arch.cod_tema);
					Enter();
				}else{
					printf("Codigo Autor: ");
					gets(arch.cod_autor);
					fflush(stdin);
					// Validar que el autor ingresado es valido
					lbuscar(l_autor,arch.cod_autor,&existe);
					if (!existe){
						printf("El autor '%s' ingresado no existe en la base.\nIngrese uno valido\n",arch.cod_autor);
						Enter();
					}else{
						printf("Título del libro: ");
						gets(arch.titulo);
						fflush(stdin);
						printf("Flag: ");
						scanf("%c",&arch.flag);
						fflush(stdin);
						printf("Ubicacion: ");
						gets(arch.ubicacion);
						fflush(stdin);
						ind.clave = arch.cod;
						ind.pos = fgetpos (ARCHIVO,&pos);
						ind.flag = arch.flag;
						linsertarorden_inx(l,ind,'a');
						fwrite(&arch,sizeof(arch),1,ARCHIVO);
					}
				}
			}else{
				printf("El codigo libro %d ya existe.", arch.cod);
				Enter();
			}
			system("cls");
			printf("Codigo: (0 Para Salir)");
			scanf("%d",&arch.cod);
			fflush(stdin);
		}
		fclose(ARCHIVO);
		return(1);
	}
}//--------------------------------------------------------------------
//Carga el archivo Temas con datos
int cargar_Temas(char nom[128],tlista_s *l)
{
	FILE *ARCHIVO;
	Temas arch;
	int existe;
	fpos_t pos;
	Tdato_IString ind;

	if((ARCHIVO = fopen(nom, "rb+")) == NULL){
		printf("Pruebe crear el archivo primero");
		Enter();
		return(0);
	}else{
		system("cls");
		fseek(ARCHIVO,0L,SEEK_END);
		printf("Tema (Salir con blancos): ");
		gets(arch.cod);
		fflush(stdin);
		while(strlen(arch.cod) > 0){
			lbuscar(l,arch.cod,&existe);
			if (!existe){
				printf("Flag: ");
				scanf("%c",&arch.flag);
				fflush(stdin);
				strcpy(ind.clave,arch.cod);
				ind.pos = fgetpos (ARCHIVO,&pos);
				ind.flag = arch.flag;
				linsertarorden(l,ind,'a');
				fwrite(&arch,sizeof(arch),1,ARCHIVO);
			}else{
				printf("El codigo de tema %s ya existe.", arch.cod);
				Enter();
			}
			system("cls");
			printf("Tema (Salir con blancos): ");
			gets(arch.cod);
			fflush(stdin);
		}
		fclose(ARCHIVO);
		return(1);
	}
}


//--------------------------------------------------------------------
//Carga el archivo Autores con datos
int cargar_Autores(char nom[128],tlista_s *l)
{
	FILE *ARCHIVO;
	Autores arch;
	int existe;
	fpos_t pos;
	Tdato_IString ind;
	
	if((ARCHIVO = fopen(nom, "rb+")) == NULL){
		printf("Pruebe crear el archivo primero");
		Enter();
		return(0);
	}else{
		system("cls");
		fseek(ARCHIVO,0L,SEEK_END);
		printf("Nombre del autor (Salir con blancos): ");
		gets(arch.cod);
		fflush(stdin);
		while(strlen(arch.cod) > 0){
			lbuscar(l,arch.cod,&existe);
			if (!existe){
				printf("Flag: ");
				scanf("%c",&arch.flag);
				fflush(stdin);
				strcpy(ind.clave,arch.cod);
				ind.pos = fgetpos (ARCHIVO,&pos);
				ind.flag = arch.flag;
				linsertarorden(l,ind,'a');
				fwrite(&arch,sizeof(arch),1,ARCHIVO);
			}else{
				printf("El codigo de autor %d ya existe.", arch.cod);
				Enter();
			}
			system("cls");
			printf("Nombre del autor (Salir con blancos): ");
			gets(arch.cod);
			fflush(stdin);
		}
		fclose(ARCHIVO);
		return(1);
	}
}//--------------------------------------------------------------------
//Carga el archivo Socios con datos
int cargar_Socios(char nom[128],tlista *l)
{
	FILE *ARCHIVO;
	Socios arch;
	int existe;
	fpos_t pos;
	Tdatoindex ind;
	
	if((ARCHIVO = fopen(nom, "rb+")) == NULL){
		printf("Pruebe crear el archivo primero");
		Enter();
		return(0);
	}else{
		system("cls");
		fseek(ARCHIVO,0L,SEEK_END);
		printf("Codigo (Salir 0): ");
		scanf("%d",&arch.cod);
		fflush(stdin);
		while(arch.cod != 0){
			lbuscar_inx(l,arch.cod,&existe);
			if (!existe){
				printf("Nombre y apellido del socio: ");
				gets(arch.nombreyapellido);
				fflush(stdin);
				printf("Flag: ");
				scanf("%c",&arch.flag);
				fflush(stdin);
				printf("DNI: ");
				scanf("%d",&arch.dni);
				fflush(stdin);
				printf("Direccion: ");
				gets(arch.direccion);
				fflush(stdin);
				ind.clave = arch.cod;
				ind.pos = fgetpos (ARCHIVO,&pos);
				ind.flag = arch.flag;
				linsertarorden_inx(l,ind,'a');
				fwrite(&arch,sizeof(arch),1,ARCHIVO);
			}else{
				printf("El codigo de socio %d ya existe.", arch.cod);
				Enter();
			}
			system("cls");
			printf("Codigo: (0 Para Salir)");
			scanf("%d",&arch.cod);
			fflush(stdin);
		}
		fclose(ARCHIVO);
		return(1);
	}
}//--------------------------------------------------------------------
//Carga el archivo Prestamos con datos
int cargar_Prestamos(char nom[128], tlista *l, tlista *l_socio, tlista *l_libro)
{
	FILE *ARCHIVO;
	Prestamos arch;
	int existe;
	fpos_t pos;
	Tdatoindex ind;
	
	if((ARCHIVO = fopen(nom, "rb+")) == NULL){
		printf("Pruebe crear el archivo primero");
		Enter();
		return(0);
	}else{
		system("cls");
		fseek(ARCHIVO,0L,SEEK_END);
		printf("Codigo (Salir 0): ");
		scanf("%d",&arch.cod);
		fflush(stdin);
		while(arch.cod != 0){
			lbuscar_inx(l,arch.cod,&existe);
			if (!existe){
				printf("Codigo de Socio: ");
				scanf("%d",&arch.cod_socio);
				fflush(stdin);
				// Validar que el socio ingresado es valido
				lbuscar_inx(l_socio,arch.cod_socio,&existe);
				if (!existe){
					printf("El socio '%d' ingresado no existe en la base.\nIngrese uno valido\n",arch.cod_socio);
					Enter();
				}else{
					printf("Codigo de Libro: ");
					scanf("%d",&arch.cod_libro);
					fflush(stdin);
					// Validar que el libro ingresado es valido
					lbuscar_inx(l_libro,arch.cod_libro,&existe);
					if (!existe){
						printf("El libro '%d' ingresado no existe en la base.\nIngrese uno valido\n",arch.cod_libro);
						Enter();
					}else{
						printf("Flag: ");
						scanf("%c",&arch.flag);
						fflush(stdin);
						ind.clave = arch.cod;
						ind.pos = fgetpos (ARCHIVO,&pos);
						ind.flag = arch.flag;
						linsertarorden_inx(l,ind,'a');
						fwrite(&arch,sizeof(arch),1,ARCHIVO);
					}
				}
			}else{
				printf("El codigo de prestamo %d ya existe.", arch.cod);
				Enter();
			}
			system("cls");
			printf("Codigo: (0 Para Salir)");
			scanf("%d",&arch.cod);
			fflush(stdin);
		}
		fclose(ARCHIVO);
		return(1);
	}
}//--------------------------------------------------------------------

void borrarindice(tlista *l)
{
	while(!lvacia_inx(l)){
		lborrarppio_inx(l);
	}

}

void borrarindice_s(tlista_s *l)
{
	while(!lvacia(l)){
		lborrarppio(l);
	}

}

//Para crear el indice carga el archivo Libros ordenandolo en la lista
void LibroALista(tlista *l, char nom[128])
{
	FILE *ARCHIVO;
	Libros arch;
	Tdatoindex d;
	long pos = 0;
	if((ARCHIVO = fopen(nom, "rb+")) == NULL){
		printf("Pruebe crear el archivo primero");
		Enter();
	}else{
		fseek(ARCHIVO,0,0);
		fread(&arch,sizeof(arch),1,ARCHIVO);
		while(!feof(ARCHIVO)){
			d.clave = arch.cod;
			d.pos = pos;
			d.flag = arch.flag;
			linsertarorden_inx(l,d,'a');
			pos = pos + sizeof(arch);
			fread(&arch,sizeof(arch),1,ARCHIVO);
		}
	}
	fclose(ARCHIVO);
}

//Para crear el indice carga el archivo Temas ordenandolo en la lista
void TemaALista(tlista_s *l, char nom[128])
{
	FILE *ARCHIVO;
	Temas arch;
	Tdato_IString d;
	long pos = 0;
	if((ARCHIVO = fopen(nom, "rb+")) == NULL){
		printf("Pruebe crear el archivo primero");
		Enter();
	}else{
		fseek(ARCHIVO,0,0);
		fread(&arch,sizeof(arch),1,ARCHIVO);
		while(!feof(ARCHIVO)){
			strcpy(d.clave,arch.cod);
			d.pos = pos;
			d.flag = arch.flag;
			linsertarorden(l,d,'a');
			pos = pos + sizeof(arch);
			fread(&arch,sizeof(arch),1,ARCHIVO);
		}
	}
	fclose(ARCHIVO);
}

//Para crear el indice carga el archivo Prestamos ordenandolo en la lista
void PrestamoALista(tlista *l, char nom[128])
{
	FILE *ARCHIVO;
	Prestamos arch;
	Tdatoindex d;
	long pos = 0;
	if((ARCHIVO = fopen(nom, "rb+")) == NULL){
		printf("Pruebe crear el archivo primero");
		Enter();
	}else{
		fseek(ARCHIVO,0,0);
		fread(&arch,sizeof(arch),1,ARCHIVO);
		while(!feof(ARCHIVO)){
			d.clave = arch.cod;
			d.pos = pos;
			d.flag = arch.flag;
			linsertarorden_inx(l,d,'a');
			pos = pos + sizeof(arch);
			fread(&arch,sizeof(arch),1,ARCHIVO);
		}
	}
	fclose(ARCHIVO);
}

//Para crear el indice carga el archivo Autores ordenandolo en la lista
void AutorALista(tlista_s *l, char nom[128])
{
	FILE *ARCHIVO;
	Autores arch;
	Tdato_IString d;
	long pos = 0;
	if((ARCHIVO = fopen(nom, "rb+")) == NULL){
		printf("Pruebe crear el archivo primero");
		Enter();
	}else{
		fseek(ARCHIVO,0,0);
		fread(&arch,sizeof(arch),1,ARCHIVO);
		while(!feof(ARCHIVO)){
			strcpy(d.clave,arch.cod);
			d.pos = pos;
			d.flag = arch.flag;
			linsertarorden(l,d,'a');
			pos = pos + sizeof(arch);
			fread(&arch,sizeof(arch),1,ARCHIVO);
		}
	}
	fclose(ARCHIVO);
}

//Para crear el indice carga el archivo Socios ordenandolo en la lista
void SocioALista(tlista *l, char nom[128])
{
	FILE *ARCHIVO;
	Socios arch;
	Tdatoindex d;
	long pos = 0;
	if((ARCHIVO = fopen(nom, "rb+")) == NULL){
		printf("Pruebe crear el archivo primero");
		Enter();
	}else{
		fseek(ARCHIVO,0,0);
		fread(&arch,sizeof(arch),1,ARCHIVO);
		while(!feof(ARCHIVO)){
			d.clave = arch.cod;
			d.pos = pos;
			d.flag = arch.flag;
			linsertarorden_inx(l,d,'a');
			pos = pos + sizeof(arch);
			fread(&arch,sizeof(arch),1,ARCHIVO);
		}
	}
	fclose(ARCHIVO);
}
//--------------------------------------------------------------------

//Graba el indice en la lista en un archivo
void grabarindice(tlista *l, char nom[128])
{
	FILE *INDEX;
	Index d;
	Tdatoindex ind;

	if((INDEX = fopen(nom, "wb")) == NULL){
		printf("No se pudo crear el archivo");
		Enter();
	}else{
		if(!lvacia_inx(l)){
			lppio_inx(l);
			fseek(INDEX,0L,0);
			linfo_inx(l,&ind);
			d.cod = ind.clave;
			d.pos = ind.pos;
			d.flag = ind.flag;
			fwrite(&d,sizeof(d),1,INDEX);
			lsig_inx(l);
			while(!lfin_inx(l)){
				linfo_inx(l,&ind);
				d.cod = ind.clave;
				d.pos = ind.pos;
				d.flag = ind.flag;
				fwrite(&d,sizeof(d),1,INDEX);
				lsig_inx(l);
			}
		}
	}
	fclose(INDEX);
}
//Graba el indice tipo String en la lista tipo String en un archivo
void grabarindice_s(tlista_s *l, char nom[128])
{
	FILE *INDEX;
	IndexS d;
	Tdato_IString ind;

	if((INDEX = fopen(nom, "wb")) == NULL){
		printf("No se pudo crear el archivo");
		Enter();
	}else{
		if(!lvacia(l)){
			lppio(l);
			fseek(INDEX,0L,0);
			linfo(l,&ind);
			strcpy(d.cod,ind.clave);
			d.pos = ind.pos;
			d.flag = ind.flag;
			fwrite(&d,sizeof(d),1,INDEX);
			lsig(l);
			while(!lfin(l)){
				linfo(l,&ind);
				strcpy(d.cod,ind.clave);
				d.pos = ind.pos;
				d.flag = ind.flag;
				fwrite(&d,sizeof(d),1,INDEX);
				lsig(l);
			}
		}
	}
	fclose(INDEX);
}
//--------------------------------------------------------------------

void mostrarindice(tlista *l)
{
Tdatoindex x;

if(!lvacia_inx(l)){
	lppio_inx(l);
	linfo_inx(l,&x);
	printf("%d\n",x.clave);
	printf("%d\n",x.pos);
	printf("%c\n\n",x.flag);
	lsig_inx(l);
	while(!lfin_inx(l)){
		linfo_inx(l,&x);
		printf("%d\n",x.clave);
		printf("%d\n",x.pos);
		printf("%c\n\n",x.flag);
		lsig_inx(l);
	}
}else{
	printf("El indice esta vacio");
}

}

//--------------------------------------------------------------------

void mostrarindice_s(tlista_s *l)
{
Tdato_IString x;

if(!lvacia(l)){
	lppio(l);
	linfo(l,&x);
	printf("%s\n",x.clave);
	printf("%d\n",x.pos);
	printf("%c\n\n",x.flag);
	lsig(l);
	while(!lfin(l)){
		linfo(l,&x);
		printf("%s\n",x.clave);
		printf("%d\n",x.pos);
		printf("%c\n\n",x.flag);
		lsig(l);
	}
}else{
	printf("El indice esta vacio");
}

}