/* TUNARU Stefania Emilia - 311CB */
#include "header.h"

/* Aloca un element de tip TCelula2 si returneaza pointerul aferent */
TLista2 AlocCelula2(char x) {
  TLista2 aux = (TLista2) malloc(sizeof(TCelula2));
  if (!aux) {
    return NULL;
  }
  aux->info = x;
  aux->pre = aux->urm = NULL;
  return aux;
}

/* Creeaza santinela pentru lista folosita si initializeaza lista dublu inlantuita */
TLista2 InitLista2() {
    TLista2 aux = (TLista2) malloc(sizeof(TCelula2));
    if (!aux) {
        return NULL;
    }
  aux->info = '|';                  // informatia din santinela are valoarea '|'
  aux->pre = NULL;
  aux->urm = NULL;
  return aux;
}

/* Functia ce adauga elemente in lista */
int AdaugaLista2(TLista2 L, char info) {
  TLista2 aux = AlocCelula2(info);
  if (!aux) return 0;    //  verific daca alocarea a fost facuta cu succes
  aux->urm = NULL;
  TLista2 p = NULL;
  for (p = L; p->urm != NULL; p = p->urm) {;}    //  parcurg lista pentru a ajunge la ultimul element
  p->urm = aux;
  aux->pre = p;
  return 1;
}

/* Afisare continut lista */
void AfisareLista2(TLista2 L, FILE *fisierout)  {
  TLista2 p = L->urm;
  fprintf(fisierout, "Lista: [");
  while (p != NULL) {         //  parcurgere lista
    fprintf(fisierout, "%c ", p->info);
    p = p->urm;
  }
  fprintf(fisierout, "]\n");
}

/* Distrugere lista */
void DistrugeLista2(TLista2 *aL) {
    TLista2 p = (*aL)->urm, aux = NULL;
    while (p != NULL) {         //  distrugere elementele listei
        aux = p;
        p = p->urm;
        free(aux);
    }
    free(*aL);                  // distrugere santinela
    *aL = NULL;
}

/* Initializare banda */
TBanda InitBanda() {
  TBanda banda = (TBanda)malloc(sizeof(TCelulaBanda));
  if (!banda) return NULL;      //  verific daca alocarea s-a realizat cu succes
  banda->continut = InitLista2();
  if (AdaugaLista2(banda->continut, '#') == 0) {    //  adaug primul element al listei conform cerintei
    free(banda);
    return NULL;
  }
  banda->poz = banda->continut->urm;     //  mut degetul sa indice catre pozitia primului element al benzii
  return banda;  // initializare reusita a benzii
}

/* Distrugere banda */
void DistrBanda(TBanda *banda) {
  DistrugeLista2(&((*banda)->continut));
  (*banda)->poz = NULL;
  free(*banda);
  *banda = NULL;
}

/* Initializare coada */
TCoada* InitQ() {
  TCoada* c = (TCoada*)malloc(sizeof(TCoada));
  if (!c) return NULL;                  //  nu exista spatiu -> "esec"
  c->inc = c->sf = NULL;
  return c;          //  intoarce adresa descriptorului cozii
}

/* Introducere element in coada */
int IntrQ(TCoada *c, char *x) {  //  adauga elementul x la sfarsitul cozii
  TLista aux = NULL;
  aux = (TLista)malloc(sizeof(TCelula));      //  aloca o noua celula
  if (!aux) return 0;
  snprintf(aux->info, strlen(x) + 1, "%s", x);
  aux->urm = NULL;
  if (c->sf != NULL)          //  coada nevida
    c->sf->urm = aux;                   //  leaga celula dupa ultima din coada
  else                              //  coada vida
    c->inc = aux;                    //  noua celula se afla la inceputul cozii
  c->sf = aux;           //  actualizeaza sfarsitul cozii
  return 1;
}

