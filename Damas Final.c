#include <stdio.h>
#include <stdlib.h>
#include <locale.h> // NECESSARIO PRA USAR O SETLOCALE
#define TAB 8
#define CASA_BRANCA -1 //CASA EM BRANCO
#define CASA_VAZIA 0 //CASA VAZIA
#define A 1 // PEÇA BRANCA
#define B 2 //PEÇA PRETA


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
		printf("\n\t 2 - Informações do jogo.");
		printf("\n\t 3 - Sair do jogo.");
		printf("\n\n\t Selecione uma opção => ");
		scanf("%d", &menu);

		switch (menu) // SWITCH  CASE PARA CADA OPCAO DO MENU
		{
		case 1: //COMEÇAR O JOGO (FUNÇÃO JOGO)
			inicioGame();
			movimentarPeca();
			
			
			break;

		case 2: // INFORMAÇÕES DO JOGO
			infoGame();
			break;
			
		case 3: //SAIR DO JOGO
			system("cls");
			printf("\nVOCÊ SAIU DO JOGO!");
			break;

		default:
			system("cls");
			printf("\nOPÇÃO INVALIDA, TENTE NOVAMENTE!");	
		}
	} while (menu != 3);
	return 0;
}

void inicioGame(){ //FUNÇAO DE INICIAR JOGO
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
	
	while(brancaComida < 12 || pretaComida < 12){ //laço p/ o repetir se tiver peça branca/preta
	imprimirTabuleiro();
	vezJogador();
	
	printf("\n\tDIGITE A PEÃ‡A QUE DESEJA MOVIMENTAR!");//escolher peça
	printf("\n\n\t\t\tLINHA => ");
	scanf_s("\n%d", &linhaOrigem);
	printf("\n\n\t\t\tCOLUNA => ");
	scanf_s("\n%d", &colunaOrigem);
	printf("\n\tQUAL MOVIMENTO DESEJA FAZER?");//ocupar peça
	printf("\n\t 1 = ESQUERDA \n\t 2 = DIREITA");
	printf("\n\n\t\t\tJOGADA => ");
	scanf("\n\t%d", &movimento);

	if(jogador == 1){//jogada p/ peÃ§a preta      
		if(movimento == 1 && matriz[linhaOrigem][colunaOrigem] == B && linhaOrigem -1 >= 0 && colunaOrigem -1 >= 0)//teste do movimento e limitação
		{
			if(matriz[linhaOrigem-1][colunaOrigem-1] == 0){ //se o movimento for p/ as peças pretas, -1 casa p/ subir
				matriz[linhaOrigem][colunaOrigem] = 0; //reset na posição atual
				matriz[linhaOrigem-1][colunaOrigem-1] = B; //colocar a peça preta
				jogador = 0; //trocar a vez do jogador				
			}else{
				if(matriz[linhaOrigem-1][colunaOrigem-1] == A && matriz[linhaOrigem-2][colunaOrigem-2] == 0 && linhaOrigem -2 >= 0 && colunaOrigem -2 >= 0)//se houver uma peÃ§a branca no caminho faz o movimento -2
				{
					matriz[linhaOrigem][colunaOrigem] = 0; //reset na posição atual
					matriz[linhaOrigem-1][colunaOrigem-1] = 0; //deixar em branco a peça que comeu
					matriz[linhaOrigem-2][colunaOrigem-2] = B; //colocar a peça preta
					jogador = 0; //trocar a vez do jogador
					brancaComida++;
				}else{
					movimentoInvalido = 1; //caso movimento não seja validado pelo restante "= 1" p mostrar msg
				}								
			}
										
		}else{//jogada p/ direita
			if(movimento == 2 && matriz[linhaOrigem][colunaOrigem] == B && linhaOrigem -1 >= 0 && colunaOrigem +1 < 8)//se escolhido for igual a B faz o movimento / não ultrapassar o limite do tabuleiro
			{
				if(matriz[linhaOrigem-1][colunaOrigem+1] == 0){ //caso não tenha peçaa inimiga na diagonal
					matriz[linhaOrigem][colunaOrigem] = 0; //reset na posição atual
					matriz[linhaOrigem-1][colunaOrigem+1] = B; //colocar a peça preta
					movimentoInvalido = 0; //movimento errado zerado
					jogador = 0; //trocar a vez do jogador
				}else{
					if(matriz[linhaOrigem-1][colunaOrigem+1] == A && matriz[linhaOrigem-2][colunaOrigem+2] == 0 && linhaOrigem -1 >= 0 && colunaOrigem +2 < 8)
					{
						matriz[linhaOrigem][colunaOrigem] = 0; //reset na posição atual
						matriz[linhaOrigem-1][colunaOrigem+1] = 0; //-1 p deixar em branco a peça que comeu
						matriz[linhaOrigem-2][colunaOrigem+2] = B; //colocar a peça preta
						jogador = 0;
						brancaComida++;
					}
				}				
			}else{
				movimentoInvalido = 1;
			}		
		}
	}else{
		if(jogador == 0){//jogada peça branca
		if(movimento == 1 && matriz[linhaOrigem][colunaOrigem] == A && linhaOrigem+1 >= 0 && colunaOrigem-1 >=0)//moimento p/ direita
		{
			if(matriz[linhaOrigem+1][colunaOrigem-1] == 0)//se o movimento não tiver peça inimiga
			{
				matriz[linhaOrigem][colunaOrigem] = 0; //reset na posição atual
				matriz[linhaOrigem+1][colunaOrigem-1] = A; //colocar a peça branca
				jogador = 1;	
			}else{
				if(matriz[linhaOrigem+1][colunaOrigem-1] == B && matriz[linhaOrigem+2][colunaOrigem-2] == 0 && linhaOrigem+2 >= 0 && colunaOrigem-2 >= 0)//se houver uma peça inimiga e a proxima estiver vazia executa o movimento
				{
					matriz[linhaOrigem][colunaOrigem] = 0; //reset na posição atual
					matriz[linhaOrigem+1][colunaOrigem-1] = 0; //deixar em branco a peça que comeu
					matriz[linhaOrigem+2][colunaOrigem-2] = A; //colocar a peça branca
					jogador = 1;
					pretaComida++;
				}else{
					movimentoInvalido = 1;//se nÃ£o tiver espaço p alocar peça
				}					
			}		
		}else{
		if(movimento == 2 && matriz[linhaOrigem][colunaOrigem] == A && linhaOrigem +1 < 8  && colunaOrigem +1 < 8 ){
			if(matriz[linhaOrigem+1][colunaOrigem+1] == 0){
				matriz[linhaOrigem][colunaOrigem] = 0; //reset na posiçao atual
				matriz[linhaOrigem+1][colunaOrigem+1] = A; //colocar a peça branca
				jogador = 1;	
					}else{
						if(matriz[linhaOrigem+1][colunaOrigem+1] == B && matriz[linhaOrigem+2][colunaOrigem+2] == 0 && linhaOrigem +2 < 8  && colunaOrigem +2 < 8){
							matriz[linhaOrigem][colunaOrigem] = 0; //reset na posição atual
							matriz[linhaOrigem+1][colunaOrigem+1] = 0; //deixar em branco a peça que comeu
							matriz[linhaOrigem+2][colunaOrigem+2] = A; //colocar a peça branca
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
	printf("\n\t Objetivo do jogo é eliminar as peças inimigas.");
	printf("\n\t Com movimentos apenas na diagonal!");
	printf("\n\t Boa sorte! \n");
}
