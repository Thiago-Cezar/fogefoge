#ifndef _MAPA_H_

#define _MAPA_H_

#define HEROI '@'
#define	VAZIO '.'
#define PAREDE_VERTICAL '|'
#define PAREDE_HORIZONTAL '-'
#define FANTASMA 'F'
#define PILULA 'P'

 typedef struct {
	char** matriz;
	int linhas;
	int colunas;
}MAPA;
typedef struct {
	int x;
	int y;
}POSICAO;
void alocamapa(MAPA* m);
void lemapa(MAPA* m);
int encontranomapa(MAPA* m, POSICAO* p, char c);
void liberamapa(MAPA* m);
int ehposicaovalida(MAPA* m, int x, int y);
int ehparede(MAPA* m, int x, int y);
int ehmesmopersonagem(MAPA* m, char personagem, int x, int y);
int podeandar(MAPA* m, char personagem, int x, int y);
void andanomapa(MAPA* m, int xorigem, int yorigem, int xdestino, int ydestino);
void copiamapa(MAPA* origem, MAPA* destino);

#endif
