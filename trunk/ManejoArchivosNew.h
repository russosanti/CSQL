#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
#include <string> 



#include "LISTAINDEX.h"		// clave numerica
#include "tdatoindex.h"
#include "listas.h"			// clabe alfanumerica
#include "tdatols.h"
#include "TIPOS.h"
#define nom_ext_indice "_idx"	// Extensión de archivo Indice Primario
#define nom_ext_ind2 "_id2"		// Extensión de archivo Indice Secundario


void backup(char nom[128],int longreg);
void BackUpArchivo(char nom[128],int longreg);
void BackupArchGenerico(char nom[128],int longreg);
int cargarindice(tlista *l, char nom[128]);
int cargarindice_s(tlista_s *l, char nom[128]);
int crear_archivos(char nom[]);
int crear_archivo(char nom[128]);
char Enter();
void clrbuf();
int abrir(char nombre[36]);
int cargar_Libros(char nom[128]);
int cargar_Temas(char nom[128]);
int cargar_Autores(char nom[128]);
int cargar_Socios(char nom[128]);
int cargar_Prestamos(char nom[128]);
void borrarindice(tlista *l);
void borrarindice_s(tlista_s *l);
int LibroALista(tlista *l, tlista_s *s, char nom[128]);
int TemaALista(tlista_s *l, char nom[128]);
int AutorALista(tlista_s *l, char nom[128]);
int SocioALista(tlista *l, tlista_s *s, char nom[128]);
int PrestamoALista(tlista *l, char nom[128]);
void grabarindice(tlista *l, char nom[128]);
int grabarindice_s(tlista_s *l, char nom[128]);
void mostrarindice(tlista *l);
void mostrarindice_s(tlista_s *l);
int cargar_reg_Libros(char nom[128], Libros arch);
int cargar_reg_Tema(char nom[128], Temas arch);
int cargar_reg_Autor(char nom[128], Autores arch);
int cargar_reg_Socio(char nom[128], Socios arch);
int cargar_reg_Prestamo(char nom[128], Prestamos arch);
int Listar(char nom[128],tlista_s *campos, char nom_campo_indice[128], char campo_comp[128],char valor_comp[128]);
int ListaLibros(char nom[128],tlista_s *l, char nom_campo_indice[128], char campo_comp[128],char valor_comp[128]);
int ListarLibroPorCodigo(char nom[128], tlista *l, tlista_s *campos, char campo_comp[128],char valor_comp[128]);
int ListarLibroPorTitulo(char nom[128], tlista_s *l, tlista_s *campos, char campo_comp[128],char valor_comp[128]);
int ListaCamposLibros(Libros arch, tlista_s *campos);
int ListaTemas(char nom[128],tlista_s *campos, char nom_campo_indice[128], char campo_comp[128],char valor_comp[128]);
int ListarTemaPorCodigo(char nom[128], tlista_s *l, tlista_s *campos, char campo_comp[128],char valor_comp[128]);
int ListaCamposTemas(Temas arch, tlista_s *campos);
int ListaAutores(char nom[128],tlista_s *campos, char nom_campo_indice[128], char campo_comp[128],char valor_comp[128]);
int ListarAutorPorCodigo(char nom[128], tlista_s *l, tlista_s *campos, char campo_comp[128],char valor_comp[128]);
int ListaCamposAutores(Autores arch, tlista_s *campos);
int ListaSocios(char nom[128],tlista_s *l, char nom_campo_indice[128], char campo_comp[128],char valor_comp[128]);
int ListarSocioPorCodigo(char nom[128], tlista *l, tlista_s *campos, char campo_comp[128],char valor_comp[128]);
int ListarSocioPorNYA(char nom[128], tlista_s *l, tlista_s *campos, char campo_comp[128],char valor_comp[128]);
int ListaCamposSocios(Socios arch, tlista_s *campos);
int ListaPrestamos(char nom[128],tlista_s *l, char nom_campo_indice[128], char campo_comp[128],char valor_comp[128]);
int ListarPrestamosPorCodigo(char nom[128], tlista *l, tlista_s *campos, char campo_comp[128],char valor_comp[128]);
int ListaCamposPrestamos(Prestamos arch, tlista_s *campos);
int ListaUnCampoLibros(Libros arch, Tclave nom_campo);
int ListaUnCampoTemas(Temas arch, Tclave nom_campo);
int ListaUnCampoAutores(Autores arch, Tclave nom_campo);
int ListaUnCampoSocios(Socios arch, Tclave nom_campo);
int ListaUnCampoPrestamos(Prestamos arch, Tclave nom_campo);
int valida_campo_contiene_en_Libros(Libros arch, char campo_comp[128],char valor_comp[128]);
int valida_campo_contiene_en_Temas(Temas arch, char campo_comp[128],char valor_comp[128]);
int valida_campo_contiene_en_Autores(Autores arch, char campo_comp[128],char valor_comp[128]);
int valida_campo_contiene_en_Socios(Socios arch, char campo_comp[128],char valor_comp[128]);
int valida_campo_contiene_en_Prestamos(Prestamos arch, char campo_comp[128],char valor_comp[128]);
int valida_campo(char nom[128], char nom_campo[128]);
int valida_nom_archivo(char nom[128]);
int EliminaLibros(char nom[128], char campo_comp[128],char valor_comp[128]);
void RecrearIndicesLibros(char nom[128]);
int VerificaRelacionesConLibros(Libros arch);
int ValidaContraPrestamos(char nom[128], char campo_comp[128],char valor_comp[128]);
int EliminaTemas(char nom[128], char campo_comp[128],char valor_comp[128]);
int VerificaRelacionesConTemas(Temas arch);
int ValidaContraLibros(char nom[128], char campo_comp[128],char valor_comp[128]);
void RecrearIndicesTemas(char nom[128]);
int EliminaAutores(char nom[128], char campo_comp[128],char valor_comp[128]);
int VerificaRelacionesConAutores(Autores arch);
void RecrearIndicesAutores(char nom[128]);
int EliminaSocios(char nom[128], char campo_comp[128],char valor_comp[128]);
int VerificaRelacionesConSocios(Socios arch);
void RecrearIndicesSocios(char nom[128]);
int EliminaPrestamos(char nom[128], char campo_comp[128],char valor_comp[128]);
int VerificaRelacionesConPrestamos(Prestamos arch);
void RecrearIndicesPrestamos(char nom[128]);
void incializar_archivos();
int InsertaLibros(char nom[128],tlista_s *campos);
int InsertaRegLibros(Libros *arch, tlista_s *campos);
int InsertaUnCampoLibros(Libros *arch, Tclave valor, long campo);
int InsertaTemas(char nom[128],tlista_s *campos);
int InsertaRegTemas(Temas *arch, tlista_s *campos);
int InsertaUnCampoTemas(Temas *arch, Tclave valor, long campo);
int InsertaAutores(char nom[128],tlista_s *campos);
int InsertaRegAutores(Autores *arch, tlista_s *campos);
int InsertaUnCampoAutores(Autores *arch, Tclave valor, long campo);
int InsertaSocios(char nom[128],tlista_s *campos);
int InsertaRegSocios(Socios *arch, tlista_s *campos);
int InsertaUnCampoSocios(Socios *arch, Tclave valor, long campo);
int InsertaPrestamos(char nom[128],tlista_s *campos);
int InsertaRegPrestamos(Prestamos *arch, tlista_s *campos);
int InsertaUnCampoPrestamos(Prestamos *arch, Tclave valor, long campo);
int ListarTituloSocio(char nom[128], tlista_s *campos);
int ListaTituloUnCampoSocios(Tclave nom_campo);
int ListarTituloLibro(char nom[128], tlista_s *campos);
int ListaTituloUnCampoLibros(Tclave nom_campo);
int ListarTituloTema(char nom[128], tlista_s *campos);
int ListaTituloUnCampoTemas(Tclave nom_campo);
int ListarTituloAutor(char nom[128], tlista_s *campos);
int ListaTituloUnCampoAutores(Tclave nom_campo);
int ListarTituloPrestamo(char nom[128], tlista_s *campos);
int ListaTituloUnCampoPrestamos(Tclave nom_campo);
int EditaLibros(char nom[128],tlista_s *campos, char campo_comp[128],char valor_comp[128]);
int EditaTemas(char nom[128],tlista_s *campos, char campo_comp[128],char valor_comp[128]);
int EditaAutores(char nom[128],tlista_s *campos, char campo_comp[128],char valor_comp[128]);
int EditaSocios(char nom[128],tlista_s *campos, char campo_comp[128],char valor_comp[128]);
int EditaPrestamos(char nom[128],tlista_s *campos, char campo_comp[128],char valor_comp[128]);
int ModificaLibros(Libros *arch, tlista_s *campos);
int ModificaUnCampoLibros(Libros *arch, Tclave valor, long campo);
int ModificaTemas(Temas *arch, tlista_s *campos);
int ModificaUnCampoTemas(Temas *arch, Tclave valor, long campo);
int ModificaAutores(Autores *arch, tlista_s *campos);
int ModificaUnCampoAutores(Autores *arch, Tclave valor, long campo);
int ModificaSocios(Socios *arch, tlista_s *campos);
int ModificaUnCampoSocios(Socios *arch, Tclave valor, long campo);
int ModificaPrestamos(Prestamos *arch, tlista_s *campos);
int ModificaUnCampoPrestamos(Prestamos *arch, Tclave valor, long campo);
int ClavePrincipalNoExiste(char nom[128], Tclaveindex valor);
int ClavePrincipalNoExiste_s(char nom[128], Tclave valor);
void RecuperaArchGenerico(char nom[128],int longreg);
int RecuperaArchivo(char nom[128],int longreg);
int LimpiaArchGenerico(char nom[128]);
int LimpiaArchAutores(char nom[128]);
int LimpiaArchSocios(char nom[128]);
int LimpiaArchLibros(char nom[128]);
int LimpiaArchTemas(char nom[128]);
int LimpiaArchPrestamos(char nom[128]);


char nom_indice_Libros[128];
char nom_ind_titulo[128];
char nom_indice_Temas[128];
char nom_indice_Prestamos[128];
char nom_indice_Autores[128];
char nom_indice_Socios[128];
char nom_ind_NYA[128];

char campo_comp[128] = "";
char valor_comp[128] = "";


int main0()
{
	int opc = 0;
	tlista		indice_Libros;
	tlista_s	ind_titulo;		// Indice del Titulo del Libro
	tlista_s	indice_Temas;
	tlista		indice_Prestamos;
	tlista_s	indice_Autores;
	tlista		indice_Socios;
	tlista_s	ind_NYA;		// Indice de Nombre y Apellido del Socio

	tlista_s  campos;		// campos a solicitar ("*" significa todos)

	incializar_archivos();  // inciala los nombres de los archivos.
	
	strcpy(nom_indice_Libros,nom_arch_Libros);
	strcat(nom_indice_Libros,nom_ext_indice);

	strcpy(nom_indice_Temas,nom_arch_Temas);
	strcat(nom_indice_Temas,nom_ext_indice);
	
	strcpy(nom_indice_Prestamos,nom_arch_Prestamos);
	strcat(nom_indice_Prestamos,nom_ext_indice);
	
	strcpy(nom_indice_Autores,nom_arch_Autores);
	strcat(nom_indice_Autores,nom_ext_indice);
	
	strcpy(nom_indice_Socios,nom_arch_Socios);
	strcat(nom_indice_Socios,nom_ext_indice);


	// Realiza los backups de los archivos e índices
/*	backup(nom_arch_Libros,sizeof(Libros),nom_indice_Libros);		// backup Libros e indice
	backup(nom_arch_Temas,sizeof(Temas),nom_indice_Temas);		// backup Temas e indice asociado
	backup(nom_arch_Prestamos,sizeof(Prestamos),nom_indice_Prestamos); // backup Prestamos e indice asociado
	backup(nom_arch_Autores,sizeof(Autores),nom_indice_Autores); // backup Autores e indice asociado
	backup(nom_arch_Socios,sizeof(Socios),nom_indice_Socios);		// backup Socios e indice asociado
*/


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
		printf("\t\t511.Mostrar Indice Libros\n");
		printf("\t\t512.Mostrar Indice Libros por Titulo\n");
		printf("\t\t52.Mostrar Indice Temas\n");
		printf("\t\t53.Mostrar Indice Autores\n");
		printf("\t\t541.Mostrar Indice Socios\n");
		printf("\t\t542.Mostrar Indice Socios por Nombre y Apellido\n");
		printf("\t\t55.Mostrar Indice Prestamos\n");
		printf("\t\t61.Lista Libros por indice y campos solicitados\n");
		printf("\t\t62.Lista Temas por indice y campos solicitados\n");
		printf("\t\t63.Lista Autores por indice y campos solicitados\n");
		printf("\t\t64.Lista Socios por indice y campos solicitados\n");
		printf("\t\t65.Lista Prestamos por indice y campos solicitados\n");
		printf("\n\t\t99.Salir\n");
		printf("\n\t\OPCIÓN: ");
		scanf("%d", &opc);
		fflush(stdin);
		printf("\n\n");
		switch(opc){
			
			case 1:	// crea los archivos e índices
				crear_archivos(nom_arch_Libros);
				crear_archivos(nom_arch_Temas);
				crear_archivos(nom_arch_Prestamos);
				crear_archivos(nom_arch_Autores);
				crear_archivos(nom_arch_Socios);
				break;

			case 21:	
				if(!cargar_Libros(nom_arch_Libros)){//carga el archivo Libros
					Enter();
				}
				break;
			
			case 22:
				if(!cargar_Temas(nom_arch_Temas)){   //carga el archivo Temas
					Enter();
				}
				break;
			
			case 23:
				if(!cargar_Autores(nom_arch_Autores)){  //carga el archivo Autores
					Enter();
				}
				break;
			
			case 24:
				if(!cargar_Socios(nom_arch_Socios)){  //carga el archivo Socios
					Enter();
				}
				break;
			
			case 25:	
				if(!cargar_Prestamos(nom_arch_Prestamos)){//carga el archivo Prestamos
					Enter();
				}
			break;
			
			case 31:
				if(abrir(nom_arch_Libros) && abrir(nom_indice_Libros)){
					borrarindice(&indice_Libros);
//					LibroALista(&indice_Libros,nom_arch_Libros);
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
//					SocioALista(&indice_Socios,nom_arch_Socios);
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
				backup(nom_arch_Libros,sizeof(Libros));		// backup Libros e indice
				backup(nom_arch_Temas,sizeof(Temas));		// backup Temas e indice asociado
				backup(nom_arch_Prestamos,sizeof(Prestamos)); // backup Prestamos e indice asociado
				backup(nom_arch_Autores,sizeof(Autores)); // backup Autores e indice asociado
				backup(nom_arch_Socios,sizeof(Socios));		// backup Socios e indice asociado
			break;

			case 511:	// indice principal de Libros
				lcrear_inx(&indice_Libros);
				if(abrir(nom_indice_Libros)){
					cargarindice(&indice_Libros,nom_indice_Libros); //carga el indice
					mostrarindice(&indice_Libros);
				}else{
					printf("Error al abrir los archivos, intente crearlos nuevamente");
				}
				Enter();
				break;
		
			case 512:	// indice alterno de Libros
				//Define el índice por Titulo
				strcpy(nom_ind_titulo,nom_arch_Libros);
				strcat(nom_ind_titulo,nom_ext_ind2);

				lcrear(&ind_titulo);
				if(abrir(nom_ind_titulo)){
					cargarindice_s(&ind_titulo,nom_ind_titulo); //carga el indice
					mostrarindice_s(&ind_titulo);
				}else{
					printf("Error al abrir los archivos, intente crearlos nuevamente");
				}
				Enter();
				break;

			case 52:
				lcrear(&indice_Temas);
				if(abrir(nom_indice_Temas)){
					cargarindice_s(&indice_Temas,nom_indice_Temas); //carga el indice
					mostrarindice_s(&indice_Temas);
				}else{
					printf("Error al abrir los archivos, intente crearlos nuevamente");
				}
				Enter();
				break;

			case 53:
				lcrear(&indice_Autores);
				if(abrir(nom_indice_Autores)){
					cargarindice_s(&indice_Autores,nom_indice_Autores); //carga el indice
					mostrarindice_s(&indice_Autores);
				}else{
					printf("Error al abrir los archivos, intente crearlos nuevamente");
				}
				Enter();
				break;

			case 541:
				lcrear_inx(&indice_Socios);
				if(abrir(nom_indice_Socios)){
					cargarindice(&indice_Socios,nom_indice_Socios); //carga el indice
					mostrarindice(&indice_Socios);
				}else{
					printf("Error al abrir los archivos, intente crearlos nuevamente");
				}
				Enter();
				break;

			case 542:
				//Define el índice por Nombre y Apellido
				strcpy(nom_ind_NYA,nom_arch_Socios);
				strcat(nom_ind_NYA,nom_ext_ind2);

				lcrear(&ind_NYA);
				if(abrir(nom_ind_NYA)){
					cargarindice_s(&ind_NYA,nom_ind_NYA); //carga el indice
					mostrarindice_s(&ind_NYA);
				}else{
					printf("Error al abrir los archivos, intente crearlos nuevamente");
				}
				Enter();
				break;

			case 55:
				lcrear_inx(&indice_Prestamos);
				if(abrir(nom_indice_Prestamos)){
					cargarindice(&indice_Prestamos,nom_indice_Prestamos); //carga el indice
					mostrarindice(&indice_Prestamos);
				}else{
					printf("Error al abrir los archivos, intente crearlos nuevamente");
				}
				Enter();
				break;

			case 61:	// lista libros por indice solicitado y campos solicitados
				Listar(nom_arch_Libros, &campos, "titulo", campo_comp, valor_comp);
				Enter();
				break;

			case 62:	// lista temas por indice solicitado y campos solicitados
				Listar(nom_arch_Temas, &campos, "cod", campo_comp, valor_comp);
				Enter();
				break;

			case 63:	// lista autores por indice solicitado y campos solicitados
				Listar(nom_arch_Autores, &campos, "cod", campo_comp, valor_comp);
				Enter();
				break;

			case 64:	// lista socios por indice solicitado y campos solicitados
				Listar(nom_arch_Socios, &campos, "nombreyapellido", campo_comp, valor_comp);
				Enter();
				break;

			case 65:	// lista socios por indice solicitado y campos solicitados
				Listar(nom_arch_Prestamos, &campos, "cod", campo_comp, valor_comp);
				Enter();
				break;

		}
	}
	return(0);
}
//--------------------------------------------------------------------

