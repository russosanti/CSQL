#include <stdio.h>
#include <conio.h>
#include <stdlib.h>  // PROBLEMA CON EL CARGAR LIBRO O LEER LIBROO
#include <iostream>
#include <string>               
using namespace std;
#include <sys\stat.h>
#define maxt 30
#define maxDBname 128	// long maxima nombre base de datos
#define maxSQL 1028
#include "listas.h"
#include "TDATOLS.h"
#define	long_reg_DB	99	// longitud en bytes del registro Estructura de la Base de Datos
#define long_reg_tabla 291  // longitud en bytes del registro Estructura de la Tabla
#define long_reg_campo 310  // longitud en bytes del registro Estrucutra del Campo
#define long_nom_columna 30	// longitud en bytes del Nombre de una Columna de una Tabla

void cargar_libros();
void ModificarLibro();
char Salir();
void clrbuf();
char Enter();
int ExecSQL(char SQLString[maxSQL]);	
void ValidaSentenciaSQL(char SQLString[maxSQL]);
int EjecutaSentenciaSQL(char SQLString[maxSQL]);
int val_balance(char cad[maxSQL]);
int DividirStringEnPartes (char SQLString[maxSQL],tlista *l);
void insertar_en_lista(char *ptr,tlista *l);
int ProcesarInstrucciones(tlista *l);
int ProcesaCreate(tlista *l);
int ProcesaCreateSchema(tlista *l);
int ProcesaCreateTable(tlista *l, char nomDB[maxDBname]);
int ProcesaCreateView(tlista *l);
int ProcesaSelect(tlista *l);
bool ValidarNoEsKeyWord(char palabra[MAX]);
bool VerificaTipoDatoValido(char TipoDatoCampo[MAX]);
bool VerificaComando(char comando[MAX]);
int ProcesaElementosDeLaTabla(tlista *l);
int CrearDB(char nomDB[maxDBname]);
int CrearTabla(char nomDB[maxDBname],char nomTabla[maxDBname],tlista *l);
int ProcesaConstraintDefDeLaTabla(tlista *l);
void mostrarlista(tlista *l);
bool InicializaDB(char nomDB[maxDBname], FILE *DB);
int MostrarEstructuraDB(char nomDB[maxDBname]);
int ProcesaDisplay(tlista *l);
int ProcesaDisplayDatabase(tlista *l);
int ProcesaDisplayTable(tlista *l, char nomDB[maxDBname]);


// Estructura de la base de datos
struct reg_estruct_DB{
	char nom_base[maxDBname];	// nombre de la base de datos
	char desc_base[256];	// descripción de la base de datos
	int cant_elementos;		// cantidad de elementos que componen la base (ej: Tablas)
	long p_primer_elemento;	// puntero al primer elemento (0 = sin elementos)
	int long_registro;		// almacena la longitud de este registro
};
struct reg_estruct_DBElemento{
	char TipoElemento[1];	// Tipo de elemento de la base (ej: T = Tabla)
	char nom_elemento[maxDBname];	// nombre del elemento de la DB
	char desc_elemento[256];	// descripción del elemento de la DB
	int cant_elementos;		// cantidad de elementos que componen este tipo (si es una Tabla, por ej: Campos, Primary Key, etc.)
	long p_primer_elemento;	// puntero al primer elemento (0 = sin elementos)
	long p_siguiente_TipoElemento;	// puntero al siguiente tipo de elemento (0 = si es el último)
	int long_registro;		// almacena la longitud de este registro
};
struct reg_estruct_DBComponente{
	char TipoComponente[1];	// Tipo de componente de un elemento de la base (ej: C = Campo)
	char nom_componente[maxDBname];	// nombre del Componente del Elemento de la DB
	char TipoDato[8];	// Tipo de dato (INT, CHAR, etc)
	int LongDato;		// Longitud del tipo de dato
	int LongDelimitador;	// puntero al primer elemento (0 = sin elementos)
	char PropiedadDato[2];	// Propiedad del dato (NN = Not Null, NU = Null)
	char DefaultDato[256];	// valor default del campo ('  ', NULL, USER)
};


