/*
 __  __      ____            __  __  ______  __  __   __    __
/\ \/\ \    /\  _`\         /\ \/\ \/\  _  \/\ \/\ \ /\ \  /\ \
\ \ \ \ \   \ \,\L\_\       \ \ `\\ \ \ \L\ \ \ \ \ \\ `\`\\/'/
 \ \ \ \ \   \/_\__ \        \ \ , ` \ \  __ \ \ \ \ \`\ `\ /'
  \ \ \_\ \  __/\ \L\ \  __   \ \ \`\ \ \ \/\ \ \ \_/ \ `\ \ \
	\ \_____\/\_\ `\____\/\_\   \ \_\ \_\ \_\ \_\ `\___/   \ \_\
	 \/_____/\/_/\/_____/\/_/    \/_/\/_/\/_/\/_/`\/__/     \/_/

															by Flash Gordon Co.

B: Barco     //2,3,4,5
X: Barco tocado
*: Mina //no se muestra
~: agua
O: agua tirado o minas tirado
1028 ASCII: tablero vacio

*/


#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define max 0
#define maxx 10     		 //max de ancho de la matriz
#define maxy 10     		 //max de largo de la matriz
#define movminas 1 		 //cantidad de pos que explotan las minas
#define cantidadbarcos 5 //cantidad de barcos
#define cantidad_min 1
#define cantidad_max 2
#define coord_min 3
#define coord_max 5
#define max_minas 10     //max cantidad de minas
#define min_long_barco 1
#define max_long_barco 7
#define max_rango_barco 2 //se cuenta el \0 :P es mas que nada para el uppercase de la direccion del barco
#define max_coordenada 6
#define min_coordenada 3


void inicializar(char ar[maxx+1][maxy+1]); //inizializa la matriz en '~'
void inicializar_tablero(char ar[maxx+1][maxy+1]); //inizializa el tablero
void loading_minas(int load);                		// Interfaz de carga
void loading_players(int load);                     // Interfaz de carga
void delay(float t);                   		// Genera un delay
void cargar_minas(char archivo[15],char coord[maxx+1][maxy+1]); //carga minas
void tratarPlayer(char archivo[15],char ar[maxx+1][maxy+1],char ar2[maxx+1][maxy+1],char nombre_p1[40],char nombre_p2[40],char tablero1[maxx+1][maxy+1],char tablero2[maxx+1][maxy+1],int *cantb1,int *cantb2,int *gano); //carga barcos
void validarPlayer(FILE *fp, char caracteres[85],int *i,char ar[maxx+1][maxy+1], char nombre_p[40],char tablero[maxx+1][maxy+1],int *cantb,int *gano,int jug); //carga barcos
void tratarCoordenadas(char **sub_ptr,int **i, int *iii, int *long_barco, int *len_coord,char ar[maxx+1][maxy+1],char direccion, int *aux_coordX, int *aux_coordY,char tablero[maxx+1][maxy+1],int *cantb,int *gano,int jug);
void verif_bm(char barcos[maxx+1][maxy+1],char tablero[maxx+1][maxy+1],int *cantb,int *gano,int jug,int X,int Y,int tambarco);
void clrbuf();                         		// Limpia el buffer del getch
void mostrartablero(char ar[maxx+1][maxy+1]);// Muestra el tablero en la pantalla
int Modo_Juego();                            // Valida la seleccion del modo de juego
void jugar(char jugador2[maxx+1][maxy+1],char tablero1[maxx+1][maxy+1],int *cantb,int *gano,int jug);
void Jugar_coordenadas(int *X,int *Y,char tablero[maxx+1][maxy+1]); //jugas las coordenadas
void proceso(char jugador2[maxx+1][maxy+1],char tablero1[maxx+1][maxy+1],int *cantb,int *gano,int jug,int X,int Y);
char barco_hundido(char jugador2[maxx+1][maxy+1],int X,int Y,int tambarco);//se fija si el barco esta undido
void jugar_cpu(char jugador2[maxx+1][maxy+1],char tablero1[maxx+1][maxy+1],int *cantb,int *gano,int jug);
void Coordenadas_cpu(int *X,int *Y,char tablero[maxx+1][maxy+1]); //juega la CPU
char Seguro_Salir();                   		// Confirma el exit
char Enter();                          		// Valida un enter
void Ganador(int gano,int jug,char name1[85],char name2[85]); // Informa ganador
void mostrar_tableros(char ar[maxx+1][maxy+1],char ar2[maxx+1][maxy+1],char nombre[40]);



