#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "auxiliares.h"
#define MAX_LINEA 160			//ftell para agarrar la posicion ftell("hola");
#define maxSQL 1028


void sacarblancos(char ar[]);
void tratar_comando(char comando[]);
void validar_comando(char comando[],char ptr[]);
void ingresa_registros(char ptr[]);
void val_lista(char comando[], char ptr[]);
void ingreso_autores(char ptr[]);
void ingreso_temas(char ptr[]);
void lista_registros(char ptr[]);
char Enter();
int crear_archivos(char nom[]);
int val_balance(char cad[]);
void val_elimina(char comando[], char ptr[]);
void val_edita(char comando[], char ptr[]);
void elimina_registros(char ptr[]);
void edita_registros(char ptr[]);
void backup_archivos(char ptr[]);
void crea_archivos(char ptr[]);
int nro_de_campo_valido(char nom[128], char campo_comp[128]);
void recupera_archivos(char ptr[]);
void limpia_archivos(char ptr[]);

int main()
{
	incializar_archivos();  // inciala los nombres de los archivos.

	int error;
	char comando[MAX_LINEA+1];
	printf("Ingrese comando: ");
	gets(comando);
	fflush(stdin);
	while(stricmp(comando,"EXIT")!=0){
		tratar_comando(comando);
		system("cls");
		printf("Ingrese comando: ");
		gets(comando);
		fflush(stdin);
	}
}

void sacarblancos(char ar[])
{
	int i=0;
	while(ar[0]!='\0' && (ar[0]==' ' || ar[0]=='\t')){
		for(int i=0;i<=strlen(ar);i++){
			ar[i]=ar[i+1];
		}
	}


}


void tratar_comando(char comando[])
{
	char *ptr;
	char *aux_com;
	if((strlen(comando)) < MAX_LINEA)
	{
		sacarblancos(comando);
		if(strlen(comando)==0)
		{
			printf("No ingreso comando\n");
		}else{
			aux_com = (char*)malloc((strlen(comando)+1) * sizeof(char));
			strcpy(aux_com,comando);
			ptr=strtok(aux_com," ");
			validar_comando(comando,ptr);
		}
	}else{
		printf("Linea muy larga (debe ser menor a %d caracteres)\n",MAX_LINEA);
	}
	Enter();
}


void validar_comando(char comando[],char ptr[])
{
	char *otr;
	if(stricmp(ptr,"CREAR")==0){
		otr=strtok(NULL," ");
		if(otr==NULL){ //chequea que se pase la tabla
			printf("NO SE ESPECIFICO NI TABLA NI PARAMETROS");
		}else{
			crea_archivos(otr);
		}
	}else{
		if(stricmp(ptr,"INSERTAR")==0){
			otr=strtok(NULL," ");
			if(otr==NULL){ //chequea que se pase la tabla
				printf("NO SE ESPECIFICO NI TABLA NI PARAMETROS");
			}else{
				ingresa_registros(otr);
			}
		}else{
			if(stricmp(ptr,"EDITAR")==0){
				otr=strtok(NULL," ");
				if(otr==NULL){ //chequea que se pase la tabla
					printf("NO SE ESPECIFICO NI TABLA NI PARAMETROS");
				}else{
					edita_registros(otr);
				}
			}else{
				if(stricmp(ptr,"LISTAR")==0){
					otr=strtok(NULL," ");
					if(otr==NULL){ //chequea que se pase la tabla
						printf("NO SE ESPECIFICO NI TABLA NI PARAMETROS");
					}else{
						lista_registros(otr);
					}
				}else{
					if(stricmp(ptr,"ELIMINAR")==0){
						otr=strtok(NULL," ");
						if(otr==NULL){ //chequea que se pase la tabla
							printf("NO SE ESPECIFICO NI TABLA NI PARAMETROS");
						}else{
							elimina_registros(otr);
						}
					}else{
						if(stricmp(ptr,"BACKUP")==0){
							otr=strtok(NULL," ");
							if(otr==NULL){ //chequea que se pase la tabla
								printf("NO SE ESPECIFICO NI TABLA NI PARAMETROS");
							}else{
								backup_archivos(otr);
							}
						}else{
							if(stricmp(ptr,"LIMPIAR")==0){
								otr=strtok(NULL," ");
								if(otr==NULL){ //chequea que se pase la tabla
									printf("NO SE ESPECIFICO NI TABLA NI PARAMETROS");
								}else{
									limpia_archivos(otr);
								}
							}else{
								if(stricmp(ptr,"RECUPERAR")==0){
									otr=strtok(NULL," ");
									if(otr==NULL){ //chequea que se pase la tabla
										printf("NO SE ESPECIFICO NI TABLA NI PARAMETROS");
									}else{
										recupera_archivos(otr);
									}
								}else{
									if(stricmp(ptr,"MENU")==0){
										main0();
									}else{
										printf("COMANDO ERRONEO");
									}
								}
							}
						}
					}
				}
			}
		}
	}
}