void main2()
{
int opc=0;
int error;
char nom_tabla[maxt];
char SQLString[maxSQL];		// Longitud máxima del string de SQL a ejecutar
char nomDB[maxDBname];			// Nombre de la base de datos


error=0;
//clrscr();
system("cls");
while(opc != 99){
	printf("\n\t\t¿Que desea Hacer?\n\n");
	printf("\t\t1.Crear Esquema con Tablas\n");
	printf("\n\t\t99.Salir\n");
	printf("\n\t\OPCIÓN: ");
	scanf("%d", &opc);
	fflush(stdin);
	clrbuf();
	printf("\n\n");
	switch(opc){
		case 1:         //Crea el DB Schema con tablas, vistas y permisos
			strcpy(SQLString, "CREATE DATABASE Biblioteca_Sarmiento");
			switch (ExecSQL(SQLString)){
				case 0:
					break;
				case 1:
					printf("Sintaxis incorrecta - No pudo procesar las instrucciones\n");
					Enter();
					break;
				case 2:
					printf("La Base de Datos ya existe\n");
					Enter();
					break;
				case 3:
					printf("Sintaxis incorrecta - Parentesis no balancean\n");
					Enter();
					break;
				case 4:
					printf("La Base de Datos no existe\n");
					Enter();
					break;
				case 5:
					printf("Error en la estructura de la Base de Datos\n");
					Enter();
					break;
				default:
					printf("Ocurrio un Error al procesar la instruccion\n");
					Enter();
			}

			strcpy(SQLString,
				"CREATE TABLE libros  (nroLibro int, nomLibro char(30), autor character(50)) PRIMARY KEY (nroLibro, nomLibro)   CREATE TABLE socios  (nrosocio smallint, nomSocio char(30) )  CREATE TABLE books  (nrobook int, nomBook char(30), author character(50)) ");
			switch (ExecSQL(SQLString)){
				case 0:
					break;
				case 1:
					printf("Sintaxis incorrecta - No pudo procesar las instrucciones\n");
					Enter();
					break;
				case 2:
					printf("La Base de Datos ya existe\n");
					Enter();
					break;
				case 3:
					printf("Sintaxis incorrecta - Parentesis no balancean\n");
					Enter();
					break;
				case 4:
					printf("La Base de Datos no existe\n");
					Enter();
					break;
				case 5:
					printf("Error en la estructura de la Base de Datos\n");
					Enter();
					break;
				default:
					printf("Ocurrio un Error al procesar la instruccion\n");
					Enter();
			}


			strcpy(SQLString, "DISPLAY DATABASE Biblioteca_Sarmiento");
			switch (ExecSQL(SQLString)){
				case 0:
					Enter();
					break;
				case 1:
					printf("Sintaxis incorrecta - No pudo procesar las instrucciones\n");
					Enter();
					break;
				case 2:
					printf("La Base de Datos ya existe\n");
					Enter();
					break;
				case 3:
					printf("Sintaxis incorrecta - Parentesis no balancean\n");
					Enter();
					break;
				case 4:
					printf("La Base de Datos no existe\n");
					Enter();
					break;
				case 5:
					printf("Error en la estructura de la Base de Datos\n");
					Enter();
					break;
				default:
					printf("Ocurrio un Error al procesar la instruccion\n");
					Enter();
			}

			break;

		
		case 99:
			exit(1);

		default:
			printf("Error, el comando no es válido\n");
			break;
		}
//		clrscr();
		system("cls");
	}

}


//*** Función principal que ejecuta una instrucción SQL sobre la base de datos ***//
int ExecSQL(char SQLString[maxSQL])
{
//	*error=0;

	ValidaSentenciaSQL(SQLString);  // valida que la sentencia SQL esté correcta
	return EjecutaSentenciaSQL(SQLString);	// Ejecuta la sentencia SQL a partir de la estructura
	
/*	if ValidaSentenciaSQL(SQLString) == 1
	{
		printf("Sentencia SQL inválida. Corríjala. \n");
		exit(1);
	}else{
		printf("Procesó la sentencia SQL\n\n");
	}
	;
*/
}



//*** Rutina de validacion de sentencia SQL y armado de estructura para ejecutar luego
void ValidaSentenciaSQL(char SQLString[maxSQL])
{
//	printf("\nSQL validado: %s", SQLString);
//	Enter();
//	exit(0);
}