//Pre{Pasar por linea de comando los archivos}//
void main(int argi,char *argv[])
{
char jugador1[maxx+1][maxy+1];
char jugador2[maxx+1][maxy+1];
char tablero1[maxx+1][maxy+1];
char tablero2[maxx+1][maxy+1];
char name1[40];
char name2[40];
int gano=0;
int cantb1=cantidadbarcos;
int cantb2=cantidadbarcos;
int jug=0;

randomize();

printf("WELCOME TO:\n\n");
printf("_|    _|        _|_|_|          _|      _|    _|_|    _|      _|  _|      _|\n");
printf("_|    _|      _|                _|_|    _|  _|    _|  _|      _|    _|  _|  \n");
printf("_|    _|        _|_|            _|  _|  _|  _|_|_|_|  _|      _|      _|    \n");
printf("_|    _|            _|          _|    _|_|  _|    _|    _|  _|        _|    \n");
printf("  _|_|    _|  _|_|_|    _|      _|      _|  _|    _|      _|          _|    \n");
Enter();

inicializar(jugador1);//aca cargan los barcos
inicializar(jugador2);//aca cargan los barcos
inicializar_tablero(tablero1);// en el caso que al apoyar un barco caiga en una mina se pone esa pocicion como explotada X
inicializar_tablero(tablero2);// en el caso que al apoyar un barco caiga en una mina se pone esa pocicion como explotada

loading_minas(4);
cargar_minas(argv[2],jugador1);	// en minas 1 secarga minas2.txt
cargar_minas(argv[1],jugador2);	// en minas 2 secarga minas1.txt

loading_players(8);
tratarPlayer(argv[3],jugador1,jugador2,name1,name2,tablero1,tablero2,&cantb1,&cantb2,&gano);

printf("Tablero %s: \n",name1);
mostrartablero(tablero1);
Enter();
clrscr();
printf("Tablero %s: \n",name2);
mostrartablero(tablero2);
Enter();
clrscr();
printf("Referencias del tablero:\n\n");
printf("B: Barco\n");
printf("X: Barco tocado\n");
printf("*: Mina //no se muestra\n");
printf("~: agua\n");
printf("O: agua tirado o minas tirado\n");
printf("1028 ASCII: tablero vacio\n");
Enter();
clrscr();
jug=Modo_Juego();
switch(jug){
	case 1:     //CPU MODE
	{
		int juega=0;
		juega=random(2)+1;
		clrscr();
		while(gano==0){
			if(juega==1){
				printf("Turno del jugador 1: %s\n",name1);
				Enter();
				clrscr();
				mostrar_tableros(jugador1,tablero1,name1);
				jugar(jugador2,tablero1,&cantb2,&gano,juega);
				mostrar_tableros(jugador1,tablero1,name1);
				juega=2;
				clrscr();
			}else{
				if(juega==2){
				printf("Turno de la CPU %s\n",name2);
				Enter();
				clrscr();
				jugar_cpu(jugador1,tablero2,&cantb1,&gano,juega);
				juega=1;
				clrscr();
				}else{
					printf("Error en la seleccion de jugadores, autocorreccion, empieza por jugador 1");
					Enter();
					clrscr();
					juega=1;
				}
			}
		}
		Ganador(gano,jug,name1,name2);
	}
	break;

	case 2:    //2 PLAYERS MODE
	{
		int juega=0;
		juega=random(2)+1;
		clrscr();
		while(gano==0){
			if(juega==1){
				printf("Turno del jugador 1: %s\n",name1);
				Enter();
				clrscr();
				mostrar_tableros(jugador1,tablero1,name1);
				jugar(jugador2,tablero1,&cantb2,&gano,juega);
				mostrar_tableros(jugador1,tablero1,name1);
				juega=2;
				clrscr();
			}else{
				if(juega==2){
				printf("Turno del jugador 2: %s\n",name2);
				Enter();
				clrscr();
				mostrar_tableros(jugador2,tablero2,name2);
				jugar(jugador1,tablero2,&cantb1,&gano,juega);
            mostrar_tableros(jugador2,tablero2,name2);
				juega=1;
				clrscr();
				}else{
					printf("Error en la seleccion de jugadores, autocorreccion, empieza por jugador 1");
					Enter();
					clrscr();
					juega=1;
				}
			}
		}
		Ganador(gano,jug,name1,name2);
	}
	break;

	default:
	{
		printf("Error en el ingreso de modo de juego");
	}
	break;
}

printf("\nGracias por haber jugado a:\n\n");
printf("_|    _|        _|_|_|          _|      _|    _|_|    _|      _|  _|      _|\n");
printf("_|    _|      _|                _|_|    _|  _|    _|  _|      _|    _|  _|  \n");
printf("_|    _|        _|_|            _|  _|  _|  _|_|_|_|  _|      _|      _|    \n");
printf("_|    _|            _|          _|    _|_|  _|    _|    _|  _|        _|    \n");
printf("  _|_|    _|  _|_|_|    _|      _|      _|  _|    _|      _|          _|    \n\n");
printf("																	by Flash Gordon Co. ");



}

//Pre{...}//
void inicializar(char ar[maxx+1][maxy+1])
{
int i,j;
ar[0][0]='@';
for(i=1;i<=maxx;i++){
	ar[i][0]=(i+'0');
}
for(j=1;j<=maxx;j++){
	ar[0][j]=(j+'0');
}
for(i=1;i<=maxx;i++){
	for(j=1;j<=maxy;j++){
		ar[i][j]='~';//ar[i][j]='~';
	}
}
}
//Pos{Inicializa la matriz pedida en agua}//
/*---------------------------------*/


//Pre{...}//
void inicializar_tablero(char ar[maxx+1][maxy+1])
{
int i,j;
ar[0][0]='@';
for(i=1;i<=maxx;i++){
	ar[i][0]=(i+'0');
}
for(j=1;j<=maxx;j++){
	ar[0][j]=(j+'0');
}
for(i=1;i<=maxx;i++){
	for(j=1;j<=maxy;j++){
		ar[i][j]=1028;
	}
}
}
//Pos{Inicializa la matriz pedida en ''}//
/*---------------------------------*/


//Pre{...}//
void loading_minas(int load)
{
time_t start;
time_t current;
int i;
clrscr();
printf("Validando archivo minas,por favor espere\n");
printf("LOADING");
time(&start);
do{
	for(i=0;i<=3;i++){
		delay(1);
		printf(".");
	}
	clrscr();
	printf("Validando archivo minas,por favor espere\n");
	printf("LOADING");
	time(&current);
}while(difftime(current,start) < load);
clrscr();
}
//Pos{Muestra la interfaz de carga}//
/*----------------------------------*/


//Pre{...}//
void loading_players(int load)
{
time_t start;
time_t current;
int i;
clrscr();
printf("Validando archivo players,por favor espere\n");
printf("LOADING");
time(&start);
do{
	for(i=0;i<=3;i++){
		delay(1);
		printf(".");
	}
	clrscr();
	printf("Validando archivo players,por favor espere\n");
	printf("LOADING");
	time(&current);
}while(difftime(current,start) < load);
clrscr();
}
//Pos{Muestra la interfaz de carga}//
/*----------------------------------*/

//Pre{Utilizar time.h}//
void delay(float t)
{
time_t start;
time_t current;

time(&start);
do{
	time(&current);
}while(difftime(current,start) < t);

}
//Pos{Genera un delay de 0 a max (constante definida) segundos}//
/*-------------------------------------------------------------*/

