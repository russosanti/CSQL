#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string> 
//#include "LISTAINDEX.h"
//#include "tdatoindex.h"
#include "Listado.cpp"

//typedef struct prod {
//	int cod;
//	char descrip[256];
//	float precio;
//	int stock;
//	int flag;
//}Producto;

typedef struct indice{
	int cod;
	long pos;
	char flag;
}Index;
 

void backup(char nom1[256],char nom2[256]);
void backMAESTRO(char nom[256]);
void backINDICE(char nom[256]);
void cargarindice(tlista *l, char nom[256]);
int crear_archivos(char nom1[256],char nom2[256]);
char Enter();
int abrir(FILE *F, char nombre[36]);
int cargar_maestro(char nom[256]);
void borrarindice(tlista *l);
void maestroalista(tlista *l, char nom[256]);
void grabarindice(tlista *l, char nom[256]);
void mostrarindice(tlista *l);
void Listado(char nom[256], tlista *l);
void Mostrar(Producto reg);


int main()
{
	int opc = 0;
	tlista indice;
	FILE *MAE = NULL;
	FILE *INDEX = NULL;

	backup("MAESTRO","INDICE"); //se realiza el backup del maestro y los indices
	
	lcrear_inx(&indice);
	if(abrir(INDEX,"INDICE")){
		cargarindice(&indice,"INDICE"); //carga el indice
	}else{
		printf("Error al abrir los archivos, intente crearlos nuevamente");
		Enter();
	}

	while(opc != 99){
		system("cls");
		printf("\n\t\t¿Que desea Hacer?\n\n");
		printf("\t\t1.Crear Archivos\n");
		printf("\t\t2.Cargar Maestro\n");
		printf("\t\t3.Crear Indice\n");
		printf("\t\t4.Backup\n");
		printf("\t\t5.Mostrar Indice\n");
		printf("\t\t6.Mostrar Listado\n");
		printf("\n\t\t99.Salir\n");
		printf("\n\t\OPCIÓN: ");
		scanf("%d", &opc);
		fflush(stdin);
		printf("\n\n");
		switch(opc){
			
			case 1:
				crear_archivos("MAESTRO","INDICE"); //crea los archivos necesarios
			break;

			case 2:
				
				if(abrir(MAE,"MAESTRO")){
					if(cargar_maestro("MAESTRO")){//carga el archivo maestro
						borrarindice(&indice);
						maestroalista(&indice,"MAESTRO");
						grabarindice(&indice,"INDICE");
					}
				}else{
					printf("Error al abrir los archivos, intente crearlos nuevamente");
					Enter();
				}
			break;
			
			case 3:
				if(abrir(MAE,"MAESTRO") && abrir(INDEX,"INDICE")){
					borrarindice(&indice);
					maestroalista(&indice,"MAESTRO");
					grabarindice(&indice,"INDICE");
				}else{
					printf("Error al abrir los archivos, intente crearlos nuevamente");
					Enter();
				}
			break;

			case 4:
				backup("MAESTRO","INDICE");
			break;

			case 5:
				mostrarindice(&indice);
				Enter();
			break;

			case 6:
				Listado("MAESTRO",&indice);
		}
	}
	if(abrir(MAE,"MAESTRO")){
		grabarindice(&indice,"INDICE");
	}else{
		printf("Por errores internos graves no se grabara la lista");
	}
	return(0);
}
//--------------------------------------------------------------------

//Pregunta si se quiere realizar un backup
void backup(char nom1[256],char nom2[256])
{
	char resp = 'S';
	//rename("MAESTRO","MAESTRO_BKUP");
	printf("Quiere hacer un backup?\n");
	printf("Esto puede durar unos minutos\n");
	printf(" S (Si)   N (No)   :\n");
	scanf("%c",&resp);
	system("cls");
	while(resp != 's' && resp != 'S' && resp != 'n' && resp != 'N'){
		printf("Ingrese 'S' si quiere realizar un backup o 'N' si no desea\n");
		scanf("%c",&resp);
	}

	if(resp=='s' || resp=='S'){
		printf("Aguarde mientras se realiza el backup...");
		Enter();
		backMAESTRO(nom1);
		backINDICE(nom2);
	}else{
		printf("Si quiere realizar el backup puede seleccionarlo desde el menu");
		Enter();
		system("cls");
	}
}
//--------------------------------------------------------------------