//*** Ejecutar la sentencia SQL a partir de la estructura ***//
int EjecutaSentenciaSQL(char SQLSentencia[maxSQL])
{
	tlista l;

	lcrear(&l);	// Crea la lista donde quedan las instrucciones SQL


//  Validacion 
	if(val_balance(SQLSentencia)){
	 }else{
		return 3;
	 }

//  Recorre la instruccion SQL y deja los comandos en una lista
	if(DividirStringEnPartes (SQLSentencia,&l) != 0){
		return 1;
	}else{
		return ProcesarInstrucciones(&l);
	}
}

//*** Divide el string en cada parte sin tener en cuenta espacios, coma o parentesis ***//
//    e inserta cada instruccion en una lista 
int DividirStringEnPartes (char SQLString[maxSQL],tlista *l)
{
  char *cstr =" ";
  char *p;

  cstr = new char [maxSQL];
  strcpy (cstr, SQLString);

  p=strtok (cstr," ,()");
  while (p!=NULL)
  {
	insertar_en_lista(p,l);   // Insertar la instruccion en una lista
	p=strtok(NULL," ,()");
  }

  delete[] cstr;  
  return 0;
}

// Verifica si la instruccion SQL tiene los separadores balanceados
int val_balance(char cad[maxSQL])
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

			case '*':
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
		printf("La memoria esta llena, sera imposible agragar los campos solicitados");
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

	
//Procesar todas las instrucciones cargadas en la lista
int ProcesarInstrucciones(tlista *l)
{
Tdato x;
char campo[MAX];
int cod_error;
cod_error = 0;

//mostrarlista(l);

if(!lvacia(l)){
	lppio(l);
	linfo(l,&x);
	strcpy(campo,x.clave);
	if (VerificaComando(x.clave)){ // valida que la sentencia inicia con un comando
		lsig(l);
		while((!lfin(l)) && (cod_error == 0)){  // ejecuta hasta que encuentra el fin de la lista o que sucede un error de procesamiento
			if (stricmp(campo,"CREATE")==0){
				cod_error = ProcesaCreate(l);
				if (!lfin(l)) {
					strcpy(campo,x.clave);
					lsig(l);
				}
			}else{
				if (stricmp(campo,"SELECT")==0){
					cod_error = ProcesaSelect(l);
					if (!lfin(l)) {
						strcpy(campo,x.clave);
						lsig(l);
					}
				}else{
					if (stricmp(campo,"DISPLAY")==0){
						cod_error = ProcesaDisplay(l);
						if (!lfin(l)) {
							strcpy(campo,x.clave);
							lsig(l);
						}
					}else{
						cod_error = 1;
					}
				}
			}
		}
	}else{
		cod_error = 1;
	}
	return cod_error;
}else{
	return 1;
}
printf("Codigo error %d", cod_error);
}

//Procesar la instrucción CREATE
int ProcesaCreate(tlista *l)
{
Tdato x;
char nomDB[maxDBname];

if(!lfin(l)){
	linfo(l,&x);
	if (stricmp(x.clave,"DATABASE")==0){
		lsig(l);
		return ProcesaCreateSchema(l);
	}else{
		if (stricmp(x.clave,"TABLE")==0){
			lsig(l);
			strcpy(nomDB,"Biblioteca_Sarmiento");
			return ProcesaCreateTable(l,nomDB);
		}else{
/*			if (stricmp(x.clave,"VIEW")==0){	// Sin implementar el VIEW
				lsig(l);						// Sin implementar el VIEW
				return ProcesaCreateView(l);	// Sin implementar el VIEW
			}else{
*/				
				return 1;
//			}									// Sin implementar el VIEW
		}
	}
}else{
	return 1;
}
}

//Procesar la instrucción CREATE DATABASE
int ProcesaCreateSchema(tlista *l)
{
Tdato x;
char nomDB[maxDBname];

if(!lfin(l)){
	linfo(l,&x);
	if (ValidarNoEsKeyWord(x.clave)){
		strcpy(nomDB,x.clave);		// Guarda el nombre de la Base de datos
		lsig(l);  // Sigue procesando todos los elementos de la tabla hasta el fin u otra instruccion
		if (CrearDB(nomDB)==0){
			return 0;
		}else{
			return 2;
		}
	}else{
		return 1;
	}
}else{
	return 1;
}
}