void ingresa_registros(char ptr[])
{
	char *otr;
	char *nom;
	char aux[MAX_LINEA];
	Tdato_IString ind;
	tlista_s  campos;		// campos a solicitar ("*" significa todos)

	int i = 0;
	int sec_campo = 0; // indica que procesa cada campo con su valor
	lcrear(&campos);
	nom = (char*)malloc((strlen(ptr)+1) * sizeof(char));
	strcpy(nom,strupr(ptr));
	while (((ptr = strtok( NULL, ", =" )) != NULL ) && (i == 0)){    // Posteriores llamadas
		if((stricmp(ptr,"ASIGNAR")==0) || (stricmp(ptr,"asignar")==0)){
			i = 1;		
		}
	}
	if (i == 1){
		while (ptr != NULL ){
			if (sec_campo == 0){
				// indica que está en el nombre de campo
				ind.pos = nro_de_campo_valido(nom,ptr);  // Asigna un nro a cada campo valido guardandolo en pos
				strcpy(ind.clave,"");	// coloca el valor del campo a modificar en blanco hasta obtener el valor de la cadena
				ind.flag = 'v';
				sec_campo = 1;	// lo coloca en 1 para indicar que pasó por el nombre del campo a modificar
				ptr = strtok( NULL, ",""" );
			}else{
				strcpy(ind.clave,ptr);	// asigna el valor que debe modificar en el registro
				linsertarfin(&campos,ind);  // inserta el campo y valor a modificar al final de la lista
				sec_campo = 0;	// lo coloca en 0 para indicar que pasó por el valor del campo a modificar
				ptr = strtok( NULL, "=" );    // Posteriores llamadas
			}
		}
		switch (Insertar(nom, &campos))
		{
			case 0:		// sin errores al procesar
				break;
			case 1:
				printf("El archivo %s no existe en esta base de datos.\n", nom);
				break;
			case 2:
				printf("Error al tratar de insertar un registro en el archivo %s.\n", nom);
				break;
			default:
				printf("Ocurrio un error insertar un registro en el archivo %s.\n", nom);
		}
	}else{
		printf("Falta ingresar campos y valores a ingresar para %s\n", nom);
	}
}


