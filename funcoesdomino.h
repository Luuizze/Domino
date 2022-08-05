#ifndef funcoesdomino_h
#define	funcoesdomino_h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "funcoesdomino2.h"

//Jogadores
typedef struct infojogador{
	int qntpedras;
	tp_listase *mao;
}tp_jogador;

char jogador[4][99];
void scanJogadores(int Nj){
	for(int i=0; i<Nj; i++){
		printf("Digite o nome do jogador %d: ", i+1);
		scanf(" %s", &jogador[i]);
	}
}
//Funcoes Jogo
#define startmao 7

void inverte_pedra(tp_pedra *pedra){
	int aux;
	aux = pedra->numbaixo;
	pedra->numbaixo = pedra->numcima;
	pedra->numcima = aux;
}

int encaixa(tp_pedra *jogada,tp_listad *mesa, char escolha){
	if(escolha == 'D' || escolha == 'd'){
		if(lista_vazia(mesa)){
			printf("A mesa está vazia.\n");
			return 1;	
		}else{
			printf("Este é o número presente na direita %d\n", mesa->fim->info.numbaixo);

			if(mesa->fim->info.numbaixo == jogada->numcima){
				printf("Este número encaixa.\n");
				return 1;	
			}else{
				
				if(mesa->fim->info.numbaixo == jogada->numbaixo){
					printf("É necessário inverter, invertendo...\n");
					inverte_pedra(jogada);
					return 1;
				}else{
					printf("Este número não encaixa.\n");
					return 0;
				}
			}
		}
	}else{
		
		if(lista_vazia(mesa)){
			printf("A mesa está vazia.\n");
			
			return 1;
			
		}else{
			printf("Este é o número presente na esquerda %d \n", mesa->ini->info.numcima);
			if(mesa->ini->info.numcima == jogada->numbaixo){
				return 1;
				printf("Este número encaixa.\n");
			}else{
				if(mesa->ini->info.numcima == jogada->numcima){
					printf("É necessário inverter, invertendo...\n");
					inverte_pedra(jogada);
					return 1;
				}else{
					printf("Este número não encaixa.\n");
					return 0;
				}
			}
		}
	}		
}

int insere(tp_pedra *jogada, tp_listad *mesa, char escolha){
	if(encaixa(jogada, mesa, escolha)){
		return 1;						
	}else{
		return 0;
	}
}

void construir_monte(tp_pilha *teste){
	tp_listase *pedras = inicializa_listase();
	tp_pedra array{numpedras}, aux;
	inicializa_pilha(teste);
	int i = numpedras, aleat;
	
	for(int cont = 0; cont <= 6; cont++){
		for(int cont2 = cont; cont2 <=6 ; cont2++ ){
			aux.numcima = cont;
			aux.numbaixo = cont2;
			insere_listase_no_fim(&pedras,aux);
		}
	}	
	while(i>0){
		aleat = rand()%i;
		aux = remove_item_listase(&pedras,aleat);
		push(teste, aux);
		i--;
	}
}

int Organiza_Pedras(tp_listase **mao){
	int i, tamanhomao;
	tp_pedra vetor[21];

	tamanhomao = tamanho_listase(*mao);
	tp_pedra aux;
	for(i = 0; i != tamanhomao; i++){
		remove_item_listase2(mao, &aux);
		vetor[i] = aux;
	}
	int cont = 0;
	while(cont != tamanhomao){
		cont++;
	}
	heapSort(vetor, tamanhomao);
	 cont = 0;
	while(cont != tamanhomao){
		cont++;
	}

	for(i = 0; i != tamanhomao ; i++){
		insere_listase_no_fim(mao,vetor[i]);
	}
	return 1;
}

int distribuir_pedras(tp_pilha *monte, tp_listase **mao){
	tp_pedra aux;
	int i;
	for(i = 0; i != startmao; i++){
		pop(monte, &aux);
		insere_listase_no_fim(mao,aux);
	}
	return 1;
}

#endif