//Pre{Que exista el archivo e inicializar el tablero}//
void cargar_minas(char archivo[15],char coord[maxx+1][maxy+1])
{
	char caracteres[85];
	char aux_caracteres[85];
	int i=1;
	int fmax;
	int coordX;
	int coordY;
	int len;
	int len_ptr;
	int ii;
	int is_end;
	int count;
	int count_comas;
	char buffer[4];
	char *ptr;
	FILE *fp;

	fp = fopen(archivo,"r");

	if(fgets( caracteres, 85, fp) == NULL ){
		printf("Archivo vacio");
		exit(0);
	}

	len = strlen( caracteres );
	len--;

	if(strchr(caracteres, '\n') != NULL){
		caracteres[len] = '\0';
	}else{
			len++;
	}

	if(len > cantidad_max){
		printf("Error: longitud maxima exedida fin de ejecucion");
		exit(0);
	}
	strcpy(aux_caracteres,caracteres);
	if(strcmp(caracteres,"0")){
		ii = 0;
		count = 0;
		is_end=0;
		while(ii < len){
			if(caracteres[ii] == '0' && !(is_end) && (ii < len-1)){
				count++;
			}else{
				if(caracteres[ii] == ' '){
					count++;
				}else{
					caracteres[ii-count] = caracteres[ii];
					is_end=1;
				}
			}
			ii++;
		}
	  caracteres[ii-count] = '\0';
	}
	if(!strcmp(caracteres, "")){
		printf("Error: falta cantidad de minas en la linea 1");
		exit(0);
	}
	if(strchr(caracteres, ',') != NULL){
		printf("Error: coordenada indeseada, hace falta definir la cantidad de minas");
		exit(0);
	}
	fmax = atoi( caracteres );
	itoa(fmax, buffer, 10);
	//Verificamos que sea realmente un numero y que no posea caracteres indeseados
	if(strcmp( caracteres, buffer)){
		printf("Error: la cantidad de minas esta mal formada");
		exit(0);
	}

	//Verificamos que no supere el maximo permitido de minas ( MAX )
	if(fmax > max_minas){
		printf("Error: la cantidad de minas supera el maximo permitido de %d minas", max_minas);
		exit(0);
	}
	if(fmax < 0){
		printf("Error: la cantidad de minas no puede ser negativo");
		exit(0);
	}


	while(!(feof(fp)) && (fmax >= i)){
		coordX=-1;
		coordY=-1;
		fgets( caracteres, 85, fp);

		len = strlen( caracteres );
		len--;

		if(strchr(caracteres, '\n') != NULL){
			caracteres[len] = '\0';
		}else{
			len++;
		}

		strcpy(aux_caracteres,caracteres);

		//Verificamos que si tenemos como cantidad de minas 0 entonses no deben de haber coordenadas
		if(fmax == 0){
			printf("Error: la cantidad de minas es nula no deben haber coordenadas");
			exit(0);
		}

		if(len > coord_max){
			printf("Error: exedio el maximo de longitud permitida para la coordenada de la linea %d",i+1);
			exit(0);
		}
		if(len < coord_min){
			printf("Error: no cumple con el minimo de longitud requerida para la coordenada de la linea %d",i+1);
			exit(0);
		}

		if(strchr(caracteres, ',') == NULL){
			printf("Error: la coordenada de la linea %d no posee coma",i+1);
			exit(0);
		}
		ptr = strtok( caracteres , "," );
		if(ptr == NULL){
			printf("Error: falta coordenada X en la linea %d", i+1);
			exit(0);
		}
		coordX = atoi( ptr );
		itoa( coordX, buffer, 10);
		len_ptr = strlen( ptr );

		ii = 0;
		count = 0;
		is_end=0;
		while(ii < len_ptr){
			if(ptr[ii] == '0' && !(is_end) && (ii < len_ptr-1)){
					count++;
			}else{
				if(ptr[ii] == ' '){
					 count++;
				}else{
					 ptr[ii-count] = ptr[ii];
					 is_end=1;
				}
			}
			ii++;
		}
		ptr[ii-count] = '\0';

		if(!strcmp(ptr, "0")){
			printf("Error: la coordenada X de numeracion 0 no es posible en la linea %d",i+1);
			exit(0);
		}

		if(!strcmp(ptr, "")){
			printf("Error: falta coordenada X en la linea %d", i+1);
			exit(0);
		}
		if(strcmp( ptr, buffer)){
			printf("Error: la coordenada X de la linea %d esta mal formada", i+1);
			exit(0);
		}

		if(coordX > maxx){
			printf("Error: la coordenada X de la linea %d supera las dimensiones del tablero", i+1);
			exit(0);
		}
		if(coordX < 0){
			printf("Error: la coordenada X de la linea %d es negativo", i+1);
			exit(0);
		}
		count_comas = 0;
		while( ( ptr=strtok( NULL, "," )) != NULL ){    // Posteriores llamadas
			count_comas++;
			if(count_comas > 1){
				printf("Error: hay mas de 1 coma en la coordenada de la linea %d", i+1);
				exit(0);
			}
			coordY = atoi( ptr );
			itoa( coordY, buffer, 10);

			len_ptr = strlen( ptr );
			ii = 0;
			count = 0;
			is_end=0;
			while(ii < len_ptr){
				if(ptr[ii] == '0' && !(is_end) && (ii < len_ptr-1)){
					count++;
				}else{
					if(ptr[ii] == ' '){
						 count++;
					}else{
						 ptr[ii-count] = ptr[ii];
						 is_end=1;
					}
				}
				ii++;
			}
			ptr[ii-count] = '\0';

			if(!strcmp(ptr, "0")){
				printf("Error: la coordenada Y de numeracion 0 no es posible en la linea %d",i+1);
				exit(0);
			}
			if(!strcmp(ptr, "")){
				printf("Error: falta coordenada Y en la linea %d", i+1);
				exit(0);
			}
			if(strcmp( ptr, buffer)){
				printf("Error: la coordenada Y de la linea %d esta mal formada", i+1);
				exit(0);
			}
			if(coordY > maxy){
				printf("Error: la coordenada Y de la linea %d supera las dimensiones del tablero", i+1);
				exit(0);
			}
			if(coordY < 0){
				printf("Error: la coordenada Y de la linea %d es negativo", i+1);
				exit(0);
			 }

		}

		if(count_comas == 0){
			printf("Error: falta coordenada Y en la linea %d", i+1);
			exit(0);
		}
		if(aux_caracteres[len] == ','){
			printf("Error: hay mas de 1 coma en la coordenada de la linea %d", i+1);
			exit(0);
		}
		if(coord[coordX][coordY]=='*'){
			printf("Error: no puede haber mas de una mina en la posicion %d,%d",coordX,coordY);
			exit(0);
		}else{
			coord[coordX][coordY]='*';
		}
		i++;
	}
	if(!feof(fp)){
		printf("Error: hay mas coordenadas que minas a ingresar");
		exit(0);
	}
	if(fmax > i-1){
		printf("Error: hay menos coordenadas que minas a ingresar");
		exit(0);
	}
	fclose(fp);

}
//Pos{Carga las minas en la matriz pasada pro parametro}//
/*-----------------------------------------------------------------------------------------*/

//Pre{Que exista el archivo e inicializar el tablero}//
void tratarPlayer(char archivo[15],char ar[maxx+1][maxy+1],char ar2[maxx+1][maxy+1],char nombre_p1[40],char nombre_p2[40],char tablero1[maxx+1][maxy+1],char tablero2[maxx+1][maxy+1],int *cantb1,int *cantb2,int *gano){
	FILE *fp;
	char caracteres[85];
	int i = 0;
	int h,j;
	fp = fopen(archivo,"r");
	if(fgets( caracteres, 85, fp) == NULL ){
		printf("Archivo vacio");
		exit(0);
	}

	printf("PLAYER 1:\n\n");
	validarPlayer(fp, caracteres, &i, ar, nombre_p1,tablero2,cantb1,gano,1);
	clrscr();
	if(fgets( caracteres, 85, fp) == NULL){
		printf("Error: falta jugador 2");
		exit(0);
	}
	if(!(feof(fp)) && (strchr(caracteres,'"') == NULL)){
		printf("Error: el jugador %s tiene mas de %d barcos", nombre_p1, cantidadbarcos);
		exit(0);
	}
	printf("PLAYER 2: \n\n");
	validarPlayer(fp, caracteres, &i, ar2, nombre_p2,tablero1,cantb2,gano,2);
	clrscr();
	if(fgets( caracteres, 85, fp) != NULL){
		printf("Error: no debe haber mas de 2 jugadores");
		exit(0);
	}
	if(!(feof(fp)) && (strchr(caracteres,'"') == NULL)){
		printf("Error: el jugador %s tiene mas de %d barcos", nombre_p2, cantidadbarcos);
		exit(0);
	}
	fclose(fp);
}
//Pos{Chequea que el archivo no este vacia para continuar validando}//
/*--------------------------------------------------------------------------------*/