//
// Elimina los datos de los archivos
void elimina_registros(char ptr[])
{
	char *otr;
	char *nom;
	char aux[MAX_LINEA];

	char campo_comp[128] = "";		// indica el nombre del campo por el cual compara
	char valor_comp[128] = "";		// indica el valor a comparar 
	int i = 0;

	nom = (char*)malloc((strlen(ptr)+1) * sizeof(char));
	strcpy(nom,strupr(ptr));
	while( (ptr = strtok( NULL, ", " )) != NULL ){    // Posteriores llamadas
		if (i == 1){
			strcpy(campo_comp,ptr);
			if( (ptr = strtok( NULL, ", " )) != NULL ){    // Posteriores llamadas
				if ((stricmp(ptr,"CONTIENE")==0) || (stricmp(ptr,"contiene")==0)){
					if( (ptr = strtok( NULL, ", " )) != NULL ){    // Posteriores llamadas
						strcpy(valor_comp,ptr);
					}else{
						printf("Falta valor para comparar campo %s", campo_comp);
						break;		
					}
				}else{
					printf("Comando invalido para comparar campo %s. Debe usar 'contiene'", campo_comp);
					break;		
				}
			}else{
				printf("Falta comparación del campo %s", campo_comp);
				break;
			}
			i = 0;
		}else{
			if((stricmp(ptr,"DONDE")==0) || (stricmp(ptr,"donde")==0)){
				i = 1;		
			}else{
				printf("Falta la condicion que debe cumplir para eliminar registro del archivo %s", nom);
			}
		}
	}
	switch (Eliminar(nom, campo_comp, valor_comp))
	{
		case 0:		// sin errores al procesar
			break;
		case 1:
			printf("El archivo %s no existe en esta base de datos.", nom);
            break;
        case 2:
            printf("Error al tratar de eliminar registros en el archivo %s.", nom);
            break;
        default:
            printf("Ocurrio un error al intentar eliminar registros en el archivo %s.", nom);
	}
}


//
// Edita los datos de los archivos
void edita_registros(char ptr[])
{
	char *otr;
	char *nom;
	char aux[MAX_LINEA];
	Tdato_IString ind;
	tlista_s  campos;		// campos a solicitar ("*" significa todos)

	char campo_comp[128] = "";		// indica el nombre del campo por el cual compara
	char valor_comp[128] = "";		// indica el valor a comparar 
	int i = 0;
	int j = 0;
	int sec_campo = 0; // indica que procesa cada campo con su valor
	
	lcrear(&campos);

	nom = (char*)malloc((strlen(ptr)+1) * sizeof(char));
	strcpy(nom,strupr(ptr));
	while (((ptr = strtok( NULL, ", =" )) != NULL ) && (i == 0)){    // Posteriores llamadas
		if((stricmp(ptr,"ASIGNAR")==0) || (stricmp(ptr,"asignar")==0)){
			i = 1;		
		}else{
			if (j == 1){
				strcpy(campo_comp,ptr);
				if( (ptr = strtok( NULL, ", " )) != NULL ){    // Posteriores llamadas
					if((stricmp(ptr,"CONTIENE")==0) || (stricmp(ptr,"contiene")==0)){
						if( (ptr = strtok( NULL, ", " )) != NULL ){    // Posteriores llamadas
							strcpy(valor_comp,ptr);
						}else{
							printf("Falta valor para comparar campo %s\n", campo_comp);
							break;		
						}
					}else{
						printf("Comando invalido para comparar campo %s. Debe usar 'contiene'\n", campo_comp);
						break;		
					}
				}else{
					printf("Falta comparación del campo %s\n", campo_comp);
					break;
				}
				j = 0;
			}else{
				if((stricmp(ptr,"DONDE")==0) || (stricmp(ptr,"donde")==0)){
					j = 1;		
				}
			}
		}
	}
	if (i == 1){
		while (ptr != NULL ){
			if (sec_campo == 0){
				// indica que está en el nombre de campo
				ind.pos = nro_de_campo_valido(nom,ptr);  // Asigna un nro a cada campo valido guardandolo en pos
				strcpy(ind.clave,"");	// coloca el valor del campo a modificar en blanco hasta obtener el valor de la cadena
				ind.flag = 'v';
				sec_campo = 1;	// lo coloca en 1 para indicar que pasó por el nombre del campo a modificar
				ptr = strtok( NULL, ",""" );
			}else{
				strcpy(ind.clave,ptr);	// asigna el valor que debe modificar en el registro
				linsertarfin(&campos,ind);  // inserta el campo y valor a modificar al final de la lista
				sec_campo = 0;	// lo coloca en 0 para indicar que pasó por el valor del campo a modificar
				ptr = strtok( NULL, "=" );    // Posteriores llamadas
			}
		}
		switch (Editar(nom, &campos, campo_comp, valor_comp))
		{
			case 0:		// sin errores al procesar
				break;
			case 1:
				printf("El archivo %s no existe en esta base de datos.\n", nom);
				break;
			case 2:
				printf("Error al tratar de editar el archivo %s.\n", nom);
				break;
			default:
				printf("Ocurrio un error al editar el archivo %s.\n", nom);
		}
	}else{
		printf("Falta ingresar campos y valores a modificar para %s\n", nom);
	}
}

