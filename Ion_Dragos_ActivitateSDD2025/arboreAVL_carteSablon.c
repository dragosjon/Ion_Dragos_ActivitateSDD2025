a#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    int cod;
    char* titlu;
    int nrAutori;
    float pret;
} carte;

typedef struct nodAVL {
    carte inf;
    struct nodAVL* stanga, * dreapta;
    int inaltime;
} nodAVL;

int inaltime(nodAVL* nod) {
    return nod ? nod->inaltime : 0;
}

int maxim(int a, int b) {
    return (a > b) ? a : b;
}

nodAVL* creareNodAVL(carte c) {
    nodAVL* nou = (nodAVL*)malloc(sizeof(nodAVL));
    nou->inf.cod = c.cod;
    nou->inf.titlu = (char*)malloc((strlen(c.titlu) + 1) * sizeof(char));
    strcpy(nou->inf.titlu, c.titlu);
    nou->inf.nrAutori = c.nrAutori;
    nou->inf.pret = c.pret;
    nou->stanga = nou->dreapta = NULL;
    nou->inaltime = 1;
    return nou;
}

int factorEchilibru(nodAVL* nod) {
    return nod ? inaltime(nod->stanga) - inaltime(nod->dreapta) : 0;
}

nodAVL* rotireDreapta(nodAVL* y) {
    nodAVL* x = y->stanga;
    nodAVL* T2 = x->dreapta;

    x->dreapta = y;
    y->stanga = T2;

    y->inaltime = maxim(inaltime(y->stanga), inaltime(y->dreapta)) + 1;
    x->inaltime = maxim(inaltime(x->stanga), inaltime(x->dreapta)) + 1;

    return x;
}

nodAVL* rotireStanga(nodAVL* x) {
    nodAVL* y = x->dreapta;
    nodAVL* T2 = y->stanga;

    y->stanga = x;
    x->dreapta = T2;

    x->inaltime = maxim(inaltime(x->stanga), inaltime(x->dreapta)) + 1;
    y->inaltime = maxim(inaltime(y->stanga), inaltime(y->dreapta)) + 1;

    return y;
}

nodAVL* inserareAVL(nodAVL* rad, carte c) {
    if (rad == NULL)
        return creareNodAVL(c);

    if (c.cod < rad->inf.cod)
        rad->stanga = inserareAVL(rad->stanga, c);
    else if (c.cod > rad->inf.cod)
        rad->dreapta = inserareAVL(rad->dreapta, c);
    else
        return rad;

    rad->inaltime = 1 + maxim(inaltime(rad->stanga), inaltime(rad->dreapta));

    int echilibru = factorEchilibru(rad);

    // Rotiri pentru echilibrare
    if (echilibru > 1 && c.cod < rad->stanga->inf.cod)
        return rotireDreapta(rad);

    if (echilibru < -1 && c.cod > rad->dreapta->inf.cod)
        return rotireStanga(rad);

    if (echilibru > 1 && c.cod > rad->stanga->inf.cod) {
        rad->stanga = rotireStanga(rad->stanga);
        return rotireDreapta(rad);
    }

    if (echilibru < -1 && c.cod < rad->dreapta->inf.cod) {
        rad->dreapta = rotireDreapta(rad->dreapta);
        return rotireStanga(rad);
    }

    return rad;
}

void preordineAVL(nodAVL* rad) {
    if (rad != NULL) {
        printf("\nCod=%d, Titlu=%s, Nr. autori=%d, Pret=%5.2f",
            rad->inf.cod, rad->inf.titlu, rad->inf.nrAutori, rad->inf.pret);
        preordineAVL(rad->stanga);
        preordineAVL(rad->dreapta);
    }
}

void inordineAVL(nodAVL* rad) {
	if (rad != NULL) {
		inordineAVL(rad->stanga);
		printf("\nCod=%d, Titlu=%s, Nr. autori=%d, Pret=%5.2f",
			rad->inf.cod, rad->inf.titlu, rad->inf.nrAutori, rad->inf.pret);
		inordineAVL(rad->dreapta);
	}
}

void postordineAVL(nodAVL* rad) {
	if (rad != NULL) {
		postordineAVL(rad->stanga);
		postordineAVL(rad->dreapta);
		printf("\nCod=%d, Titlu=%s, Nr. autori=%d, Pret=%5.2f",
			rad->inf.cod, rad->inf.titlu, rad->inf.nrAutori, rad->inf.pret);
	}
}



void dezalocareAVL(nodAVL* rad) {
    if (rad != NULL) {
        dezalocareAVL(rad->stanga);
        dezalocareAVL(rad->dreapta);
        free(rad->inf.titlu);
        free(rad);
    }
}

void main() {
    nodAVL* rad = NULL;
    carte c;
    int nrCarti;
    char buffer[30];
    FILE* f = fopen("carti.txt", "r");
    fscanf(f, "%d", &nrCarti);
    for (int i = 0; i < nrCarti; i++) {
        fscanf(f, "%d", &c.cod);
        fscanf(f, "%s", buffer);
        c.titlu = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(c.titlu, buffer);
        fscanf(f, "%d", &c.nrAutori);
        fscanf(f, "%f", &c.pret);
        rad = inserareAVL(rad, c);
        free(c.titlu);
    }
    fclose(f);

    printf("\n-------preordine AVL----\n");
    preordineAVL(rad);

	printf("\n-------inordine AVL----\n");
	inordineAVL(rad);

	printf("\n-------postordine AVL----\n");
	postordineAVL(rad);




    dezalocareAVL(rad);
}
