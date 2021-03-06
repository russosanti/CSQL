#ifndef LISTA_H
#define LISTA_H
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "TDATOL.h"


//typedef struct nodoe puntero

typedef struct nodoe
{
	Tdato info;
	nodoe *sig;
	nodoe *ant;
} nodoe;

typedef struct listap
{
	nodoe *cab;
	nodoe *actual;
} tlistap;

typedef tlistap tlista;



void crearnodo(nodoe **nue,Tdato x)
{
	*nue = (nodoe*) malloc(sizeof(nodoe));
	(*nue)->sig = NULL;
	(*nue)->ant = NULL;
	(*nue)->info = x;
}

/* Crea la Lista Circular Doblemente Encadenada */
void lcrear (tlista *l)
{
	l->cab = NULL;
}

/* Verifica si la lista se encuentra vac�a */
int lvacia (tlista *l)
{
	return (l->cab == NULL);
}

/* Verifica si la lista se encuentra llena */
int lllena (tlista *l)
{
	return (0);
}

/* Se posiciona al principio de la lista */
void lppio (tlista *l)
{
	l->actual = l->cab;
}

/* Se posiciona al ultimo de la lista */
void lult(tlista *l)
{
	l->actual = l->cab->ant;
}

/* Se posiciona en el siguiente item de la lista */
void lsig(tlista *l)
{
	l->actual = l->actual->sig;
}

/* Se posiciona en el item anterior de la lista */
void lant(tlista *l)
{
	l->actual = l->actual->ant;
}

/* Se posiciona en el �ltimo item de la lista */
int lfin(tlista *l) {
	return (l->actual == l->cab);
}

/* Muestra la informaci�n del item en la posici�n solicitada */
void linfo (tlista *l,Tdato *x)
{
*x=(l->actual->info);
}

/* Modifica la informaci�n del item en la posici�n solicitada */
void lmodificar (tlista *l,Tdato aux)
{
 l->actual->info=aux;

}

/* Inserta un elemento al principio de la lista */
void linsertarppio(tlista *l, Tdato x)
{
	nodoe *nue;
	crearnodo(&nue,x);
	if(l->cab==NULL){
		l->cab=nue;
		l->cab->sig=l->cab;
		l->cab->ant=l->cab;
	}else{
		nue->sig=l->cab;
		nue->ant=l->cab->ant;
		l->cab->ant->sig=nue;
		l->cab->ant=nue;
		l->cab=nue;
	}
}


/* Inserta un elemento al final de la lista */
void linsertarfin(tlista*l, Tdato x)
{
	nodoe *nue,*aux;
	crearnodo(&nue,x);
	if (l->cab==NULL){
		l->cab=nue;
		l->cab->sig=l->cab;
		l->cab->ant=l->cab;
	}else{
		aux=l->cab->ant;
		nue->sig=l->cab;
		nue->ant=aux;
		aux->sig=nue;
		l->cab->ant=nue;
	}
}

/* Inserta un elemento en forma ordenada en la lista */
void linsertarorden(tlista *l, Tdato x, char torden){
nodoe *nue;
nodoe *aux;

crearnodo(&nue,x);
if(l->cab == NULL){
	l->cab = nue;
	l->cab->sig=l->cab;
	l->cab->ant=l->cab;
}else{
	if((torden=='a' && (l->cab->info.clave)>x.clave) || (torden=='d' && (l->cab->info.clave)<x.clave)) {
		aux=l->cab->ant;
		nue->sig=l->cab;
		nue->ant=aux;
		aux->sig=nue;
		l->cab->ant=nue;
		l->cab=nue;
	}else{
		aux=l->cab;
		while((aux->sig!=l->cab) && ( ((torden=='a') && (aux->sig->info.clave<x.clave)) || ((torden=='d') && (aux->sig->info.clave>x.clave)) )){
			aux=aux->sig;
		 }
		 nue->sig=aux->sig;
		 nue->ant=aux;
		 aux->sig->ant=nue;
		 aux->sig=nue;
	}
}
}

/* Elimina el primer elemento de la lista */
void lborrarppio(tlista *l)
{
	 nodoe *aux;
	 if(l->cab->sig==l->cab){
		aux=l->cab;
		l->cab=NULL;
	 }else{
		aux=l->cab;
		l->cab->ant->sig=l->cab->sig;
		l->cab->sig->ant=l->cab->ant;
		l->cab=l->cab->sig;
	 }
	 free(aux);
}


/* Elimina el �ltimo elemento de la lista */
void lborrarfin(tlista *l)
{
nodoe *aux;

if(l->cab->ant==l->cab){
	aux=l->cab;
	l->cab=NULL;
}else{
	aux=l->cab->ant;
	aux->ant->sig=l->cab;
	l->cab->ant=aux->ant;
}
free(aux);
}

/* Elimina el elemento de la lista en la posici�n solicitada */
void lborraractual(tlista *l)
{
nodoe *aux,*t;

aux=l->actual;
if(l->cab==l->actual){
	 if(l->cab->sig==l->cab){
		l->cab=NULL;
		l->actual=NULL;
	 }else{
		aux=l->cab;
		l->cab->ant->sig=l->cab->sig;
		l->cab->sig->ant=l->cab->ant;
		l->cab=l->cab->sig;
		l->actual=l->cab;
	 }
}else{
	aux=l->actual;
	aux->ant->sig=aux->sig;
	aux->sig->ant=aux->ant;
	l->actual=l->actual->sig;
}
free(aux);
}

/* Busca un elemento de la lista que coincide con el solicitado */
void lbuscar(tlista *l,Tclave clave,int *existe){
nodoe *aux;
*existe=0;
if(l->cab!=NULL){
	aux=l->cab;
	if(l->cab->sig==l->cab){
		if(l->cab->info.clave==clave){
			*existe=1;
		}
	}else{
		if(l->cab->info.clave < l->cab->sig->info.clave){
			while((aux->sig!=l->cab) && (clave > aux->info.clave)){
				aux=aux->sig;
			}
		}else{
			while((aux->sig!=l->cab) && (clave < aux->info.clave)){
				aux=aux->sig;
			}
		}
		*existe=(clave==aux->info.clave);
	}
}
if(*existe){
	l->actual=aux;
}
}

#endif