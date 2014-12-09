#ifndef LISTAINDEX_H
#define LISTAINDEX_H
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "tdatoindex.h"


//typedef struct nodoe puntero

typedef struct nodo_inx
{
	Tdatoindex info;
	nodo_inx *sig;
	nodo_inx *ant;
} nodo_inx;

typedef struct listap
{
	nodo_inx *cab;
	nodo_inx *actual;
} tlistap;

typedef tlistap tlista;



void crearnodo_inx(nodo_inx **nue,Tdatoindex x)
{
	*nue = (nodo_inx*) malloc(sizeof(nodo_inx));
	(*nue)->sig = NULL;
	(*nue)->ant = NULL;
	(*nue)->info = x;
}

/* Crea la Lista Circular Doblemente Encadenada */
void lcrear_inx (tlista *l)
{
	l->cab = NULL;
}

/* Verifica si la lista se encuentra vacía */
int lvacia_inx (tlista *l)
{
	return (l->cab == NULL);
}

/* Verifica si la lista se encuentra llena */
int lllena_inx (tlista *l)
{
	return (0);
}

/* Se posiciona al principio de la lista */
void lppio_inx (tlista *l)
{
	l->actual = l->cab;
}

/* Se posiciona al ultimo de la lista */
void lult_inx(tlista *l)
{
	l->actual = l->cab->ant;
}

/* Se posiciona en el siguiente item de la lista */
void lsig_inx(tlista *l)
{
	l->actual = l->actual->sig;
}

/* Se posiciona en el item anterior de la lista */
void lant_inx(tlista *l)
{
	l->actual = l->actual->ant;
}

/* Se posiciona en el último item de la lista */
int lfin_inx(tlista *l) {
	return (l->actual == l->cab);
}

/* Muestra la información del item en la posición solicitada */
void linfo_inx (tlista *l,Tdatoindex *x)
{
	*x=(l->actual->info);
}

/* Modifica la información del item en la posición solicitada */
void lmodificar_inx (tlista *l,Tdatoindex aux)
{
 l->actual->info=aux;

}

/* Inserta un elemento al principio de la lista */
void linsertarppio_inx(tlista *l, Tdatoindex x)
{
	nodo_inx *nue;
	crearnodo_inx(&nue,x);
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
void linsertarfin_inx(tlista*l, Tdatoindex x)
{
	nodo_inx *nue,*aux;
	crearnodo_inx(&nue,x);
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
void linsertarorden_inx(tlista *l, Tdatoindex x, char torden){
nodo_inx *nue;
nodo_inx *aux;

crearnodo_inx(&nue,x);
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
void lborrarppio_inx(tlista *l)
{
	 nodo_inx *aux;
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


/* Elimina el último elemento de la lista */
void lborrarfin_inx(tlista *l)
{
nodo_inx *aux;

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

/* Elimina el elemento de la lista en la posición solicitada */
void lborraractual_inx(tlista *l)
{
nodo_inx *aux,*t;

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
void lbuscar_inx(tlista *l,Tclaveindex clave,int *existe){
nodo_inx *aux;
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