#ifndef _FOGEFOGE_H_

#define  _FOGEFOGE_H_

#define CIMA 'w'
#define BAIXO 's'
#define ESQUERDA 'a'
#define DIREITA 'd'
#define BOMBA 'b'
int direcaovalida(char direcao);
void move(char movimento);
int movimentofantasmavalido(int xatual, int yatual, int* xdestino, int* ydestino);
void movefantasma();
int acabou();

#endif
