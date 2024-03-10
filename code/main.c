/* TUNARU Stefania Emilia - 311CB */
#include "header.h"
#define OSUTAUNU 101

int main() {
    TBanda banda = InitBanda();
    TCoada* coada = InitQ();
    TStiva stivaUNDO = InitS();
    TStiva stivaREDO = InitS();

    int nrcomenzi = 0, i = 0;
    char comanda[OSUTAUNU];
    FILE *fisierin = fopen("tema1.in", "r");
    FILE *fisierout = fopen("tema1.out", "wa");
    fscanf(fisierin, "%d", &nrcomenzi);
    fgets(comanda, OSUTAUNU, fisierin);
    for (i = 1; i <= nrcomenzi; i++) {
        fgets(comanda, OSUTAUNU, fisierin);
        comanda[strlen(comanda)-1] = '\0';       // elimin \n
        if (strcmp(comanda, "SHOW") == 0) show(banda, fisierout);
        if (strcmp(comanda, "SHOW_CURRENT") == 0) fprintf(fisierout, "%c\n", current(banda));
        if (strstr(comanda, "WRITE")) IntrQ(coada, comanda);
        if (strcmp(comanda, "MOVE_LEFT") == 0) IntrQ(coada, comanda);
        if (strcmp(comanda, "MOVE_RIGHT") == 0) IntrQ(coada, comanda);
        if (strstr(comanda, "MOVE_LEFT_CHAR")) IntrQ(coada, comanda);
        if (strstr(comanda, "MOVE_RIGHT_CHAR")) IntrQ(coada, comanda);
        if (strstr(comanda, "INSERT_LEFT")) IntrQ(coada, comanda);
        if (strstr(comanda, "INSERT_RIGHT")) IntrQ(coada, comanda);
        if (strcmp(comanda, "EXECUTE") == 0) {
            ExtrQ(coada, comanda);
            if (strstr(comanda, "WRITE")) write(banda, comanda[strlen(comanda)-1]);
            if (strcmp(comanda, "MOVE_LEFT") == 0) {
                TLista2 aux = banda->poz;
                if (move_left(banda)) Push(&stivaUNDO, aux);
            }
            if (strcmp(comanda, "MOVE_RIGHT") == 0) {Push(&stivaUNDO, banda->poz); move_right(banda);}
            if (strstr(comanda, "MOVE_LEFT_CHAR")) move_left_char(banda, comanda[strlen(comanda)-1], fisierout);
            if (strstr(comanda, "MOVE_RIGHT_CHAR")) move_right_char(banda, comanda[strlen(comanda)-1]);
            if (strstr(comanda, "INSERT_LEFT")) insert_left(banda, comanda[strlen(comanda)-1], fisierout);
            if (strstr(comanda, "INSERT_RIGHT")) insert_right(banda, comanda[strlen(comanda)-1]);
        }
        if (strcmp(comanda, "UNDO") == 0) undo(banda, &stivaUNDO, &stivaREDO);
        if (strcmp(comanda, "REDO") == 0) redo(banda, &stivaREDO, &stivaUNDO);
    }
    DistrugeS(&stivaUNDO);
    DistrugeS(&stivaREDO);
    DistrQ(&coada);
    DistrBanda(&banda);
    fclose(fisierin);
    fclose(fisierout);
    return 0;
}
