/* TUNARU Stefania Emilia - 311CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OSUTAUNU 101

/* definire continut banda ca lista dublu inlantuita cu santinela*/
typedef struct celula2 {
  char info;
  struct celula2 *pre, *urm;
} TCelula2, *TLista2;

typedef struct banda {
    TLista2 continut;  //  pointer la adresa de inceput a continutului benzii
    TCelula2* poz;  //  pointer la adresa unde se afla pozitia degetu lui in lista dublu inlantuita
} TCelulaBanda, *TBanda;  // TCelulaBanda -> celula ce cuprinde lista dublu inlantuita si pointerul la pozitia degetului

typedef struct celula {
    char info[OSUTAUNU];   //  retin numele operatiilor ce trebuie adaugate in coada
    struct celula *urm;
} TCelula, *TLista;

/* implementare coada drept lista simplu inlantuita */
typedef struct coada {
    TLista inc, sf;
}TCoada;

/* implementare stiva drept lista simplu inlantuita */
typedef struct celst {
    TLista2 info;  //  stiva retine pointer catre o celula din continutul benzii
    struct celst *urm;
}TCelulaStiva, *TStiva;

TLista2 AlocCelula2(char x);
TLista2 InitLista2();
int AdaugaLista2(TLista2 L, char info);
void AfisareLista2(TLista2 L, FILE *fisierout);
void DistrugeLista2(TLista2 *aL);
TBanda InitBanda();
void DistrBanda(TBanda *banda);
TCoada* InitQ();
int IntrQ(TCoada *c, char *x);
int ExtrQ(TCoada *c, char *x);
void DistrQ(TCoada **c);
void AfisareQ(TCoada *c, FILE *fisierout);
TStiva InitS(void);
int Push(TStiva *vf, TLista2 x);
int Pop(TStiva *vf, TLista2 *ax);
void DistrugeS(TStiva* vf);
char current(TBanda banda);
void show(TBanda banda, FILE *fisierout);
int move_left(TBanda b);
void move_right(TBanda banda);
void move_left_char(TBanda banda, char c, FILE *fisierout);
void move_right_char(TBanda banda, char c);
void write(TBanda banda, char c);
void insert_left(TBanda banda, char c, FILE *fisierout);
void insert_right(TBanda banda, char c);
void undo(TBanda banda, TStiva *stivaUNDO, TStiva *stivaREDO);
void redo(TBanda banda, TStiva *stivaREDO, TStiva *stivaUNDO);
