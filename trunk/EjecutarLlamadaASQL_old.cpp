#include <stdio.h>
#include <conio.h>
#include <stdlib.h>  // PROBLEMA CON EL CARGAR LIBRO O LEER LIBROO
#include <iostream>
#include <string>               
using namespace std;
#include <sys\stat.h>
#define maxt 100
#define maxSQL 1028
#include <list>
#include "LISTAS.h"
#include "TDATOLS.h"



void cargar_libros();
void ModificarLibro();
char Salir();
void clrbuf();
char Enter();
void listar_libros(int *error);
void showpos(FILE *stream);
void CrearTabla(char nom_tabla[maxt]);
void showpos(FILE *stream);
void CrearRegistroConfiguracion(FILE *stream);
void CrearRegistroCampos(FILE *stream);
void ExecSQL(char SQLString[maxSQL], int *error);	
void ValidaSentenciaSQL(char SQLString[maxSQL]);
void EjecutaSentenciaSQL(char SQLString[maxSQL]);
int ObtenerString(string stringbusqueda, size_t pos_inicial, size_t &pos_final, string &NombreTabla);
int ObtenerCamposACrear(string stringbusqueda, size_t pos_inicial, string &campos);
int ObtieneDatosUnCampo(string stringbusqueda, size_t pos_inicial, size_t &pos_final, string &campos);
char VerificaTableConstraintDef(string CampoAVerificar, string stringbusqueda,size_t pos_inicio);
int DividirStringEnPartes (string str, std::list <char *> listInstruccion);
int VerificaTipoDatoValido(string &TipoDatoCampo);
void lista();
int insertar();
int val_balance(char cad[maxSQL]);

struct reg_libro{
	int nro_libro;
	char autor[42];
	char titulo[80];
};

struct reg_configuracion{
	int p_campos;	  //     Puntero a Campos (integer)
	int cant_campos;  //     Cantidad de Campos (integer)
	long p_reg_libre; //     Puntero a Registro Libre (long)
	long p_primer_reg; //     Puntero a Primer Registro (long)
};
int main()
{
FILE *index_principal;
FILE *libros;
int opc,error;
char nom_tabla[maxt];
char SQLString[maxSQL];		// Longitud m�xima del string de SQL a ejecutar


error=0;
//clrscr();
system("cls");
while(opc != 99){
	printf("\n\t\t�Que desea Hacer?\n\n");
	printf("\t\t1.Crear Esquema con Tablas\n");
	printf("\t\t2.Lista\n");
	printf("\t\t3.Insertar en Lista\n");
	printf("\t\t9.Crear Tabla\n");
	printf("\t\t10.Eliminar Tabla\n");
	printf("\t\t11.Modificar Tabla\n");
	printf("\t\t12.Insertar Registro en una Tabla\n");
	printf("\t\t13.Eliminar un Registro de una Tabla\n");
	printf("\t\t14.Modificar un Registro de una Tabla\n");
	printf("\t\t15.Crear una Relaci�n Permanente entre dos Tablas\n");
	printf("\t\t16.Crear un Nuevo Indice para una Tabla\n");
	printf("\t\t17.Modificar un Indice en una Tabla\n");
	printf("\n\t\t99.Salir\n");
	printf("\n\t\OPCI�N: ");
	scanf("%d", &opc);
	fflush(stdin);
	clrbuf();
	printf("\n\n");
	switch(opc){
		case 1:         //Crea el DB Schema con tablas, vistas y permisos
			strcpy(SQLString,
				"CREATE SCHEMA bd_test AUTORIZATION claudio CREATE TABLE libros  (nroLibro int, nomLibro char(30), autor (50))");
			ExecSQL(SQLString,&error);
		break;

		case 2:
			lista();
			break;

		case 3:
			insertar();
			system("PAUSE");
			break;

		case 4:        // Listar los libros en forma ascendente
			listar_libros(&error);
			break;

		case 9:        // Crear tabla
			printf("\n\t\tNombre de la Tabla a crear: ");
			gets(nom_tabla);
			fflush(stdin);
			CrearTabla(nom_tabla);
			printf("\n\t\tTabla creada --> %s ", nom_tabla);
			Enter();
			break;
		
		case 99:
			exit(1);

		default:
			printf("Error, el comando no es v�lido\n");
			break;
		}
//		clrscr();
		system("cls");
	}

}

