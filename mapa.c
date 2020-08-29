#include <stdio.h>
#include <stdlib.h>
#include "mapa.h"

void alocamapa(MAPA* m)
{
	m->matriz = malloc(sizeof(char*) * m->linhas);
	for(int i = 0; i < m->linhas; i++) {
		m->matriz[i] = malloc(sizeof(char) * m->colunas + 1);
	}
}

void lemapa(MAPA* m)
{
	FILE* f;
	f = fopen("mapa.txt", "r");
	if(f == 0) {
		printf("Erro ao carregar o mapa.");
		exit(1);
	}
	fscanf(f, "%d %d", &(m->linhas), &(m->colunas));
	alocamapa(m);
	for(int i = 0; i < m->linhas; i++) {
		fscanf(f, "%s", m->matriz[i]);
	}
	fclose(f);
}

int encontranomapa(MAPA* m, POSICAO* p, char c)
{
	for(int i = 0; i < m->linhas; i++) {
		for(int j = 0; j < m->colunas; j++) {
			if(m->matriz[i][j] == c) {
				p->x = i;
				p->y = j;
				return 1;
			}
		}
	}
	return 0;
}

void liberamapa(MAPA* m)
{
	for(int i = 0; i < m->linhas; i++) {
		free(m->matriz[i]);
	}
	free(m->matriz);
}
int ehposicaovalida(MAPA* m, int x, int y)
{
	if(x >= m->linhas)
		return 0;
	if(y >= m->colunas)
		return 0;

	return 1;
}
int ehparede(MAPA* m, int x, int y)
{
	return m->matriz[x][y] == PAREDE_HORIZONTAL || m->matriz[x][y] == PAREDE_VERTICAL;
}
int ehmesmopersonagem(MAPA* m, char personagem, int x, int y)
{
	return m->matriz[x][y] == personagem;
}

int podeandar(MAPA* m, char personagem, int x, int y)
{
	return
		ehposicaovalida(m, x, y) &&
		!ehparede(m, x, y) &&
		!ehmesmopersonagem(m, personagem, x, y);
}

void andanomapa(MAPA* m, int xorigem, int yorigem, int xdestino, int ydestino)
{
	char personagem = m->matriz[xorigem][yorigem];
	m->matriz[xdestino][ydestino] = personagem;
	m->matriz[xorigem][yorigem] = VAZIO;
}
void copiamapa(MAPA* origem, MAPA* destino)
{	
	destino->linhas = origem->linhas;
	destino->colunas = origem->colunas;
	alocamapa(destino);
	for(int i = 0; i < origem->linhas; i++) {
		strcpy(destino->matriz[i], origem->matriz[i]);
	}
}