//Procesar la instrucción CREATE TABLE
int ProcesaCreateTable(tlista *l, char nomDB[maxDBname])
{
Tdato x;
char nomTabla[maxDBname];

if(!lfin(l)){
	linfo(l,&x);
	if (ValidarNoEsKeyWord(x.clave)){   // Verifica que no es palabra clave
		strcpy(nomTabla,x.clave);		// Guarda el nombre de la tabla
		lsig(l);  // Sigue procesando todos los elementos de la tabla hasta el fin u otra instruccion
		if (ProcesaElementosDeLaTabla(l) == 0){
			CrearTabla(nomDB,nomTabla,l);
		}else{
			return 1;
		}	
	}else{
		return 1;
	}			
}else{
	return 1;
}
}

//Procesa todos los elementos de la tabla
int ProcesaElementosDeLaTabla(tlista *l)
{
Tdato x;
char nomCampo[MAX];
char tipoCampo[20];
int longCampo;

linfo(l,&x);
while(!lfin(l) && !VerificaComando(x.clave)){ // si no termino o no inicia un nuevo comando sigue procesando la instrucción SQL
	if (ValidarNoEsKeyWord(x.clave)){   // Verifica que no es palabra clave
		strcpy(nomCampo,x.clave);		// Guarda el nombre del campo con
		lsig(l);
		if (!lfin(l)) { // procesa el tipo de campo
			linfo(l,&x);
			strcpy(tipoCampo,x.clave);		// Guarda el tipo de campo 
			if (VerificaTipoDatoValido(x.clave)){
				if (
					stricmp(x.clave,"CHARACTER") == 0 || 
					stricmp(x.clave,"CHAR") == 0 || 
					stricmp(x.clave,"NUMERIC") == 0 ||  
					stricmp(x.clave,"DECIMAL") == 0 || 
					stricmp(x.clave,"DEC") == 0 || 
					stricmp(x.clave,"FLOAT") == 0 ) {
					lsig(l);
					if (!lfin(l)) { // procesa longitud del tipo de campo
						linfo(l,&x);
						longCampo = atoi(x.clave);		// Guarda longitud tipo de campo 
					}else{
						return 1;
						break;
					}
				}else{
					if (
						stricmp(x.clave,"INTEGER") == 0 || 
						stricmp(x.clave,"INT") == 0 || 
						stricmp(x.clave,"SMALLINT") == 0 ) {
						longCampo = 6;		// Guarda longitud tipo de campo 
					}else{
						if (
							stricmp(x.clave,"REAL") == 0 ) {
							longCampo = 12;		// Guarda longitud tipo de campo 
						}else{
							return 1;
							break;
						}
					}
				}
			}else{		// tipo dato inválido
				return 1;
				break;
			}
		}else{
			return 1;
			break;
		}
		lsig(l);
	}else{		// no es un campo, verifica si es un Constraint
		if (ProcesaConstraintDefDeLaTabla(l)!=0){
			return 1;
			break;
		}
	}
	if (!lfin(l)){	
		linfo(l,&x);
	}
}
return 0;
}

//Procesar Definicion de Constraint de Tablas (ej: NOT NULL, CHECK, REFERENCES
int ProcesaConstraintDefDeLaTabla(tlista *l)
{
	Tdato x;
	int i;

	linfo(l,&x);
	if (stricmp(x.clave,"PRIMARY") == 0){ 
		lsig(l);
		if (!lfin(l)) { // procesa el tipo de campo
			linfo(l,&x);
			if (stricmp(x.clave,"KEY") == 0){
				lsig(l);
				if (!lfin(l)) { // procesa el tipo de campo
					linfo(l,&x);
					i = 0;
					while (ValidarNoEsKeyWord(x.clave) && !lfin(l)){   // cuenta la cantidad de columnas de la Primary Key que debe ser >= 1
						i++;
						lsig(l);
						linfo(l,&x);
					}
					if (i != 0)
						return 0;
					else
						return 1;
				}else{
					return 1;
				}
			}else{
				return 1;
			}
		}else{
			return 1;
		}
	}else{	// falta procesar otros constraints (Foreign Key, Unique)
		return 0;
	}
			
	
}
//Procesar la instrucción CREATE VIEW
int ProcesaCreateView(tlista *l)
{
	return 0;
}

//Procesar la instrucción SELECT
int ProcesaSelect(tlista *l)
{
	return 0;
}


