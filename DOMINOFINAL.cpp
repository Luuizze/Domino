#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <windows.h>
#include "funcoesdomino.h"
#include "funcoesdomino2.h"
int main(){
	srand(time(NULL));
	setlocale(LC_ALL,"Portuguese");
	tp_pedra pedra, analise;
	tp_jogador jogadores[4];
	tp_listase *mao;
	tp_pilha monte;
	tp_listad *mesa;
	char direcao;
	int njogadores, turnos, a, opcao, op, escopedra;

	do{
		printf("* * * * * * * * * * * * * * * * * * * * * * * *\n");
	    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n");
	    printf("* *                                         * *\n");
	    printf("* *           D  O  M  I  N  �              * *\n");
	    printf("* *                                         * *\n");
	    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n");
		printf("* * * * * * * * * * * * * * * * * * * * * * * *\n");
		printf("\n 1 - Modos de Jogo\n 2 - Sair\n");
		scanf(" %d", &op);
		
		if(op!=1 || op!=2){
			system("cls");
		}
		
		switch(op) {
            case (1):
            	for(int j = 0; j != 4; j++){
					jogadores[j].mao = inicializa_listase();
				}
				mesa = inicializa_listad();
				construir_monte(&monte);
            	
            	printf("[Modo 2 jogadores]\n");
            	printf("[Modo 4 jogadores]\n");
            	printf("  Digite 2 ou 4:  ");
				scanf(" %d", &njogadores);
				while(njogadores != 4 && njogadores!= 2){
					printf("N�mero de jogadores inv�lido. Tente novamente:\n");
					scanf(" %d", &njogadores);
				}
				system("cls");
			
				for(int j = 0; j != njogadores; j++){
					distribuir_pedras(&monte, &jogadores[j].mao);
					Organiza_Pedras(&jogadores[j].mao);
				}
				a = rand()%njogadores;
				turnos = a;
				scanJogadores(njogadores);
				printf("Foi sorteado o jogador %d\n",a+1);
				printf("Aguarde...\n");
				Sleep(2000);
				
				while (true){
					if(turnos == njogadores){
						turnos = 0;						
					}
					system("cls");
					printf("Turno do %s ", jogador[turnos]);
					printf("\n");
					printf("M�o do jogador:\n");
					imprime_listase(jogadores[turnos].mao);
					printf("\n");
					
					printf("\tO monte tem %d pedras\n", altura_pilha(&monte));

					if(lista_vazia(mesa)){
						printf("\t*MESA  VAZIA*\n");
						
					}else{
						printf("\tMesa atual:\n");

						imprime_listad(mesa, 1);
					}
					
					printf("\n Digite: \n 1 - Colocar pedra \n 2 - Cavar \n 3 - Passar a vez\n");
					scanf(" %d", &opcao);
					
					int vez = 0;
					
					switch (opcao){
						case (1):
								while(vez == 0){
									printf("Digite o n�mero da pedra que voc� quer colocar:\n");
									scanf(" %d", &escopedra);
									while(escopedra > tamanho_listase(jogadores[turnos].mao) || escopedra < 0){
									printf("Pedra inv�lida, tente novamente:\n");
									scanf(" %d", &escopedra);	
								}
								
								printf("Digite: \n E para esquerda \n D para direita\n");
								scanf(" %c", &direcao);
								
								while(direcao!= 'D' && direcao != 'd' && direcao != 'E' && direcao != 'e' ){
									printf("Escolha inv�lida, tente novamente:");
									scanf(" %c", &direcao);	
								}
								
								analise = acha_pedra(&jogadores[turnos].mao,escopedra);
								system("pause");
	
								if(insere(&analise, mesa, direcao)){
									if(direcao == 'D' || direcao == 'd'){
										insere_listad_na_direita(mesa, analise);
									}else{
										insere_listad_na_esquerda(mesa, analise);
									}
									
									tira_posicao(&jogadores[turnos].mao, escopedra);
									
									printf("Voc� colocou a pedra!\n");
					 				printf("Aguarde...\n");
					 				vez = 1;
									Sleep(2000);
									system("pause");
									system("cls");
								
								}else{
									printf("A pedra n�o encaixa. Tente novamente.\n");
								}		
							}
						break;
				 		case (2):
				 			if(pilha_vazia(&monte)){
				 				printf("O monte esta vazio. N�o � possivel cavar\n");
				 				system("pause");

							}else{
								pop(&monte, &analise);
								insere_listase_no_fim(&jogadores[turnos].mao, analise);
								Organiza_Pedras(&jogadores[turnos].mao);
							}
							
				 		break;
				 		case (3):
				 			printf("Voc� passou sua vez!\n");
				 			printf("Aguarde...\n");
				 			Sleep(2000);
				 			system("pause");
				 		break;
				 		default:
				 			printf("A� n�o pode!\n");
				 			Sleep(1500);
				 			turnos--;
				 		break;
					}
					
					if(listase_vazia(jogadores[turnos].mao)){
						printf("Fim de jogo!\n");
						printf("Jogador: %s Venceu!!\n", jogador[turnos]);
						break;
					}		
					turnos++;				
				}
			break;
			case (2):
                printf("Escolheu sair do jogo\n");
                break;	
		}	
	}
	while (op != 2);
return 0;
}