// Rutina para cargar libros
void cargar_libros()
{
char control;
FILE *libros;
struct reg_libro a;
struct reg_libro reg;
struct stat statbuf;

if ((libros = fopen("LIBROS.TXT", "a+b")) == NULL) /* open file TEST.$$$ */
{
		fprintf(stderr, "Cannot open output file.\n");
		//return 1;
}else{
	//Busco el ultimo numero para poder asignar el nro de libro siguiente.
	fstat(fileno(libros), &statbuf);
	a.nro_libro = statbuf.st_size  /  sizeof(a);
	//comienzo a cargar los libros y archivarlos
	fclose(libros);
	control='s';
	while(control=='s' || control=='S'){
		if ((libros = fopen("LIBROS.TXT", "a+b")) == NULL){
			fprintf(stderr, "Cannot open output file.\n");
			//return 1;
		}
		a.nro_libro=a.nro_libro+1;
		printf("Autor = ");
		gets(a.autor);
		fflush(stdin);
		printf("Titulo = ");
		gets(a.titulo);
		fflush(stdin);
		fwrite(&a, sizeof(a), 1, libros);
		fclose(libros);
		// insertar libro agregado en la lista ordenada
 /*	if(!lllena(l)){
			dato.clave=a.nro_libro;
			dato.sig=0;
			dato.ant=0;
			linsertarorden(l,dato,'a');
		// grabar lista ordenada en archivo
		Grabar(l);
	}*/
	control=Salir();

	}

}
}

//Modificar Libros
void ModificarLibro()
{
FILE *libros;
struct reg_libro reg;
{
	if ((libros = fopen("LIBROS.TXT", "rb+")) == NULL){
		fprintf(stderr, "Cannot open output file.\n");
			//return 1;
	}

	fpos_t filepos;

	/* set a new file position, display it */
	fseek(libros,0, SEEK_SET);
	filepos=134;
	if (fsetpos(libros, &filepos) == 0){
		showpos(libros);
		Enter();
		fread(&reg, sizeof(reg), 1, libros);
		printf("%d     %s                %s    %d\n",reg.nro_libro,reg.titulo,reg.autor,sizeof(reg));
		Enter();
		filepos=134;
		fsetpos(libros, &filepos);
		showpos(libros); Enter();
		strcpy(reg.autor,"Autor Claudio");
		fwrite(&reg, sizeof(reg), 1, libros);
		printf("%d     %s                %s    %d\n",reg.nro_libro,reg.titulo,reg.autor,sizeof(reg));
		Enter();
	}else{
		fprintf(stderr, "Error setting file pointer.\n");
		exit(1);
	}
}
	fclose(libros);
}