//*** Verifica si es un tipo de dato válido ***//
bool VerificaTipoDatoValido(char TipoDatoCampo[MAX])
{
	if (
		stricmp(TipoDatoCampo,"CHARACTER") == 0 || 
		stricmp(TipoDatoCampo,"CHAR") == 0 || 
		stricmp(TipoDatoCampo,"NUMERIC") == 0 ||  
		stricmp(TipoDatoCampo,"DECIMAL") == 0 || 
		stricmp(TipoDatoCampo,"DEC") == 0 || 
		stricmp(TipoDatoCampo,"INTEGER") == 0 || 
		stricmp(TipoDatoCampo,"INT") == 0 || 
		stricmp(TipoDatoCampo,"SMALLINT") == 0 || 
		stricmp(TipoDatoCampo,"FLOAT") == 0 || 
		stricmp(TipoDatoCampo,"REAL") == 0  )
		return true; 
	else
		return false; // Indica que no un tipo de dato válido
	
}


//Validar que no es una pablabra clave de SQL
bool ValidarNoEsKeyWord(char palabra[MAX])
{
	if (
		stricmp(palabra,"PRIMARY") == 0 || 
		stricmp(palabra,"KEY") == 0 || 
		stricmp(palabra,"FOREIGN") == 0 ||  
		stricmp(palabra,"CHECK") == 0 || 
		stricmp(palabra,"UNIQUE") == 0 || 
		stricmp(palabra,"CREATE") == 0 || 
		stricmp(palabra,"TABLE") == 0 || 
		stricmp(palabra,"DATABASE") == 0 || 
		stricmp(palabra,"SELECT") == 0 || 
		stricmp(palabra,"DISPLAY") == 0 ) {
		return false;
	}else{
		return true;
	}
}

//Verifica si es un comando (ej: SELECT, CREATE, DROP, GRANT, etc.
bool VerificaComando(char comando[MAX])
{
	if (
		stricmp(comando,"CREATE") == 0  
		|| stricmp(comando,"SELECT") == 0 
		|| stricmp(comando,"DISPLAY") == 0 
	/* comandos sin implementar todavía
		|| comando == "GRANT" 
		|| comando == "CLOSE" 
		|| comando == "COMMIT"
		|| comando == "DELETE"
		|| comando == "FETCH" 
		|| comando == "INSERT"
		|| comando == "OPEN"
		|| comando == "ROLLBACK"
		|| comando == "UPDATE"  
	*/
		)
		return true; 
	else
		return false; // Indica que no es un comando implementado
}


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

// Crear una Nueva Base de datos si no existe a partir del nombre ingresado //
int CrearDB(char nomDB[maxDBname])
{
	char nomDB_CFG[maxDBname+4];
	FILE *DB;		// Configuracion de la DB

	strcpy (nomDB_CFG,nomDB);
	strcat(nomDB_CFG,".DBS");		// Archivo donde queda la estructura de todo el db schema, tablas, views, etc.

	if ((DB = fopen(nomDB_CFG, "rb+")) == NULL) /* open file  */
		{								// Crea la base de datos
		DB = fopen(nomDB_CFG, "wb+");
		if (InicializaDB(nomDB, DB)){
			fclose(DB);
			return 0;
		}else{
			fclose(DB);
			return 1;		// No pudo inciializar correctamente la DB
		}
	}else{
		fclose(DB);
		return 1;						// La base de datos ya existe
	}

}

//Procesar la instrucción DISPLAY
int ProcesaDisplay(tlista *l)
{
Tdato x;
char nomDB[maxDBname];

if(!lfin(l)){
	linfo(l,&x);
	if (stricmp(x.clave,"DATABASE")==0){
		lsig(l);
		return ProcesaDisplayDatabase(l);
	}else{
		if (stricmp(x.clave,"TABLE")==0){
			lsig(l);
			strcpy(nomDB,"Biblioteca_Sarmiento");
			return ProcesaDisplayTable(l,nomDB);
		}else{
			return 1;
		}
	}
}else{
	return 1;
}
}

