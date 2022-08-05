#ifndef funcoesdomino2_h
#define	funcoesdomino2_h
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
//PEDRA
typedef struct pedras{
	int numcima, numbaixo;
} tp_pedra;

//LISTASE
typedef tp_pedra tp_item;

typedef struct tp_noLS{
	tp_item info;
	struct tp_noLS *prox;
}tp_listase;

tp_listase *inicializa_listase(){
	return NULL;
}

int tamanho_listase(tp_listase *lista){
	int cont=0;
	tp_listase *atu;
	atu=lista;
	while(atu!=NULL){
		cont++;
		atu=atu->prox;
	}
	return cont;
}

int listase_vazia(tp_listase *lista){
	if(lista==NULL) return 1;
	return 0;
}

tp_listase * aloca_listase(){
	tp_listase *novo_no;
	novo_no=(tp_listase*) malloc(sizeof(tp_listase));
	return novo_no;
}

int insere_listase_no_fim(tp_listase **l, tp_item e){
	tp_listase *novo_no, *atu;
	novo_no=aloca_listase();
	
	if(novo_no == NULL) return 0;
	novo_no->info = e;
	novo_no->prox = NULL;
	if(listase_vazia(*l)){
		*l = novo_no;
	}else{	
		atu=*l;
		while(atu->prox!=NULL){
			atu=atu->prox;
		}
		atu->prox=novo_no;
	}
	return 1;
}

tp_pedra remove_item_listase(tp_listase **lista, int e){
	tp_pedra retorne;
	int cont = 1;
	tp_listase *ant, *atu;
	atu=*lista;
	ant=NULL;
	
	while( (atu!=NULL) && (cont <= e) ){
		ant=atu;
		atu=atu->prox;
		cont++;
	}
	
	if(ant==NULL){
		*lista=atu->prox;
	}
	else{
		ant->prox = atu->prox;
	}
	retorne = atu->info;

	free(atu);
	atu = NULL;
	return retorne;
}

tp_pedra acha_pedra(tp_listase **lista, int e){
	tp_pedra retorne;
	int cont = 1;
	tp_listase *ant, *atu;
	atu=*lista;
	ant=NULL;
	
	while( (atu!=NULL) && (cont != e) ){
		ant=atu;
		atu=atu->prox;
		cont++;
	}
	retorne = atu->info;
	
	return retorne;
}

int tira_posicao(tp_listase **lista, int e){
	tp_pedra retorne;
	int cont = 1;
	tp_listase *ant, *atu;
	atu=*lista;
	ant=NULL;
	
	while(cont != e){
		ant = atu;
		atu=atu->prox;
		cont++;
	}

	if(tamanho_listase(*lista) == 0){
		return 0; 
	}
	
	if((e == 1)){
		printf("Pedra retirada : [%d|%d]\n", atu->info.numcima, atu->info.numbaixo);
		*lista = atu->prox;
		
	}else{
		printf("Pedra retirada : [%d|%d]\n", atu->info.numcima, atu->info.numbaixo);

		ant->prox = atu->prox;	
	}
	return 1;
}

void imprime_listase(tp_listase *lista){	
	tp_listase *atu;
	int cont;
	atu = lista;
	cont = 1;
	while(atu != NULL){
		printf("[%d|%d] ", atu->info.numcima, atu->info.numbaixo);
		printf("%d\n", cont);
		cont++;
		atu = atu->prox;
	}
}

int remove_item_listase2(tp_listase **lista, tp_pedra *e){
	tp_listase *atu, *ant;
	ant = NULL;
	atu = *lista;
	while(atu->prox != NULL){
    	ant = atu;
    	atu = atu->prox;
	}
	*e = atu->info;
  
	if(ant != NULL){
		ant->prox = NULL;
  		free(atu);
  		atu = NULL;
  		return 1;	
  	}else{
  		*lista = NULL;
  	return 1;
  	}
}

//LISTADE
typedef tp_pedra tp_item;

typedef struct tp_no_aux{
	struct tp_no_aux *ant;
	tp_item info;
	struct tp_no_aux *prox;
} tp_no;

typedef struct{
	tp_no *ini;
	tp_no *fim;
} tp_listad;