//Pre{Archivo no vacio}//
void validarPlayer(FILE *fp, char caracteres[85],int *i,char ar[maxx+1][maxy+1], char nombre_p[40],char tablero[maxx+1][maxy+1],int *cantb,int *gano,int jug){
	char aux_caracteres[85];
	int len;
	int len_ptr;
	int len_coord;
	int ii;
	int iii;
	int barcos;
	int count;
	int is_end;
	int long_barco;
	int aux_coordX=0;
	int aux_coordY=0;
	char direccion;
	char buffer[4];
	char *ptr;
	char *sub_ptr;
	char aux_ptr[100];
	int barcosdisponiblescant = 5;
	int barcosdisponibles[cantidadbarcos];

	//Cargamos los barcos disponibles
	barcosdisponibles[0]=2;
	barcosdisponibles[1]=3;
	barcosdisponibles[2]=4;
	barcosdisponibles[3]=4;
	barcosdisponibles[4]=5;

	//Tomamos la longitud de la cadena y le restamos 1 por el salto de linea
	len = strlen( caracteres );
	len--;
	//Quitamos el salto de linea en caso de que alla sino le sumamos 1 a len
	if(strchr(caracteres, '\n') != NULL){
		caracteres[len] = '\0';
	}else{
		len++;
	}
	strcpy(aux_caracteres,caracteres);

	if(strchr(caracteres,'"') == NULL){
		printf("Error: faltan comillas dobles en el nombre del jugador");
		exit(0);
	}
	//Revisamos a simple validacion si directamente esta bien formada y no trae ningun valor entre ambos
	if(caracteres[0]=='"' && caracteres[1]=='"' && caracteres[2]=='\0'){
		printf("Error: falta nombre del jugador");
		exit(0);
	}
	if(caracteres[0]=='"' && caracteres[1]=='\0'){
		printf("Error: falta nombre del jugador y comillas dobles del lado derecho");
		exit(0);
	}

	//Empezamos con el parseo de la primer linea
	ptr = strtok( caracteres , "\"" );

	if(ptr != NULL){
	len_ptr = strlen(ptr);

		if(aux_caracteres[0] != '"'){
			printf("Error: faltan comillas dobles del lado izquierdo en el nombre del jugador");
			exit(0);
		}
		//Utilizamos esta rutina para quitar los espacios
		ii = 0;
		count = 0;
		is_end = 0;
		while(ii < len_ptr){
			if((ptr[ii] == ' ' ) && (!(is_end))){
				count++;
			}else{
				ptr[ii-count] = ptr[ii];
				is_end=1;
			}
			ii++;
		}
		ptr[ii-count] = '\0';
		if(ptr[0] == '\0'){
			printf("Error: falta nombre del jugador");
			exit(0);
		}

		if( ( ptr=strtok( NULL, "\"" )) != NULL ){
			printf("Error: posee caracteres indeseados fuera de los corchetes dobles");
			exit(0);
		}
		if(aux_caracteres[len-1] != '"'){
			printf("Error: faltan comillas dobles del lado derecho en el nombre del jugador");
			exit(0);
		}
		strcpy(nombre_p,caracteres);
	}

	*i=*i+1;
	barcos = 1;
	while(!(feof(fp)) && (barcos<=cantidadbarcos)){

		fgets( caracteres, 85, fp);

		if((strchr(caracteres,'"') != NULL) && (barcos < cantidadbarcos)){
			printf("Error: el jugador %s tiene menos de %d barcos", nombre_p , cantidadbarcos);
			exit(0);
		}

		aux_coordX=0;
		aux_coordY=0;

		//Tomamos la longitud de la cadena y le restamos 1 por el salto de linea
		len = strlen( caracteres );
		len--;
		//Quitamos el salto de linea en caso de que alla sino le sumamos 1 a len
		if(strchr(caracteres, '\n') != NULL){
			caracteres[len] = '\0';
		}else{
			len++;
		}
		strcpy(aux_caracteres,caracteres);
		ptr = strtok(caracteres, "-" );

		if(ptr != NULL){
			len_ptr = strlen(ptr);
			if(len_ptr > max_rango_barco){
				printf("Error: longitud de barco fuera del rango permitido (debe ser solo un numero de 1 digito) en linea %d",*i+1);
				exit(0);
			}

			long_barco = atoi( ptr );
			itoa(long_barco, buffer, 10);

			if(strcmp(ptr,buffer)){
				printf("Error: longitud del barco mal formada en la linea %d",*i+1);
				exit(0);
			}

			if(long_barco < min_long_barco){
				printf("Error: la longitud del barco es menor al minimo permitido en la linea %d",*i+1);
				exit(0);
			}
			if(long_barco > max_long_barco){
				printf("Error: la longitud del barco es mayor al maximo permitido en la linea %d",*i+1);
				exit(0);
			}

			if(( ptr=strtok( NULL, "-" )) != NULL){
				len_ptr = strlen(ptr);

				if(len_ptr > max_rango_barco){
					printf("Error: direccion del barco fuera del rango permitido (debe ser solo un caracter V o H) en linea %d",*i+1);
					exit(0);
				}
				ptr[0] = toupper(ptr[0]);
				if((strcmp(ptr,"V")) && (strcmp(ptr,"H"))){
					printf("Error: la posicion del barco definida en la linea %d es inexistente",*i+1);
					exit(0);
				}

				if(!(strcmp(ptr,"V"))){
					direccion = 'V';
				}else{
					direccion = 'H';
				}
				if(( ptr=strtok( NULL, "-" )) != NULL){
					iii=1;
					strcpy(aux_ptr,ptr);

					if((long_barco >= iii) && ((sub_ptr=strtok( ptr, ";" )) != NULL)){
						tratarCoordenadas(&sub_ptr,&i,&iii,&long_barco,&len_coord,ar,direccion,&aux_coordX,&aux_coordY,tablero,cantb,gano,jug);
						iii++;
					}else{
						printf("Error: deben haber almenos 2 coordenadas");
						exit(0);
					}

					len = strlen(aux_ptr);
					ii = 0;
					count = 0;
					while(ii < len){
						if(ii <= len_coord){
							count++;
						}else{
							aux_ptr[ii-count] = aux_ptr[ii];
						}
						ii++;
					}
					aux_ptr[ii-count] = '\0';
					strcpy(ptr,aux_ptr);
					while((sub_ptr=strtok( ptr, ";" )) != NULL){
						if((long_barco < iii)){
							printf("Error: hay mas coordenadas que longitud del barco en la linea %d",*i+1);
							exit(0);
						}

						tratarCoordenadas(&sub_ptr,&i,&iii,&long_barco,&len_coord,ar,direccion,&aux_coordX,&aux_coordY,tablero,cantb,gano,jug);

						if(iii >= 3){
							len_coord = len_coord + 1;
						}

						len = strlen(aux_ptr);
						ii = 0;
						count = 0;
						while(ii < len){
							if(ii < len_coord){
								count++;
							}else{
								aux_ptr[ii-count] = aux_ptr[ii];
							}
						ii++;
						}
						aux_ptr[ii-count] = '\0';
						strcpy(ptr,aux_ptr);

						iii++;
					}
					if((long_barco > iii-1)){
							printf("Error: hay menos coordenadas que longitud del barco en la linea %d",*i+1);
							exit(0);
					}
					len = strlen(aux_caracteres);
					if(aux_caracteres[len-1] != '.'){
						printf("Error: falta punto final en linea %d",*i+1);
						exit(0);
					}
				}else{
					printf("Error: faltan todas las coordenadas del barco en la linea %d",*i+1);
					exit(0);
				}
			}else{
				printf("Error: falta posicion del barco en la linea %d",*i+1);
				exit(0);
			}
		}else{
			printf("Error: no posee ningun atributo definido del barco en la linea %d",*i+1);
		}
		ii=0;
		count=0;
		is_end = 0;
		while(ii<barcosdisponiblescant){
			if((long_barco==barcosdisponibles[ii]) && (!(is_end))){
				is_end = 1;
				count++;
			}else{
				barcosdisponibles[ii-count] = barcosdisponibles[ii];
			}
			ii++;
		}
		barcosdisponibles[ii-count] = barcosdisponibles[ii];
		barcosdisponiblescant = ii - count;

		if((barcosdisponiblescant > 0) && (!(is_end))){
			printf("Error: no puedo haber mas barcos de longitud %d en la linea %d", long_barco,*i+1);
			exit(0);
		}

		*i=*i+1;
		barcos++;
	}
	if(barcos == 1){
		printf("Error: el jugador %s no tiene barcos", nombre_p );
		exit(0);
	}
	if(barcos <= cantidadbarcos){
		printf("Error: el jugador %s tiene menos de %d barcos", nombre_p ,cantidadbarcos);
		exit(0);
	}

}
//Pos{Valida y recorre el archivo de Barcos}//
/*------------------------------------------------------------------------------------*/