/* Extragere element din coada */
int ExtrQ(TCoada *coada, char *c) {         //  extrage primul element din coada
  TLista aux = NULL;
  if (coada->inc == NULL) return 0;     //  coada vida -> nu se extrage
  aux = coada->inc;               //  retin pozitia de inceput a cozii
  snprintf(c, strlen(aux->info) + 1, "%s", aux->info);    //  retin valoarea de la inceputul cozii
  coada->inc = aux->urm;               //  actualizez inceputul cozii
  if (coada->inc == NULL) coada->sf = NULL;      //  o singura valoare in lista
  free(aux);
  return 1;
  }

/* Distrugere coada */
void DistrQ(TCoada **c) {    //  distruge coada
  TLista p = NULL, aux = NULL;
  p = (*c)->inc;
  while (p) {
    aux = p;
    p = p->urm;
    free(aux);      // elibereaza memoria ocupata de elementele cozii
  }
  free(*c);        //  elibereaza memoria ocupata de adresa cozii
  *c = NULL;
}

/* Afisare coada */
void AfisareQ(TCoada *coada, FILE *fisierout) {     //  afisare elementele cozii
  TLista p = NULL;
  if (coada->inc == NULL) {
    fprintf(fisierout, "Coada vida\n");
    return;
  }
  for (p = coada->inc; p != NULL; p = p->urm)     //  parcurgere elementele cozii si afisearea lor
    fprintf(fisierout, "%s ", p->info);
  fprintf(fisierout, "\n");
}

/* Initializare stiva vida */
TStiva InitS(void) {
  return NULL;
}

/* Inserare in stiva */
int Push(TStiva *vf, TLista2 x) {
  TStiva aux = (TStiva)malloc(sizeof(TCelulaStiva));   //  se declara si se aloca o variabila aux
  if (!aux) return 0;
  aux->info = x;     // se retine informatia ce trebuie adaugata in stiva in variabila aux->info
  aux->urm = NULL;
  aux->urm = *vf;
  *vf = aux;      //  se actualizeaza varful stivei
  return 1;
}

/* Extragere din stiva */
int Pop(TStiva *vf, TLista2 *ax) {
  TStiva aux = NULL;
  if (*vf == NULL) return 0;    //  verifica daca stiva este vida
  *ax = (*vf)->info;         //  se retine informatia din varful stivei
  aux = *vf;
  *vf = aux->urm;        //  se actualizeaza varful stivei
  free(aux);        //  se elibereaza memoria ocupata de fostul varf al stivei
  return 1;
}

/* Distrugere stiva */
void DistrugeS(TStiva* vf) {
  TStiva aux = NULL;
  while (*vf) {      //  se parcurge stiva
    aux = *vf;
    *vf = (*vf)->urm;
    free(aux);    //  se elibereaza memoria ocupata de elementele stivei
  }
}

/* Comanda SHOW_CURRENT */
char current(TBanda banda) {
  return banda->poz->info;
}

/* Comanda SHOW */
void show(TBanda banda, FILE *fisierout) {
  TLista2 p = banda->continut->urm;  // variabila p se pozitioneaza pe primul element al benzii
  while (p != NULL) {    //  este parcursa banda
    if (p == banda->poz) {
      fprintf(fisierout, "|%c|", p->info);   //  daca se ajunge pe pozitia degetului acesta se afiseaza conform cerintei
    } else {
    fprintf(fisierout, "%c", p->info);   //  se afiseaza in mod normal restul de elemente ale benzii
    }
    p = p->urm;
  }
  fprintf(fisierout, "\n");
}

/* Comanda MOVE_LEFT */
int move_left(TBanda banda) {
  if (banda->poz == banda->continut->urm)   //  verific daca ma aflu pe prima pozitie a benzii, caz in care nu fac nimic
    return 0;
  else
    banda->poz = banda->poz->pre;   //  in caz contrar mut degetul cu o pozitie mai la stanga
  return 1;
}