//
// Lista los datos de los archivos
void lista_registros(char ptr[])
{
	char *otr;
	char *nom;
	char aux[MAX_LINEA];
	Tdato_IString ind;
	tlista_s  campos;		// campos a solicitar ("*" significa todos)
	
	lcrear(&campos);
	char indice[128];		// indica el indice por el cual ordena la consulta
	strcpy(indice,"cod");
	char campo_comp[128] = "";		// indica el nombre del campo por el cual compara
	char valor_comp[128] = "";		// indica el valor a comparar 
	int i = 0;
	int j = 0;

	nom = (char*)malloc((strlen(ptr)+1) * sizeof(char));
	strcpy(nom,strupr(ptr));
	while( (ptr = strtok( NULL, ", " )) != NULL ){    // Posteriores llamadas
		if (i == 1){
			strcpy(indice,ptr);
			i = 0;
		}else{
			if((stricmp(ptr,"POR")==0) || (stricmp(ptr,"por")==0)){
				i = 1;		
			}else{
				if (j == 1){
					strcpy(campo_comp,ptr);
					if( (ptr = strtok( NULL, ", " )) != NULL ){    // Posteriores llamadas
						if((stricmp(ptr,"CONTIENE")==0) || (stricmp(ptr,"contiene")==0)){
							if( (ptr = strtok( NULL, ", " )) != NULL ){    // Posteriores llamadas
								strcpy(valor_comp,ptr);
							}else{
								printf("Falta valor para comparar campo %s", campo_comp);
								break;		
							}
						}else{
							printf("Comando invalido para comparar campo %s. Debe usar 'contiene'", campo_comp);
							break;		
						}
					}else{
						printf("Falta comparación del campo %s", campo_comp);
						break;
					}
					j = 0;
				}else{
					if((stricmp(ptr,"DONDE")==0) || (stricmp(ptr,"donde")==0)){
						j = 1;		
					}else{
						strcpy(ind.clave,ptr);
						ind.pos = 0;
						ind.flag = 'v';
						linsertarfin(&campos,ind);
					}
				}
			}
		}
	}
	switch (Listar(nom, &campos, indice, campo_comp, valor_comp))
	{
		case 0:		// sin errores al procesar
			break;
		case 1:
			printf("El archivo %s no existe en esta base de datos.", nom);
            break;
        case 2:
            printf("Error al tratar de listar el archivo %s.", nom);
            break;
        default:
            printf("Ocurrio un error al listar el archivo %s.", nom);
	}
}

