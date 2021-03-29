#include <stdio.h>
#include <stdlib.h>
#include <locale.h> // NECESSARIO PRA USAR O SETLOCALE
#define TAB 8
#define CASA_BRANCA -1 //CASA EM BRANCO
#define CASA_VAZIA 0 //CASA VAZIA
#define A 1 // PE�A BRANCA
#define B 2 //PE�A PRETA


int matriz[TAB][TAB]; // MATRIZ TABULEIRO 
int menu = 0, i = 0, j = 0; // VARIAVEIS PARA O MENU
int fimJogo = 0, coluna = 0, iLinha =0, iColuna=0, movimentoInvalido, linhaDestino = 0, 
colunaDestino = 0, linhaOrigem = 0, colunaOrigem = 0, movimento = 0, jogador = 0, brancaComida = 0, pretaComida = 0; //VARIAVEIS DAS PECAS E MOVIMENTOS

int main() { // MENU DO JOGO
	
	setlocale(LC_ALL, "portuguese"); // CONFIGURANDO PORTUGUES COMO IDIOMA
	do
	{
		printf("\n\t Bem vindo ao jogo de Damas!");
		printf("\n\t 1 - Iniciar jogo.");
		printf("\n\t 2 - Informa��es do jogo.");
		printf("\n\t 3 - Sair do jogo.");
		printf("\n\n\t Selecione uma op��o => ");
		scanf("%d", &menu);

		switch (menu) // SWITCH  CASE PARA CADA OPCAO DO MENU
		{
		case 1: //COME�AR O JOGO (FUN��O JOGO)
			inicioGame();
			movimentarPeca();
			
			
			break;

		case 2: // INFORMA��ES DO JOGO
			infoGame();
			break;
			
		case 3: //SAIR DO JOGO
			system("cls");
			printf("\nVOC� SAIU DO JOGO!");
			break;

		default:
			system("cls");
			printf("\nOP��O INVALIDA, TENTE NOVAMENTE!");	
		}
	} while (menu != 3);
	return 0;
}

void inicioGame(){ //FUN�AO DE INICIAR JOGO
	for(iLinha = 0 ; iLinha < 8; iLinha++) 
	{
		for(iColuna = 0 ; iColuna < 8; iColuna++) // FOR PARA PREENCHER AS COLUNAS
		{
			matriz[iLinha][iColuna] = 0;
		}
	}
			for(iColuna = coluna; iColuna < 8; iColuna+=2) // FOR PARA DEIXAR UMA CASA EM BRANCO
			{
				matriz[iLinha][iColuna] = CASA_BRANCA;
			}
		for(iLinha = 0 ; iLinha < 8; iLinha++) // FOR PARA PREENCHER AS LINHAS
		{
			for(iColuna = 0 ; iColuna < 8; iColuna++)
			{
				if (((iLinha % 2 == 0) && (iColuna % 2 == 0)) || ((iLinha % 2 == 1) && (iColuna % 2 == 1)))// TESTE LOGICO PARA DEFINIR OS INDICES
				{
				if (iLinha < 3) matriz[iLinha][iColuna] = A; // PECAS BRANCAS
				else if (iLinha > 4) matriz[iLinha][iColuna] = B; // PECAS PRETAS
				else matriz[iLinha][iColuna] = 0;// VAZIO
				}
			}
		}
	}
	
void imprimirTabuleiro(){ // FUNCAO PARA IMPRIMIR O TABULEIRO
	system("cls");
    printf("\t     TABULEIRO");
    printf("\n----------------------------------\n");
	printf("   0   1   2   3   4   5   6   7");
	for(iLinha = 0; iLinha < 8; iLinha++)
	{
		printf("\n%d ",iLinha); //mostrar coluna
		for(iColuna = 0; iColuna < 8; iColuna++)
		{
			if(matriz[iLinha][iColuna] == A)//printar casas brancas
			{
				printf(" A  ");
			}else{
				if(matriz[iLinha][iColuna] == B)//printar casas pretas
				{
					printf(" B  ");
				}else{
					if(matriz[iLinha][iColuna] == CASA_BRANCA)//printar casas em branco
					{
						printf(" .  "); 
					}else{
						printf(" .  ");
					}
				}
			}
		}
		printf("\n");
	}
}
  