/* Comanda MOVE_RIGHT */
void move_right(TBanda banda) {
  if (banda->poz->urm == NULL) AdaugaLista2(banda->continut, '#');  // degetul pe ultima pozitie -> adaugare element
  banda->poz = banda->poz->urm;   //  se actualizeaza pozitia degetului
}

/* Comanda MOVE_LEFT_CHAR */
void move_left_char(TBanda banda, char c, FILE *fisierout) {
  TLista2 p = NULL;
  for (p = banda->poz; p != banda->continut; p = p->pre) {  //  parcurge partea stanga a listei de la elementul curent
    if (p->info == c) {
      banda->poz = p;    // se actualizeaza pozitia degetului daca este gasit caracterul cautat
      break;
    }
  }
  if (p == banda->continut) fprintf(fisierout, "ERROR\n");   //  adresa de inceput a benzii -> mesajul de eroare
}

/* Comanda MOVE_RIGHT_CHAR */
void move_right_char(TBanda banda, char c) {
  TLista2 p = NULL, aux = NULL;
  for (p = banda->poz; p != NULL; p = p->urm) {  //  se parcurge partea dreapta a listei incepand de la elementul curent
    if (p->info == c) {
      banda->poz = p;    // se actualizeaza pozitia degetului daca este gasit caracterul cautat
      break;
    }
  }
  if (p == NULL) {
  AdaugaLista2(banda->continut, '#');   //  nu este gasit caracterul cautat -> un nou element la sfarsitul benzii
  for (aux = banda->continut; aux->urm != NULL; aux = aux->urm) {;}  // parcurge banda -> ma pozitionez pe ultimul el.
  banda->poz = aux; }   //  se actualizeaza pozitia degetului pe banda
}

/* Comanda WRITE */
void write(TBanda banda, char c) {
  banda->poz->info = c;  //  se scrie caracterul indicat pe pozitia degetului
}

/* Comanda INSERT_LEFT */
void insert_left(TBanda banda, char c, FILE *fisierout) {
  if (banda->poz == banda->continut->urm) {   // ma aflu pe primul element al benzii -> mesajul de eroare
    fprintf(fisierout, "ERROR\n");
  } else {
    TLista2 aux = AlocCelula2(c);
    aux->urm = banda->poz;
    aux->pre = banda->poz->pre;
    banda->poz->pre = aux;
    aux->pre->urm = aux;
    banda->poz = aux;    //  aloc celula in care retin caracterul 'c', apoi fac legaturile corespunzatoare inserarii
  }
}

/* Comanda INSERT_RIGHT*/
void insert_right(TBanda banda, char c) {
  TLista2 aux = AlocCelula2(c);   //  aloc celula in care retin caracterul 'c'
  if (banda->poz->urm == NULL) {
    aux->pre = banda->poz;   //   daca ma aflu pe utlimul element al benzii
    banda->poz->urm = aux;
  } else {
    aux->pre = banda->poz;    //  inserez la dreapta elementului curent si fac legaturile corespunzatoare
    aux->urm = banda->poz->urm;
    banda->poz->urm = aux;
    aux->urm->pre = aux;
  }
  banda->poz = aux;    //  actualizez pozitia curenta a degetului
}

/* Comanda UNDO */
void undo(TBanda banda, TStiva *stivaUNDO, TStiva *stivaREDO) {
  Push(stivaREDO, banda->poz);          //  introduc pointerul la pozitia curenta a degetului in stiva de REDO
  Pop(stivaUNDO, &(banda->poz));        //  extrag pointerul din varful stivei de UNDO pe care il retin in banda->poz
}

/* Comanda REDO */
void redo(TBanda banda, TStiva *stivaREDO, TStiva *stivaUNDO) {
  Push(stivaUNDO, banda->poz);     //  introduc pointerul la pozitia curenta a degetului in stiva de UNDO
  Pop(stivaREDO, &(banda->poz));   //  extrag pointerul din varful stivei de REDO pe care il retin in banda->poz
}