//Pre{Los aux_coord en 0}//
void tratarCoordenadas(char **sub_ptr,int **i, int *iii, int *long_barco, int *len_coord,char ar[maxx+1][maxy+1],char direccion, int *aux_coordX, int *aux_coordY,char tablero[maxx+1][maxy+1],int *cantb,int *gano,int jug){
	int len_ptr;
	int coordX;
	int coordY;
	int ii;
	int count;
	int is_end;
	int count_comas;
	char *coord_ptr;
	char buffer[4];

	*len_coord = strlen(*sub_ptr);

	if(strchr(*sub_ptr, ',') == NULL){
		printf("Error: la coordenada (aparicion numero %d) de la linea %d no posee coma",*iii, **i+1);
		exit(0);
	}
	if(*len_coord > max_coordenada){
		printf("Error: la coordenada (aparicion numero %d) de la linea %d se va fuera del rango maximo de longitud de coordenada",*iii, **i+1);
		exit(0);
	}
	if(*len_coord < min_coordenada){
		printf("Error: la coordenada (aparicion numero %d) de la linea %d no cumple con el rango minimo de longitud de coordenada",*iii, **i+1);
		exit(0);
	}
	coord_ptr = strtok( *sub_ptr , "," );

	if(coord_ptr == NULL){
		printf("Error: falta coordenada X (aparicion numero %d) en la linea %d",*iii, **i+1);
		exit(0);
	}
	coordX = atoi( coord_ptr );
	itoa( coordX, buffer, 10);
	len_ptr = strlen( coord_ptr );

	ii = 0;
	count = 0;
	is_end=0;
	while(ii < len_ptr){
		if(coord_ptr[ii] == '0' && !(is_end) && (ii < len_ptr-1)){
			count++;
		}else{
			if(coord_ptr[ii] == ' '){
				count++;
			}else{
				coord_ptr[ii-count] = coord_ptr[ii];
				is_end=1;
			}
		}
		ii++;
	}

	coord_ptr[ii-count] = '\0';

	if(!(strcmp(coord_ptr,"0"))){
		printf("Error: la coordenada X (de la coordenada numero %d) de numeracion 0 no es posible en la linea %d",*iii, **i+1);
		exit(0);
	}

	if(!strcmp(coord_ptr, "")){
		printf("Error: falta coordenada X (de la coordenada numero %d) en la linea %d",*iii, **i+1);
		exit(0);
	}
	if(strcmp( coord_ptr, buffer)){
		printf("Error: la coordenada X (de la coordenada numero %d) de la linea %d esta mal formada",*iii, **i+1);
		exit(0);
	}

	if(coordX > maxx){
		printf("Error: la coordenada X (de la coordenada numero %d) de la linea %d supera las dimensiones del tablero",*iii, **i+1);
		exit(0);
	}
	if(coordX < 0){
		printf("Error: la coordenada X (de la coordenada numero %d) de la linea %d es negativo",*iii, **i+1);
		exit(0);
	}
	count_comas = 0;
	while( ( coord_ptr=strtok( NULL, "," )) != NULL ){    // Posteriores llamadas
		count_comas++;
		if(count_comas > 1){
			printf("Error: hay mas de 1 coma en la coordenada (de la coordenada numero %d) de la linea %d",*iii, **i+1);
			exit(0);
		}
		coordY = atoi( coord_ptr );
		itoa( coordY, buffer, 10);

		len_ptr = strlen( coord_ptr );
		ii = 0;
		count = 0;
		is_end=0;
		while(ii < len_ptr){
			if(coord_ptr[ii] == '0' && !(is_end) && (ii < len_ptr-1)){
				count++;
			}else{
				if(coord_ptr[ii] == ' '){
					count++;
				}else{
					coord_ptr[ii-count] = coord_ptr[ii];
					is_end=1;
				}
			}
			ii++;
		}
		coord_ptr[ii-count] = '\0';

		if(!(strcmp(coord_ptr,"0"))){
			printf("Error: la coordenada Y (de la coordenada numero %d) de numeracion 0 no es posible en la linea %d",*iii, **i+1);
			exit(0);
		}
		if(!strcmp(coord_ptr, "")){
			printf("Error: falta coordenada Y (de la coordenada numero %d) en la linea %d",*iii, **i+1);
			exit(0);
		}
		if((strchr(coord_ptr,'.') != NULL) && (*long_barco == *iii)){
			coord_ptr[len_ptr-1]='\0';
		}
		if(strcmp( coord_ptr, buffer)){
			printf("Error: la coordenada Y (de la coordenada numero %d) de la linea %d esta mal formada",*iii, **i+1);
			exit(0);
		}

		if(coordY > maxy){
			printf("Error: la coordenada Y (de la coordenada numero %d) de la linea %d supera las dimensiones del tablero",*iii, **i+1);
			exit(0);
		}
		if(coordY < 0){
			printf("Error: la coordenada Y (de la coordenada numero %d) de la linea %d es negativo",*iii, **i+1);
			exit(0);
		}

	}
	if((direccion == 'V') && (*iii > 1) && ((*aux_coordX!=coordX-1 && *aux_coordX!=coordX+1) && (*aux_coordY!=coordY))){
		printf("Error: la coordenada X (de la coordenada numero %d) debe ser continua y la coordenada Y no debe variar ya que la direccion es vertical en la linea %d",*iii, **i+1);
		exit(0);
	}
	if((direccion == 'V') && (*iii > 1) && ((*aux_coordX!=coordX-1 && *aux_coordX!=coordX+1) && (*aux_coordY==coordY))){
		printf("Error: la coordenada X (de la coordenada numero %d) debe ser continua en la linea %d",*iii, **i+1);
		exit(0);
	}
	if((direccion == 'V') && (*iii > 1) && ((*aux_coordX==coordX-1 || *aux_coordX==coordX+1) && (*aux_coordY!=coordY))){
		printf("Error: la coordenada Y (de la coordenada numero %d) no debe variar ya que la direccion es vertical en la linea %d",*iii, **i+1);
		exit(0);
	}

	if((direccion == 'H') && (*iii > 1) && ((*aux_coordY!=coordY-1 && *aux_coordY!=coordY+1) && (*aux_coordX!=coordX))){
		printf("Error: la coordenada Y (de la coordenada numero %d) debe ser continua y la coordenada X no debe variar ya que la direccion es horizontal en la linea %d",*iii, **i+1);
		exit(0);
	}
	if((direccion == 'H') && (*iii > 1) && ((*aux_coordY!=coordY-1 && *aux_coordY!=coordY+1) && (*aux_coordX==coordX))){
		printf("Error: la coordenada Y (de la coordenada numero %d) debe ser continua en la linea %d",*iii, **i+1);
		exit(0);
	}
	if((direccion == 'H') && (*iii > 1) && ((*aux_coordY==coordY-1 || *aux_coordY==coordY+1) && (*aux_coordX!=coordX))){
		printf("Error: la coordenada X (de la coordenada numero %d) no debe variar ya que la direccion es horizontal en la linea %d",*iii, **i+1);
		exit(0);
	}

	if(ar[coordX][coordY]=='2' || ar[coordX][coordY]=='3' || ar[coordX][coordY]=='4' || ar[coordX][coordY]=='5' || ar[coordX][coordY]=='X'){
		printf("Error, se posiciono un barco sobre otro (en la coordenada numero %d) de la linea %d",*iii,**i+1);
		exit(0);
	}else{
		if( (direccion == 'V') && (coordX-1>0) && (*aux_coordX!=coordX-1) && (ar[coordX-1][coordY]=='2' || ar[coordX-1][coordY]=='3' || ar[coordX-1][coordY]=='4' || ar[coordX-1][coordY]=='5' || ar[coordX-1][coordY]=='X')){
			printf("Error, la coordenada %d,%d  esta muy pegada a la coordenada %d,%d (en la coordenada numero %d) de la linea %d",coordX,coordY,coordX-1,coordY,*iii,**i+1);
			exit(0);
		}else{
			if( (direccion == 'V') && (coordX+1<maxx+1) && (*aux_coordX!=coordX+1) && (ar[coordX+1][coordY]=='2' || ar[coordX+1][coordY]=='3' || ar[coordX+1][coordY]=='4' || ar[coordX+1][coordY]=='5' || ar[coordX+1][coordY]=='X')){
				printf("Error, la coodenada %d,%d  esta muy pegada a la coordenada %d,%d (en la coordenada numero %d) de la linea %d",coordX,coordY,coordX+1,coordY,*iii,**i+1);
				exit(0);
			}else{
				if( (direccion == 'H') && (coordY-1>0) && (*aux_coordY!=coordY-1) && (ar[coordX][coordY-1]=='2' || ar[coordX][coordY-1]=='3' || ar[coordX][coordY-1]=='4' || ar[coordX][coordY-1]=='5' || ar[coordX][coordY-1]=='X')){
					printf("Error, la coodenada %d,%d  esta muy pegada a la coordenada %d,%d (en la coordenada numero %d) de la linea %d",coordX,coordY,coordX,coordY-1,*iii,**i+1);
					exit(0);
				}else{
					if( (direccion == 'H') && (coordY+1<maxy+1) && (*aux_coordY!=coordX+1) && (ar[coordX][coordY+1]=='2' || ar[coordX][coordY+1]=='3' || ar[coordX][coordY+1]=='4' || ar[coordX][coordY+1]=='5' || ar[coordX][coordY+1]=='X')){
						printf("Error, la coodenada %d,%d esta muy pegada a la coordenada %d,%d (en la coordenada numero %d) de la linea %d",coordX,coordY,coordX,coordY+1,*iii,**i+1);
						exit(0);
					}
				}
			}
		}
	}


	if((*iii == 1) && (direccion == 'V') && (coordY-1>0) && (ar[coordX][coordY-1]=='2' || ar[coordX][coordY-1]=='3' || ar[coordX][coordY-1]=='4' || ar[coordX][coordY-1]=='5' || ar[coordX][coordY-1]=='X')){
		printf("Error: hay barcos en la perisferias de la coordenada %d,%d (en la coordenada numero %d) de la linea %d",coordX,coordY,*iii,**i+1);
		exit(0);
	}
	if((*iii == 1) && (direccion == 'V') && (coordY+1<maxy+1) && (ar[coordX][coordY+1]=='2' || ar[coordX][coordY+1]=='3' || ar[coordX][coordY+1]=='4' || ar[coordX][coordY+1]=='5' || ar[coordX][coordY+1]=='X')){
		printf("Error: hay barcos en la perisferias de la coordenada %d,%d (en la coordenada numero %d) de la linea %d",coordX,coordY,*iii,**i+1);
		exit(0);
	}
	if((*iii == 1) && (direccion == 'H') && (coordX-1>0) && (ar[coordX-1][coordY]=='2' || ar[coordX-1][coordY]=='3' || ar[coordX-1][coordY]=='4' || ar[coordX-1][coordY]=='5' || ar[coordX-1][coordY]=='X')){
		printf("Error: hay barcos en la perisferias de la coordenada %d,%d (en la coordenada numero %d) de la linea %d",coordX,coordY,*iii,**i+1);
		exit(0);
	}
	if((*iii == 1) && (direccion == 'H') && (coordX+1<maxx+1) && (ar[coordX+1][coordY]=='2' || ar[coordX+1][coordY]=='3' || ar[coordX+1][coordY]=='4' || ar[coordX+1][coordY]=='5' || ar[coordX+1][coordY]=='X')){
		printf("Error: hay barcos en la perisferias de la coordenada %d,%d (en la coordenada numero %d) de la linea %d",coordX,coordY,*iii,**i+1);
		exit(0);
	}

	if((*iii == *long_barco) && (direccion == 'V') && (coordY-1>0) && ((*aux_coordX!=coordX) && (*aux_coordY!=coordY-1)) && (ar[coordX][coordY-1]=='2' || ar[coordX][coordY-1]=='3' || ar[coordX][coordY-1]=='4' || ar[coordX][coordY-1]=='5' || ar[coordX][coordY-1]=='X')){
		printf("Error: hay barcos en la perisferias de la coordenada %d,%d (en la coordenada numero %d) de la linea %d",coordX,coordY,*iii,**i+1);
		exit(0);
	}
	if((*iii == *long_barco) && (direccion == 'V') && (coordY+1<maxy+1) && ((*aux_coordX!=coordX) && (*aux_coordY!=coordY+1)) && (ar[coordX][coordY+1]=='2' || ar[coordX][coordY+1]=='3' || ar[coordX][coordY+1]=='4' || ar[coordX][coordY+1]=='5' || ar[coordX][coordY+1]=='X')){
		printf("Error: hay barcos en la perisferias de la coordenada %d,%d (en la coordenada numero %d) de la linea %d",coordX,coordY,*iii,**i+1);
		exit(0);
	}
	if((*iii == *long_barco) && (direccion == 'H') && (coordX-1>0) && ((*aux_coordX-1!=coordX) && (*aux_coordY!=coordY)) && (ar[coordX-1][coordY]=='2' || ar[coordX-1][coordY]=='3' || ar[coordX-1][coordY]=='4' || ar[coordX-1][coordY]=='5' || ar[coordX-1][coordY]=='X')){
		printf("Error: hay barcos en la perisferias de la coordenada %d,%d (en la coordenada numero %d) de la linea %d",coordX,coordY,*iii,**i+1);
		exit(0);
	}
	if((*iii == *long_barco) && (direccion == 'H') && (coordX+1<maxx+1) && ((*aux_coordX+1!=coordX) && (*aux_coordY!=coordY)) && (ar[coordX+1][coordY]=='2' || ar[coordX+1][coordY]=='3' || ar[coordX+1][coordY]=='4' || ar[coordX+1][coordY]=='5' || ar[coordX+1][coordY]=='X')){
		printf("Error: hay barcos en la perisferias de la coordenada %d,%d (en la coordenada numero %d) de la linea %d",coordX,coordY,*iii,**i+1);
		exit(0);
	}

	itoa(*long_barco,buffer,10);
	if(ar[coordX][coordY]=='*'){
		verif_bm(ar,tablero,cantb,gano,jug,coordX,coordY,*long_barco);
	}else{
		ar[coordX][coordY] = buffer[0];
	}
	*aux_coordX = coordX;
	*aux_coordY = coordY;
}
//Pos{Valida y posiciona los barcos}//
/*--------------------------------------------------------------------------------------------------*/