//LISTA LIBROS
void listar_libros(int *error)
{
FILE *libros;
struct reg_libro reg;
*error=0;
fpos_t filepos;

if ((libros = fopen("LIBROS.TXT", "rb")) == NULL) /* open file TEST.$$$ */
{
	fprintf(stderr, "No se encuentra el archivo\n");
	Enter();
	*error=1;
}else{
	fseek(libros,0, SEEK_SET);
	fgetpos(libros, &filepos);
			if(fsetpos(libros, &filepos) == 0){
				showpos(libros);
			}else{
				fprintf(stderr, "Error setting file pointer.\n");
				exit(1);
			}
			Enter();
	fread(&reg, sizeof(reg), 1, libros);
	if(!feof(libros)){
		printf("Nro lib     titulo              autor\n\n");
		while(!feof(libros)){
			fgetpos(libros, &filepos);
			if(fsetpos(libros, &filepos) == 0){
				showpos(libros);
			}else{
				fprintf(stderr, "Error setting file pointer.\n");
				exit(1);
			}
			Enter();
			printf("%d     %s                %s    %d\n",reg.nro_libro,reg.titulo,reg.autor,sizeof(reg));
			fread(&reg, sizeof(reg), 1, libros);
		}
	}else{
		printf("La base de datos esta vacia, procure ingresar datos antes de operar\n\n");
	}
	Enter();
//	clrscr();
	system("cls");
	fclose(libros);
}
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
//clrscr();
system("cls");
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



//*** Funci�n principal que ejecuta una instrucci�n SQL sobre la base de datos ***//
void ExecSQL(char SQLString[maxSQL], int *error)
{
//	*error=0;

	ValidaSentenciaSQL(SQLString);  // valida que la sentencia SQL est� correcta
	EjecutaSentenciaSQL(SQLString);	// Ejecuta la sentencia SQL a partir de la estructura
	
/*	if ValidaSentenciaSQL(SQLString) == 1
	{
		printf("Sentencia SQL inv�lida. Corr�jala. \n");
		exit(1);
	}else{
		printf("Proces� la sentencia SQL\n\n");
	}
	;
*/
}



//*** Rutina de validacion de sentencia SQL y armado de estructura para ejecutar luego
void ValidaSentenciaSQL(char SQLString[maxSQL])
{
	printf("\nSQL validado: %s", SQLString);
	Enter();
//	exit(0);
}

//*** Ejecutar la sentencia SQL a partir de la estructura ***//
void EjecutaSentenciaSQL(char SQLString[maxSQL])
{
	char SQLSentencia2[maxSQL];		// Sentencia SQL a ejecutar
	strcpy(SQLSentencia2,
				"CREATE TABLE libros  (nroLibro int, nomLibro char(30), autor (50))");
	string SQLSentencia ("CREATE TABLE   libros  (nroLibro int, nomLibro char(30), autor (50))");
//	string SQLSeencia ("CREATE TABLE");
//  Validacion 
	if(val_balance(SQLSentencia2)){
		printf("Sintaxis correcta");
	 }else{
		printf("Sintaxis incorrecta");
	 }
	string str2 ("CREATE ");
	string NombreTabla, campos;

	size_t found, encontrado;
	size_t ini_string;
	size_t fin_string;
	int cod_error;

	std::list <char *> listInstruccion;

// elimina los blancos al final de la sentencia SQL
	string whitespaces (" \t\f\v\n\r");
  
	found=SQLSentencia.find_last_not_of(whitespaces);
	if (found!=string::npos)
		SQLSentencia.erase(found+1);
	else
		SQLSentencia.clear();            // str is all whitespace

// Comienza a analizar la sentencia SQL
	cod_error = DividirStringEnPartes (SQLSentencia, listInstruccion);

// Lista la cadena armada
	std::list <char *> ::iterator i;
	for ( i = listInstruccion.begin (); i != listInstruccion.end (); ++ i )
        std::cout << *i << std::endl;


	found=SQLSentencia.find(str2);
	if (found!=string::npos){	
		found=SQLSentencia.find_first_not_of(" ",found+str2.length()); 
		if (found!=string::npos){	
			encontrado=SQLSentencia.find("TABLE ",found,6);
			if (encontrado!=string::npos){	
				if (ObtenerString(SQLSentencia,found+6,fin_string,NombreTabla) == 0){
					cout << "TABLA " << NombreTabla << endl;
					if (ObtenerCamposACrear(SQLSentencia,fin_string,campos) == 0){
						cout << "Campos: " << campos << endl;
					}else{
						printf("Campos de Tabla con sintaxis incorrecta");
					}
				}else{
					printf("construcci�n CREATE incorrecta (sin TABLE )");
				}
			}else{
				encontrado=SQLSentencia.find("VIEW ",found,5);
				if (encontrado!=string::npos){	
					if (ObtenerString(SQLSentencia,found+5,fin_string,NombreTabla) == 0){
						cout << "VIEW " << NombreTabla << endl;
					}else{
						printf("construcci�n CREATE incorrecta (sin VIEW)");
					}
				}else{
					printf("construcci�n CREATE incorrecta (sin TABLE ni VIEW)");
				};
			};
		};
	};
	Enter();
//	exit(0);
}


//*** Obtener primer palabra de un string ***//
int ObtenerString(string stringbusqueda, size_t pos_inicial, size_t &pos_final, string &NombreTabla)
{
	size_t ini_string;
	int cod_error = 0;

	ini_string=stringbusqueda.find_first_not_of(" ,()",pos_inicial); // busca inicio del nombre de la tabla
	if (ini_string!=string::npos){	
		pos_final=stringbusqueda.find_first_of(" ,()",ini_string); // busca fin del nombre de la tabla
		if (pos_final!=string::npos){	
			NombreTabla = stringbusqueda.substr(ini_string,pos_final - ini_string); 
			}else{
			cod_error = 1;
			};
	}else{
		cod_error = 1;
	};
	return cod_error;

}
			
//*** Obtener Campos a crear de una tabla ***//
int ObtenerCamposACrear(string stringbusqueda, size_t pos_inicial, string &campos)
{
	size_t ini_string, pos_final;
	int cod_error = 0;
	char * NomTab;

	ini_string=stringbusqueda.find_first_not_of(" ",pos_inicial); // busca inicio de los campos a crear luego de los blancos
	if (ini_string!=string::npos){	
		ini_string=stringbusqueda.find_first_not_of("(",ini_string); // debe comenzar con un parentesis
		if (ini_string!=string::npos){
			cod_error = ObtieneDatosUnCampo(stringbusqueda, ini_string, pos_final, campos);
			while (cod_error == 0 && stringbusqueda.at(pos_final)!=')' )
			{
				cout << "Campos: " << campos << endl;
				cod_error = ObtieneDatosUnCampo(stringbusqueda, pos_final+1, pos_final, campos);
			}
		}else{
			cod_error = 1;
		}
	}else{
		cod_error = 1;
	};
	return cod_error;

}

//*** Obtener Campos a crear de una tabla ***//
int ObtieneDatosUnCampo(string stringbusqueda, size_t pos_inicial, size_t &pos_final, string &campos)
{
	size_t ini_string, fin_string;
	int cod_error = 0;
	string NomCampo, TipoDatoCampo, ConstraintTabla;
	string campo;

	ini_string=stringbusqueda.find_first_not_of(" ",pos_inicial); // busca inicio de los campos a crear luego de los blancos
	pos_final=stringbusqueda.find_first_of(",",ini_string); // busca el fin del base_table_element
	if (pos_final!=string::npos){
		if (ObtenerString(stringbusqueda,ini_string,fin_string,campo) == 0){
			if (VerificaTableConstraintDef(campo,stringbusqueda,fin_string) == 'S'){ // Es un comando de Table
				ConstraintTabla = campo;		
				cout << "TipoConstraint: " << ConstraintTabla << endl;
			}else{	// Es el nombre del campo
				NomCampo = campo;	
				cout << "NombreCampo: " << NomCampo << endl;
				ini_string = fin_string; // se posiciona para extraer el tipo de dato
				if (ObtenerString(stringbusqueda,ini_string,fin_string,campo) == 0){
					TipoDatoCampo = campo;
					cout << "TipoDato: " << TipoDatoCampo << endl;
					if (VerificaTipoDatoValido(TipoDatoCampo) == 0){
					}else{
						cod_error = 1;
					}
			//		if TipoDatoCampo =
				}else{
				}
			}
		}else{
			printf("construcci�n CREATE incorrecta (sin VIEW)");
		}
		campos = stringbusqueda.substr(ini_string,pos_final - ini_string); 
	}else{
		cod_error = 1;
	}
	return cod_error;

}

//*** Verifica si es un constraint de una tabla y no un campo ***//
char VerificaTableConstraintDef(string CampoAVerificar, string stringbusqueda,size_t pos_inicio)
{
	if (CampoAVerificar == "UNIQUE" || CampoAVerificar == "PRIMARY" || 
		CampoAVerificar == "CHECK" ||  CampoAVerificar == "FOREIGN"){
		return 'S'; 
	}else{
		return 'N'; // Indica que no era un Table Constraint sino un nombre de campo
	}
}
//*** Verifica si es un tipo de dato v�lido ***//
int VerificaTipoDatoValido(string &TipoDatoCampo)
{
	if (
		TipoDatoCampo == "CHARACTER" || 
		TipoDatoCampo == "CHAR" || 
		TipoDatoCampo == "NUMERIC" ||  
		TipoDatoCampo == "DECIMAL" || 
		TipoDatoCampo == "DEC" || 
		TipoDatoCampo == "INTEGER" || 
		TipoDatoCampo == "INT" || 
		TipoDatoCampo == "SMALLINT" || 
		TipoDatoCampo == "FLOAT" || 
		TipoDatoCampo == "INTEGER"  )
		return 0; 
	else
		return 1; // Indica que no un tipo de dato v�lido
	
}

//*** Divida el string en cada parte sin tener en cuenta espacios, coma o parentesis ***//
int DividirStringEnPartes (string str, std::list <char *> listInstruccion)
{
  char * cstr, *p;

  cstr = new char [str.size()+1];
  strcpy (cstr, str.c_str());

  // cstr now contains a c-string copy of str

  p=strtok (cstr," ,()");
  while (p!=NULL)
  {
    cout << p << endl;
    listInstruccion.push_back (p);
	p=strtok(NULL," ,()");
  }

  delete[] cstr;  
  return 0;
}

//*** Crear una Nueva Tabla a partir del nombre de tabla ingresado ***//
void CrearTabla(char NombreTabla[maxt])
{
	#define TipoIndice 'p'

	FILE *TablaConfig;	// Configuracion
	FILE *Tabla;	// Tabla
	FILE *TablaIndice;	// Tabla Indice
	fpos_t filepos;
	char nomtabla_CFG[maxt+4];
	char nomtabla[maxt+4];
	char nomtabla_IDX[maxt+7];
	char nom_tipoindice[3];

	/*** Tabla de Configuracion (contiene la estructura y metodo de acceso a 
		la tabla de datos) ***/
	strcpy (nomtabla_CFG,NombreTabla);
	strcat(nomtabla_CFG,".CFG");
	printf("%s",nomtabla_CFG);
	Enter();
	if ((TablaConfig = fopen(nomtabla_CFG, "rb+")) == NULL) /* open file  */
		{
		TablaConfig = fopen(nomtabla_CFG, "wb+");
		fclose(TablaConfig);
		TablaConfig = fopen(nomtabla_CFG, "rb+");
		}

	// Crear Registro 0 de Configuraci�n
	//     Puntero a Campos (integer)
	//     Cantidad de Campos (integer)
	//     Puntero a Registro Libre (long)
	//     Puntero a Primer Registro (long)
	CrearRegistroConfiguracion(TablaConfig);

	// Crear Registro 1 de Campos
	//     Puntero a Siguiente Campo(long)
	//     Nombre del Campo (50 bytes)
	//     Tipo de Campo (int)
	//     Longitud del Campo (int)
	CrearRegistroCampos(TablaConfig);

	/* Cerrar Tabla de Configuraci�n */
	fclose(TablaConfig);


	/*** Tabla Principal (contiene los datos) ***/
	strcpy (nomtabla,NombreTabla);
	strcat(nomtabla,".TAB");
	printf("%s",nomtabla);
	Enter();
	if ((Tabla = fopen(nomtabla, "rb+")) == NULL) /* open file  */
		{
		Tabla = fopen(nomtabla, "wb+");
		fclose(Tabla);
		Tabla = fopen(nomtabla, "rb+");
		}
	
	/* Cerrar Tabla Principal */
	fclose(Tabla);



	/*** Tablas de Indices (contiene los �ndices creados para los campos de 
	   la tabla de datos) ***/
	// EJECUTAR TANTAS VECES COMO INDICES HAYA CREADOS

	if (TipoIndice == 'p')
	{
		strcpy(nom_tipoindice,"_P1");
	}else{
		strcpy(nom_tipoindice,"_Sn");
	}
	strcpy (nomtabla_IDX,NombreTabla);
	strcat(nomtabla_IDX,nom_tipoindice);	
	strcat(nomtabla_IDX,".IDX");	
	printf("%s",nomtabla_IDX);
	Enter();
	if ((TablaIndice = fopen(nomtabla_IDX, "rb+")) == NULL) /* open file  */
		{
		TablaIndice = fopen(nomtabla_IDX, "wb+");
		fclose(TablaIndice);
		TablaIndice = fopen(nomtabla_IDX, "rb+");
		}
	
	/* Cerrar Tabla Principal */
	fclose(TablaIndice);

}


void CrearRegistroConfiguracion(FILE *stream)
{
	struct reg_configuracion rcfg;
	fpos_t filepos;
	
	rcfg.p_campos = 16;  //  Puntero a Campos (donde termina el registro Configuracion + 1)
	rcfg.cant_campos = 1;  //  Cantidad de Campos (suma de los ingresados)
	rcfg.p_reg_libre = NULL; //  Puntero a Registro Libre (nulo al crear el archivo ya que no hay registros)
	rcfg.p_primer_reg = NULL; //   Puntero a Primer Registro (al crear el archivo, es donde termina el registro Campos + 1)
	fwrite(&rcfg, sizeof(rcfg), 1, stream);
	showpos(stream);

	/* set a new file position, display it */
	//fseek(libros,0, SEEK_SET);
	/* 
	filepos=0;
	fsetpos(stream, &filepos);
	showpos(stream);
	Enter();
	fread(&rcfg, sizeof(rcfg), 1, stream);
	printf("Puntero Campos:%d  CantidadCampos:%d   PunteroRegLibre:%d   Puntero1erReg:%d   LongReg:%d\n",rcfg.p_campos,rcfg.cant_campos,rcfg.p_reg_libre,rcfg.p_primer_reg,sizeof(rcfg));
	*/

	printf("\nRegistro de Configuraci�n Creado\n");

}

void CrearRegistroCampos(FILE *stream)
{
	printf("\nRegistro de Campos Creado\n");

}

//*** Eliminar una Tabla existente ingresando el nombre de la misma ***//
/* Consiste:
	1	Ubicar la tabla
	2	Verificar que la misma no est� en uso (queda para otro release)
	3	Verificar que no haya ning�n �ndice o relaci�n en uso (queda para otro release)
	4	Eliminar todos los �ndices y relaciones
	5	Hacer un backup de la tabla, renombrandola como ".BAK" a los datos y ".BCF" a la configuraci�n, previo eliminar cualquiera de estos preexistentes
*/
void EliminarTabla(char NombreTabla[maxt])
{

}

//*** Modificar una Tabla existente ingresando el nombre de la misma ***//
/* Consiste:
	1	Ubicar la tabla
	2	Verificar que la misma no est� en uso (queda para otro release)
	3	Verificar que no haya ning�n �ndice o relaci�n en uso (queda para otro release)
	4	Identificar si la modificaci�n consiste en
		4.1 Actualizar un Indice
			4.1.1	Agregar un indice nuevo
			4.1.2	Eliminar un �ndice
				4.1.2.1	Verificar si el indice forma parte de una relaci�n
			4.1.3	Modificar un indice
		4.2 Actualizar un Campo
			4.2.1	Agregar un campo nuevo
			4.2.2	Eliminar un campo
			4.2.3	Modificar un campo
		4.3 Actualizar una Relacion
			4.3.1	Agregar una nueva relacion
			4.3.2	Modificar una relacion existente 
			4.3.3	Eliminar una relacion existente	
*/
void ModificarTabla(char NombreTabla[maxt])
{

}

//*** Insertar un registro ingresando el nombre de la misma y el registro a insertar ***//
/* Consiste:
	1	Ubicar la tabla
	2	Verificar que la misma no est� en uso (queda para otro release)
	3	Verificar que no haya ning�n �ndice o relaci�n en uso (queda para otro release)
	4	Identificar si la modificaci�n consiste en
		4.1 Actualizar un Indice
			4.1.1	Agregar un indice nuevo
			4.1.2	Eliminar un �ndice
				4.1.2.1	Verificar si el indice forma parte de una relaci�n
			4.1.3	Modificar un indice
		4.2 Actualizar un Campo
			4.2.1	Agregar un campo nuevo
			4.2.2	Eliminar un campo
			4.2.3	Modificar un campo
		4.3 Actualizar una Relacion
			4.3.1	Agregar una nueva relacion
			4.3.2	Modificar una relacion existente 
			4.3.3	Eliminar una relacion existente	
*/
void InsertarRegistro(char NombreTabla[maxt])
{

}
/*
	printf("\t\t12.Insertar Registro en una Tabla\n");
	printf("\t\t13.Eliminar un Registro de una Tabla\n");
	printf("\t\t14.Modificar un Registro de una Tabla\n");
	printf("\t\t15.Crear una Relaci�n Permanente entre dos Tablas\n");
	printf("\t\t16.Crear un Nuevo Indice para una Tabla\n");
	printf("\t\t17.Modificar un Indice en una Tabla\n");
*/