//Pregunta si se quiere realizar un backup
void backup(char nom[128],int longreg)
{
	char nom_indice[128];
	char resp = 'S';

	printf("Quiere hacer un backup de %s?\n",nom);
	printf("Esto puede durar unos minutos\n");
	printf(" S (Si)   N (No)   :\n");
	scanf("%c",&resp);
	system("cls");
	while(resp != 's' && resp != 'S' && resp != 'n' && resp != 'N'){
		printf("Ingrese 'S' si quiere realizar un backup o 'N' si no desea\n");
		scanf("%c",&resp);
	}

	if(resp=='s' || resp=='S'){
		printf("Aguarde mientras se realiza el backup de %s...",nom);
		Enter();
		BackupArchGenerico(nom, longreg);
	}else{
		printf("Si quiere realizar el backup puede seleccionarlo desde el menu");
		Enter();
		system("cls");
	}
}
// backup de un archivo genérico
void BackupArchGenerico(char nom[128],int longreg)
{
	char nom_indice[128];

	// backup archivo ppal
	BackUpArchivo(nom,longreg);			

	// backup archivo indice del ppal
	strcpy(nom_indice,nom);
	strcat(nom_indice,nom_ext_indice);

	if ((stricmp(nom,nom_arch_Temas) == 0) || (stricmp(nom,nom_arch_Autores) == 0)){
		BackUpArchivo(nom_indice,sizeof(IndexS));		
	}else{
		BackUpArchivo(nom_indice,sizeof(Index));		// backup archivo indice del ppal
	}
		
	// backup archivo indice secundario de algunos archivos
	if ((stricmp(nom,nom_arch_Libros) == 0) || (stricmp(nom,nom_arch_Socios) == 0)){	
		strcpy(nom_indice,nom);
		strcat(nom_indice,nom_ext_ind2);	
		BackUpArchivo(nom_indice,sizeof(IndexS));		
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

// recupera archivo genérico
void RecuperaArchGenerico(char nom[128],int longreg)
{
	// recupera archivo ppal
	if (RecuperaArchivo(nom,longreg) == 0){

		if (stricmp(nom,nom_arch_Temas) == 0)
			RecrearIndicesTemas(nom);
	
		if (stricmp(nom,nom_arch_Autores) == 0)
			RecrearIndicesAutores(nom);
	
		if (stricmp(nom,nom_arch_Prestamos) == 0)
			RecrearIndicesPrestamos(nom);
	
		if (stricmp(nom,nom_arch_Libros) == 0)
			RecrearIndicesLibros(nom);
	
		if (stricmp(nom,nom_arch_Socios) == 0)
			RecrearIndicesSocios(nom);
	}
}

//--------------------------------------------------------------------
//Recupera archivo del backup
int RecuperaArchivo(char nom[128],int longreg)
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

	if((F = fopen(bak, "rb")) == NULL){
		printf("El archivo %s de backup no existe.\nNo puede recuperar la informacion.\n",bak);
		return(1);
		Enter();
	}else{
		if((FBK = fopen(nom, "wb")) == NULL){
			printf("El archivo %s no puede ser recuperado del backup\nIntente nuevamente mas tarde",nom);
			fclose(F);
			Enter();
			return(1);
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
	return(0);
}
// reorganiza archivo genérico
int LimpiaArchGenerico(char nom[128])
{
	// recupera archivo ppal
	if (stricmp(nom,nom_arch_Temas) == 0)
		if (LimpiaArchTemas(nom) == 0){
			RecrearIndicesTemas(nom);
			return(0);
		}
		
	if (stricmp(nom,nom_arch_Autores) == 0)
		if (LimpiaArchAutores(nom) == 0){
			RecrearIndicesAutores(nom);
			return(0);
		}

	if (stricmp(nom,nom_arch_Prestamos) == 0)
		if (LimpiaArchPrestamos(nom) == 0){
			RecrearIndicesPrestamos(nom);
			return(0);
		}
	
	if (stricmp(nom,nom_arch_Libros) == 0)
		if (LimpiaArchLibros(nom) == 0){
			RecrearIndicesLibros(nom);
			return(0);
		}
	
	if (stricmp(nom,nom_arch_Socios) == 0)
		if (LimpiaArchSocios(nom) == 0){
			RecrearIndicesSocios(nom);
			return(0);
		}

	return(1);
}
//--------------------------------------------------------------------
//Recupera archivo del backup
int LimpiaArchTemas(char nom[128])
{
	Temas arch;

	BackupArchGenerico(nom,sizeof(Temas));		

	FILE *F;
	FILE *FBK;
	char bak[262];
	strcpy(bak,nom);
	strcat(bak,"_BKUP");

	if((F = fopen(bak, "rb")) == NULL){
		return(1);
	}else{
		if((FBK = fopen(nom, "wb")) == NULL){
			fclose(F);
			return(1);
		}else{
			fseek(F,0L,0);
			fseek(FBK,0L,0);
			fread(&arch,sizeof(arch),1,F);
			while(!feof(F)){
				if ((arch.flag == 'v') || (arch.flag == 'V'))  
					fwrite(&arch,sizeof(arch),1,FBK);
				fread(&arch,sizeof(arch),1,F);
			}
			fclose(F);
			fclose(FBK);
		}
	}
	return(0);
}
//--------------------------------------------------------------------
//Recupera archivo del backup
int LimpiaArchAutores(char nom[128])
{
	Autores arch;

	BackupArchGenerico(nom,sizeof(Autores));		

	FILE *F;
	FILE *FBK;
	char bak[262];
	strcpy(bak,nom);
	strcat(bak,"_BKUP");

	if((F = fopen(bak, "rb")) == NULL){
		return(1);
	}else{
		if((FBK = fopen(nom, "wb")) == NULL){
			fclose(F);
			return(1);
		}else{
			fseek(F,0L,0);
			fseek(FBK,0L,0);
			fread(&arch,sizeof(arch),1,F);
			while(!feof(F)){
				if ((arch.flag == 'v') || (arch.flag == 'V'))  
					fwrite(&arch,sizeof(arch),1,FBK);
				fread(&arch,sizeof(arch),1,F);
			}
			fclose(F);
			fclose(FBK);
		}
	}
	return(0);
}
//--------------------------------------------------------------------
//Recupera archivo del backup
int LimpiaArchSocios(char nom[128])
{
	Socios arch;

	BackupArchGenerico(nom,sizeof(Socios));		

	FILE *F;
	FILE *FBK;
	char bak[262];
	strcpy(bak,nom);
	strcat(bak,"_BKUP");

	if((F = fopen(bak, "rb")) == NULL){
		return(1);
	}else{
		if((FBK = fopen(nom, "wb")) == NULL){
			fclose(F);
			return(1);
		}else{
			fseek(F,0L,0);
			fseek(FBK,0L,0);
			fread(&arch,sizeof(arch),1,F);
			while(!feof(F)){
				if ((arch.flag == 'v') || (arch.flag == 'V'))  
					fwrite(&arch,sizeof(arch),1,FBK);
				fread(&arch,sizeof(arch),1,F);
			}
			fclose(F);
			fclose(FBK);
		}
	}
	return(0);
}
//--------------------------------------------------------------------
//Recupera archivo del backup
int LimpiaArchLibros(char nom[128])
{
	Libros arch;

	BackupArchGenerico(nom,sizeof(Libros));		

	FILE *F;
	FILE *FBK;
	char bak[262];
	strcpy(bak,nom);
	strcat(bak,"_BKUP");

	if((F = fopen(bak, "rb")) == NULL){
		return(1);
	}else{
		if((FBK = fopen(nom, "wb")) == NULL){
			fclose(F);
			return(1);
		}else{
			fseek(F,0L,0);
			fseek(FBK,0L,0);
			fread(&arch,sizeof(arch),1,F);
			while(!feof(F)){
				if ((arch.flag == 'v') || (arch.flag == 'V'))  
					fwrite(&arch,sizeof(arch),1,FBK);
				fread(&arch,sizeof(arch),1,F);
			}
			fclose(F);
			fclose(FBK);
		}
	}
	return(0);
}
//--------------------------------------------------------------------
//Recupera archivo del backup
int LimpiaArchPrestamos(char nom[128])
{
	Prestamos arch;

	BackupArchGenerico(nom,sizeof(Prestamos));		

	FILE *F;
	FILE *FBK;
	char bak[262];
	strcpy(bak,nom);
	strcat(bak,"_BKUP");

	if((F = fopen(bak, "rb")) == NULL){
		return(1);
	}else{
		if((FBK = fopen(nom, "wb")) == NULL){
			fclose(F);
			return(1);
		}else{
			fseek(F,0L,0);
			fseek(FBK,0L,0);
			fread(&arch,sizeof(arch),1,F);
			while(!feof(F)){
				if ((arch.flag == 'v') || (arch.flag == 'V'))  
					fwrite(&arch,sizeof(arch),1,FBK);
				fread(&arch,sizeof(arch),1,F);
			}
			fclose(F);
			fclose(FBK);
		}
	}
	return(0);
}
//Carga el indice numerico del archivo a la lista
int cargarindice(tlista *l, char nom[128])
{
	FILE *INDEX;
	Index d;
	Tdatoindex ind;
	long pos = 0;
	
	if((INDEX = fopen(nom, "rb+")) == NULL){
		return(1);		// El archivo indice no existe
	}else{
		fseek(INDEX,0L,0);
		fread(&d,sizeof(d),1,INDEX);
		while(!feof(INDEX)){
			if ((d.flag == 'v') || (d.flag == 'V')){
				ind.clave = d.cod;
				ind.pos = d.pos;
				ind.flag = d.flag;
				linsertarorden_inx(l,ind,'a');
			}
			pos = pos + sizeof(d);
			fread(&d,sizeof(d),1,INDEX);
		}
		fclose(INDEX);
		return(0);
	}
}
//Carga el indice Tipo String del archivo a la Lista String
int cargarindice_s(tlista_s *l, char nom[128])
{
	FILE *INDEX;
	IndexS d;
	Tdato_IString ind;
	long pos = 0;
	
	if((INDEX = fopen(nom, "rb+")) == NULL){
		return(1);		// El archivo indice no existe
	}else{
		fseek(INDEX,0L,0);
		fread(&d,sizeof(d),1,INDEX);
		while(!feof(INDEX)){
			if ((d.flag == 'v') || (d.flag == 'V')){
				strcpy(ind.clave,d.cod);
				ind.pos = d.pos;
				ind.flag = d.flag;
				linsertarorden(l,ind,'a');
			}
			pos = pos + sizeof(d);
			fread(&d,sizeof(d),1,INDEX);
		}
		fclose(INDEX);
		return(0);
	}
}

//--------------------------------------------------------------------
//Crea el archivo y sus índices en caso que no esten creados
int crear_archivos(char nom[])
{
	char nom_indice[128];

	crear_archivo(nom);				// crear archivo maestro
	strcpy(nom_indice,nom);
	strcat(nom_indice,nom_ext_indice);
	crear_archivo(nom_indice);		// crear indice principal
	if ((stricmp(nom,nom_arch_Libros) == 0) || (stricmp(nom,nom_arch_Socios) == 0)){	
		strcpy(nom_indice,nom);
		strcat(nom_indice,nom_ext_ind2);	
		crear_archivo(nom_indice);		// crear indice alternativo
	}	
	return(0);
}

//--------------------------------------------------------------------
//Crea un archivo
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
int cargar_Libros(char nom[128])
{
	Libros arch;
	int existe;
	tlista_s l_tema;
	char nom_indice_tema[128];
	tlista_s l_autor;
	char nom_indice_autor[128];

	strcpy(nom_indice_tema,nom_arch_Temas);
	strcat(nom_indice_tema,nom_ext_indice);
	lcrear(&l_tema);
	if(cargarindice_s(&l_tema,nom_indice_tema) != 0){   //carga el indice
		return(3); // Error al abrir el archivo de Indices
	}

	strcpy(nom_indice_autor,nom_arch_Autores);
	strcat(nom_indice_autor,nom_ext_indice);
	lcrear(&l_autor);
	if(cargarindice_s(&l_autor,nom_indice_autor) != 0){   //carga el indice
		return(3); // Error al abrir el archivo de Indices
	}

	system("cls");
	printf("Codigo Libro (Salir 0): ");
	scanf("%d",&arch.cod);
	fflush(stdin);
	while(arch.cod != 0){
		printf("Codigo Tema: ");
		gets(arch.cod_tema);
		fflush(stdin);				
		// Validar que el tema ingresado es valido
		lbuscar(&l_tema,arch.cod_tema,&existe);
		if (!existe){
			printf("El tema '%s' ingresado no existe en la base.\nIngrese uno valido\n",arch.cod_tema);
			Enter();
		}else{
			printf("Codigo Autor: ");
			gets(arch.cod_autor);
			fflush(stdin);
			// Validar que el autor ingresado es valido
			lbuscar(&l_autor,arch.cod_autor,&existe);
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
				if (cargar_reg_Libros(nom, arch) != 0){
					printf("Error al cargar el Libro %d", arch.cod);
					Enter();
				}
			}
		}
		system("cls");
		printf("Codigo Libro (Salir 0): ");
		scanf("%d",&arch.cod);
		fflush(stdin);
	}
	return(1);
}

//--------------------------------------------------------------------
//Carga el archivo Temas con datos
int cargar_Temas(char nom[128])
{
	Temas arch;

	system("cls");
	printf("Tema (Salir con blancos): ");
	gets(arch.cod);
	fflush(stdin);
	while(strlen(arch.cod) > 0){
		printf("Flag: ");
		scanf("%c",&arch.flag);
		fflush(stdin);
		if (cargar_reg_Tema(nom, arch) != 0){
			printf("Error al cargar el Tema %s", arch.cod);
			Enter();
		}
		system("cls");
		printf("Tema (Salir con blancos): ");
		gets(arch.cod);
		fflush(stdin);
	}
	return(1);
}


//--------------------------------------------------------------------
//Carga el archivo Autores con datos
int cargar_Autores(char nom[128])
{
	Autores arch;

	system("cls");
	printf("Autor (Salir con blancos): ");
	gets(arch.cod);
	fflush(stdin);
	while(strlen(arch.cod) > 0){
		printf("Flag: ");
		scanf("%c",&arch.flag);
		fflush(stdin);
		if (cargar_reg_Autor(nom, arch) != 0){
			printf("Error al cargar el Autor %s", arch.cod);
			Enter();
		}
		system("cls");
		printf("Autor (Salir con blancos): ");
		gets(arch.cod);
		fflush(stdin);
	}
	return(1);
}

//--------------------------------------------------------------------
//Carga el archivo Socios con datos
int cargar_Socios(char nom[128])
{
	Socios arch;

	system("cls");
	printf("Nro de Socio (Salir con '0'): ");
	scanf("%d",&arch.cod);
	fflush(stdin);
	while(arch.cod != 0){
		printf("Nombre y apellido del socio: ");
		gets(arch.nombreyapellido);
		fflush(stdin);
		printf("DNI: ");
		scanf("%d",&arch.dni);
		fflush(stdin);
		printf("Direccion: ");
		gets(arch.direccion);
		fflush(stdin);
		printf("Flag: ");
		scanf("%c",&arch.flag);
		fflush(stdin);
		if (cargar_reg_Socio(nom, arch) != 0){
			printf("Error al cargar el Socio %d", arch.cod);
			Enter();
		}
		system("cls");
		printf("Nro de Socio (Salir con '0'): ");
		scanf("%d",&arch.cod);
		fflush(stdin);
	}
	return(1);
}

//--------------------------------------------------------------------
//Carga el archivo Prestamos con datos
int cargar_Prestamos(char nom[128])
{
	Prestamos arch;
	int existe;
	tlista l_socio;
	char nom_indice_socio[128];
	tlista l_libro;
	char nom_indice_libro[128];

	strcpy(nom_indice_socio,nom_arch_Socios);
	strcat(nom_indice_socio,nom_ext_indice);
	lcrear_inx(&l_socio);
	if(cargarindice(&l_socio,nom_indice_socio) != 0){   //carga el indice
		return(3); // Error al abrir el archivo de Indices
	}

	strcpy(nom_indice_libro,nom_arch_Libros);
	strcat(nom_indice_libro,nom_ext_indice);
	lcrear_inx(&l_libro);
	if(cargarindice(&l_libro,nom_indice_libro) != 0){   //carga el indice
		return(3); // Error al abrir el archivo de Indices
	}

	system("cls");
	printf("Codigo Prestamo (Salir 0): ");
	scanf("%d",&arch.cod);
	fflush(stdin);
	while(arch.cod != 0){
		printf("Codigo de Socio: ");
		scanf("%d",&arch.cod_socio);
		fflush(stdin);
		// Validar que el socio ingresado es valido
		lbuscar_inx(&l_socio,arch.cod_socio,&existe);
		if (!existe){
			printf("El socio '%d' ingresado no existe en la base.\nIngrese uno valido\n",arch.cod_socio);
			Enter();
		}else{
			printf("Codigo de Libro: ");
			scanf("%d",&arch.cod_libro);
			fflush(stdin);
			// Validar que el libro ingresado es valido
			lbuscar_inx(&l_libro,arch.cod_libro,&existe);
			if (!existe){
				printf("El libro '%d' ingresado no existe en la base.\nIngrese uno valido\n",arch.cod_libro);
				Enter();
			}else{
				printf("Flag: ");
				scanf("%c",&arch.flag);
				fflush(stdin);
				if (cargar_reg_Prestamo(nom, arch) != 0){
					printf("Error al cargar el Prestamo %d", arch.cod);
					Enter();
				}
			}
		}
		system("cls");
		printf("Codigo Prestamo (Salir 0): ");
		scanf("%d",&arch.cod);
		fflush(stdin);
	}
	return(1);
}

//--------------------------------------------------------------------

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

//Para crear los indices carga el archivo Libros ordenandolo en las listas
// una lista ordenada para el codigo y otra para el titulo
int LibroALista(tlista *l, tlista_s *s, char nom[128])
{
	FILE *ARCHIVO;
	Libros arch;
	Tdatoindex d;			// indice clave primaria Cod de Libro
	Tdato_IString ind_titulo;	// indice clave secundaria Título de Libro

	long pos = 0;
	if((ARCHIVO = fopen(nom, "rb+")) == NULL){
		return(1);
	}else{
		fseek(ARCHIVO,0,0);
		fread(&arch,sizeof(arch),1,ARCHIVO);
		while(!feof(ARCHIVO)){
			if ((arch.flag == 'v') || (arch.flag == 'V')){
			// inserta en clave primaria Cod de Libro
				d.clave = arch.cod;
				d.pos = pos;
				d.flag = arch.flag;
				linsertarorden_inx(l,d,'a');
			// inserta en clave secundaria Título de Libro
				strcpy(ind_titulo.clave,arch.titulo);
				ind_titulo.pos = pos;
				ind_titulo.flag = arch.flag;
				linsertarorden(s,ind_titulo,'a');
			}
			pos = pos + sizeof(arch);
			fread(&arch,sizeof(arch),1,ARCHIVO);
		}
		fclose(ARCHIVO);
		return(0);
	}
}

//Para crear el indice carga el archivo Temas ordenandolo en la lista
int TemaALista(tlista_s *l, char nom[128])
{
	FILE *ARCHIVO;
	Temas arch;
	Tdato_IString d;
	long pos = 0;
	if((ARCHIVO = fopen(nom, "rb+")) == NULL){
		return(1);
	}else{
		fseek(ARCHIVO,0,0);
		fread(&arch,sizeof(arch),1,ARCHIVO);
		while(!feof(ARCHIVO)){
			if ((arch.flag == 'v') || (arch.flag == 'V')){
				strcpy(d.clave,arch.cod);
				d.pos = pos;
				d.flag = arch.flag;
				linsertarorden(l,d,'a');
			}
			pos = pos + sizeof(arch);
			fread(&arch,sizeof(arch),1,ARCHIVO);
		}
		fclose(ARCHIVO);
		return(0);
	}
}

//Para crear el indice carga el archivo Prestamos ordenandolo en la lista
int PrestamoALista(tlista *l, char nom[128])
{
	FILE *ARCHIVO;
	Prestamos arch;
	Tdatoindex d;
	long pos = 0;
	if((ARCHIVO = fopen(nom, "rb+")) == NULL){
		return(1);
	}else{
		fseek(ARCHIVO,0,0);
		fread(&arch,sizeof(arch),1,ARCHIVO);
		while(!feof(ARCHIVO)){
			if ((arch.flag == 'v') || (arch.flag == 'V')){
				d.clave = arch.cod;
				d.pos = pos;
				d.flag = arch.flag;
				linsertarorden_inx(l,d,'a');
			}
			pos = pos + sizeof(arch);
			fread(&arch,sizeof(arch),1,ARCHIVO);
		}
		fclose(ARCHIVO);
		return(0);
	}
}

//Para crear el indice carga el archivo Autores ordenandolo en la lista
int AutorALista(tlista_s *l, char nom[128])
{
	FILE *ARCHIVO;
	Autores arch;
	Tdato_IString d;
	long pos = 0;
	if((ARCHIVO = fopen(nom, "rb+")) == NULL){
		return(1);
	}else{
		fseek(ARCHIVO,0,0);
		fread(&arch,sizeof(arch),1,ARCHIVO);
		while(!feof(ARCHIVO)){
			if ((arch.flag == 'v') || (arch.flag == 'V')){
				strcpy(d.clave,arch.cod);
				d.pos = pos;
				d.flag = arch.flag;
				linsertarorden(l,d,'a');
			}
			pos = pos + sizeof(arch);
			fread(&arch,sizeof(arch),1,ARCHIVO);
		}
		fclose(ARCHIVO);
		return(0);
	}
}

//Para crear el indice carga el archivo Socios ordenandolo en la lista
int SocioALista(tlista *l, tlista_s *s, char nom[128])
{
	FILE *ARCHIVO;
	Socios arch;
	Tdatoindex d;
	Tdato_IString ind_NYA;	// clave secundaria Nombre y Apellido del Socio

	long pos = 0;
	if((ARCHIVO = fopen(nom, "rb+")) == NULL){
		return(1);
	}else{
		fseek(ARCHIVO,0,0);
		fread(&arch,sizeof(arch),1,ARCHIVO);
		while(!feof(ARCHIVO)){
			if ((arch.flag == 'v') || (arch.flag == 'V')){
				d.clave = arch.cod;
				d.pos = pos;
				d.flag = arch.flag;
				linsertarorden_inx(l,d,'a');

				// inserta en clave secundaria Título de Libro
				strcpy(ind_NYA.clave,arch.nombreyapellido);
				ind_NYA.pos = pos;
				ind_NYA.flag = arch.flag;
				linsertarorden(s,ind_NYA,'a');
			}
			pos = pos + sizeof(arch);
			fread(&arch,sizeof(arch),1,ARCHIVO);
		}
		fclose(ARCHIVO);
		return(0);
	}
}

// Insertar registros de tablas 
int Insertar(char nom[128],tlista_s *campos)
{
	if (valida_nom_archivo(nom) != 0)  // Verifica que es un archivo de la base
		return(1);

	if(stricmp(nom,nom_arch_Autores)==0)
		if (InsertaAutores(nom, campos) != 0){
			return(2);
		}		
	if(stricmp(nom,nom_arch_Libros)==0)
		if (InsertaLibros(nom, campos) != 0){
			return(2);
		}		
	if(stricmp(nom,nom_arch_Socios)==0)
		if (InsertaSocios(nom, campos) != 0){
			return(2);
		}		
	if(stricmp(nom,nom_arch_Temas)==0)
		if (InsertaTemas(nom, campos) != 0){
			return(2);
		}		
	if(stricmp(nom,nom_arch_Prestamos)==0)
		if (InsertaPrestamos(nom, campos) != 0){
			return(2);
		}

	return(0);
}


// Inserta un registro en el archivo Libros 
//
int InsertaLibros(char nom[128],tlista_s *campos)
{
	Libros arch;

	if (InsertaRegLibros(&arch, campos) == 0){
		if (cargar_reg_Libros(nom, arch) == 0){
			printf("\nRegistro insertado en el archivo '%s'.\n", nom);	
			return(0);
		}
	}
	return(1);
}

// Modifica los campos solicitados del archivo Libros
int InsertaRegLibros(Libros *arch, tlista_s *campos)
{
	Tdato_IString x;

	// valores default
	arch->flag = 'V';
	arch->cod = -1;
	strcpy(arch->cod_autor,"");
	strcpy(arch->cod_tema,"");
	strcpy(arch->titulo,"");
	strcpy(arch->ubicacion,"");
	
	if(!lvacia(campos)){
		lppio(campos);
		linfo(campos,&x);
		if (InsertaUnCampoLibros(arch, x.clave, x.pos) != 0)
				return(1); // Campo invalido
		lsig(campos);
		while(!lfin(campos)){
			linfo(campos,&x);
			if (InsertaUnCampoLibros(arch, x.clave, x.pos) != 0)
				return(1); // Campo invalido
			lsig(campos);
		}
		if((arch->cod==-1) || (stricmp(arch->cod_autor,"")==0) || (stricmp(arch->cod_tema,"")==0)){
			return(1);
		}
		return(0);
	}else{
		return(3); // El indice esta vacio
	}
	
}

//--------------------------------------------------------------------
//Inserta un campo
int InsertaUnCampoLibros(Libros *arch, Tclave valor, long campo)
{
	// Debe validar si es el campo es clave primaria, que no exista ya en el archivo
	// para no crear clave duplicada
	char nom_campo[128];
	char campo_texto[128];
	long valor_num;

	switch (campo){
		case 1:		
			strcpy(nom_campo,"cod");	// convierte el nro en el nombre de campo equivalente
			valor_num = atoi(valor);
			if (valor_num != 0){	// el codigo no puede ser cero
				if (ClavePrincipalNoExiste(nom_arch_Libros, valor_num) == 0){
					arch->cod = valor_num;
					return(0);
				}else{
					printf("\nNo puede ingresar el registro porque ya existe uno con este codigo\n");	
				}
			}else{
				printf("\nNo puede ingresar una clave con valor cero o alfanumerico.\n");	
			}
			break;
	
		case 2:		
			strcpy(nom_campo,"cod_tema");	// convierte el nro en el nombre de campo equivalente
			if (ClavePrincipalNoExiste_s(nom_arch_Temas,valor) != 0){  // Deberia existir el Tema para poder ingresarlo en el Libro
				strcpy(arch->cod_tema,valor);
				return(0);
			}else{
				printf("\nEl tema '%s' debe ser ingresado previamente.\n",valor);	
			}
			break;
	
		case 3:		
			strcpy(nom_campo,"titulo");	// convierte el nro en el nombre de campo equivalente
			strcpy(arch->titulo,valor);
			return(0);
			break;
	
		case 4:		
			strcpy(nom_campo,"cod_autor");	// convierte el nro en el nombre de campo equivalente
			if (ClavePrincipalNoExiste_s(nom_arch_Autores,valor) != 0){  // Deberia existir el Autor para poder ingresarlo en el Libro
				strcpy(arch->cod_autor,valor);
				return(0);
			}else{
				printf("\nEl autor '%s' debe ser ingresado previamente.\n",valor);	
			}
			break;
	
		case 5:		
			strcpy(nom_campo,"ubicacion");	// convierte el nro en el nombre de campo equivalente
			strcpy(arch->ubicacion,valor);
			return(0);
			break;
	}
	return(1);	// retorna error en caso que no haya podido modificar el campo por cualquier motivo
}
//--------------------------------------------------------------------
//Cargar registro Libros
int cargar_reg_Libros(char nom[128], Libros arch)
{
	FILE *ARCHIVO;

	if (ClavePrincipalNoExiste(nom, arch.cod) == 0){
		if((ARCHIVO = fopen(nom, "rb+")) == NULL){
			return(1);		// El archivo no fue creado
		}else{
			fseek(ARCHIVO,0L,SEEK_END);
			fwrite(&arch,sizeof(arch),1,ARCHIVO);
			fclose(ARCHIVO);
			RecrearIndicesLibros(nom);  // recrea los índices del archivo libro antes de salir
			return(0);
		}
	}else{
		return(2); // ya existe la clave en la base 
	}
}

// Inserta un registro en el archivo Temas 
//
int InsertaTemas(char nom[128],tlista_s *campos)
{
	Temas arch;

	if (InsertaRegTemas(&arch, campos) == 0){
		if (cargar_reg_Tema(nom, arch) == 0){
			printf("\nRegistro insertado en el archivo '%s'.\n", nom);	
			return(0);
		}
	}
	return(1);
}

// Modifica los campos solicitados del archivo Temas
int InsertaRegTemas(Temas *arch, tlista_s *campos)
{
	Tdato_IString x;

	// valores default (cod no puede tener valor default)
	arch->flag = 'V';

	if(!lvacia(campos)){
		lppio(campos);
		linfo(campos,&x);
		if (InsertaUnCampoTemas(arch, x.clave, x.pos) != 0)
				return(1); // Campo invalido
		lsig(campos);
		while(!lfin(campos)){
			linfo(campos,&x);
			if (InsertaUnCampoTemas(arch, x.clave, x.pos) != 0)
				return(1); // Campo invalido
			lsig(campos);
		}
		return(0);
	}else{
		return(3); // El indice esta vacio
	}
	
}

//--------------------------------------------------------------------
//Inserta un campo
int InsertaUnCampoTemas(Temas *arch, Tclave valor, long campo)
{
	// Debe validar si es el campo es clave primaria, que no exista ya en el archivo
	// para no crear clave duplicada
	char nom_campo[128];
	char campo_texto[128];
	long valor_num;

	strcpy(nom_campo,"cod");	// convierte el nro en el nombre de campo equivalente
	valor_num = strlen(valor);
	if (valor_num != 0){	// el codigo no tener longitud cero o blanco
		if (ClavePrincipalNoExiste_s(nom_arch_Temas, valor) == 0){
			strcpy(arch->cod,valor);
			return(0);
		}else{
			printf("\nNo puede ingresar el registro porque ya existe uno con este codigo\n");	
		}
	}else{
		printf("\nNo puede ingresar una clave con valor cero o alfanumerico.\n");	
	}
	return(1);	// retorna error en caso que no haya podido modificar el campo por cualquier motivo
}
//--------------------------------------------------------------------
//Cargar registro Temas
int cargar_reg_Tema(char nom[128], Temas arch)
{
	FILE *ARCHIVO;

	if (ClavePrincipalNoExiste_s(nom, arch.cod) == 0){
		if((ARCHIVO = fopen(nom, "rb+")) == NULL){
			return(1);		// El archivo no fue creado
		}else{
			fseek(ARCHIVO,0L,SEEK_END);
			fwrite(&arch,sizeof(arch),1,ARCHIVO);
			fclose(ARCHIVO);
			RecrearIndicesTemas(nom);  // recrea los índices del archivo antes de salir
			return(0);
		}
	}else{
		return(2); // ya existe la clave en la base 
	}
}

// Inserta un registro en el archivo Autores 
//
int InsertaAutores(char nom[128],tlista_s *campos)
{
	Autores arch;

	if (InsertaRegAutores(&arch, campos) == 0){
		if (cargar_reg_Autor(nom, arch) == 0){
			printf("\nRegistro insertado en el archivo '%s'.\n", nom);	
			return(0);
		}
	}
	return(1);
}

// Modifica los campos solicitados del archivo Autores
int InsertaRegAutores(Autores *arch, tlista_s *campos)
{
	Tdato_IString x;

	// valores default (cod no puede tener valor default)
	arch->flag = 'V';

	if(!lvacia(campos)){
		lppio(campos);
		linfo(campos,&x);
		if (InsertaUnCampoAutores(arch, x.clave, x.pos) != 0)
				return(1); // Campo invalido
		lsig(campos);
		while(!lfin(campos)){
			linfo(campos,&x);
			if (InsertaUnCampoAutores(arch, x.clave, x.pos) != 0)
				return(1); // Campo invalido
			lsig(campos);
		}
		return(0);
	}else{
		return(3); // El indice esta vacio
	}
	
}

//--------------------------------------------------------------------
//Inserta un campo
int InsertaUnCampoAutores(Autores *arch, Tclave valor, long campo)
{
	// Debe validar si es el campo es clave primaria, que no exista ya en el archivo
	// para no crear clave duplicada
	char nom_campo[128];
	char campo_texto[128];
	long valor_num;

	strcpy(nom_campo,"cod");	// convierte el nro en el nombre de campo equivalente
	valor_num = strlen(valor);
	if (valor_num != 0){	// el codigo no tener longitud cero o blanco
		if (ClavePrincipalNoExiste_s(nom_arch_Autores, valor) == 0){
			strcpy(arch->cod,valor);
			return(0);
		}else{
			printf("\nNo puede ingresar el registro porque ya existe uno con este codigo\n");	
		}
	}else{
		printf("\nNo puede ingresar una clave con valor cero o alfanumerico.\n");	
	}
	return(1);	// retorna error en caso que no haya podido modificar el campo por cualquier motivo
}
//--------------------------------------------------------------------
//Cargar registro Autores
int cargar_reg_Autor(char nom[128], Autores arch)
{
	FILE *ARCHIVO;

	if (ClavePrincipalNoExiste_s(nom, arch.cod) == 0){
		if((ARCHIVO = fopen(nom, "rb+")) == NULL){
			return(1);		// El archivo no fue creado
		}else{
			fseek(ARCHIVO,0L,SEEK_END);
			fwrite(&arch,sizeof(arch),1,ARCHIVO);
			fclose(ARCHIVO);
			RecrearIndicesAutores(nom);  // recrea los índices del archivo antes de salir
			return(0);
		}
	}else{
		return(2); // ya existe la clave en la base 
	}
}


// Inserta un registro en el archivo Socios 
//
int InsertaSocios(char nom[128],tlista_s *campos)
{
	Socios arch;

	if (InsertaRegSocios(&arch, campos) == 0){
		if (cargar_reg_Socio(nom, arch) == 0){
			printf("\nRegistro insertado en el archivo '%s'.\n", nom);	
			return(0);
		}
	}
	return(1);
}

// Modifica los campos solicitados del archivo Socios
int InsertaRegSocios(Socios *arch, tlista_s *campos)
{
	Tdato_IString x;

	// valores default (cod, cod_tema y cod_autor no pueden tener valor default)
	arch->flag = 'V';
	strcpy(arch->nombreyapellido,"");
	strcpy(arch->direccion,"");
	arch->dni = 0;

	if(!lvacia(campos)){
		lppio(campos);
		linfo(campos,&x);
		if (InsertaUnCampoSocios(arch, x.clave, x.pos) != 0)
				return(1); // Campo invalido
		lsig(campos);
		while(!lfin(campos)){
			linfo(campos,&x);
			if (InsertaUnCampoSocios(arch, x.clave, x.pos) != 0)
				return(1); // Campo invalido
			lsig(campos);
		}
		return(0);
	}else{
		return(3); // El indice esta vacio
	}
	
}

//--------------------------------------------------------------------
//Inserta un campo
int InsertaUnCampoSocios(Socios *arch, Tclave valor, long campo)
{
	// Debe validar si es el campo es clave primaria, que no exista ya en el archivo
	// para no crear clave duplicada
	char nom_campo[128];
	char campo_texto[128];
	long valor_num;

	switch (campo){
		case 1:		
			strcpy(nom_campo,"cod");	// convierte el nro en el nombre de campo equivalente
			valor_num = atoi(valor);
			if (valor_num != 0){	// el codigo no puede ser cero
				if (ClavePrincipalNoExiste(nom_arch_Socios, valor_num) == 0){
					arch->cod = valor_num;
					return(0);
				}else{
					printf("\nNo puede ingresar el registro porque ya existe uno con este codigo\n");	
				}
			}else{
				printf("\nNo puede ingresar una clave con valor cero o alfanumerico.\n");	
			}
			break;
	
		case 2:		
			strcpy(nom_campo,"nombreyapellido");	// convierte el nro en el nombre de campo equivalente
			strcpy(arch->nombreyapellido,valor);
			return(0);
			break;
	
		case 3:		
			strcpy(nom_campo,"dni");	// convierte el nro en el nombre de campo equivalente
			arch->dni = atoi(valor);
			return(0);
			break;
	
		case 4:		
			strcpy(nom_campo,"direccion");	// convierte el nro en el nombre de campo equivalente
			strcpy(arch->direccion,valor);
			return(0);
	}
	return(1);	// retorna error en caso que no haya podido modificar el campo por cualquier motivo
}
//--------------------------------------------------------------------
//Cargar registro Socios
int cargar_reg_Socio(char nom[128], Socios arch)
{
	FILE *ARCHIVO;

	if (ClavePrincipalNoExiste(nom, arch.cod) == 0){
		if((ARCHIVO = fopen(nom, "rb+")) == NULL){
			return(1);		// El archivo no fue creado
		}else{
			fseek(ARCHIVO,0L,SEEK_END);
			fwrite(&arch,sizeof(arch),1,ARCHIVO);
			fclose(ARCHIVO);
			RecrearIndicesSocios(nom);  // recrea los índices del archivo antes de salir
			return(0);
		}
	}else{
		return(2); // ya existe la clave en la base 
	}
}

// Inserta un registro en el archivo Prestamos 
//
int InsertaPrestamos(char nom[128],tlista_s *campos)
{
	Prestamos arch;

	if (InsertaRegPrestamos(&arch, campos) == 0){
//  revisar
		if (cargar_reg_Prestamo(nom, arch) == 0){
			printf("\nRegistro insertado en el archivo '%s'.\n", nom);	
			return(0);
		}
	}
	return(1);
}

// Modifica los campos solicitados del archivo Socios
int InsertaRegPrestamos(Prestamos *arch, tlista_s *campos)
{
	Tdato_IString x;

	// valores default (cod, cod_tema y cod_autor no pueden tener valor default)
	arch->flag = 'V';

	if(!lvacia(campos)){
		lppio(campos);
		linfo(campos,&x);
		if (InsertaUnCampoPrestamos(arch, x.clave, x.pos) != 0)
				return(1); // Campo invalido
		lsig(campos);
		while(!lfin(campos)){
			linfo(campos,&x);
			if (InsertaUnCampoPrestamos(arch, x.clave, x.pos) != 0)
				return(1); // Campo invalido
			lsig(campos);
		}
		return(0);
	}else{
		return(3); // El indice esta vacio
	}
	
}

//--------------------------------------------------------------------
//Inserta un campo
int InsertaUnCampoPrestamos(Prestamos *arch, Tclave valor, long campo)
{
	// Debe validar si es el campo es clave primaria, que no exista ya en el archivo
	// para no crear clave duplicada
	char nom_campo[128];
	char campo_texto[128];
	long valor_num;

	switch (campo){
		case 1:		
			strcpy(nom_campo,"cod");	// convierte el nro en el nombre de campo equivalente
			valor_num = atoi(valor);
			if (valor_num != 0){	// el codigo no puede ser cero
				if (ClavePrincipalNoExiste(nom_arch_Prestamos, valor_num) == 0){
					arch->cod = valor_num;
					return(0);
				}else{
					printf("\nNo puede ingresar el registro porque ya existe uno con este codigo\n");	
				}
			}else{
				printf("\nNo puede ingresar una clave con valor cero o alfanumerico.\n");	
			}
			break;
	
		case 2:		
			strcpy(nom_campo,"cod_socio");	// convierte el nro en el nombre de campo equivalente
			valor_num = atoi(valor);
			if (valor_num != 0){	// el codigo no puede ser cero
				if (ClavePrincipalNoExiste(nom_arch_Socios, valor_num) == 0){
					printf("\nEl %s = %d debe existir en el archivo %s.\n",nom_campo,valor_num,nom_arch_Socios);	
				}else{
					arch->cod_socio = valor_num;
					return(0);
				}
			}else{
				printf("\nNo puede ingresar una clave con valor cero o alfanumerico.\n");	
			}
			break;
	
		case 3:		
			strcpy(nom_campo,"cod_libro");	// convierte el nro en el nombre de campo equivalente
			valor_num = atoi(valor);
			if (valor_num != 0){	// el codigo no puede ser cero
				if (ClavePrincipalNoExiste(nom_arch_Libros, valor_num) == 0){
					printf("\nEl %s = %d debe existir en el archivo %s.\n",nom_campo,valor_num,nom_arch_Socios);	
				}else{
					arch->cod_libro = valor_num;
					return(0);
				}
			}else{
				printf("\nNo puede ingresar una clave con valor cero o alfanumerico.\n");	
			}
			break;
	
	}
	return(1);	// retorna error en caso que no haya podido modificar el campo por cualquier motivo
}
//--------------------------------------------------------------------
//Cargar registro Prestamos
int cargar_reg_Prestamo(char nom[128], Prestamos arch)
{
	FILE *ARCHIVO;

	if (ClavePrincipalNoExiste(nom, arch.cod) == 0){
		if((ARCHIVO = fopen(nom, "rb+")) == NULL){
			return(1);		// El archivo no fue creado
		}else{
			fseek(ARCHIVO,0L,SEEK_END);
			fwrite(&arch,sizeof(arch),1,ARCHIVO);
			fclose(ARCHIVO);
			RecrearIndicesPrestamos(nom);  // recrea los índices del archivo antes de salir
			return(0);
		}
	}else{
		return(2); // ya existe la clave en la base 
	}
}

//--------------------------------------------------------------------
// Listar registros de tablas segun condiciones solicitadas
int Listar(char nom[128],tlista_s *campos, char nom_campo_indice[128], char campo_comp[128],char valor_comp[128])
{
	if (valida_nom_archivo(nom) != 0)  // Verifica que es un archivo de la base
		return(1);

	if(stricmp(nom,nom_arch_Autores)==0)
		if (ListaAutores(nom, campos, nom_campo_indice, campo_comp, valor_comp) != 0){
			return(2);
		}		
	if(stricmp(nom,nom_arch_Libros)==0)
		if (ListaLibros(nom, campos, nom_campo_indice, campo_comp, valor_comp) != 0){
			return(2);
		}		
	if(stricmp(nom,nom_arch_Socios)==0)
		if (ListaSocios(nom, campos, nom_campo_indice, campo_comp, valor_comp) != 0){
			return(2);
		}		
	if(stricmp(nom,nom_arch_Temas)==0)
		if (ListaTemas(nom, campos, nom_campo_indice, campo_comp, valor_comp) != 0){
			return(2);
		}		
	if(stricmp(nom,nom_arch_Prestamos)==0)
		if (ListaPrestamos(nom, campos, nom_campo_indice, campo_comp, valor_comp) != 0){
			return(2);
		}

	return(0);
}

// Lista todos los libros que cumplen una condición, ordenados por el indice
// solicitado y conteniendo los campos solicitados
//
int ListaLibros(char nom[128],tlista_s *campos, char nom_campo_indice[128], char campo_comp[128],char valor_comp[128])
// Nom = Nombre del archivo
// campos = lista con campos a listar
// nom_indice = nombre del campo índice por el cual lista
{
	char nom_indice[128];
	tlista		indice_Libros;
	tlista_s	ind_titulo;		// Indice del Titulo del Libro

	if (strlen(campo_comp) != 0)
		if (valida_campo(nom, campo_comp) !=0)
			return(3); // campo de comparacion no existe
	
	if (valida_campo(nom, nom_campo_indice) !=0)
		return(3); // campo indice no existe
	strcpy(nom_indice,nom);
	if (stricmp(nom_campo_indice,"cod") == 0){
		strcat(nom_indice,nom_ext_indice);
		if(abrir(nom_indice)){
			lcrear_inx(&indice_Libros);
			cargarindice(&indice_Libros,nom_indice); //carga el indice
			ListarLibroPorCodigo(nom, &indice_Libros, campos, campo_comp, valor_comp);
			borrarindice(&indice_Libros);
		}else{
			return(2); // archivo de índice no encontrado
		}
	}else{
		if (stricmp(nom_campo_indice,"titulo") == 0){
			strcat(nom_indice,nom_ext_ind2);
			if(abrir(nom_indice)){
				lcrear(&ind_titulo);
				cargarindice_s(&ind_titulo,nom_indice); //carga el indice
				ListarLibroPorTitulo(nom, &ind_titulo, campos, campo_comp, valor_comp);
				borrarindice_s(&ind_titulo);
			}else{
				return(2); // archivo de índice no encontrado
			}
		}else{
			return(1); // indice inexistente para este archivo
		}
	}
	return(0); 
}

//--------------------------------------------------------------------
int ListarLibroPorCodigo(char nom[128], tlista *l, tlista_s *campos, char campo_comp[128],char valor_comp[128])
{
	Tdatoindex x;
	FILE *ARCHIVO;
	Libros arch;
	int linea = 0;		// iniciala fila de impresión

	long pos = 0;
	if((ARCHIVO = fopen(nom, "rb")) == NULL){		// abre el archivo de lectura nomas
		return(1);	// Archivo no encontrado
	}else{
		if(!lvacia_inx(l)){
			lppio_inx(l);
			linfo_inx(l,&x);
			fseek(ARCHIVO,x.pos,SEEK_SET );
			fread(&arch,sizeof(arch),1,ARCHIVO);
			if (!feof(ARCHIVO)){
				ListarTituloLibro(nom, campos);
				if ((x.flag == 'v') || (x.flag == 'V')) {
					if (strlen(campo_comp) == 0){
						linea++;
						if (ListaCamposLibros(arch, campos) == 0)
							printf("\n");	
					}else{
						if (valida_campo_contiene_en_Libros(arch, campo_comp, valor_comp) == 0){
							linea++;
							if (ListaCamposLibros(arch, campos) == 0)
								printf("\n");	
						}
					}
				}
			}else{
				return(2);	// Registro no encontrado
			}

			lsig_inx(l);
			while(!lfin_inx(l)){
				linfo_inx(l,&x);
				fseek(ARCHIVO,x.pos,SEEK_SET );
				fread(&arch,sizeof(arch),1,ARCHIVO);
				if (!feof(ARCHIVO)){
					if ((x.flag == 'v') || (x.flag == 'V'))  {
						if (strlen(campo_comp) == 0){
							linea++;
							if (ListaCamposLibros(arch, campos) == 0)
								printf("\n");	
						}else{
							if (valida_campo_contiene_en_Libros(arch, campo_comp, valor_comp) == 0){
								linea++;
								if (ListaCamposLibros(arch, campos) == 0)
									printf("\n");	
							}
						}
					}
				}else{
					return(2);	// Registro no encontrado
				}
				lsig_inx(l);
			}
		}else{
			return(3); // El indice esta vacio
		}
		fclose(ARCHIVO);
		printf("\nCantidad de registros: %5d\n", linea);	
		return(0);
	}
}

//--------------------------------------------------------------------
int ListarLibroPorTitulo(char nom[128], tlista_s *l, tlista_s *campos, char campo_comp[128],char valor_comp[128])
{
	Tdato_IString x;
	FILE *ARCHIVO;
	Libros arch;
	int linea = 0;		// iniciala fila de impresión

	long pos = 0;
	if((ARCHIVO = fopen(nom, "rb")) == NULL){		// abre el archivo de lectura nomas
		return(1);	// Archivo no encontrado
	}else{
		if(!lvacia(l)){
			lppio(l);
			linfo(l,&x);
			fseek(ARCHIVO,x.pos,SEEK_SET );
			fread(&arch,sizeof(arch),1,ARCHIVO);
			if (!feof(ARCHIVO)){
				ListarTituloLibro(nom, campos);
				if ((x.flag == 'v') || (x.flag == 'V')) {
					if (strlen(campo_comp) == 0){
						linea++;
						if (ListaCamposLibros(arch, campos) == 0)
							printf("\n");	
					}else{
						if (valida_campo_contiene_en_Libros(arch, campo_comp, valor_comp) == 0){
							linea++;
							if (ListaCamposLibros(arch, campos) == 0)
								printf("\n");	
						}
					}
				}
			}else{
				return(2);	// Registro no encontrado
			}

			lsig(l);
			while(!lfin(l)){
				linfo(l,&x);
				fseek(ARCHIVO,x.pos,SEEK_SET );
				fread(&arch,sizeof(arch),1,ARCHIVO);
				if (!feof(ARCHIVO)){
					if ((x.flag == 'v') || (x.flag == 'V'))  {
						if (strlen(campo_comp) == 0){
							linea++;
							if (ListaCamposLibros(arch, campos) == 0)
								printf("\n");	
						}else{
							if (valida_campo_contiene_en_Libros(arch, campo_comp, valor_comp) == 0){
								linea++;
								if (ListaCamposLibros(arch, campos) == 0)
									printf("\n");	
							}
						}
					}
				}else{
					return(2);	// Registro no encontrado
				}
				lsig(l);
			}
		}else{
			return(3); // El indice esta vacio
		}
		fclose(ARCHIVO);
		printf("\nCantidad de registros: %5d\n", linea);	
		return(0);
	}
}

//--------------------------------------------------------------------
//Lista todos los campos solicitados del archivo
int ListaCamposLibros(Libros arch, tlista_s *campos)
{
	Tdato_IString x;

	if(!lvacia(campos)){
		lppio(campos);
		linfo(campos,&x);
		if (stricmp(x.clave,"*") == 0){
			printf("%6d  %-15s  %-25s  %-20s  %-9s  ",arch.cod, arch.cod_tema, arch.titulo, arch.cod_autor, arch.ubicacion);
		}else{
			if (ListaUnCampoLibros(arch, x.clave) != 0)
				return(1); // Campo invalido
		}
		lsig(campos);
		while(!lfin(campos)){
			linfo(campos,&x);
			if (ListaUnCampoLibros(arch, x.clave) != 0)
				return(1); // Campo invalido
			lsig(campos);
		}
	}else{
		return(3); // El indice esta vacio
	}
	
	return(0);
}

//--------------------------------------------------------------------
//Lista un campo
int ListaUnCampoLibros(Libros arch, Tclave nom_campo)
{
	if (stricmp(nom_campo,"cod") == 0){
		printf("%6d  ",arch.cod);
	}else{
		if (stricmp(nom_campo,"cod_tema") == 0){
			printf("%-15s  ",arch.cod_tema);
		}else{
			if (stricmp(nom_campo,"titulo") == 0){
				printf("%-25s  ",arch.titulo);
			}else{
				if (stricmp(nom_campo,"cod_autor") == 0){
					printf("%-20s  ", arch.cod_autor);
				}else{
					if (stricmp(nom_campo,"ubicacion") == 0){
						printf("%-9s  ", arch.ubicacion);
					}else{
						printf("*invalido*  ");   // campo inexistente
					}
				}
			}
		}
	}
	return(0);
}
//--------------------------------------------------------------------
//Valida que un campo contiene el valor buscado
int valida_campo_contiene_en_Libros(Libros arch, char campo_comp[128],char valor_comp[128])
{
	if (stricmp(campo_comp,"cod")==0){ 
		if (arch.cod == atoi(valor_comp))
			return(0);
		else
			return(1);
	}
	if (stricmp(campo_comp,"cod_tema")==0) {
		if (strstr(strlwr(arch.cod_tema), strlwr(valor_comp)) != NULL)
			return(0);
		else
			return(1);
	}
	if (stricmp(campo_comp,"titulo")==0){
		if (strstr(strlwr(arch.titulo), strlwr(valor_comp)) != NULL)
			return(0);
		else
			return(1);
	}
	if (stricmp(campo_comp,"cod_autor")==0) {
		if (strstr(strlwr(arch.cod_autor), strlwr(valor_comp)) != NULL)
			return(0);
		else
			return(1);
	}
	if (stricmp(campo_comp,"ubicacion")==0){
		if (strstr(strlwr(arch.ubicacion), strlwr(valor_comp)) != NULL)
			return(0);
		else
			return(1);
	}
}
//--------------------------------------------------------------------
//Lista todos los campos solicitados del archivo
int ListarTituloLibro(char nom[128], tlista_s *campos)
{
	Tdato_IString x;

	printf("\n\nListado del archivo: %s\n\n", nom);
	if(!lvacia(campos)){
		lppio(campos);
		linfo(campos,&x);
		if (stricmp(x.clave,"*") == 0){
			printf("Codigo  Tema             Titulo                     Autor                 Ubicacion  ");
		}else{
			if (ListaTituloUnCampoLibros(x.clave) != 0)
				return(1); // Campo invalido
		}
		lsig(campos);
		while(!lfin(campos)){
			linfo(campos,&x);
			if (ListaTituloUnCampoLibros(x.clave) != 0)
				return(1); // Campo invalido
			lsig(campos);
		}
	}else{
		return(3); // El indice esta vacio
	}
	printf("\n\n");
	return(0);
}
//--------------------------------------------------------------------
//Lista un campo
int ListaTituloUnCampoLibros(Tclave nom_campo)
{
	if (stricmp(nom_campo,"cod") == 0){
		printf("Codigo  ");
	}else{
		if (stricmp(nom_campo,"cod_tema") == 0){
			printf("Tema             ");
		}else{
			if (stricmp(nom_campo,"titulo") == 0){
				printf("Titulo                     ");
			}else{
				if (stricmp(nom_campo,"cod_autor") == 0){
					printf("Autor                 ");
				}else{
					if (stricmp(nom_campo,"ubicacion") == 0){
						printf("Ubicacion  ");
					}else{
						printf("%-10.10s  ",nom_campo);	// campo inexistente
					}
				}
			}
		}
	}
	return(0);
}
//--------------------------------------------------------------------
// Lista todos los Temas que cumplen una condición, ordenados por el indice
// solicitado y conteniendo los campos solicitados
//
int ListaTemas(char nom[128],tlista_s *campos, char nom_campo_indice[128], char campo_comp[128],char valor_comp[128])
// Nom = Nombre del archivo
// campos = lista con campos a listar
// nom_indice = nombre del campo índice por el cual lista
{
	char nom_indice[128];
	tlista_s	indice_Temas;		// Indice de Temas

	if (strlen(campo_comp) != 0)
		if (valida_campo(nom, campo_comp) !=0)
			return(3); // campo de comparacion no existe
	
	if (valida_campo(nom, nom_campo_indice) !=0)
		return(3); // campo indice no existe
	strcpy(nom_indice,nom);
	if (stricmp(nom_campo_indice,"cod") == 0){
		strcat(nom_indice,nom_ext_indice);
		if(abrir(nom_indice)){
			lcrear(&indice_Temas);
			cargarindice_s(&indice_Temas,nom_indice); //carga el indice
			ListarTemaPorCodigo(nom, &indice_Temas, campos, campo_comp, valor_comp);
			borrarindice_s(&indice_Temas);
		}else{
			return(2); // archivo de índice no encontrado
		}
	}else{
		return(1); // indice inexistente para este archivo
	}
	return(0); 
}



//--------------------------------------------------------------------
int ListarTemaPorCodigo(char nom[128], tlista_s *l, tlista_s *campos, char campo_comp[128],char valor_comp[128])
{
	Tdato_IString x;
	FILE *ARCHIVO;
	Temas arch;
	int linea = 0;		// iniciala fila de impresión

	long pos = 0;
	if((ARCHIVO = fopen(nom, "rb")) == NULL){		// abre el archivo de lectura nomas
		return(1);	// Archivo no encontrado
	}else{
		if(!lvacia(l)){
			lppio(l);
			linfo(l,&x);
			fseek(ARCHIVO,x.pos,SEEK_SET );
			fread(&arch,sizeof(arch),1,ARCHIVO);
			if (!feof(ARCHIVO)){
				ListarTituloTema(nom, campos);
				if ((x.flag == 'v') || (x.flag == 'V')) {
					if (strlen(campo_comp) == 0){
						linea++;
						if (ListaCamposTemas(arch, campos) == 0)
							printf("\n");	
					}else{
						if (valida_campo_contiene_en_Temas(arch, campo_comp, valor_comp) == 0){
							linea++;
							if (ListaCamposTemas(arch, campos) == 0)
								printf("\n");	
						}
					}
				}
			}else{
				return(2);	// Registro no encontrado
			}

			lsig(l);
			while(!lfin(l)){
				linfo(l,&x);
				fseek(ARCHIVO,x.pos,SEEK_SET );
				fread(&arch,sizeof(arch),1,ARCHIVO);
				if (!feof(ARCHIVO)){
					if ((x.flag == 'v') || (x.flag == 'V'))  {
						if (strlen(campo_comp) == 0){
							linea++;
							if (ListaCamposTemas(arch, campos) == 0)
								printf("\n");	
						}else{
							if (valida_campo_contiene_en_Temas(arch, campo_comp, valor_comp) == 0){
								linea++;
								if (ListaCamposTemas(arch, campos) == 0)
									printf("\n");	
							}
						}
					}
				}else{
					return(2);	// Registro no encontrado
				}
				lsig(l);
			}
		}else{
			return(3); // El indice esta vacio
		}
		fclose(ARCHIVO);
		printf("\nCantidad de registros: %5d\n", linea);	
		return(0);
	}
}

//--------------------------------------------------------------------
//Lista todos los campos solicitados del archivo
int ListaCamposTemas(Temas arch, tlista_s *campos)
{
	Tdato_IString x;

	if(!lvacia(campos)){
		lppio(campos);
		linfo(campos,&x);
		if (stricmp(x.clave,"*") == 0){
			printf("%-20s  ",arch.cod);
		}else{
			if (ListaUnCampoTemas(arch, x.clave) != 0)
				return(1); // Campo invalido
		}
		lsig(campos);
		while(!lfin(campos)){
			linfo(campos,&x);
			if (ListaUnCampoTemas(arch, x.clave) != 0)
				return(1); // Campo invalido
			lsig(campos);
		}
		return(0);
	}else{
		return(3); // El indice esta vacio
	}
	
}
//--------------------------------------------------------------------
//Lista un campo
int ListaUnCampoTemas(Temas arch, Tclave nom_campo)
{
	if (stricmp(nom_campo,"cod") == 0){
		printf("%-20s  ",arch.cod);
	}else{
		printf("*invalido*  ");   // campo inexistente
	}
	return(0);
}
//--------------------------------------------------------------------
//Valida que un campo contiene el valor buscado
int valida_campo_contiene_en_Temas(Temas arch, char campo_comp[128],char valor_comp[128])
{
	if (stricmp(campo_comp,"cod")==0){ 
		if (strstr(strlwr(arch.cod), strlwr(valor_comp)) != NULL)
			return(0);
		else
			return(1);
	}
}
//--------------------------------------------------------------------
//Lista todos los campos solicitados del archivo
int ListarTituloTema(char nom[128], tlista_s *campos)
{
	Tdato_IString x;

	printf("\n\nListado del archivo: %s\n\n", nom);
	if(!lvacia(campos)){
		lppio(campos);
		linfo(campos,&x);
		if (stricmp(x.clave,"*") == 0){
			printf("Codigo                   ");
		}else{
			if (ListaTituloUnCampoTemas(x.clave) != 0)
				return(1); // Campo invalido
		}
		lsig(campos);
		while(!lfin(campos)){
			linfo(campos,&x);
			if (ListaTituloUnCampoTemas(x.clave) != 0)
				return(1); // Campo invalido
			lsig(campos);
		}
	}else{
		return(3); // El indice esta vacio
	}
	printf("\n\n");
	return(0);
}
//--------------------------------------------------------------------
//Lista un campo
int ListaTituloUnCampoTemas(Tclave nom_campo)
{
	if (stricmp(nom_campo,"cod") == 0){
		printf("Codigo                   ");
	}else{
		printf("%-10.10s  ",nom_campo);	// campo inexistente
	}
	return(0);
}
//--------------------------------------------------------------------
// Lista todos los Autores que cumplen una condición, ordenados por el indice
// solicitado y conteniendo los campos solicitados
//
int ListaAutores(char nom[128],tlista_s *campos, char nom_campo_indice[128], char campo_comp[128],char valor_comp[128])
// Nom = Nombre del archivo
// campos = lista con campos a listar
// nom_indice = nombre del campo índice por el cual lista
{
	char nom_indice[128];
	tlista_s	indice_Autores;		// Indice de Autores

	if (strlen(campo_comp) != 0)
		if (valida_campo(nom, campo_comp) !=0)
			return(3); // campo de comparacion no existe
	
	if (valida_campo(nom, nom_campo_indice) !=0)
		return(3); // campo indice no existe
	strcpy(nom_indice,nom);
	if (stricmp(nom_campo_indice,"cod") == 0){
		strcat(nom_indice,nom_ext_indice);
		if(abrir(nom_indice)){
			lcrear(&indice_Autores);
			cargarindice_s(&indice_Autores,nom_indice); //carga el indice
			ListarAutorPorCodigo(nom, &indice_Autores, campos, campo_comp, valor_comp);
			borrarindice_s(&indice_Autores);
		}else{
			return(2); // archivo de índice no encontrado
		}
	}else{
		return(1); // indice inexistente para este archivo
	}
	return(0); 
}



//--------------------------------------------------------------------
int ListarAutorPorCodigo(char nom[128], tlista_s *l, tlista_s *campos, char campo_comp[128],char valor_comp[128])
{
	Tdato_IString x;
	FILE *ARCHIVO;
	Autores arch;
	int linea = 0;		// iniciala fila de impresión

	long pos = 0;
	if((ARCHIVO = fopen(nom, "rb")) == NULL){		// abre el archivo de lectura nomas
		return(1);	// Archivo no encontrado
	}else{
		if(!lvacia(l)){
			lppio(l);
			linfo(l,&x);
			fseek(ARCHIVO,x.pos,SEEK_SET );
			fread(&arch,sizeof(arch),1,ARCHIVO);
			if (!feof(ARCHIVO)){
				ListarTituloAutor(nom, campos);
				if ((x.flag == 'v') || (x.flag == 'V')) {
					if (strlen(campo_comp) == 0){
						linea++;
						if (ListaCamposAutores(arch, campos) == 0)
							printf("\n");	
					}else{
						if (valida_campo_contiene_en_Autores(arch, campo_comp, valor_comp) == 0){
							linea++;
							if (ListaCamposAutores(arch, campos) == 0)
								printf("\n");	
						}
					}
				}
			}else{
				return(2);	// Registro no encontrado
			}

			lsig(l);
			while(!lfin(l)){
				linfo(l,&x);
				fseek(ARCHIVO,x.pos,SEEK_SET );
				fread(&arch,sizeof(arch),1,ARCHIVO);
				if (!feof(ARCHIVO)){
					if ((x.flag == 'v') || (x.flag == 'V'))  {
						if (strlen(campo_comp) == 0){
							linea++;
							if (ListaCamposAutores(arch, campos) == 0)
								printf("\n");	
						}else{
							if (valida_campo_contiene_en_Autores(arch, campo_comp, valor_comp) == 0){
								linea++;
								if (ListaCamposAutores(arch, campos) == 0)
									printf("\n");	
							}
						}
					}
				}else{
					return(2);	// Registro no encontrado
				}
				lsig(l);
			}
		}else{
			return(3); // El indice esta vacio
		}
		fclose(ARCHIVO);
		printf("\nCantidad de registros: %5d\n", linea);	
		return(0);
	}
}

//--------------------------------------------------------------------
//Lista todos los campos solicitados del archivo
int ListaCamposAutores(Autores arch, tlista_s *campos)
{
	Tdato_IString x;

	if(!lvacia(campos)){
		lppio(campos);
		linfo(campos,&x);
		if (stricmp(x.clave,"*") == 0){
			printf("%-20s  ",arch.cod);
		}else{
			if (ListaUnCampoAutores(arch, x.clave) != 0)
				return(1); // Campo invalido
		}
		lsig(campos);
		while(!lfin(campos)){
			linfo(campos,&x);
			if (ListaUnCampoAutores(arch, x.clave) != 0)
				return(1); // Campo invalido
			lsig(campos);
		}
	}else{
		return(3); // El indice esta vacio
	}
	
	return(0);

}
//--------------------------------------------------------------------
//Lista un campo
int ListaUnCampoAutores(Autores arch, Tclave nom_campo)
{
	if (stricmp(nom_campo,"cod") == 0){
		printf("%-20s  ",arch.cod);
	}else{
		printf("*invalido*  ");   // campo inexistente
	}
	return(0);
}
//--------------------------------------------------------------------
//Valida que un campo contiene el valor buscado
int valida_campo_contiene_en_Autores(Autores arch, char campo_comp[128],char valor_comp[128])
{
	if (stricmp(campo_comp,"cod")==0){ 
		if (strstr(strlwr(arch.cod), strlwr(valor_comp)) != NULL)
			return(0);
		else
			return(1);
	}
}
//--------------------------------------------------------------------
//Lista todos los campos solicitados del archivo
int ListarTituloAutor(char nom[128], tlista_s *campos)
{
	Tdato_IString x;

	printf("\n\nListado del archivo: %s\n\n", nom);
	if(!lvacia(campos)){
		lppio(campos);
		linfo(campos,&x);
		if (stricmp(x.clave,"*") == 0){
			printf("Codigo                   ");
		}else{
			if (ListaTituloUnCampoAutores(x.clave) != 0)
				return(1); // Campo invalido
		}
		lsig(campos);
		while(!lfin(campos)){
			linfo(campos,&x);
			if (ListaTituloUnCampoAutores(x.clave) != 0)
				return(1); // Campo invalido
			lsig(campos);
		}
	}else{
		return(3); // El indice esta vacio
	}
	printf("\n\n");
	return(0);
}
//--------------------------------------------------------------------
//Lista un campo
int ListaTituloUnCampoAutores(Tclave nom_campo)
{
	if (stricmp(nom_campo,"cod") == 0){
		printf("Codigo                   ");
	}else{
		printf("%-10.10s  ",nom_campo);	// campo inexistente
	}
	return(0);
}
// Lista todos los socios que cumplen una condición, ordenados por el indice
// solicitado y conteniendo los campos solicitados
//
int ListaSocios(char nom[128],tlista_s *campos, char nom_campo_indice[128], char campo_comp[128],char valor_comp[128])
// Nom = Nombre del archivo
// campos = lista con campos a listar
// nom_indice = nombre del campo índice por el cual lista
{
	char nom_indice[128];
	tlista		indice_Socios;
	tlista_s	ind_NYA;		// Indice del Nombre y Apellido del Socio

	if (strlen(campo_comp) != 0)
		if (valida_campo(nom, campo_comp) !=0)
			return(3); // campo de comparacion no existe
	
	if (valida_campo(nom, nom_campo_indice) !=0)
		return(3); // campo indice no existe
	strcpy(nom_indice,nom);
	if (stricmp(nom_campo_indice,"cod") == 0){
		strcat(nom_indice,nom_ext_indice);
		if(abrir(nom_indice)){
			lcrear_inx(&indice_Socios);
			cargarindice(&indice_Socios,nom_indice); //carga el indice
			ListarSocioPorCodigo(nom, &indice_Socios, campos, campo_comp, valor_comp);
			borrarindice(&indice_Socios);
		}else{
			return(2); // archivo de índice no encontrado
		}
	}else{
		if (stricmp(nom_campo_indice,"nombreyapellido") == 0){
			strcat(nom_indice,nom_ext_ind2);
			if(abrir(nom_indice)){
				lcrear(&ind_NYA);
				cargarindice_s(&ind_NYA,nom_indice); //carga el indice
				ListarSocioPorNYA(nom, &ind_NYA, campos, campo_comp, valor_comp);
				borrarindice_s(&ind_NYA);
			}else{
				return(2); // archivo de índice no encontrado
			}
		}else{
			return(1); // indice inexistente para este archivo
		}
	}
	return(0); 
}

//--------------------------------------------------------------------
int ListarSocioPorCodigo(char nom[128], tlista *l, tlista_s *campos, char campo_comp[128],char valor_comp[128])
{
	Tdatoindex x;
	FILE *ARCHIVO;
	Socios arch;
	int linea;

	linea = 0;		// iniciala fila de impresión
	long pos = 0;
	if((ARCHIVO = fopen(nom, "rb")) == NULL){		// abre el archivo de lectura nomas
		return(1);	// Archivo no encontrado
	}else{
		if(!lvacia_inx(l)){
			lppio_inx(l);
			linfo_inx(l,&x);
			fseek(ARCHIVO,x.pos,SEEK_SET );
			fread(&arch,sizeof(arch),1,ARCHIVO);
			if (!feof(ARCHIVO)){
				ListarTituloSocio(nom, campos);
				if ((x.flag == 'v') || (x.flag == 'V')) {
					if (strlen(campo_comp) == 0){
						linea++;
						if (ListaCamposSocios(arch, campos) == 0)
							printf("\n");	
					}else{
						if (valida_campo_contiene_en_Socios(arch, campo_comp, valor_comp) == 0){
							linea++;
							if (ListaCamposSocios(arch, campos) == 0)
								printf("\n");	
						}
					}
				}
			}else{
				return(2);	// Registro no encontrado
			}

			lsig_inx(l);
			while(!lfin_inx(l)){
				linfo_inx(l,&x);
				fseek(ARCHIVO,x.pos,SEEK_SET );
				fread(&arch,sizeof(arch),1,ARCHIVO);
				if (!feof(ARCHIVO)){
					if ((x.flag == 'v') || (x.flag == 'V'))  {
						if (strlen(campo_comp) == 0){
							linea++;
							if (ListaCamposSocios(arch, campos) == 0)
								printf("\n");	
						}else{
							if (valida_campo_contiene_en_Socios(arch, campo_comp, valor_comp) == 0){
								linea++;
								if (ListaCamposSocios(arch, campos) == 0)
									printf("\n");	
							}
						}
					}
				}else{
					return(2);	// Registro no encontrado
				}
				lsig_inx(l);
			}
		}else{
			return(3); // El indice esta vacio
		}
		fclose(ARCHIVO);
		printf("\nCantidad de registros: %5d\n", linea);	
		return(0);
	}
}

//--------------------------------------------------------------------
int ListarSocioPorNYA(char nom[128], tlista_s *l, tlista_s *campos, char campo_comp[128],char valor_comp[128])
{
	Tdato_IString x;
	FILE *ARCHIVO;
	Socios arch;
	int linea;

	linea = 0;		// iniciala fila de impresión
	long pos = 0;
	if((ARCHIVO = fopen(nom, "rb")) == NULL){		// abre el archivo de lectura nomas
		return(1);	// Archivo no encontrado
	}else{
		if(!lvacia(l)){
			lppio(l);
			linfo(l,&x);
			fseek(ARCHIVO,x.pos,SEEK_SET );
			fread(&arch,sizeof(arch),1,ARCHIVO);
			if (!feof(ARCHIVO)){
				ListarTituloSocio(nom, campos);
				if ((x.flag == 'v') || (x.flag == 'V')) {
					if (strlen(campo_comp) == 0){
						linea++;
						if (ListaCamposSocios(arch, campos) == 0)
							printf("\n");	
					}else{
						if (valida_campo_contiene_en_Socios(arch, campo_comp, valor_comp) == 0){
							linea++;
							if (ListaCamposSocios(arch, campos) == 0)
								printf("\n");	
						}
					}
				}
			}else{
				return(2);	// Registro no encontrado
			}

			lsig(l);
			while(!lfin(l)){
				linfo(l,&x);
				fseek(ARCHIVO,x.pos,SEEK_SET );
				fread(&arch,sizeof(arch),1,ARCHIVO);
				if (!feof(ARCHIVO)){
					if ((x.flag == 'v') || (x.flag == 'V'))  {
						if (strlen(campo_comp) == 0){
							linea++;
							if (ListaCamposSocios(arch, campos) == 0)
								printf("\n");	
						}else{
							if (valida_campo_contiene_en_Socios(arch, campo_comp, valor_comp) == 0){
								linea++;
								if (ListaCamposSocios(arch, campos) == 0)
									printf("\n");	
							}
						}
					}
				}else{
					return(2);	// Registro no encontrado
				}
				lsig(l);
			}
		}else{
			return(3); // El indice esta vacio
		}
		fclose(ARCHIVO);
		printf("\nCantidad de registros: %5d\n", linea);	
		return(0);
	}
}

//--------------------------------------------------------------------
//Lista todos los campos solicitados del archivo
int ListarTituloSocio(char nom[128], tlista_s *campos)
{
	Tdato_IString x;

	printf("\n\nListado del archivo: %s\n\n", nom);
	if(!lvacia(campos)){
		lppio(campos);
		linfo(campos,&x);
		if (stricmp(x.clave,"*") == 0){
			printf("Codigo  Nombre y Apellido         DNI     Direccion                       ");
		}else{
			if (ListaTituloUnCampoSocios(x.clave) != 0)
				return(1); // Campo invalido
		}
		lsig(campos);
		while(!lfin(campos)){
			linfo(campos,&x);
			if (ListaTituloUnCampoSocios(x.clave) != 0)
				return(1); // Campo invalido
			lsig(campos);
		}
	}else{
		return(3); // El indice esta vacio
	}
	printf("\n\n");
	return(0);
}
//--------------------------------------------------------------------
//Lista un campo
int ListaTituloUnCampoSocios(Tclave nom_campo)
{
	if (stricmp(nom_campo,"cod") == 0){
		printf("Codigo  ");
	}else{
		if (stricmp(nom_campo,"nombreyapellido") == 0){
			printf("Nombre y Apellido     ");
		}else{
			if (stricmp(nom_campo,"dni") == 0){
				printf("    DNI     ");
			}else{
				if (stricmp(nom_campo,"direccion") == 0){
					printf("Direccion                       ");
				}else{
					printf("%-10.10s  ",nom_campo);	// campo inexistente
				}
			}
		}
	}
	return(0);
}
//--------------------------------------------------------------------
//Lista todos los campos solicitados del archivo
int ListaCamposSocios(Socios arch, tlista_s *campos)
{
	Tdato_IString x;

	if(!lvacia(campos)){
		lppio(campos);
		linfo(campos,&x);
		if (stricmp(x.clave,"*") == 0){
			printf("%6d  %-20s  %10d  %-30s  ",arch.cod, arch.nombreyapellido, arch.dni, arch.direccion);
		}else{
			if (ListaUnCampoSocios(arch, x.clave) != 0)
				return(1); // Campo invalido
		}
		lsig(campos);
		while(!lfin(campos)){
			linfo(campos,&x);
			if (ListaUnCampoSocios(arch, x.clave) != 0)
				return(1); // Campo invalido
			lsig(campos);
		}
	}else{
		return(3); // El indice esta vacio
	}
	
	return(0);
}
//--------------------------------------------------------------------
//Lista un campo
int ListaUnCampoSocios(Socios arch, Tclave nom_campo)
{
	if (stricmp(nom_campo,"cod") == 0){
		printf("%6d  ",arch.cod);
	}else{
		if (stricmp(nom_campo,"nombreyapellido") == 0){
			printf("%-20s  ",arch.nombreyapellido);
		}else{
			if (stricmp(nom_campo,"dni") == 0){
				printf("%10d  ",arch.dni);
			}else{
				if (stricmp(nom_campo,"direccion") == 0){
					printf("%-30s  ", arch.direccion);
				}else{
					printf("*invalido*  ");   // campo inexistente
				}
			}
		}
	}
	return(0);
}
//--------------------------------------------------------------------
//Valida que un campo contiene el valor buscado
int valida_campo_contiene_en_Socios(Socios arch, char campo_comp[128],char valor_comp[128])
{
	if (stricmp(campo_comp,"cod")==0){ 
		if (arch.cod == atoi(valor_comp))
			return(0);
		else
			return(1);
	}
	if (stricmp(campo_comp,"nombreyapellido")==0) {
		if (strstr(strlwr(arch.nombreyapellido), strlwr(valor_comp)) != NULL)
			return(0);
		else
			return(1);
	}
	if (stricmp(campo_comp,"direccion")==0){
		if (strstr(strlwr(arch.direccion), strlwr(valor_comp)) != NULL)
			return(0);
		else
			return(1);
	}
	if (stricmp(campo_comp,"dni")==0) {
		if (arch.dni == atol(valor_comp))
			return(0);
		else
			return(1);
	}
}
// Lista todos los prestamos que cumplen una condición, ordenados por el indice
// solicitado y conteniendo los campos solicitados
//
int ListaPrestamos(char nom[128],tlista_s *campos, char nom_campo_indice[128], char campo_comp[128],char valor_comp[128])
// Nom = Nombre del archivo
// campos = lista con campos a listar
// nom_indice = nombre del campo índice por el cual lista
{
	char nom_indice[128];
	tlista		indice_Prestamos;

	if (strlen(campo_comp) != 0)
		if (valida_campo(nom, campo_comp) !=0)
			return(3); // campo de comparacion no existe
	
	if (valida_campo(nom, nom_campo_indice) !=0)
		return(3); // campo indice no existe
	strcpy(nom_indice,nom);
	if (stricmp(nom_campo_indice,"cod") == 0){
		strcat(nom_indice,nom_ext_indice);
		if(abrir(nom_indice)){
			lcrear_inx(&indice_Prestamos);
			cargarindice(&indice_Prestamos,nom_indice); //carga el indice
			ListarPrestamosPorCodigo(nom, &indice_Prestamos, campos, campo_comp, valor_comp);
			borrarindice(&indice_Prestamos);
		}else{
			return(2); // archivo de índice no encontrado
		}
	}else{
		return(1); // indice inexistente para este archivo
	}
	return(0); 
}

//--------------------------------------------------------------------
int ListarPrestamosPorCodigo(char nom[128], tlista *l, tlista_s *campos, char campo_comp[128],char valor_comp[128])
{
	Tdatoindex x;
	FILE *ARCHIVO;
	Prestamos arch;
	int linea = 0;		// iniciala fila de impresión

	long pos = 0;
	if((ARCHIVO = fopen(nom, "rb")) == NULL){		// abre el archivo de lectura nomas
		return(1);	// Archivo no encontrado
	}else{
		if(!lvacia_inx(l)){
			lppio_inx(l);
			linfo_inx(l,&x);
			fseek(ARCHIVO,x.pos,SEEK_SET );
			fread(&arch,sizeof(arch),1,ARCHIVO);
			if (!feof(ARCHIVO)){
				ListarTituloPrestamo(nom, campos);
				if ((x.flag == 'v') || (x.flag == 'V')) {
					if (strlen(campo_comp) == 0){
						linea++;
						if (ListaCamposPrestamos(arch, campos) == 0)
							printf("\n");	
					}else{
						if (valida_campo_contiene_en_Prestamos(arch, campo_comp, valor_comp) == 0){
							linea++;
							if (ListaCamposPrestamos(arch, campos) == 0)
								printf("\n");	
						}
					}
				}
			}else{
				return(2);	// Registro no encontrado
			}

			lsig_inx(l);
			while(!lfin_inx(l)){
				linfo_inx(l,&x);
				fseek(ARCHIVO,x.pos,SEEK_SET );
				fread(&arch,sizeof(arch),1,ARCHIVO);
				if (!feof(ARCHIVO)){
					if ((x.flag == 'v') || (x.flag == 'V'))  {
						if (strlen(campo_comp) == 0){
							linea++;
							if (ListaCamposPrestamos(arch, campos) == 0)
								printf("\n");	
						}else{
							if (valida_campo_contiene_en_Prestamos(arch, campo_comp, valor_comp) == 0){
								linea++;
								if (ListaCamposPrestamos(arch, campos) == 0)
									printf("\n");	
							}
						}
					}
				}else{
					return(2);	// Registro no encontrado
				}
				lsig_inx(l);
			}
		}else{
			return(3); // El indice esta vacio
		}
		fclose(ARCHIVO);
		printf("\nCantidad de registros: %5d\n", linea);	
		return(0);
	}
}


//--------------------------------------------------------------------
//Lista todos los campos solicitados del archivo
int ListaCamposPrestamos(Prestamos arch, tlista_s *campos)
{
	Tdato_IString x;

	if(!lvacia(campos)){
		lppio(campos);
		linfo(campos,&x);
		if (stricmp(x.clave,"*") == 0){
			printf("%6d  %9d  %9d  ",arch.cod, arch.cod_socio, arch.cod_libro);
		}else{
			if (ListaUnCampoPrestamos(arch, x.clave) != 0)
				return(1); // Campo invalido
		}
		lsig(campos);
		while(!lfin(campos)){
			linfo(campos,&x);
			if (ListaUnCampoPrestamos(arch, x.clave) != 0)
				return(1); // Campo invalido
			lsig(campos);
		}
	}else{
		return(3); // El indice esta vacio
	}
	
	return(0);
}
//--------------------------------------------------------------------
//Lista un campo
int ListaUnCampoPrestamos(Prestamos arch, Tclave nom_campo)
{
	if (stricmp(nom_campo,"cod") == 0){
		printf("%6d  ",arch.cod);
	}else{
		if (stricmp(nom_campo,"cod_socio") == 0){
			printf("%9d  ",arch.cod_socio);
		}else{
			if (stricmp(nom_campo,"cod_libro") == 0){
				printf("%9d  ",arch.cod_libro);
			}else{
				printf("*invalido*  ");   // campo inexistente
			}
		}
	}
	return(0);
}

//--------------------------------------------------------------------
//Valida que un campo contiene el valor buscado
int valida_campo_contiene_en_Prestamos(Prestamos arch, char campo_comp[128],char valor_comp[128])
{
	if (stricmp(campo_comp,"cod")==0){ 
		if (arch.cod == atoi(valor_comp))
			return(0);
		else
			return(1);
	}
	if (stricmp(campo_comp,"cod_socio")==0) {
		if (arch.cod_socio == atoi(valor_comp))
			return(0);
		else
			return(1);
	}
	if (stricmp(campo_comp,"cod_libro")==0) {
		if (arch.cod_libro == atoi(valor_comp))
			return(0);
		else
			return(1);
	}
}
//--------------------------------------------------------------------
//Lista todos los campos solicitados del archivo
int ListarTituloPrestamo(char nom[128], tlista_s *campos)
{
	Tdato_IString x;

	printf("\n\nListado del archivo: %s\n\n", nom);
	if(!lvacia(campos)){
		lppio(campos);
		linfo(campos,&x);
		if (stricmp(x.clave,"*") == 0){
			printf("Codigo  Cod Socio  Cod Libro  ");
		}else{
			if (ListaTituloUnCampoPrestamos(x.clave) != 0)
				return(1); // Campo invalido
		}
		lsig(campos);
		while(!lfin(campos)){
			linfo(campos,&x);
			if (ListaTituloUnCampoPrestamos(x.clave) != 0)
				return(1); // Campo invalido
			lsig(campos);
		}
	}else{
		return(3); // El indice esta vacio
	}
	printf("\n\n");
	return(0);
}
//--------------------------------------------------------------------
//Lista un campo
int ListaTituloUnCampoPrestamos(Tclave nom_campo)
{
	if (stricmp(nom_campo,"cod") == 0){
		printf("Codigo  ");
	}else{
		if (stricmp(nom_campo,"cod_socio") == 0){
			printf("Cod Socio  ");
		}else{
			if (stricmp(nom_campo,"cod_libro") == 0){
				printf("Cod Libro  ");
			}else{
				printf("%-10.10s  ",nom_campo);	// campo inexistente
			}
		}
	}
	return(0);
}

// Editar registros de tablas segun condiciones solicitadas
int Editar(char nom[128],tlista_s *campos, char campo_comp[128],char valor_comp[128])
{
	if (valida_nom_archivo(nom) != 0)  // Verifica que es un archivo de la base
		return(1);

	if(stricmp(nom,nom_arch_Autores)==0)
		if (EditaAutores(nom, campos, campo_comp, valor_comp) != 0){
			return(2);
		}		
	if(stricmp(nom,nom_arch_Libros)==0)
		if (EditaLibros(nom, campos, campo_comp, valor_comp) != 0){
			return(2);
		}		
	if(stricmp(nom,nom_arch_Socios)==0)
		if (EditaSocios(nom, campos, campo_comp, valor_comp) != 0){
			return(2);
		}		
	if(stricmp(nom,nom_arch_Temas)==0)
		if (EditaTemas(nom, campos, campo_comp, valor_comp) != 0){
			return(2);
		}		
	if(stricmp(nom,nom_arch_Prestamos)==0)
		if (EditaPrestamos(nom, campos, campo_comp, valor_comp) != 0){
			return(2);
		}

	return(0);
}


// Modifica campos solicitados de los registros del archivo Libros que cumplen una condición
//
int EditaLibros(char nom[128],tlista_s *campos, char campo_comp[128],char valor_comp[128])
{
	FILE *ARCHIVO;
	Libros arch;

	int k = 0;
	int modificados = 0;
	int sinmodificar = 0;
	if((ARCHIVO = fopen(nom, "r+b")) == NULL){		// abre el archivo de lectura nomas
		return(1);	// Archivo no encontrado
	}else{
		fseek(ARCHIVO, k*sizeof(arch), 0);
		fread(&arch, sizeof(arch), 1, ARCHIVO);
		while (!feof(ARCHIVO)){			// finaliza con el ultimo registro del archivo
			if (((arch.flag == 'v') || (arch.flag == 'V'))  
				&& (valida_campo_contiene_en_Libros(arch, campo_comp, valor_comp) == 0)) {
				if (ModificaLibros(&arch, campos) == 0){
					fseek(ARCHIVO, k*sizeof(arch), 0);
					fwrite(&arch,sizeof(arch),1,ARCHIVO);
					modificados++;
				}else{
					sinmodificar++;
				}
			}
	   		k++;
			fseek(ARCHIVO, k*sizeof(arch), 0);
			fread(&arch, sizeof(arch), 1, ARCHIVO);
		}
		fclose(ARCHIVO);
		RecrearIndicesLibros(nom);  // recrea los índices del archivo libro antes de salir
	}
	printf("\n%d registros Actualizados y %d Sin Actualizar, de %d encontrados.\n", modificados, sinmodificar,modificados+sinmodificar);	
	return(0);
}

// Modifica los campos solicitados del archivo Libros
int ModificaLibros(Libros *arch, tlista_s *campos)
{
	Tdato_IString x;

	if(!lvacia(campos)){
		lppio(campos);
		linfo(campos,&x);
		if (ModificaUnCampoLibros(arch, x.clave, x.pos) != 0)
				return(1); // Campo invalido
		lsig(campos);
		while(!lfin(campos)){
			linfo(campos,&x);
			if (ModificaUnCampoLibros(arch, x.clave, x.pos) != 0)
				return(1); // Campo invalido
			lsig(campos);
		}
		return(0);
	}else{
		return(3); // El indice esta vacio
	}
	
}
//--------------------------------------------------------------------
//Lista un campo
int ModificaUnCampoLibros(Libros *arch, Tclave valor, long campo)
{
	// Debe validar si es el campo es clave primaria, que no exista ya en el archivo
	// para no crear clave duplicada
	char nom_campo[128];
	char campo_texto[128];

	int valor_num;

	switch (campo){
		case 1:		
			strcpy(nom_campo,"cod");	// convierte el nro en el nombre de campo equivalente
			valor_num = atoi(valor);
			if (valor_num != 0){	// el codigo no puede ser cero
				if (ClavePrincipalNoExiste(nom_arch_Libros, valor_num) == 0){
					if (ValidaContraPrestamos(nom_arch_Prestamos,"cod_libro",itoa(arch->cod,campo_texto,10)) == 0){
						arch->cod = valor_num;
						return(0);
					}else{
						printf("\nNo puede modificar el campo '%s' porque existe al menos un registro relacionado en el archivo '%s'.\n",nom_campo,nom_arch_Prestamos);	
					}
				}else{
					printf("\nNo puede modificar la clave principal porque ya existe una con ese valor\n");	
				}
			}else{
				printf("\nNo puede ingresar una clave con valor cero\n");	
			}
			break;
	
		case 2:		
			strcpy(nom_campo,"cod_tema");	// convierte el nro en el nombre de campo equivalente
			if (ClavePrincipalNoExiste_s(nom_arch_Temas,valor) != 0){  // Deberia existir el Tema para poder cambiarlo en el Libro
				strcpy(arch->cod_tema,valor);
				return(0);
			}else{
				printf("\nNo puede modificar el campo '%s' porque el tema no existe en el archivo '%s'.\n",nom_campo,nom_arch_Libros);	
			}
			break;
	
		case 3:		
			strcpy(nom_campo,"titulo");	// convierte el nro en el nombre de campo equivalente
			strcpy(arch->titulo,valor);
			return(0);
			break;
	
		case 4:		
			strcpy(nom_campo,"cod_autor");	// convierte el nro en el nombre de campo equivalente
			if (ClavePrincipalNoExiste_s(nom_arch_Autores,valor) != 0){  // Deberia existir el Autor para poder cambiarlo en el Libro
				strcpy(arch->cod_autor,valor);
				return(0);
			}else{
				printf("\nNo puede modificar el campo '%s' porque el autor no existe en el archivo '%s'.\n",nom_campo,nom_arch_Libros);	
			}
			break;
	
		case 5:		
			strcpy(nom_campo,"ubicacion");	// convierte el nro en el nombre de campo equivalente
			strcpy(arch->ubicacion,valor);
			return(0);
			break;
	}
	return(1);	// retorna error en caso que no haya podido modificar el campo por cualquier motivo
}

// Modifica campos solicitados de los registros del archivo Temas que cumplen una condición
//
int EditaTemas(char nom[128],tlista_s *campos, char campo_comp[128],char valor_comp[128])
{
	FILE *ARCHIVO;
	Temas arch;

	int k = 0;
	int modificados = 0;
	int sinmodificar = 0;
	if((ARCHIVO = fopen(nom, "r+b")) == NULL){		// abre el archivo de lectura nomas
		return(1);	// Archivo no encontrado
	}else{
		fseek(ARCHIVO, k*sizeof(arch), 0);
		fread(&arch, sizeof(arch), 1, ARCHIVO);
		while (!feof(ARCHIVO)){			// finaliza con el ultimo registro del archivo
			if (((arch.flag == 'v') || (arch.flag == 'V'))  
				&& (valida_campo_contiene_en_Temas(arch, campo_comp, valor_comp) == 0)) {
				if (ModificaTemas(&arch, campos) == 0){
					fseek(ARCHIVO, k*sizeof(arch), 0);
					fwrite(&arch,sizeof(arch),1,ARCHIVO);
					modificados++;
				}else{
					sinmodificar++;
				}
			}
	   		k++;
			fseek(ARCHIVO, k*sizeof(arch), 0);
			fread(&arch, sizeof(arch), 1, ARCHIVO);
		}
		fclose(ARCHIVO);
		RecrearIndicesTemas(nom);  // recrea los índices del archivo libro antes de salir
	}
	printf("\n%d registros Actualizados y %d Sin Actualizar, de %d encontrados.\n", modificados, sinmodificar,modificados+sinmodificar);	
	return(0);
}

// Modifica los campos solicitados del archivo temas
int ModificaTemas(Temas *arch, tlista_s *campos)
{
	Tdato_IString x;

	if(!lvacia(campos)){
		lppio(campos);
		linfo(campos,&x);
		if (ModificaUnCampoTemas(arch, x.clave, x.pos) != 0)
				return(1); // Campo invalido
		lsig(campos);
		while(!lfin(campos)){
			linfo(campos,&x);
			if (ModificaUnCampoTemas(arch, x.clave, x.pos) != 0)
				return(1); // Campo invalido
			lsig(campos);
		}
		return(0);
	}else{
		return(3); // El indice esta vacio
	}
	
}
//--------------------------------------------------------------------
//Lista un campo
int ModificaUnCampoTemas(Temas *arch, Tclave valor, long campo)
{
	// Debe validar si es el campo es clave primaria, que no exista ya en el archivo
	// para no crear clave duplicada
	char nom_campo[128];
	int valor_num;

	if (campo == 1){ 
		strcpy(nom_campo,"cod");	// convierte el nro en el nombre de campo equivalente
		valor_num = strlen(valor);
		if (valor_num != 0){	// el codigo no tener longitud cero o blanco
			if (ClavePrincipalNoExiste_s(nom_arch_Temas, valor) == 0){
				if (ValidaContraLibros(nom_arch_Libros,"cod_tema",arch->cod) == 0){
					strcpy(arch->cod,valor);
					return(0);
				}else{
					printf("\nNo puede modificar el campo '%s' porque existe al menos un registro relacionado en el archivo '%s'.\n",nom_campo,nom_arch_Libros);	
				}
			}else{
				printf("\nNo puede modificar la clave principal porque ya existe una con ese valor\n");	
			}
		}else{
			printf("\nNo puede ingresar una clave en blanco\n");	
		}
	}
	
	return(1);	// retorna error en caso que no haya podido modificar el campo por cualquier motivo
}

// Modifica campos solicitados de los registros del archivo Autores que cumplen una condición
//
int EditaAutores(char nom[128],tlista_s *campos, char campo_comp[128],char valor_comp[128])
{
	FILE *ARCHIVO;
	Autores arch;

	int k = 0;
	int modificados = 0;
	int sinmodificar = 0;
	if((ARCHIVO = fopen(nom, "r+b")) == NULL){		// abre el archivo de lectura nomas
		return(1);	// Archivo no encontrado
	}else{
		fseek(ARCHIVO, k*sizeof(arch), 0);
		fread(&arch, sizeof(arch), 1, ARCHIVO);
		while (!feof(ARCHIVO)){			// finaliza con el ultimo registro del archivo
			if (((arch.flag == 'v') || (arch.flag == 'V'))  
				&& (valida_campo_contiene_en_Autores(arch, campo_comp, valor_comp) == 0)) {
				if (ModificaAutores(&arch, campos) == 0){
					fseek(ARCHIVO, k*sizeof(arch), 0);
					fwrite(&arch,sizeof(arch),1,ARCHIVO);
					modificados++;
				}else{
					sinmodificar++;
				}
			}
	   		k++;
			fseek(ARCHIVO, k*sizeof(arch), 0);
			fread(&arch, sizeof(arch), 1, ARCHIVO);
		}
		fclose(ARCHIVO);
		RecrearIndicesAutores(nom);  // recrea los índices del archivo libro antes de salir
	}
	printf("\n%d registros Actualizados y %d Sin Actualizar, de %d encontrados.\n", modificados, sinmodificar,modificados+sinmodificar);	
	return(0);
}

// Modifica los campos solicitados del archivo Autores
int ModificaAutores(Autores *arch, tlista_s *campos)
{
	Tdato_IString x;

	if(!lvacia(campos)){
		lppio(campos);
		linfo(campos,&x);
		if (ModificaUnCampoAutores(arch, x.clave, x.pos) != 0)
				return(1); // Campo invalido
		lsig(campos);
		while(!lfin(campos)){
			linfo(campos,&x);
			if (ModificaUnCampoAutores(arch, x.clave, x.pos) != 0)
				return(1); // Campo invalido
			lsig(campos);
		}
		return(0);
	}else{
		return(3); // El indice esta vacio
	}
	
}
//--------------------------------------------------------------------
//Lista un campo
int ModificaUnCampoAutores(Autores *arch, Tclave valor, long campo)
{
	// Debe validar si es el campo es clave primaria, que no exista ya en el archivo
	// para no crear clave duplicada
	char nom_campo[128];
	int valor_num;

	if (campo == 1){ 
		strcpy(nom_campo,"cod");	// convierte el nro en el nombre de campo equivalente
		valor_num = strlen(valor);
		if (valor_num != 0){	// el codigo no tener longitud cero o blanco
			if (ClavePrincipalNoExiste_s(nom_arch_Autores, valor) == 0){
				if (ValidaContraLibros(nom_arch_Libros,"cod_autor",arch->cod) == 0){
					strcpy(arch->cod,valor);
					return(0);
				}else{
					printf("\nNo puede modificar el campo '%s' porque existe al menos un registro relacionado en el archivo '%s'.\n",nom_campo,nom_arch_Libros);	
				}
			}else{
				printf("\nNo puede modificar la clave principal porque ya existe una con ese valor\n");	
			}
		}else{
			printf("\nNo puede ingresar una clave en blanco\n");	
		}
	}
	
	return(1);	// retorna error en caso que no haya podido modificar el campo por cualquier motivo
}

// Modifica campos solicitados de los registros del archivo Socios que cumplen una condición
//
int EditaSocios(char nom[128],tlista_s *campos, char campo_comp[128],char valor_comp[128])
{
	FILE *ARCHIVO;
	Socios arch;

	int k = 0;
	int modificados = 0;
	int sinmodificar = 0;
	if((ARCHIVO = fopen(nom, "r+b")) == NULL){		// abre el archivo de lectura nomas
		return(1);	// Archivo no encontrado
	}else{
		fseek(ARCHIVO, k*sizeof(arch), 0);
		fread(&arch, sizeof(arch), 1, ARCHIVO);
		while (!feof(ARCHIVO)){			// finaliza con el ultimo registro del archivo
			if (((arch.flag == 'v') || (arch.flag == 'V'))  
				&& (valida_campo_contiene_en_Socios(arch, campo_comp, valor_comp) == 0)) {
				if (ModificaSocios(&arch, campos) == 0){
					fseek(ARCHIVO, k*sizeof(arch), 0);
					fwrite(&arch,sizeof(arch),1,ARCHIVO);
					modificados++;
				}else{
					sinmodificar++;
				}
			}
	   		k++;
			fseek(ARCHIVO, k*sizeof(arch), 0);
			fread(&arch, sizeof(arch), 1, ARCHIVO);
		}
		fclose(ARCHIVO);
		RecrearIndicesSocios(nom);  // recrea los índices del archivo libro antes de salir
	}
	printf("\n%d registros Actualizados y %d Sin Actualizar, de %d encontrados.\n", modificados, sinmodificar,modificados+sinmodificar);	
	return(0);
}

// Modifica los campos solicitados del archivo Libros
int ModificaSocios(Socios *arch, tlista_s *campos)
{
	Tdato_IString x;

	if(!lvacia(campos)){
		lppio(campos);
		linfo(campos,&x);
		if (ModificaUnCampoSocios(arch, x.clave, x.pos) != 0)
				return(1); // Campo invalido
		lsig(campos);
		while(!lfin(campos)){
			linfo(campos,&x);
			if (ModificaUnCampoSocios(arch, x.clave, x.pos) != 0)
				return(1); // Campo invalido
			lsig(campos);
		}
		return(0);
	}else{
		return(3); // El indice esta vacio
	}
	
}
//--------------------------------------------------------------------
//Lista un campo
int ModificaUnCampoSocios(Socios *arch, Tclave valor, long campo)
{
	// Debe validar si es el campo es clave primaria, que no exista ya en el archivo
	// para no crear clave duplicada
	char nom_campo[128];
	char campo_texto[128];
	int valor_num;

	switch (campo){
		case 1:		
			strcpy(nom_campo,"cod");	// convierte el nro en el nombre de campo equivalente
			valor_num = atoi(valor);
			if (valor_num != 0){	// el codigo no puede ser cero
				if (ClavePrincipalNoExiste(nom_arch_Socios, valor_num) == 0){
					if (ValidaContraPrestamos(nom_arch_Prestamos,"cod_socio",itoa(arch->cod,campo_texto,10)) == 0){
						arch->cod = valor_num;
						return(0);
					}else{
						printf("\nNo puede modificar el campo '%s' porque existe al menos un registro relacionado en el archivo '%s'.\n",nom_campo,nom_arch_Prestamos);	
					}
				}else{
					printf("\nNo puede modificar la clave principal porque ya existe una con ese valor\n");	
				}
			}else{
				printf("\nNo puede ingresar una clave con valor cero\n");	
			}
			break;
	
		case 2:		
			strcpy(nom_campo,"nombreyapellido");	// convierte el nro en el nombre de campo equivalente
			strcpy(arch->nombreyapellido,valor);
			return(0);
			break;
	
		case 3:		
			strcpy(nom_campo,"dni");	// convierte el nro en el nombre de campo equivalente
			arch->dni = atoi(valor);
			return(0);
			break;
	
		case 4:		
			strcpy(nom_campo,"direccion");	// convierte el nro en el nombre de campo equivalente
			strcpy(arch->direccion,valor);
			return(0);
			break;
	
	}
	return(1);	// retorna error en caso que no haya podido modificar el campo por cualquier motivo
}

// Modifica campos solicitados de los registros del archivo Prestamos que cumplen una condición
//
int EditaPrestamos(char nom[128],tlista_s *campos, char campo_comp[128],char valor_comp[128])
{
	FILE *ARCHIVO;
	Prestamos arch;

	int k = 0;
	int modificados = 0;
	int sinmodificar = 0;
	if((ARCHIVO = fopen(nom, "r+b")) == NULL){		// abre el archivo de lectura nomas
		return(1);	// Archivo no encontrado
	}else{
		fseek(ARCHIVO, k*sizeof(arch), 0);
		fread(&arch, sizeof(arch), 1, ARCHIVO);
		while (!feof(ARCHIVO)){			// finaliza con el ultimo registro del archivo
			if (((arch.flag == 'v') || (arch.flag == 'V'))  
				&& (valida_campo_contiene_en_Prestamos(arch, campo_comp, valor_comp) == 0)) {
				if (ModificaPrestamos(&arch, campos) == 0){
					fseek(ARCHIVO, k*sizeof(arch), 0);
					fwrite(&arch,sizeof(arch),1,ARCHIVO);
					modificados++;
				}else{
					sinmodificar++;
				}
			}
	   		k++;
			fseek(ARCHIVO, k*sizeof(arch), 0);
			fread(&arch, sizeof(arch), 1, ARCHIVO);
		}
		fclose(ARCHIVO);
		RecrearIndicesPrestamos(nom);  // recrea los índices del archivo libro antes de salir
	}
	printf("\n%d registros Actualizados y %d Sin Actualizar, de %d encontrados.\n", modificados, sinmodificar,modificados+sinmodificar);	
	return(0);
}

// Modifica los campos solicitados del archivo Libros
int ModificaPrestamos(Prestamos *arch, tlista_s *campos)
{
	Tdato_IString x;

	if(!lvacia(campos)){
		lppio(campos);
		linfo(campos,&x);
		if (ModificaUnCampoPrestamos(arch, x.clave, x.pos) != 0)
				return(1); // Campo invalido
		lsig(campos);
		while(!lfin(campos)){
			linfo(campos,&x);
			if (ModificaUnCampoPrestamos(arch, x.clave, x.pos) != 0)
				return(1); // Campo invalido
			lsig(campos);
		}
		return(0);
	}else{
		return(3); // El indice esta vacio
	}
	
}
//--------------------------------------------------------------------
//Lista un campo
int ModificaUnCampoPrestamos(Prestamos *arch, Tclave valor, long campo)
{
	// Debe validar si es el campo es clave primaria, que no exista ya en el archivo
	// para no crear clave duplicada
	char nom_campo[128];
	char campo_texto[128];
	int valor_num;

	switch (campo){
		case 1:		
			strcpy(nom_campo,"cod");	// convierte el nro en el nombre de campo equivalente
			valor_num = atoi(valor);
			if (valor_num != 0){	// el codigo no puede ser cero
				if (ClavePrincipalNoExiste(nom_arch_Prestamos, valor_num) == 0){
					arch->cod = valor_num;
					return(0);
				}else{
					printf("\nNo puede modificar la clave principal porque ya existe una con ese valor\n");	
				}
			}else{
				printf("\nNo puede ingresar una clave con valor cero\n");	
			}
			break;
	
		case 2:		
			strcpy(nom_campo,"cod_socio");	// convierte el nro en el nombre de campo equivalente
			if (ClavePrincipalNoExiste(nom_arch_Socios, atoi(valor)) == 0){
				printf("\nNo puede modificar el socio del Prestamo ya que no existe en la tabla %s\n",nom_arch_Socios);	
			}else{
				arch->cod_socio = atoi(valor);
				return(0);
			}
			break;
	
		case 3:		
			strcpy(nom_campo,"cod_libro");	// convierte el nro en el nombre de campo equivalente
			if (ClavePrincipalNoExiste(nom_arch_Libros, atoi(valor)) == 0){
				printf("\nNo puede modificar el libro del Prestamo ya que no existe en la tabla %s\n",nom_arch_Libros);	
			}else{
				arch->cod_libro = atoi(valor);
				return(0);
			}
			break;
	

	}
	return(1);	// retorna error en caso que no haya podido modificar el campo por cualquier motivo
}

// Eliminar registros de tablas segun condiciones solicitadas
int Eliminar(char nom[128], char campo_comp[128],char valor_comp[128])
{
	if (valida_nom_archivo(nom) != 0)  // Verifica que es un archivo de la base
		return(1);

	if(stricmp(nom,nom_arch_Autores)==0)
		if (EliminaAutores(nom, campo_comp, valor_comp) != 0){
			return(2);
		}		
	if(stricmp(nom,nom_arch_Libros)==0)
		if (EliminaLibros(nom, campo_comp, valor_comp) != 0){
			return(2);
		}		
	if(stricmp(nom,nom_arch_Socios)==0)
		if (EliminaSocios(nom, campo_comp, valor_comp) != 0){
			return(2);
		}		
	if(stricmp(nom,nom_arch_Temas)==0)
		if (EliminaTemas(nom, campo_comp, valor_comp) != 0){
			return(2);
		}		
	if(stricmp(nom,nom_arch_Prestamos)==0)
		if (EliminaPrestamos(nom, campo_comp, valor_comp) != 0){
			return(2);
		}

	return(0);
}


//--------------------------------------------------------------------
// Eliminar los registros del archivo segun la condicion ingresada
int EliminaLibros(char nom[128], char campo_comp[128],char valor_comp[128])
{
	FILE *ARCHIVO;
	Libros arch;

	int k = 0;
	int eliminados = 0;
	if((ARCHIVO = fopen(nom, "r+b")) == NULL){		// abre el archivo de lectura nomas
		return(1);	// Archivo no encontrado
	}else{
		fseek(ARCHIVO, k*sizeof(arch), 0);
		fread(&arch, sizeof(arch), 1, ARCHIVO);
		while (!feof(ARCHIVO)){			// finaliza con el ultimo registro del archivo
			if (((arch.flag == 'v') || (arch.flag == 'V'))  
				&& (valida_campo_contiene_en_Libros(arch, campo_comp, valor_comp) == 0) 
				&& (VerificaRelacionesConLibros(arch) == 0)){
	   			arch.flag = 'F';	
				fseek(ARCHIVO, k*sizeof(arch), 0);
				fwrite(&arch,sizeof(arch),1,ARCHIVO);
				eliminados++;
			}
	   		k++;
			fseek(ARCHIVO, k*sizeof(arch), 0);
			fread(&arch, sizeof(arch), 1, ARCHIVO);
		}
		fclose(ARCHIVO);
		RecrearIndicesLibros(nom);  // recrea los índices del archivo libro antes de salir
	}
	printf("\nRegistros eliminados: %5d\n", eliminados);	
	return(0);
}

//--------------------------------------------------------------------
//Verifica que el registro de libro a eliminar no tenga valores asociados vigentes en otras tablas
int VerificaRelacionesConLibros(Libros arch)
{
// Valida contra Prestamos
	char valor_comp[128];
	sprintf (valor_comp,"%d",arch.cod);

	return(ValidaContraPrestamos(nom_arch_Prestamos,"cod_libro",valor_comp));
}

//--------------------------------------------------------------------
int ValidaContraPrestamos(char nom[128], char campo_comp[128],char valor_comp[128])
{
	FILE *ARCHIVO;
	Prestamos arch;

	if((ARCHIVO = fopen(nom, "rb")) == NULL){		// abre el archivo de lectura nomas
		return(1);	// Archivo no encontrado
	}else{
		fseek(ARCHIVO,0,SEEK_SET );
		fread(&arch,sizeof(arch),1,ARCHIVO);
		while (!feof(ARCHIVO)){
			if ((arch.flag == 'v') || (arch.flag == 'V'))  {
				if (valida_campo_contiene_en_Prestamos(arch, campo_comp, valor_comp) == 0){
					fclose(ARCHIVO);
					return(2);	// Registro encontrado
				}
			}
			fread(&arch,sizeof(arch),1,ARCHIVO);
		}	
		fclose(ARCHIVO);
		return(0);
	}
}
//--------------------------------------------------------------------
//Recrear indices de Libros después de una Alta ,Baja o Modificacion
void RecrearIndicesLibros(char nom[128])
{
	tlista indice;				// Indice del Codigo Libro
	char nom_indice[128];

	tlista_s ind_titulo;		// Indice del Titulo del Libro
	char nom_ind_titulo[128];

	//Define el índice por Titulo
	strcpy(nom_ind_titulo,nom);
	strcat(nom_ind_titulo,nom_ext_ind2);

	//Define el índice por Codigo de Libro 
	strcpy(nom_indice,nom);
	strcat(nom_indice,nom_ext_indice);

	lcrear_inx(&indice);		// Crear índice primario
	lcrear(&ind_titulo);		// crear indice secundario
	LibroALista(&indice,&ind_titulo,nom);
	grabarindice(&indice,nom_indice);   // graba el índice primario Cod Libro
	grabarindice_s(&ind_titulo,nom_ind_titulo); // graba el índice secundario Titulo Libro
}

//--------------------------------------------------------------------
// Eliminar los registros del archivo segun la condicion ingresada
int EliminaTemas(char nom[128], char campo_comp[128],char valor_comp[128])
{
	FILE *ARCHIVO;
	Temas arch;

	int k = 0;
	int eliminados = 0;
	if((ARCHIVO = fopen(nom, "r+b")) == NULL){		// abre el archivo de lectura nomas
		return(1);	// Archivo no encontrado
	}else{
		fseek(ARCHIVO, k*sizeof(arch), 0);
		fread(&arch, sizeof(arch), 1, ARCHIVO);
		while (!feof(ARCHIVO)){			// finaliza con el ultimo registro del archivo
			if (((arch.flag == 'v') || (arch.flag == 'V'))  
				&& (valida_campo_contiene_en_Temas(arch, campo_comp, valor_comp) == 0) 
				&& (VerificaRelacionesConTemas(arch) == 0)){
	   			arch.flag = 'F';	
				fseek(ARCHIVO, k*sizeof(arch), 0);
				fwrite(&arch,sizeof(arch),1,ARCHIVO);
				eliminados++;
			}
	   		k++;
			fseek(ARCHIVO, k*sizeof(arch), 0);
			fread(&arch, sizeof(arch), 1, ARCHIVO);
		}
		fclose(ARCHIVO);
		RecrearIndicesTemas(nom);  // recrea los índices del archivo libro antes de salir
	}
	printf("\nRegistros eliminados: %5d\n", eliminados);	
	return(0);
}
//--------------------------------------------------------------------
//Verifica que el registro de Tema a eliminar no tenga valores asociados vigentes en otras tablas
int VerificaRelacionesConTemas(Temas arch)
{
// Valida contra Libros

	return(ValidaContraLibros(nom_arch_Libros,"cod_tema",arch.cod));
}

//--------------------------------------------------------------------
int ValidaContraLibros(char nom[128], char campo_comp[128],char valor_comp[128])
{
	FILE *ARCHIVO;
	Libros arch;

	if((ARCHIVO = fopen(nom, "rb")) == NULL){		// abre el archivo de lectura nomas
		return(1);	// Archivo no encontrado
	}else{
		fseek(ARCHIVO,0,SEEK_SET );
		fread(&arch,sizeof(arch),1,ARCHIVO);
		while (!feof(ARCHIVO)){
			if ((arch.flag == 'v') || (arch.flag == 'V'))  {
				if (valida_campo_contiene_en_Libros(arch, campo_comp, valor_comp) == 0){
					fclose(ARCHIVO);
					return(2);	// Registro encontrado
				}
			}
			fread(&arch,sizeof(arch),1,ARCHIVO);
		}	
		fclose(ARCHIVO);
		return(0);
	}
}
//--------------------------------------------------------------------
//Recrear indices de Temas después de una Alta ,Baja o Modificacion
void RecrearIndicesTemas(char nom[128])
{
	tlista_s indice;
	char nom_indice[128];

	strcpy(nom_indice,nom);
	strcat(nom_indice,nom_ext_indice);

	lcrear(&indice);		// Crear índice primario
	TemaALista(&indice,nom);
	grabarindice_s(&indice,nom_indice);
}
//--------------------------------------------------------------------
// Eliminar los registros del archivo segun la condicion ingresada
int EliminaSocios(char nom[128], char campo_comp[128],char valor_comp[128])
{
	FILE *ARCHIVO;
	Socios arch;

	int k = 0;
	int eliminados = 0;
	if((ARCHIVO = fopen(nom, "r+b")) == NULL){		// abre el archivo de lectura nomas
		return(1);	// Archivo no encontrado
	}else{
		fseek(ARCHIVO, k*sizeof(arch), 0);
		fread(&arch, sizeof(arch), 1, ARCHIVO);
		while (!feof(ARCHIVO)){			// finaliza con el ultimo registro del archivo
			if (((arch.flag == 'v') || (arch.flag == 'V'))  
				&& (valida_campo_contiene_en_Socios(arch, campo_comp, valor_comp) == 0) 
				&& (VerificaRelacionesConSocios(arch) == 0)){
	   			arch.flag = 'F';	
				fseek(ARCHIVO, k*sizeof(arch), 0);
				fwrite(&arch,sizeof(arch),1,ARCHIVO);
				eliminados++;
			}
	   		k++;
			fseek(ARCHIVO, k*sizeof(arch), 0);
			fread(&arch, sizeof(arch), 1, ARCHIVO);
		}
		fclose(ARCHIVO);
		RecrearIndicesSocios(nom);  // recrea los índices del archivo libro antes de salir
	}
	printf("\nRegistros eliminados: %5d\n", eliminados);	
	return(0);
}
//--------------------------------------------------------------------
//Verifica que el registro de Socio a eliminar no tenga valores asociados vigentes en otras tablas
int VerificaRelacionesConSocios(Socios arch)
{
// Valida contra Prestamos
	char valor_comp[128];
	sprintf (valor_comp,"%d",arch.cod);

	return(ValidaContraPrestamos(nom_arch_Prestamos,"cod_socio",valor_comp));
}

//--------------------------------------------------------------------
//Recrear indices de Socios después de una Alta ,Baja o Modificacion
void RecrearIndicesSocios(char nom[128])
{
	tlista_s ind_NYA;		// Indice secundario por Nombre y Apellido del Socio
	char nom_ind_NYA[128];

	tlista indice;				// Indice del Codigo Socio
	char nom_indice[128];

	//Define el índice por Nombre y Apellido
	strcpy(nom_ind_NYA,nom);
	strcat(nom_ind_NYA,nom_ext_ind2);

	//Define el índice por Codigo de Socios 
	strcpy(nom_indice,nom);
	strcat(nom_indice,nom_ext_indice);

	lcrear_inx(&indice);		// Crear índice primario
	lcrear(&ind_NYA);		// crear indice secundario
	SocioALista(&indice,&ind_NYA,nom);
	grabarindice(&indice,nom_indice);   // graba el índice primario Cod Socio
	grabarindice_s(&ind_NYA,nom_ind_NYA); // graba el índice secundario Titulo Socios
}
//--------------------------------------------------------------------
// Eliminar los registros del archivo segun la condicion ingresada
int EliminaAutores(char nom[128], char campo_comp[128],char valor_comp[128])
{
	FILE *ARCHIVO;
	Autores arch;

	int k = 0;
	int eliminados = 0;
	if((ARCHIVO = fopen(nom, "r+b")) == NULL){		// abre el archivo de lectura nomas
		return(1);	// Archivo no encontrado
	}else{
		fseek(ARCHIVO, k*sizeof(arch), 0);
		fread(&arch, sizeof(arch), 1, ARCHIVO);
		while (!feof(ARCHIVO)){			// finaliza con el ultimo registro del archivo
			if (((arch.flag == 'v') || (arch.flag == 'V'))  
				&& (valida_campo_contiene_en_Autores(arch, campo_comp, valor_comp) == 0) 
				&& (VerificaRelacionesConAutores(arch) == 0)){
	   			arch.flag = 'F';	
				fseek(ARCHIVO, k*sizeof(arch), 0);
				fwrite(&arch,sizeof(arch),1,ARCHIVO);
				eliminados++;
			}
	   		k++;
			fseek(ARCHIVO, k*sizeof(arch), 0);
			fread(&arch, sizeof(arch), 1, ARCHIVO);
		}
		fclose(ARCHIVO);
		RecrearIndicesAutores(nom);  // recrea los índices del archivo libro antes de salir
	}
	printf("\nRegistros eliminados: %5d\n", eliminados);	
	return(0);
}
//--------------------------------------------------------------------
//Verifica que el registro de Autores a eliminar no tenga valores asociados vigentes en otras tablas
int VerificaRelacionesConAutores(Autores arch)
{
// Valida contra Libros

	return(ValidaContraLibros(nom_arch_Libros,"cod_autor",arch.cod));
}


//--------------------------------------------------------------------
//Recrear indices de Autores después de una Alta ,Baja o Modificacion
void RecrearIndicesAutores(char nom[128])
{
	tlista_s indice;
	char nom_indice[128];

	strcpy(nom_indice,nom);
	strcat(nom_indice,nom_ext_indice);

	lcrear(&indice);		// Crear índice primario
	AutorALista(&indice,nom);
	grabarindice_s(&indice,nom_indice);
}
//--------------------------------------------------------------------
// Eliminar los registros del archivo segun la condicion ingresada
int EliminaPrestamos(char nom[128], char campo_comp[128],char valor_comp[128])
{
	FILE *ARCHIVO;
	Prestamos arch;

	int k = 0;
	int eliminados = 0;
	if((ARCHIVO = fopen(nom, "r+b")) == NULL){		// abre el archivo de lectura nomas
		return(1);	// Archivo no encontrado
	}else{
		fseek(ARCHIVO, k*sizeof(arch), 0);
		fread(&arch, sizeof(arch), 1, ARCHIVO);
		while (!feof(ARCHIVO)){			// finaliza con el ultimo registro del archivo
			if (((arch.flag == 'v') || (arch.flag == 'V'))  
				&& (valida_campo_contiene_en_Prestamos(arch, campo_comp, valor_comp) == 0) 
				&& (VerificaRelacionesConPrestamos(arch) == 0)){
	   			arch.flag = 'F';	
				fseek(ARCHIVO, k*sizeof(arch), 0);
				fwrite(&arch,sizeof(arch),1,ARCHIVO);
				eliminados++;
			}
	   		k++;
			fseek(ARCHIVO, k*sizeof(arch), 0);
			fread(&arch, sizeof(arch), 1, ARCHIVO);
		}
		fclose(ARCHIVO);
		RecrearIndicesPrestamos(nom);  // recrea los índices del archivo libro antes de salir
	}
	printf("\nRegistros eliminados: %5d\n", eliminados);	
	return(0);
}
//--------------------------------------------------------------------
//Verifica que el registro de Prestamos a eliminar no tenga valores asociados vigentes en otras tablas
int VerificaRelacionesConPrestamos(Prestamos arch)
{
// No existe ninguna relacion que impida dar de baja un Prestamo

	return(0);
}
//--------------------------------------------------------------------
//Recrear indices de Prestamos después de una Alta ,Baja o Modificacion
void RecrearIndicesPrestamos(char nom[128])
{
	tlista indice;				// Indice del Codigo Prestamo
	char nom_indice[128];

	//Define el índice por Codigo de Socios 
	strcpy(nom_indice,nom);
	strcat(nom_indice,nom_ext_indice);

	lcrear_inx(&indice);		// Crear índice primario
	PrestamoALista(&indice,nom);
	grabarindice(&indice,nom_indice);   // graba el índice primario Cod Prestamo
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
int grabarindice_s(tlista_s *l, char nom[128])
{
	FILE *INDEX;
	IndexS d;
	Tdato_IString ind;

	if((INDEX = fopen(nom, "wb")) == NULL){
		return(1);
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
		fclose(INDEX);
		return(0);
	}
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
//--------------------------------------------------------------------
//Valida la existencia de un campo en una estructura de archivo
int valida_campo(char nom[128], char nom_campo[128])
{
	if(stricmp(nom,nom_arch_Libros)==0){
		if((stricmp(nom_campo,"cod")==0) || (stricmp(nom_campo,"flag")==0) ||
			(stricmp(nom_campo,"cod_tema")==0) || (stricmp(nom_campo,"titulo")==0) ||
			(stricmp(nom_campo,"cod_autor")==0) || (stricmp(nom_campo,"ubicacion")==0)){
			return(0);
		}else{
			return(1);
		}
	}
	if(stricmp(nom,nom_arch_Autores)==0){
		if((stricmp(nom_campo,"cod")==0) || (stricmp(nom_campo,"flag")==0)){
			return(0);
		}else{
			return(1);
		}
	}
	if(stricmp(nom,nom_arch_Socios)==0){
		if((stricmp(nom_campo,"cod")==0) || (stricmp(nom_campo,"flag")==0) ||
			(stricmp(nom_campo,"nombreyapellido")==0) || (stricmp(nom_campo,"dni")==0) ||
			(stricmp(nom_campo,"direccion")==0)){
			return(0);
		}else{
			return(1);
		}
	}
	if(stricmp(nom,nom_arch_Temas)==0){
		if((stricmp(nom_campo,"cod")==0) || (stricmp(nom_campo,"flag")==0)){
			return(0);
		}else{
			return(1);
		}
	}
	if(stricmp(nom,nom_arch_Prestamos)==0){
		if((stricmp(nom_campo,"cod")==0) || (stricmp(nom_campo,"flag")==0) ||
			(stricmp(nom_campo,"cod_socio")==0) || (stricmp(nom_campo,"cod_libro")==0)){
			return(0);
		}else{
			return(1);
		}
	}
	return(1);
}

//--------------------------------------------------------------------
//Valida el nombre del archivo
int valida_nom_archivo(char nom[128])
{
	if(stricmp(nom,nom_arch_Libros)==0)
		return(0);
	if(stricmp(nom,nom_arch_Temas)==0)
		return(0);
	if(stricmp(nom,nom_arch_Prestamos)==0)
		return(0);
	if(stricmp(nom,nom_arch_Autores)==0)
		return(0);
	if(stricmp(nom,nom_arch_Socios)==0)
		return(0);
	// si no es ninguno de los anteriores entonces no existe
	return(1);
}

void incializar_archivos()
{
	strcpy(nom_arch_Libros,"LIBROS");
	strcpy(nom_arch_Temas,"TEMAS");
	strcpy(nom_arch_Prestamos,"PRESTAMOS");
	strcpy(nom_arch_Autores,"AUTORES");
	strcpy(nom_arch_Socios,"SOCIOS");
}	

//--------------------------------------------------------------------
// Verifica si la clave principal ya existe
int ClavePrincipalNoExiste(char nom[128], Tclaveindex valor)
{
	int existe;

	tlista		indice;		

	char nom_indice[128];
	strcpy(nom_indice,nom);
	strcat(nom_indice,nom_ext_indice);
	
	if ((stricmp(nom,nom_arch_Libros) == 0) || (stricmp(nom,nom_arch_Socios) == 0) || (stricmp(nom,nom_arch_Prestamos) == 0)){
		lcrear_inx(&indice);
		if(cargarindice(&indice,nom_indice) != 0){    //carga el indice
			return(1); // Error al abrir el archivo de Indices
		}
		lbuscar_inx(&indice,valor,&existe);
	}

	if (existe){
		return(1); // ya existe la clave en la base 
	}else{
		return(0);
	}
}
//--------------------------------------------------------------------
// Verifica si la clave principal "formato string" ya existe
int ClavePrincipalNoExiste_s(char nom[128], Tclave valor)
{
	int existe;

	tlista_s	indice;	

	char nom_indice[128];
	strcpy(nom_indice,nom);
	strcat(nom_indice,nom_ext_indice);
	
	if ((stricmp(nom,nom_arch_Temas) == 0) || (stricmp(nom,nom_arch_Autores) == 0)){
		lcrear(&indice);
		if(cargarindice_s(&indice,nom_indice) != 0){    //carga el indice
			return(1); // Error al abrir el archivo de Indices
		}
		lbuscar(&indice,valor,&existe);
	}

	if (existe){
		return(1); // ya existe la clave en la base 
	}else{
		return(0);
	}
}
