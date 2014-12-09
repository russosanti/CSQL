#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "TDATOE.H"

void main()
{
tlista l;
TdatoE num;
int existe;
int opc = 0;  	// Opción a seleccionar para testear
int busca;  	// Valor a buscar en la lista

lcrear(&l);

num.clave=-1;

clrscr();
while(opc != 99){
	printf("\n\t\t¿Que desea Hacer?\n\n");
	printf("\t\t1.Insertar valores en la lista\n");
	printf("\t\t2.Verificar si la lista está vacía o no\n");
	printf("\t\t3.Verificar si la lista está llena o no\n");
	printf("\t\t4.Mostrar los valores ingresados en forma ascendente\n");
	printf("\t\t5.Mostrar los valores ingresados en forma descendente\n");
	printf("\t\t6.Mostrar el primer elemento de la lista\n");
	printf("\t\t7.Mostrar el último elemento de la lista\n");
	printf("\t\t8.Ver el item siguiente en la lista\n");
	printf("\t\t9.Modificar el último item que se mostró\n");
	printf("\t\t10.Buscar un valor en la lista\n");
	printf("\n\t\t99.Salir\n");
	printf("\n\t\OPCIÓN: ");
	scanf("%d", &opc);
	printf("\n\n");
	switch(opc){
		case 1:
			while(!lllena(&l) && (num.clave!=0)){
				scanf("%d",&num.clave);

				/* inserta un elemento en el final de la Lista */
				if(num.clave==100){
					if(!lvacia(&l)){
						lppio(&l);
						linfo(&l,&num);
						printf("%d ",num.clave);
						lsig(&l);
						while(!lfin(&l)){
							linfo(&l,&num);
							printf("%d ",num.clave);
							lsig(&l);
						}
					}
				}else{
					if(num.clave != (-1)){
						linsertarorden(&l,num,'a');
					}else{
						//lbuscar(&l,4,&existe);
						//if(existe){
						if(!lvacia(&l)){
							lborrarfin(&l);
						}
						//	}else{
							//	printf("NO\n");
							//}
					
				}
			}
		}
		break;

		case 2:
			if(lvacia(&l)){
				printf("La lista se encuentra vacía.\n\n");
			}else{
				printf("La lista ya tiene elementos ingresados.\n\n");
			}break;

		case 3:
			if(lllena(&l))
				printf("La lista se encuentra llena.\n\n");
			else
				printf("Tiene espacio para colocar más elementos en la lista.\n\n");
			break;

		case 4:        // mostrar los valores en forma ascendente
			if(!lvacia(&l))
				{
				lppio(&l);
				linfo(&l,&num);
				printf("%d ",num.clave);
				lsig(&l);
				while(!lfin(&l))
					{
					linfo(&l,&num);
					printf("%d ",num.clave);
					lsig(&l);
					}
				}
			break;

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

		case 99:
			exit(1);

		default:
			printf("Error, el comando no es válido\n");
			break;
		}
		getch();
		clrscr();
	}

}
