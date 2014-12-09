#include <stdio.h>
#include <conio.h>
#include <stdlib.h>  // PROBLEMA CON EL CARGAR LIBRO O LEER LIBROO
#include <string.h>               // PROBLEMA AL GUARDAR CADA REGISTRO Y LEERLO.
#include <sys\stat.h>
#define maxt 100

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

error=0;
//clrscr();
system("cls");
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
	printf("\t\t9.Crear Tabla\n");
	printf("\t\t10.Eliminar Tabla\n");
	printf("\t\t11.Modificar Tabla\n");
	printf("\t\t12.Insertar Registro en una Tabla\n");
	printf("\t\t13.Eliminar un Registro de una Tabla\n");
	printf("\t\t14.Modificar un Registro de una Tabla\n");
	printf("\t\t15.Crear una Relación Permanente entre dos Tablas\n");
	printf("\t\t16.Crear un Nuevo Indice para una Tabla\n");
	printf("\t\t17.Modificar un Indice en una Tabla\n");
	printf("\n\t\t99.Salir\n");
	printf("\n\t\OPCIÓN: ");
	scanf("%d", &opc);
	fflush(stdin);
	clrbuf();
	printf("\n\n");
	switch(opc){
		case 1:         //Carga de libros
			cargar_libros();
		break;

		/*case 2:
			if(lvacia(&l)){
				printf("La lista se encuentra vacía.\n\n");
			}else{
				printf("La lista ya tiene elementos ingresados.\n\n");
			}break;
		*/

		case 3:
			ModificarLibro();
			break;

		case 4:        // Listar los libros en forma ascendente
			listar_libros(&error);
			break;
		/*
		case 5:        // prueba
			PruebaGrabacion();
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

		*/
		case 9:        // Crear tabla
			printf("\n\t\tNombre de la Tabla a crear: ", nom_tabla);
			gets(nom_tabla);
			fflush(stdin);
			CrearTabla(nom_tabla);
			printf("\n\t\tTabla creada --> %s ", nom_tabla);
			Enter();
			break;
		
		/*
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
			exit(1);

		default:
			printf("Error, el comando no es válido\n");
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

	// Crear Registro 0 de Configuración
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

	/* Cerrar Tabla de Configuración */
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



	/*** Tablas de Indices (contiene los índices creados para los campos de 
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

	printf("\nRegistro de Configuración Creado\n");

}

void CrearRegistroCampos(FILE *stream)
{
	printf("\nRegistro de Campos Creado\n");

}

//*** Eliminar una Tabla existente ingresando el nombre de la misma ***//
/* Consiste:
	1	Ubicar la tabla
	2	Verificar que la misma no está en uso (queda para otro release)
	3	Verificar que no haya ningún índice o relación en uso (queda para otro release)
	4	Eliminar todos los índices y relaciones
	5	Hacer un backup de la tabla, renombrandola como ".BAK" a los datos y ".BCF" a la configuración, previo eliminar cualquiera de estos preexistentes
*/
void EliminarTabla(char NombreTabla[maxt])
{

}

//*** Modificar una Tabla existente ingresando el nombre de la misma ***//
/* Consiste:
	1	Ubicar la tabla
	2	Verificar que la misma no está en uso (queda para otro release)
	3	Verificar que no haya ningún índice o relación en uso (queda para otro release)
	4	Identificar si la modificación consiste en
		4.1 Actualizar un Indice
			4.1.1	Agregar un indice nuevo
			4.1.2	Eliminar un índice
				4.1.2.1	Verificar si el indice forma parte de una relación
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
	2	Verificar que la misma no está en uso (queda para otro release)
	3	Verificar que no haya ningún índice o relación en uso (queda para otro release)
	4	Identificar si la modificación consiste en
		4.1 Actualizar un Indice
			4.1.1	Agregar un indice nuevo
			4.1.2	Eliminar un índice
				4.1.2.1	Verificar si el indice forma parte de una relación
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
	printf("\t\t15.Crear una Relación Permanente entre dos Tablas\n");
	printf("\t\t16.Crear un Nuevo Indice para una Tabla\n");
	printf("\t\t17.Modificar un Indice en una Tabla\n");
*/
