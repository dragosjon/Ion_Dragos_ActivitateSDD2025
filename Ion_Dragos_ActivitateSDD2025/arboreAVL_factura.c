#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structura pentru factură
typedef struct {
    int numarFactura;
    char* dataEmitere;
    char* denumireClient;
    float valoareFactura;
    int numarProduse;
} Factura;

// Structura pentru nodul AVL
typedef struct nodAVL {
    Factura inf;
    struct nodAVL* stanga, * dreapta;
    int inaltime;
} nodAVL;

// Funcție pentru a obține înălțimea unui nod
int inaltime(nodAVL* nod) {
    return nod ? nod->inaltime : 0;
}

// Funcție pentru a calcula maximul dintre două valori
int maxim(int a, int b) {
    return (a > b) ? a : b;
}

// Funcție pentru a crea un nod AVL
nodAVL* creareNodAVL(Factura f) {
    nodAVL* nou = (nodAVL*)malloc(sizeof(nodAVL));
    nou->inf.numarFactura = f.numarFactura;
    nou->inf.dataEmitere = (char*)malloc((strlen(f.dataEmitere) + 1) * sizeof(char));
    strcpy(nou->inf.dataEmitere, f.dataEmitere);
    nou->inf.denumireClient = (char*)malloc((strlen(f.denumireClient) + 1) * sizeof(char));
    strcpy(nou->inf.denumireClient, f.denumireClient);
    nou->inf.valoareFactura = f.valoareFactura;
    nou->inf.numarProduse = f.numarProduse;
    nou->stanga = nou->dreapta = NULL;
    nou->inaltime = 1;
    return nou;
}

// Funcție pentru a calcula factorul de echilibru
int factorEchilibru(nodAVL* nod) {
    return nod ? inaltime(nod->stanga) - inaltime(nod->dreapta) : 0;
}

// Rotire dreapta
nodAVL* rotireDreapta(nodAVL* y) {
    nodAVL* x = y->stanga;
    nodAVL* T2 = x->dreapta;

    x->dreapta = y;
    y->stanga = T2;

    y->inaltime = maxim(inaltime(y->stanga), inaltime(y->dreapta)) + 1;
    x->inaltime = maxim(inaltime(x->stanga), inaltime(x->dreapta)) + 1;

    return x;
}

// Rotire stânga
nodAVL* rotireStanga(nodAVL* x) {
    nodAVL* y = x->dreapta;
    nodAVL* T2 = y->stanga;

    y->stanga = x;
    x->dreapta = T2;

    x->inaltime = maxim(inaltime(x->stanga), inaltime(x->dreapta)) + 1;
    y->inaltime = maxim(inaltime(y->stanga), inaltime(y->dreapta)) + 1;

    return y;
}

// Funcție pentru inserarea unui nod în arborele AVL
nodAVL* inserareAVL(nodAVL* rad, Factura f) {
    if (rad == NULL)
        return creareNodAVL(f);

    if (f.numarFactura < rad->inf.numarFactura)
        rad->stanga = inserareAVL(rad->stanga, f);
    else if (f.numarFactura > rad->inf.numarFactura)
        rad->dreapta = inserareAVL(rad->dreapta, f);
    else
        return rad;

    rad->inaltime = 1 + maxim(inaltime(rad->stanga), inaltime(rad->dreapta));

    int echilibru = factorEchilibru(rad);

    // Rotiri pentru echilibrare
    if (echilibru > 1 && f.numarFactura < rad->stanga->inf.numarFactura)
        return rotireDreapta(rad);

    if (echilibru < -1 && f.numarFactura > rad->dreapta->inf.numarFactura)
        return rotireStanga(rad);

    if (echilibru > 1 && f.numarFactura > rad->stanga->inf.numarFactura) {
        rad->stanga = rotireStanga(rad->stanga);
        return rotireDreapta(rad);
    }

    if (echilibru < -1 && f.numarFactura < rad->dreapta->inf.numarFactura) {
        rad->dreapta = rotireDreapta(rad->dreapta);
        return rotireStanga(rad);
    }

    return rad;
}

// Funcție pentru traversarea în inordine
void inordineAVL(nodAVL* rad) {
    if (rad != NULL) {
        inordineAVL(rad->stanga);
        printf("\nNumăr Factură=%d, Data=%s, Client=%s, Valoare=%.2f, Produse=%d",
            rad->inf.numarFactura, rad->inf.dataEmitere, rad->inf.denumireClient,
            rad->inf.valoareFactura, rad->inf.numarProduse);
        inordineAVL(rad->dreapta);
    }
}

// Funcție pentru traversarea în preordine
void preordineAVL(nodAVL* rad) {
	if (rad != NULL) {
		printf("\nNumăr Factură=%d, Data=%s, Client=%s, Valoare=%.2f, Produse=%d",
			rad->inf.numarFactura, rad->inf.dataEmitere, rad->inf.denumireClient,
			rad->inf.valoareFactura, rad->inf.numarProduse);
		preordineAVL(rad->stanga);
		preordineAVL(rad->dreapta);
	}
}


// Funcție pentru traversarea în postordine

void postordineAVL(nodAVL* rad) {
	if (rad != NULL) {
		postordineAVL(rad->stanga);
		postordineAVL(rad->dreapta);
		printf("\nNumăr Factură=%d, Data=%s, Client=%s, Valoare=%.2f, Produse=%d",
			rad->inf.numarFactura, rad->inf.dataEmitere, rad->inf.denumireClient,
			rad->inf.valoareFactura, rad->inf.numarProduse);
	}
}


// Funcție pentru dezalocarea arborelui AVL
void dezalocareAVL(nodAVL* rad) {
    if (rad != NULL) {
        dezalocareAVL(rad->stanga);
        dezalocareAVL(rad->dreapta);
        free(rad->inf.dataEmitere);
        free(rad->inf.denumireClient);
        free(rad);
    }
}

// Funcția principală
void main() {
    nodAVL* rad = NULL;
    Factura f;
    int nrFacturi;
    char buffer1[30], buffer2[50];
    FILE* fptr = fopen("facturi.txt", "r");
 

    fscanf(fptr, "%d", &nrFacturi);
    for (int i = 0; i < nrFacturi; i++) {
        fscanf(fptr, "%d", &f.numarFactura);
        fscanf(fptr, "%s", buffer1);
        f.dataEmitere = (char*)malloc((strlen(buffer1) + 1) * sizeof(char));
        strcpy(f.dataEmitere, buffer1);
        fscanf(fptr, "%s", buffer2);
        f.denumireClient = (char*)malloc((strlen(buffer2) + 1) * sizeof(char));
        strcpy(f.denumireClient, buffer2);
        fscanf(fptr, "%f", &f.valoareFactura);
        fscanf(fptr, "%d", &f.numarProduse);
        rad = inserareAVL(rad, f);
        free(f.dataEmitere);
        free(f.denumireClient);
    }
    fclose(fptr);

    printf("\n------- Traversare Inordine AVL -------\n");
    inordineAVL(rad);
	printf("\n------- Traversare Preordine AVL -------\n");
	preordineAVL(rad);
	printf("\n------- Traversare Postordine AVL -------\n");
	postordineAVL(rad);


    dezalocareAVL(rad);
}
