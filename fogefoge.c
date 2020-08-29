#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fogefoge.h"
#include "mapa.h"
#include "ui.h"

MAPA m;
POSICAO heroi;
int tempilula = 0;

int direcaovalida(char direcao)
{
	return
		direcao == CIMA ||
		direcao == BAIXO ||
		direcao == ESQUERDA ||
		direcao == DIREITA;
}

void move(char direcao)
{
	int proximox = heroi.x;
	int proximoy = heroi.y;

	switch(direcao) {
		case CIMA:
			proximox--;
			break;
		case BAIXO:
			proximox++;
			break;
		case ESQUERDA:
			proximoy--;
			break;
		case DIREITA:
			proximoy++;
			break;
	}

	if(!podeandar(&m, HEROI, proximox, proximoy))
		return;

	if(ehmesmopersonagem(&m, PILULA, proximox, proximoy))
		tempilula = 1;

	andanomapa(&m, heroi.x, heroi.y, proximox, proximoy);

	heroi.x = proximox;
	heroi.y = proximoy;
}

int movimentofantasmavalido(int xatual, int yatual, int* xdestino, int* ydestino)
{
	int opcoes[4][2] = {
		{ xatual - 1, yatual},
		{ xatual + 1, yatual},
		{ xatual, yatual - 1},
		{ xatual, yatual + 1}
	};
	srand(time(0));
	int posicaovalida[4] = {0,0,0,0};
	int j = 0;
	for(int i = 0; i < 4; i++) {
		if(podeandar(&m, FANTASMA, opcoes[i][0], opcoes[i][1])) {
			posicaovalida[j] = i;
			j++;
		}
	}
	if(j >= 1) {
		int posicao;
		if(j == 0) {
			posicao = posicaovalida[j];
			*xdestino = opcoes[posicao][0];
			*ydestino = opcoes[posicao][1];
		}

		posicao = rand() % j;
		posicao = posicaovalida[posicao];
		*xdestino = opcoes[posicao][0];
		*ydestino = opcoes[posicao][1];
		return 1;
	}
	return 0;
}

void movefantasma()
{
	MAPA copia;
	copiamapa(&m, &copia);
	for(int i = 0; i < copia.linhas; i++) {
		for(int j = 0; j < copia.colunas; j++) {
			if(copia.matriz[i][j] == FANTASMA) {
				int xdestino;
				int ydestino;
				int encontrou = movimentofantasmavalido(i, j, &xdestino, &ydestino);
				if(encontrou) {
					andanomapa(&m, i, j, xdestino, ydestino);
				}
			}
		}
	}
	liberamapa(&copia);
}

int acabou()
{
	POSICAO pos;
	int perdeu = !encontranomapa(&m, &pos, HEROI);
	int ganhou = !encontranomapa(&m, &pos, FANTASMA);
	return perdeu || ganhou;
}

void explodepilula2(int x, int y, int somax, int somay, int qtd)
{
	if(qtd == 0) return;

	int novox = x + somax;
	int novoy = y + somay;

	if(!ehposicaovalida(&m, novox, novoy)) return;
	if(ehparede(&m, novox, novoy)) return;

	m.matriz[novox][novoy] = VAZIO;
	explodepilula2(novox, novoy, somax, somay, qtd-1);
}
void explodepilula()
{
	if(!tempilula) return;

	explodepilula2(heroi.x, heroi.y, 0, 1, 3);
	explodepilula2(heroi.x, heroi.y, 0, -1, 3);
	explodepilula2(heroi.x, heroi.y, 1, 0, 3);
	explodepilula2(heroi.x, heroi.y, -1, 0, 3);

	tempilula = 0;
}
int main()
{
	lemapa(&m);
	encontranomapa(&m, &heroi, HEROI);
	do {
		imprimemapa(&m);

		char comando;
		scanf(" %c", &comando);
		if(direcaovalida(comando)) move(comando);
		if(comando == BOMBA) explodepilula();
		movefantasma();
	}while(!acabou());
	liberamapa(&m);
	return 0;
}