//Copia el maestro pasado por nom a su backup
void backMAESTRO(char nom[256])
{
	Producto x;
	FILE *F;
	FILE *FBK;
	char bak[262];
	strcpy(bak,nom);
	strcat(bak,"_BKUP");

	if((F = fopen(nom, "rb+")) == NULL){
		printf("El archivo MAESTRO de origen no puede abrirse\nAsegurese que este creado");
		Enter();
	}else{
		if((FBK = fopen(bak, "wb")) == NULL){
			printf("El archivo MAESTRO para backup no pudo ser creado\nIntente nuevamente mas tarde");
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
//--------------------------------------------------------------------

//Copia el Indice pasado por nom a su backup
void backINDICE(char nom[256])
{
	Index x;
	FILE *F;
	FILE *FBK;
	char bak[262];
	strcpy(bak,nom);
	strcat(bak,"_BKUP");

	if((F = fopen(nom, "rb+")) == NULL){
		printf("El archivo INDICE de origen no puede abrirse\nAsegurese que este creado");
		Enter();
	}else{
		if((FBK = fopen(bak, "wb")) == NULL){
			printf("El archivo INDICE para backup no pudo ser creado\nIntente nuevamente mas tarde");
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
//--------------------------------------------------------------------

//Carga el indice del archivo a la lista
void cargarindice(tlista *l, char nom[256])
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
			ind.act = d.flag;
			linsertarorden_inx(l,ind,'a');
			pos = pos + sizeof(d);
			fread(&d,sizeof(d),1,INDEX);
		}
	}
	fclose(INDEX);
}
//--------------------------------------------------------------------

//Crea los archivos necesarios para trabajar en caso q no esten creados
int crear_archivos(char nom1[256], char nom2[256])
{
	FILE *MAE;
	FILE *INDEX;
	if((MAE = fopen(nom1, "rb+")) == NULL){
		if((MAE = fopen(nom1, "wb+")) == NULL){
			printf("Error al crear el archivo MAESTRO");
			Enter();
			exit(0);
		}else{
			fclose(MAE);
		}
	}else{
		printf("El archivo MAESTRO ya ha sido creado");
		Enter();
	}
	if((INDEX = fopen(nom2, "rb+")) == NULL){
		if((INDEX = fopen(nom2, "wb+")) == NULL){
			printf("Error al crear el archivo INDICE");
			Enter();
			exit(0);
		}else{
			fclose(INDEX);
		}
	}else{
		printf("El archivo INDICE ya ha sido creado");
		Enter();

	}
	return(0);
}

//Se fija si puede abrir el archivo
int abrir(FILE *F, char nombre[36])
{
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

//Carga el maestro con datos
int cargar_maestro(char nom[256])
{
	FILE *MAE;
	Producto p;
	
	if((MAE = fopen(nom, "rb+")) == NULL){
		printf("Pruebe crear el archivo primero");
		Enter();
		return(0);
	}else{
		system("cls");
		fseek(MAE,0L,SEEK_END);
		printf("Codigo (Salir 0): ");
		scanf("%d",&p.cod);
		fflush(stdin);
		while(p.cod != 0){
			printf("Descripcion: ");
			gets(p.descrip);
			fflush(stdin);
			printf("Flag: ");
			scanf("%d",&p.flag);
			fflush(stdin);
			printf("Precio: ");
			scanf("%f",&p.precio);
			fflush(stdin);
			printf("Stock: ");
			scanf("%d",&p.stock);
			fflush(stdin);
			fwrite(&p,sizeof(p),1,MAE);
			system("cls");
			printf("Codigo: (0 Para Salir)");
			scanf("%d",&p.cod);
			fflush(stdin);
		}
		fclose(MAE);
		return(1);
	}
}
//--------------------------------------------------------------------

void borrarindice(tlista *l)
{
	while(!lvacia_inx(l)){
		lborrarppio_inx(l);
	}

}


//Para crear el indice carga el maestro ordenandolo en la lista
void maestroalista(tlista *l, char nom[256])
{
	FILE *MAE;
	Producto p;
	Tdatoindex d;
	long pos = 0;
	
	if((MAE = fopen(nom, "rb+")) == NULL){
		printf("Pruebe crear el archivo primero");
		Enter();
	}else{
		fseek(MAE,0,0);
		fread(&p,sizeof(p),1,MAE);
		while(!feof(MAE)){
			d.clave = p.cod;
			d.pos = pos;
			d.act = p.flag;
			linsertarorden_inx(l,d,'a');
			pos = pos + sizeof(p);
			fread(&p,sizeof(p),1,MAE);
		}
	}
	fclose(MAE);
}
//--------------------------------------------------------------------

//Graba el indice en la lista en un archivo
void grabarindice(tlista *l, char nom[256])
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
			d.flag = ind.act;
			fwrite(&d,sizeof(d),1,INDEX);
			lsig_inx(l);
			while(!lfin_inx(l)){
				linfo_inx(l,&ind);
				d.cod = ind.clave;
				d.pos = ind.pos;
				d.flag = ind.act;
				fwrite(&d,sizeof(d),1,INDEX);
				lsig_inx(l);
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
	printf("%c\n\n",x.act);
	lsig_inx(l);
	while(!lfin_inx(l)){
		linfo_inx(l,&x);
		printf("%d\n",x.clave);
		printf("%d\n",x.pos);
		printf("%c\n\n",x.act);
		lsig_inx(l);
	}
}else{
	printf("El indice esta vacio");
}

}