//Pre{i y j validos,i<=maxx y j<+maxy en minas '*' y en barcos '2,3,4,5'}//
void verif_bm(char barcos[maxx+1][maxy+1],char tablero[maxx+1][maxy+1],int *cantb,int *gano,int jug,int X,int Y,int tambarco)
{

	barcos[X][Y]='X';
	tablero[X][Y]='X';
	printf("Puso un barco sobre una mina. Barco tocado\n");
	Enter();
	if(barco_hundido(barcos,X,Y,tambarco)=='V'){
		printf("Barco hundido\n");
		*cantb=*cantb-1;
		Enter();
		if(*cantb==0){
			if(*gano==0){
				*gano=jug;
			}else{
				*gano=3;
			}
		}
	}
}
//Pos{Hace explotar un barco si al cargarlo esta sobre una mina}//
/*------------------------------------------------------------------------*/

//Pre{...}//
void clrbuf()
{
char a;
while (kbhit() != 0){
			a=getch();
		}
}
//Pos{Borra el buffer del getch}//
/*-------------------------------*/


//Pre{...}//
void mostrartablero(char ar[maxx+1][maxy+1])
{
int i,j;
printf("\n");
printf("%c",ar[0][0]);
printf(" | ");
for(i=1;i<=maxx;i++){
	printf("%c",ar[i][0]);
	printf("  ");
}
printf("\n");
printf("----------------------------------------\n");
for(i=1;i<=maxx;i++){
	for(j=0;j<=maxy;j++){
		if(j==0){
			printf("%c",ar[i][j]);
			printf(" | ");
		}else{
			if(ar[i][j]=='2' || ar[i][j]=='3' || ar[i][j]=='4' || ar[i][j]=='5'){
				printf("B");
				printf("  ");
			}else{
				if(ar[i][j]=='*'){
					printf("~");
					printf("  ");
				}else{
					printf("%c",ar[i][j]);
					printf("  ");
				}
			}
		}
	}
	printf("\n");
}
}
//Pos{Muestra el tablero en la pantalla}//
/*------------------------------------------*/