//
// Crea los archivos
void crea_archivos(char ptr[])
{
	char *otr;
	char *nom;


	nom = (char*)malloc((strlen(ptr)+1) * sizeof(char));
	strcpy(nom,strupr(ptr));
	if(stricmp(nom,"*")==0){
		crear_archivos(nom_arch_Libros);
		crear_archivos(nom_arch_Temas);
		crear_archivos(nom_arch_Autores);
		crear_archivos(nom_arch_Socios);
		crear_archivos(nom_arch_Prestamos);
	}else{
		crear_archivos(nom);
	}
}
//
// Backup de los archivos
void backup_archivos(char ptr[])
{
	char *otr;
	char *nom;


	nom = (char*)malloc((strlen(ptr)+1) * sizeof(char));
	strcpy(nom,strupr(ptr));
	if(stricmp(nom,"*")==0){
		BackupArchGenerico(nom_arch_Libros,sizeof(Libros));		// backup Libros e indice
		BackupArchGenerico(nom_arch_Temas,sizeof(Temas));		// backup Temas e indice asociado
		BackupArchGenerico(nom_arch_Prestamos,sizeof(Prestamos)); // backup Prestamos e indice asociado
		BackupArchGenerico(nom_arch_Autores,sizeof(Autores)); // backup Autores e indice asociado
		BackupArchGenerico(nom_arch_Socios,sizeof(Socios));		// backup Socios e indice asociado
		printf("\nBackup exitoso de todos los archivos.\n");
	}else{
		if(stricmp(nom,nom_arch_Libros)==0){
			BackupArchGenerico(nom_arch_Libros,sizeof(Libros));		// backup Libros e indice
			printf("\nBackup exitoso del archivo %s.\n",nom);
		}else{
			if(stricmp(nom,nom_arch_Autores)==0){
				BackupArchGenerico(nom_arch_Autores,sizeof(Autores)); // backup Autores e indice asociado
				printf("\nBackup exitoso del archivo %s.\n",nom);
			}else{
				if(stricmp(nom,nom_arch_Socios)==0){
					BackupArchGenerico(nom_arch_Socios,sizeof(Socios));		// backup Socios e indice asociado
					printf("\nBackup exitoso del archivo %s.\n",nom);
				}else{
					if(stricmp(nom,nom_arch_Temas)==0){
						BackupArchGenerico(nom_arch_Temas,sizeof(Temas));		// backup Temas e indice asociado
						printf("\nBackup exitoso del archivo %s.\n",nom);
					}else{
						if(stricmp(nom,nom_arch_Prestamos)==0){
							BackupArchGenerico(nom_arch_Prestamos,sizeof(Prestamos)); // backup Prestamos e indice asociado
							printf("\nBackup exitoso del archivo %s.\n",nom);
						}else{
							printf("\nArchivo a backupear invalido.\n");
						}
					}
				}
			}
		}
	}
}
//
// recuperar los archivos
void recupera_archivos(char ptr[])
{
	char *otr;
	char *nom;


	nom = (char*)malloc((strlen(ptr)+1) * sizeof(char));
	strcpy(nom,strupr(ptr));
	if(stricmp(nom,"*")==0){
		RecuperaArchGenerico(nom_arch_Libros,sizeof(Libros));		// recuperar Libros e indice
		RecuperaArchGenerico(nom_arch_Temas,sizeof(Temas));		// recuperar Temas e indice asociado
		RecuperaArchGenerico(nom_arch_Prestamos,sizeof(Prestamos)); // recuperar Prestamos e indice asociado
		RecuperaArchGenerico(nom_arch_Autores,sizeof(Autores)); // recuperar Autores e indice asociado
		RecuperaArchGenerico(nom_arch_Socios,sizeof(Socios));		// recuperar Socios e indice asociado
		printf("\Finalizo intento de recuperacion de todos los archivos.\n");
	}else{
		if(stricmp(nom,nom_arch_Libros)==0){
			RecuperaArchGenerico(nom_arch_Libros,sizeof(Libros));		// recuperar Libros e indice
			printf("\nFinalizo intento de recuperacion del archivo %s.\n",nom);
		}else{
			if(stricmp(nom,nom_arch_Autores)==0){
				RecuperaArchGenerico(nom_arch_Autores,sizeof(Autores)); // recuperar Autores e indice asociado
				printf("\nFinalizo intento de recuperacion del archivo %s.\n",nom);
			}else{
				if(stricmp(nom,nom_arch_Socios)==0){
					RecuperaArchGenerico(nom_arch_Socios,sizeof(Socios));		// recuperar Socios e indice asociado
					printf("\nFinalizo intento de recuperacion del archivo %s.\n",nom);
				}else{
					if(stricmp(nom,nom_arch_Temas)==0){
						RecuperaArchGenerico(nom_arch_Temas,sizeof(Temas));		// recuperar Temas e indice asociado
						printf("\nFinalizo intento de recuperacion del archivo %s.\n",nom);
					}else{
						if(stricmp(nom,nom_arch_Prestamos)==0){
							RecuperaArchGenerico(nom_arch_Prestamos,sizeof(Prestamos)); // recuperar Prestamos e indice asociado
							printf("\nFinalizo intento de recuperacion del archivo %s.\n",nom);
						}else{
							printf("\nArchivo a recuperar invalido.\n");
						}
					}
				}
			}
		}
	}
}
//
// limpiar los archivos
void limpia_archivos(char ptr[])
{
	char *otr;
	char *nom;


	nom = (char*)malloc((strlen(ptr)+1) * sizeof(char));
	strcpy(nom,strupr(ptr));
	if(stricmp(nom,"*")==0){
		LimpiaArchGenerico(nom_arch_Libros);		// limpia Libros e indice
		LimpiaArchGenerico(nom_arch_Temas);		// limpia Temas e indice asociado
		LimpiaArchGenerico(nom_arch_Prestamos); // limpia Prestamos e indice asociado
		LimpiaArchGenerico(nom_arch_Autores); // limpia Autores e indice asociado
		LimpiaArchGenerico(nom_arch_Socios);		// limpia Socios e indice asociado
		printf("\Finalizo intento de reorganizacion de todos los archivos.\n");
	}else{
		if(stricmp(nom,nom_arch_Libros)==0){
			LimpiaArchGenerico(nom_arch_Libros);		// limpia Libros e indice
			printf("\nFinalizo intento de reorganizacion del archivo %s.\n",nom);
		}else{
			if(stricmp(nom,nom_arch_Autores)==0){
				LimpiaArchGenerico(nom_arch_Autores); // limpia Autores e indice asociado
				printf("\nFinalizo intento de reorganizacion del archivo %s.\n",nom);
			}else{
				if(stricmp(nom,nom_arch_Socios)==0){
					LimpiaArchGenerico(nom_arch_Socios);		// limpia Socios e indice asociado
					printf("\nFinalizo intento de reorganizacion del archivo %s.\n",nom);
				}else{
					if(stricmp(nom,nom_arch_Temas)==0){
						LimpiaArchGenerico(nom_arch_Temas);		// limpia Temas e indice asociado
						printf("\nFinalizo intento de reorganizacion del archivo %s.\n",nom);
					}else{
						if(stricmp(nom,nom_arch_Prestamos)==0){
							LimpiaArchGenerico(nom_arch_Prestamos); // limpia Prestamos e indice asociado
							printf("\nFinalizo intento de reorganizacion del archivo %s.\n",nom);
						}else{
							printf("\nArchivo a reorganizar invalido.\n");
						}
					}
				}
			}
		}
	}
}
// Asigna un numero a cada campo valido
// si no lo encuentra le asigna un 999
int nro_de_campo_valido(char nom[128], char campo_comp[128])
{
	if(stricmp(nom,nom_arch_Libros)==0){
		if (stricmp(campo_comp,"cod")==0)
			return(1);
		if (stricmp(campo_comp,"cod_tema")==0) 
			return(2);
		if (stricmp(campo_comp,"titulo")==0)
			return(3);
		if (stricmp(campo_comp,"cod_autor")==0) 
			return(4);
		if (stricmp(campo_comp,"ubicacion")==0)
			return(5);
	}

	if(stricmp(nom,nom_arch_Autores)==0){
		if (stricmp(campo_comp,"cod")==0)
			return(1);
	}

	if(stricmp(nom,nom_arch_Socios)==0){
		if (stricmp(campo_comp,"cod")==0)
			return(1);
		if (stricmp(campo_comp,"nombreyapellido")==0) 
			return(2);
		if (stricmp(campo_comp,"dni")==0)
			return(3);
		if (stricmp(campo_comp,"direccion")==0) 
			return(4);
	}

	if(stricmp(nom,nom_arch_Temas)==0){
		if (stricmp(campo_comp,"cod")==0)
			return(1);
	}

	if(stricmp(nom,nom_arch_Prestamos)==0){
		if (stricmp(campo_comp,"cod")==0)
			return(1);
		if (stricmp(campo_comp,"cod_socio")==0) 
			return(2);
		if (stricmp(campo_comp,"cod_libro")==0)
			return(3);
	}
	// si no es ninguno de los anteriores entonces no existe
	return(999);
}