tp_listad *inicializa_listad(){
	tp_listad *lista=(tp_listad*) malloc(sizeof(tp_listad));
	lista->ini=NULL;
	lista->fim=NULL;
	return lista;
}

int lista_vazia(tp_listad *lista){
	if(lista->ini == NULL) return 1;
	return 0;
}

tp_no *aloca(){
	tp_no* pt;
	pt=(tp_no*) malloc(sizeof(tp_no));
	return pt;
}

int insere_listad_na_direita(tp_listad *lista, tp_item e){
	tp_no *novo;
	novo=aloca();
	if(!novo) return 0;
	novo->info=e;
	if ((lista->ini==NULL) && (lista->fim == NULL)){

		novo->prox=NULL;
		novo->ant=NULL;
		lista->ini=lista->fim=novo;
	}
	else{
		novo->prox=NULL;
		novo->ant=lista->fim;
		lista->fim->prox=novo;
		lista->fim=novo;
	}
	return 1;
}

int insere_listad_na_esquerda(tp_listad *lista, tp_pedra e){
	tp_no *novo, *atu;
	novo=aloca();
	if(!novo) return 0;
	novo->info = e;
	novo->prox = NULL;
	novo->ant = NULL;
	if(lista_vazia(lista)){
    	lista->ini = lista->fim = novo;
  	}
  	else{
    	novo->prox = lista->ini;
    	lista->ini = novo;
    	atu = lista->ini;
    	while(atu->prox!= NULL){
    		atu = atu->prox;
		}
	lista->fim= atu;
  	}
	return 1;
}

void imprime_listad(tp_listad *lista, int ordem){
	tp_no *atu;
	printf("    ");
	switch(ordem){
		case 1: atu=lista->ini;
			while( atu!=NULL ){
				printf("[%d|%d]  ", atu->info.numcima,atu->info.numbaixo);
				atu=atu->prox;
			}
			break;
		case 2: atu=lista->fim;
			while(atu!=NULL){
				printf("%d ", atu->info);
				atu=atu->ant;
			}
			break;
		default: printf("código inválido");
	}	
	printf("\n");
}

//PILHA
#define numpedras 28

typedef struct{
	int topo;
	tp_item item[numpedras];	
} tp_pilha;

void inicializa_pilha(tp_pilha *p){
	p->topo = -1;

}

int pilha_vazia(tp_pilha *p){
	if (p->topo == -1)
		return 1;
	return 0;	
}

int pilha_cheia(tp_pilha *p){
	if (p->topo == numpedras-1){
	return 1;
	} else {	
		return 0;
	}
}

int push(tp_pilha *p, tp_item e){
	if (pilha_cheia(p)==1) return 0;
	p->topo++;
	p->item[p->topo]=e;
	return 1;
}

int pop(tp_pilha *p, tp_item *e){
	if (pilha_vazia(p)) return 0;
	*e=p->item[p->topo];
	p->topo--;
	return 1;
}

int top(tp_pilha *p, tp_item *e){
	if (pilha_vazia(p)) return 0;
	*e = p->item[p->topo];
	return 1;
}

int altura_pilha(tp_pilha *p){
	return p->topo+1;
}


//Heap sort
using namespace std;
void heapificar(tp_pedra *arr, int n, int i){
	int largo = i;
	int e = 2 * i + 1;
	int d = 2 * i + 2;

	if (e < n && (arr[e].numbaixo + arr[e].numcima) > (arr[largo].numbaixo + arr[largo].numcima)){
		largo = e;
	}
	if (d < n && (arr[d].numbaixo + arr[d].numcima) > (arr[largo].numbaixo + arr[largo].numcima)){
		largo = d;
	}
	if (largo != i){
		swap(arr[i], arr[largo]);
		heapificar(arr, n, largo);
	}
}

void heapSort(tp_pedra *arr, int n){
	int i;
	for (i = n / 2 - 1; i >= 0; i--){
		heapificar(arr, n, i);
	}
	
	for (i = n - 1; i > 0; i--){
		swap(arr[0], arr[i]);
		heapificar(arr, i, 0);
	}
}

#endif