//Pre{...}//
int Modo_Juego()
{
int OPC;
do
  {
	printf("Ingrese el modo de juego para la batalla naval:\n1)Para jugar contra la CPU\n2)Para jugar contra un humano\n");
	scanf("%d",&OPC);
  }
  while(OPC!=1 && OPC!=2);
return(OPC);
}
//Pos{Ingresa y valida las opciones del menu}//
/*---------------------------------------------------------------------------------------------------------------*/

//Pre{Matriz validada con caracteres especificos}//
void jugar(char jugador2[maxx+1][maxy+1],char tablero1[maxx+1][maxy+1],int *cantb,int *gano,int jug)
{
int X=0;
int Y=0;

Jugar_coordenadas(&X,&Y,tablero1);
printf("%d,%d\n",X,Y);
proceso(jugador2,tablero1,&*cantb,&*gano,jug,X,Y);
}
//Pos{Procedimiento del juego}//
/*------------------------------------------------------------------------------------------------------------------*/


//Pre{}//
void Jugar_coordenadas(int *X,int *Y,char tablero[maxx+1][maxy+1])
{
char salir;
printf("Ingrese las coordenadas a tirar X,Y\n0,0 para salir del programa...\n\n");
do{
	scanf("%d",&*X);
	fflush(stdin);
	scanf("%d",&*Y);
	fflush(stdin);
	clrscr();
	if(*X<1 || *X>maxx){
		printf("Error al ingresar coordenada X, ingese las cordenadas nuevamente\n");
	}
	if(*Y<1 || *Y>maxy){
		printf("Error al ingresar coordenada Y, ingese las cordenadas nuevamente\n");
	}
	if(tablero[*X][*Y]=='X' || tablero[*X][*Y]=='O'){
		printf("Ya se jugo en esa posicion, ingrese nuevamente\n");
	}
	if(*X==0 && *Y==0){
		clrscr();
		salir=Seguro_Salir();
		if(salir=='S' || salir=='s'){
			exit(0);
		}
		printf("Vuelva a ingresar las coordenadas a tirar X,Y\nRecuerde, 0,0 para salir del programa...\n\n");
	}
}while(*X<1 || *X>maxx || *Y<1 || *Y>maxy || tablero[*X][*Y]=='X' || tablero[*X][*Y]=='O');
}
//Pos{Valida las coordenadas que ingresa un jugador}//
/*------------------------------------------------------------------------------------*/


