#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include <string> 
#include "LISTAINDEX.h"
#include "tdatoindex.h"

typedef struct reg {
	int cod;
	char descrip[256];
	float precio;
	int stock;
	int flag;
}Producto;

char Enter();
void Listado(char nom[256], tlista *l);
void Mostrar(Producto reg);
 
void Listado(char nom[256], tlista *l)
{
	FILE *F;

	if((F = fopen(nom, "rb")) == NULL){
		printf("No se encontro el archivo");
		Enter();
	}else{
		Tdatoindex d;
		Producto reg;

		if(!lvacia_inx(l)){
			lppio_inx(l);
			linfo_inx(l,&d);
			fseek(F,d.pos,0);
			fread(&reg,sizeof(reg),1,F);
			//GUARDAR EN ARCHIVIN
			Mostrar(reg);
			lsig_inx(l);
			while(!lfin_inx(l)){
				linfo_inx(l,&d);
				fseek(F,d.pos,0);
				fread(&reg,sizeof(reg),1,F);
				//GUARDAR EN ARCHIVIN
				Mostrar(reg);
				lsig_inx(l);
			}
		}else{
			printf("Indice No Creado");
			Enter();
		}
		fclose(F);
	}
}

void Mostrar(Producto reg)
{
	printf("%d",reg.cod);
	printf("%s",reg.descrip);
	printf("%f",reg.precio);
	printf("%d",reg.stock);
}