//Procesar la instrucción DISPLAY DATABASE
int ProcesaDisplayDatabase(tlista *l)
{
Tdato x;
char nomDB[maxDBname];

if(!lfin(l)){
	linfo(l,&x);
	if (ValidarNoEsKeyWord(x.clave) == 0){
		strcpy(nomDB,x.clave);		// Guarda el nombre de la Base de datos
		lsig(l);  // Sigue procesando todos los elementos de la tabla hasta el fin u otra instruccion
		return MostrarEstructuraDB(nomDB);
	}else{
		return 1;
	}
}else{
	return 1;
}
}

// Mostrar la estructura de una base de datos existente //
int MostrarEstructuraDB(char nomDB[maxDBname])
{
	long pos_elemento, pos_ultimo;
	char nomDB_CFG[maxDBname+4];
	int i, j;
	FILE *DB;		// Configuracion de la DB
	struct reg_estruct_DB regDB;
	size_t cant_elementos;
	struct reg_estruct_DBElemento regTipo;
	struct reg_estruct_DBComponente regCampo;
	fpos_t posTipo;

	strcpy (nomDB_CFG,nomDB);
	strcat(nomDB_CFG,".DBS");		// Archivo donde queda la estructura de todo el db schema, tablas, views, etc.

	if ((DB = fopen(nomDB_CFG, "rb")) != NULL){ /* open file  */
		fseek(DB,0, SEEK_SET);
		cant_elementos = 1;		// cantidad de registros que lee
		fread(&regDB, sizeof(regDB), cant_elementos, DB);
		if(!feof(DB)){
			printf("NOMBRE DE LA BASE DE DATOS = %s\n",regDB.nom_base);
			printf("Descripcion                = %s\n",regDB.desc_base);
			printf("Cantidad de tablas         = %d\n",regDB.cant_elementos);
			// mostrar las tablas
			if (regDB.cant_elementos != 0){
				pos_elemento = regDB.p_primer_elemento;	// posicion primer elemento de la base
				printf("\nNombre Tabla            Campos   Descripcion\n");
				for (i = 0; (i < regDB.cant_elementos);i++){
					fseek(DB,pos_elemento, SEEK_SET);
					cant_elementos = 1;		// cantidad de registros que lee
					fread(&regTipo, sizeof(regTipo), cant_elementos, DB);
					if(!feof(DB)){
//						printf("Tipo Elemento = %c\n", regTipo.TipoElemento[0]);
						printf("\n%s                  %d      %s\n", regTipo.nom_elemento, regTipo.cant_elementos, regTipo.desc_elemento);
					}
					// mostrar los campos
					for (j = 0;(j < regTipo.cant_elementos);j++){
						cant_elementos = 1;		// cantidad de registros que lee
						fread(&regCampo, sizeof(regCampo), cant_elementos, DB);
						if(!feof(DB)){
							printf("    %s                 %s           %d\n", regCampo.nom_componente, regCampo.TipoDato, regCampo.LongDato);
						}
					}
					pos_elemento = regTipo.p_siguiente_TipoElemento;	// posicion primer elemento de la base
				}		
			}
			return 0;	// pudo listar todos los elementos de la base de datos
		}else{
			return 5;
		}
		fclose(DB);
	}else{
		fclose(DB);
		return 4;						// La base de datos no existe
	}
}


//Procesar la instrucción DISPLAY TABLE
int ProcesaDisplayTable(tlista *l, char nomDB[maxDBname])
{
	return 0;
}
// Incializa la estructura de la base de datos para agregar luego los elementos como tablas y views //
bool InicializaDB(char nomDB[maxDBname], FILE *DB)
{
	struct reg_estruct_DB reg;
	size_t cant_elementos;

	strcpy (reg.nom_base,nomDB);
	strcpy (reg.desc_base,"Aqui va la descripcion de la Base de Datos");
	reg.cant_elementos = 0;
	reg.p_primer_elemento = 0;
	reg.long_registro = sizeof(reg);
	cant_elementos = 1;		// cantidad de registros que graba
	if (fwrite(&reg, sizeof(reg), cant_elementos, DB) == cant_elementos)
		return true;	// si grabo todos los registros que se propuso
	else
		return false;
}