//Pre{Coordenadas validas}//
void proceso(char jugador2[maxx+1][maxy+1],char tablero1[maxx+1][maxy+1],int *cantb,int *gano,int jug,int X,int Y)
{
int i,j;
int tambarco;
if(jugador2[X][Y]=='*'){
	printf("Ha tocado una mina\n");
	jugador2[X][Y]='O';
	tablero1[X][Y]='O';
	Enter();
	for(i=X-movminas;i<=X+movminas;i++){
		for(j=Y-movminas;j<=Y+movminas;j++){
			if(i>0 && i<=maxx && j>0 && j<=maxy){
				proceso(jugador2,tablero1,&*cantb,&*gano,jug,i,j);
			}
		}
	}
}else{
	if(jugador2[X][Y]!='O' && jugador2[X][Y]!='X'){
		if(jugador2[X][Y]=='2' || jugador2[X][Y]=='3' || jugador2[X][Y]=='4' || jugador2[X][Y]=='5'){
			printf("Barco tocado\n");
			tambarco=jugador2[X][Y]-'0'; // atoi es solo para string
			jugador2[X][Y]='X';
			tablero1[X][Y]='X';
			Enter();
			if(barco_hundido(jugador2,X,Y,tambarco)=='V'){
				printf("Barco hundido\n");
				*cantb=*cantb-1;
				Enter();
				if(*cantb==0){
					*gano=jug;
				}
			}
		}else{
			if(jugador2[X][Y]=='~'){
				printf("Oooooleee, pego en el agua\n");
				jugador2[X][Y]='O';
				tablero1[X][Y]='O';
				Enter();
			}else{
				printf("Error en la carga de archivos");
				exit(0);
			}
		}
	}

}
}
//Pos{Realiza el proceso de comparacion para ejecutarse el juego}//
/*------------------------------------------------------------------*/


//Pre{No haya barcos pegados deben estar separadas por 1 espacio minimo}//
char barco_hundido(char barcosj2[maxx+1][maxy+1],int X,int Y,int tambarco)
{
char hundido='F';
int contX=1;
int i=0;
int aux=X;
i=aux-1;
while(i>0 && i>X-tambarco && barcosj2[i][Y]=='X'){
	contX=contX+1;
	i=i-1;
}
i=aux+1;
while(i<=maxx && i<X+tambarco && barcosj2[i][Y]=='X'){
	contX=contX+1;
	i=i+1;
}
aux=Y;
i=aux-1;
while(i>0 && i>Y-tambarco && barcosj2[X][i]=='X'){
	contX=contX+1;
	i=i-1;
}
i=aux+1;
while(i<=maxy && i<X+tambarco && barcosj2[X][i]=='X'){
	contX=contX+1;
	i=i+1;
}
if(contX==tambarco){
	hundido='V';
}
return(hundido);
}
//Pos{Devuelve 'V' cuando un barco fue hundido}//
/*----------------------------------------------------------*/


//Pre{Matriz validada con caracteres especificos}//
void jugar_cpu(char jugador2[maxx+1][maxy+1],char tablero1[maxx+1][maxy+1],int *cantb,int *gano,int jug)
{
int X=0;
int Y=0;

Coordenadas_cpu(&X,&Y,tablero1);
printf("%d,%d\n",X,Y);
proceso(jugador2,tablero1,&*cantb,&*gano,jug,X,Y);
}
//Pos{Proceso para que juegue la CPU}//
/*-----------------------------------------------------------------------*/


//Pre{...}//
void Coordenadas_cpu(int *X,int *Y,char tablero[maxx+1][maxy+1])
{
printf("Ingrese las coordenadas a tirar X,Y\n");
do{
	*X=random(maxx)+1;
	fflush(stdin);
	*Y=random(maxy)+1;
	fflush(stdin);
}while(*X<1 || *X>maxx || *Y<1 || *Y>maxy || tablero[*X][*Y]=='X' || tablero[*X][*Y]=='O');
}
//Pos{Ingresa las coordenas de la CPU}//
/*---------------------------------------------------------------------------------------*/


//Pre{...}//
char Seguro_Salir()
{
char X;
printf("\n----------------------------------------------------------------------------");
printf("\nEsta seguro que desea salir de programa?: \n S = Si       N = No \n");
fflush(stdin);
clrbuf();
do
  {
	scanf("%c",&X);
  }
while (X!='S' && X!='s' && X!='N' && X!='n');
return(X);
}
//Pos{Pregunta si esta seguro que desea salir}//
/*----------------------------------------------------------------------------*/

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
void Ganador(int gano,int jug,char name1[85],char name2[85])
{
if(gano==1){
	printf("                            FELICITACIONES            \n");
	printf("                         El Jugador 1: %s Gana                \n",strupr(name1));
	Enter();
}else{
	if(gano==2 && jug==2){
		printf("                            FELICITACIONES            \n");
		printf("                         El Jugador 2: %s Gana                \n",strupr(name2));
		Enter();
	}else{
		if(gano==2 && jug==1){
			printf("                            GAME OVER            \n");
			printf("                          LA CPU: %s Gana                \n",strupr(name2));
			Enter();
		}else{
			if(gano==3){
				printf("                              EMPATE TECNICO                      \n");
				Enter();
			}else{
				printf("Error logico");
			}
		}
	}
}
}
//Pos{Muestra el ganador segun el jugador y el ganador}//
/*-------------------------------------------------------*/


//Pre{...}//
void mostrar_tableros(char ar[maxx+1][maxy+1],char ar2[maxx+1][maxy+1],char nombre[40])
{
clrscr();
printf("Barcos %s:\n",strupr(nombre));
mostrartablero(ar);
Enter();
clrscr();
printf("Disparos %s:\n",strupr(nombre));
mostrartablero(ar2);
Enter();
clrscr();
}
//Pos{Muestra los tableros del jugador}//
/*-------------------------------------------------------*/