void movimentarPeca(){
	
	while(brancaComida < 12 || pretaComida < 12){ //la�o p/ o repetir se tiver pe�a branca/preta
	imprimirTabuleiro();
	vezJogador();
	
	printf("\n\tDIGITE A PEÇA QUE DESEJA MOVIMENTAR!");//escolher pe�a
	printf("\n\n\t\t\tLINHA => ");
	scanf_s("\n%d", &linhaOrigem);
	printf("\n\n\t\t\tCOLUNA => ");
	scanf_s("\n%d", &colunaOrigem);
	printf("\n\tQUAL MOVIMENTO DESEJA FAZER?");//ocupar pe�a
	printf("\n\t 1 = ESQUERDA \n\t 2 = DIREITA");
	printf("\n\n\t\t\tJOGADA => ");
	scanf("\n\t%d", &movimento);

	if(jogador == 1){//jogada p/ peça preta      
		if(movimento == 1 && matriz[linhaOrigem][colunaOrigem] == B && linhaOrigem -1 >= 0 && colunaOrigem -1 >= 0)//teste do movimento e limita��o
		{
			if(matriz[linhaOrigem-1][colunaOrigem-1] == 0){ //se o movimento for p/ as pe�as pretas, -1 casa p/ subir
				matriz[linhaOrigem][colunaOrigem] = 0; //reset na posi��o atual
				matriz[linhaOrigem-1][colunaOrigem-1] = B; //colocar a pe�a preta
				jogador = 0; //trocar a vez do jogador				
			}else{
				if(matriz[linhaOrigem-1][colunaOrigem-1] == A && matriz[linhaOrigem-2][colunaOrigem-2] == 0 && linhaOrigem -2 >= 0 && colunaOrigem -2 >= 0)//se houver uma peça branca no caminho faz o movimento -2
				{
					matriz[linhaOrigem][colunaOrigem] = 0; //reset na posi��o atual
					matriz[linhaOrigem-1][colunaOrigem-1] = 0; //deixar em branco a pe�a que comeu
					matriz[linhaOrigem-2][colunaOrigem-2] = B; //colocar a pe�a preta
					jogador = 0; //trocar a vez do jogador
					brancaComida++;
				}else{
					movimentoInvalido = 1; //caso movimento n�o seja validado pelo restante "= 1" p mostrar msg
				}								
			}
										
		}else{//jogada p/ direita
			if(movimento == 2 && matriz[linhaOrigem][colunaOrigem] == B && linhaOrigem -1 >= 0 && colunaOrigem +1 < 8)//se escolhido for igual a B faz o movimento / n�o ultrapassar o limite do tabuleiro
			{
				if(matriz[linhaOrigem-1][colunaOrigem+1] == 0){ //caso n�o tenha pe�aa inimiga na diagonal
					matriz[linhaOrigem][colunaOrigem] = 0; //reset na posi��o atual
					matriz[linhaOrigem-1][colunaOrigem+1] = B; //colocar a pe�a preta
					movimentoInvalido = 0; //movimento errado zerado
					jogador = 0; //trocar a vez do jogador
				}else{
					if(matriz[linhaOrigem-1][colunaOrigem+1] == A && matriz[linhaOrigem-2][colunaOrigem+2] == 0 && linhaOrigem -1 >= 0 && colunaOrigem +2 < 8)
					{
						matriz[linhaOrigem][colunaOrigem] = 0; //reset na posi��o atual
						matriz[linhaOrigem-1][colunaOrigem+1] = 0; //-1 p deixar em branco a pe�a que comeu
						matriz[linhaOrigem-2][colunaOrigem+2] = B; //colocar a pe�a preta
						jogador = 0;
						brancaComida++;
					}
				}				
			}else{
				movimentoInvalido = 1;
			}		
		}
	}else{
		if(jogador == 0){//jogada pe�a branca
		if(movimento == 1 && matriz[linhaOrigem][colunaOrigem] == A && linhaOrigem+1 >= 0 && colunaOrigem-1 >=0)//moimento p/ direita
		{
			if(matriz[linhaOrigem+1][colunaOrigem-1] == 0)//se o movimento n�o tiver pe�a inimiga
			{
				matriz[linhaOrigem][colunaOrigem] = 0; //reset na posi��o atual
				matriz[linhaOrigem+1][colunaOrigem-1] = A; //colocar a pe�a branca
				jogador = 1;	
			}else{
				if(matriz[linhaOrigem+1][colunaOrigem-1] == B && matriz[linhaOrigem+2][colunaOrigem-2] == 0 && linhaOrigem+2 >= 0 && colunaOrigem-2 >= 0)//se houver uma pe�a inimiga e a proxima estiver vazia executa o movimento
				{
					matriz[linhaOrigem][colunaOrigem] = 0; //reset na posi��o atual
					matriz[linhaOrigem+1][colunaOrigem-1] = 0; //deixar em branco a pe�a que comeu
					matriz[linhaOrigem+2][colunaOrigem-2] = A; //colocar a pe�a branca
					jogador = 1;
					pretaComida++;
				}else{
					movimentoInvalido = 1;//se não tiver espa�o p alocar pe�a
				}					
			}		
		}else{
		if(movimento == 2 && matriz[linhaOrigem][colunaOrigem] == A && linhaOrigem +1 < 8  && colunaOrigem +1 < 8 ){
			if(matriz[linhaOrigem+1][colunaOrigem+1] == 0){
				matriz[linhaOrigem][colunaOrigem] = 0; //reset na posi�ao atual
				matriz[linhaOrigem+1][colunaOrigem+1] = A; //colocar a pe�a branca
				jogador = 1;	
					}else{
						if(matriz[linhaOrigem+1][colunaOrigem+1] == B && matriz[linhaOrigem+2][colunaOrigem+2] == 0 && linhaOrigem +2 < 8  && colunaOrigem +2 < 8){
							matriz[linhaOrigem][colunaOrigem] = 0; //reset na posi��o atual
							matriz[linhaOrigem+1][colunaOrigem+1] = 0; //deixar em branco a pe�a que comeu
							matriz[linhaOrigem+2][colunaOrigem+2] = A; //colocar a pe�a branca
							jogador = 1;
							pretaComida++;
						}	
					}
				}else{
					movimentoInvalido = 1;
				}		
			}
		}
	}
	
	if(movimentoInvalido == 1){
		printf("\n\t MOVIMENTO INVALIDO!");
		movimentoInvalido = 0;
	}
	
	}
}

void vezJogador(){
	
	if(jogador == 0){
		printf("\n\n\tJOGADOR (A) %d - BRANCAS JOGANDO!!!", A);
	}else{
		printf("\n\n\tJOGADOR (B) %d - PRETAS JOGANDO!!!", B);
	}
}   


void infoGame(){
	system("cls");
	printf("\n\t Objetivo do jogo � eliminar as pe�as inimigas.");
	printf("\n\t Com movimentos apenas na diagonal!");
	printf("\n\t Boa sorte! \n");
}