// Crear una Nueva Tabla a partir del nombre de tabla ingresado //
int CrearTabla(char nomDB[maxDBname],char nomTabla[maxDBname],tlista *l)
{
	FILE *DB;		// Configuracion de la DB
	struct reg_estruct_DB regDB;
	struct reg_estruct_DBElemento regTipo;
	struct reg_estruct_DBComponente regCampo;
	size_t cant_elementos;
	int i;
	long pos_elemento, pos_ultimo;
	char nomDB_CFG[maxDBname+4];
	fpos_t posTipo, posCampo;
	Tdato x, y;
	int existe;
	FILE *Tabla;	// Tabla
	char ArchTabla[maxDBname+4];
	

	printf("Crea Tabla: %s \n",nomTabla);

	// Verifica que la base de datos existe y la abre para actualizar
	strcpy (nomDB_CFG,nomDB);
	strcat(nomDB_CFG,".DBS");		// Archivo donde queda la estructura de todo el db schema, tablas, views, etc.

	if ((DB = fopen(nomDB_CFG, "rb+")) != NULL){ /* open file  */
		fseek(DB,0, SEEK_SET);
		cant_elementos = 1;		// cantidad de registros que lee
		fread(&regDB, sizeof(regDB), cant_elementos, DB);
		if(!feof(DB)){
		}else{
			fclose(DB);
			return 100;
		}
	}else{
		fclose(DB);
		return 100;						// La base de datos no existe
	}

	// verifica que la tabla no exista ya en la base de datos
	pos_elemento = regDB.p_primer_elemento;	// posicion primer elemento de la base
	for (i = 0; (i < regDB.cant_elementos) || (pos_elemento != 0);i++){
		fseek(DB,pos_elemento, SEEK_SET);
		cant_elementos = 1;		// cantidad de registros que lee
		fread(&regTipo, sizeof(regTipo), cant_elementos, DB);
		if(!feof(DB)){
			if (stricmp(regTipo.nom_elemento,nomTabla) == 0 ){
				fclose(DB); 
				return 100;  // Sale del procedimiento si ya existe la tabla
			}
		}
		pos_elemento = regTipo.p_siguiente_TipoElemento;	// posicion primer elemento de la base
	}

	// Crea la tabla al final de la base de datos 
	pos_elemento = 0;	// posicion primer elemento de la base
	fseek(DB,pos_elemento, SEEK_END); // Se coloca al final del archivo
	fgetpos (DB,&posTipo);	// obtiene la posición donde graba el elemento

	strcpy (regTipo.TipoElemento,"T");
	strcpy (regTipo.nom_elemento,nomTabla);
	strcpy (regTipo.desc_elemento,"Aqui va la descripcion de la Tabla");
	regTipo.cant_elementos = 0;
	regTipo.p_primer_elemento = 0;
	regTipo.long_registro = sizeof(regTipo);
	regTipo.p_siguiente_TipoElemento = 0;
	cant_elementos = 1;		// cantidad de registros que graba
	if (fwrite(&regTipo, sizeof(regTipo), cant_elementos, DB) != cant_elementos){
		fclose(DB);
		return 100;
	}else{
		// Crea todos los campos de la tabla al final del archivo
		if(!lvacia(l)){
			pos_elemento = 0;	// posicion primer elemento de la base
			fseek(DB,pos_elemento, SEEK_END); // Se coloca al final del archivo
			fgetpos (DB,&posCampo);	// obtiene la posición donde graba el elemento
			strcpy (regCampo.TipoComponente,"C");

			lppio(l);
			linfo(l,&x);
			lsig(l);
			strcpy(y.clave,regTipo.nom_elemento);
			while(stricmp(x.clave,y.clave) != 0){
				linfo(l,&x);
				lsig(l);
			}
			linfo(l,&x);	
			while(!lfin(l) && (ValidarNoEsKeyWord(x.clave))){
				strcpy (regCampo.nom_componente,x.clave);
				lsig(l);
				linfo(l,&x);
				if (stricmp(x.clave,"CHARACTER") == 0){
					strcpy (regCampo.TipoDato,"CHAR");
				}else{
					if (stricmp(x.clave,"DECIMAL") == 0){
						strcpy (regCampo.TipoDato,"DEC");
					}else{
						if (stricmp(x.clave,"INTEGER") == 0){
							strcpy (regCampo.TipoDato,"INT");
						}else{
							strcpy (regCampo.TipoDato,x.clave);
						}
					}
				}
				if (
					stricmp(x.clave,"INTEGER") == 0 || 
					stricmp(x.clave,"INT") == 0 || 
					stricmp(x.clave,"SMALLINT") == 0 ) {
					regCampo.LongDato = 6;		// Guarda longitud tipo de campo 
				}else{
					if (
						stricmp(x.clave,"REAL") == 0 ) {
						regCampo.LongDato  = 12;		// Guarda longitud tipo de campo 
					}else{
						lsig(l);
						linfo(l,&x);
						regCampo.LongDato = atoi(x.clave);
					}
				}
				regCampo.LongDelimitador = 0;			//asigna valores default
				strcpy(regCampo.PropiedadDato,"NU");	//asigna valores default
				strcpy(regCampo.DefaultDato,"NULL");	//asigna valores default
				lsig(l);
				linfo(l,&x);
			// Grabar registro campo
				cant_elementos = 1;		// cantidad de registros que graba
				if (fwrite(&regCampo, sizeof(regCampo), cant_elementos, DB) != cant_elementos){
					fclose(DB);
					return 100;
				}
				regTipo.cant_elementos++;	// Le suma 1 al contador de campos de la tabla
			}
			// Si proceso todos los campos regraba el registro Tipo Elemento con la cant. Campos creados
			fseek(DB,posTipo, SEEK_SET); // Se coloca en el Tipo Elemento
			cant_elementos = 1;		
			if (fwrite(&regTipo, sizeof(regTipo), cant_elementos, DB) != cant_elementos){
				fclose(DB);
				return 100;
			}

			// Crea el archivo de la Tabla que contendra los datos en el directorio
			strcpy(ArchTabla,nomTabla);
			strcat(ArchTabla,".TAB");
			printf("%s",ArchTabla);
			Enter();
			if ((Tabla = fopen(ArchTabla, "rb+")) == NULL) // open file  
				{
				Tabla = fopen(ArchTabla, "wb+");	// si no existe la crea
				}
			fclose(Tabla);

		}
		// Crea los archivos de los índices de la tabla en el directorio
		// EJECUTAR TANTAS VECES COMO INDICES HAYA CREADOS
/*		if (TipoIndice == 'p')
		{
			strcpy(nom_tipoindice,"_P1");
		}else{
			strcpy(nom_tipoindice,"_Sn");
		}
		strcpy (nomtabla_IDX,nomTabla);
		strcat(nomtabla_IDX,nom_tipoindice);	
		strcat(nomtabla_IDX,".IDX");	
		printf("%s",nomtabla_IDX);
		Enter();
		if ((TablaIndice = fopen(nomtabla_IDX, "rb+")) == NULL) // open file 
			{
			TablaIndice = fopen(nomtabla_IDX, "wb+"); // si no existe la crea
			}
		fclose(TablaIndice);
*/

	}
	
	// Actualiza el registro ppal de la base de datos con la novedad que se creo una nueva tabla
	if (regDB.p_primer_elemento == 0)
		regDB.p_primer_elemento = posTipo;	
	regDB.cant_elementos++;	// incrementa 1 la cantidad de elementos

	fseek(DB,0, SEEK_SET); // Se coloca al ppio del archivo
	cant_elementos = 1;		// cantidad de registros que graba
	if (fwrite(&regDB, sizeof(regDB), cant_elementos, DB) != cant_elementos){	// regraba el registro actualizado
		fclose(DB);
		return 100;
	}

	// Actualiza el puntero al siguiente en la ultima tabla que ya existía antes de crear esta
	if (regDB.p_primer_elemento != posTipo){  // o sea que hay más de un registro Tipo
		pos_elemento = regDB.p_primer_elemento;
		while (pos_elemento != 0){
			fseek(DB,pos_elemento, SEEK_SET);
			cant_elementos = 1;		// cantidad de registros que lee
			pos_ultimo = pos_elemento;
			fread(&regTipo, sizeof(regTipo), cant_elementos, DB);
			if(!feof(DB)){
				pos_elemento = regTipo.p_siguiente_TipoElemento;	// posicion siguiente elemento de la base
			}else{
				fclose(DB);
				return 100;
			}
		}
		fseek(DB,pos_ultimo, SEEK_SET);

		cant_elementos = 1;		// cantidad de registros que lee
		regTipo.p_siguiente_TipoElemento = posTipo;
		if (fwrite(&regTipo, sizeof(regTipo), cant_elementos, DB)!= cant_elementos){
			fclose(DB);
			return 100;
		}
	}
	fclose(DB);
	return 0;
}