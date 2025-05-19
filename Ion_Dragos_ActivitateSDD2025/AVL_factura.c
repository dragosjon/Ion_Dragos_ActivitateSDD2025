#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    int nrFactura;
    char* dataEmiterii;
    char* denumireClient; 
    int nrProduseFacturate;
    float valoareFactura;
} Factura;

typedef struct nodAVL {
    Factura inf;
    struct nodAVL* stanga, * dreapta;
    int inaltime;
} nodAVL;

int inaltime(nodAVL* nod) {
    return nod ? nod->inaltime : 0;
}

int maxim(int a, int b) {
    return (a > b) ? a : b;
}

nodAVL* creareNodAVL(Factura c) {
    nodAVL* nou = (nodAVL*)malloc(sizeof(nodAVL));
    nou->inf.nrFactura = c.nrFactura;
    nou->inf.dataEmiterii = (char*)malloc((strlen(c.dataEmiterii) + 1) * sizeof(char));
    strcpy(nou->inf.dataEmiterii, c.dataEmiterii);
    nou->inf.denumireClient = (char*)malloc((strlen(c.denumireClient) + 1) * sizeof(char));
    strcpy(nou->inf.denumireClient, c.denumireClient);
    nou->inf.nrProduseFacturate = c.nrProduseFacturate;
    nou->inf.valoareFactura = c.valoareFactura;
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

nodAVL* inserareAVL(nodAVL* rad, Factura c) {
    if (rad == NULL)
        return creareNodAVL(c);

    if (c.nrFactura < rad->inf.nrFactura)
        rad->stanga = inserareAVL(rad->stanga, c);
    else if (c.nrFactura > rad->inf.nrFactura)
        rad->dreapta = inserareAVL(rad->dreapta, c);
    else
        return rad;

    rad->inaltime = 1 + maxim(inaltime(rad->stanga), inaltime(rad->dreapta));

    int echilibru = factorEchilibru(rad);

    // Rotiri pentru echilibrare
    if (echilibru > 1 && c.nrFactura < rad->stanga->inf.nrFactura)
        return rotireDreapta(rad);

    if (echilibru < -1 && c.nrFactura > rad->dreapta->inf.nrFactura)
        return rotireStanga(rad);

    if (echilibru > 1 && c.nrFactura > rad->stanga->inf.nrFactura) {
        rad->stanga = rotireStanga(rad->stanga);
        return rotireDreapta(rad);
    }

    if (echilibru < -1 && c.nrFactura < rad->dreapta->inf.nrFactura) {
        rad->dreapta = rotireDreapta(rad->dreapta);
        return rotireStanga(rad);
    }

    return rad;
}

void preordineAVL(nodAVL* rad) {
    if (rad != NULL) {
        printf("\nnrFactura=%d, dataEmiterii=%s, DenumireClient = %s, NrProduse=%d, valoareFactura=%.2f",
            rad->inf.nrFactura, rad->inf.dataEmiterii, rad->inf.denumireClient , rad->inf.nrProduseFacturate, rad->inf.valoareFactura);
        preordineAVL(rad->stanga);
        preordineAVL(rad->dreapta);
    }
}

void inordineAVL(nodAVL* rad) {
    if (rad != NULL) {
        inordineAVL(rad->stanga);
        printf("\nnrFactura=%d, dataEmiterii=%s, DenumireClient = %s, NrProduse=%d, valoareFactura=%.2f",
            rad->inf.nrFactura, rad->inf.dataEmiterii, rad->inf.denumireClient, rad->inf.nrProduseFacturate, rad->inf.valoareFactura);
        inordineAVL(rad->dreapta);
    }
}

void postordineAVL(nodAVL* rad) {
    if (rad != NULL) {
        postordineAVL(rad->stanga);
        postordineAVL(rad->dreapta);
        printf("\nnrFactura=%d, dataEmiterii=%s, DenumireClient = %s, NrProduse=%d, valoareFactura=%.2f",
            rad->inf.nrFactura, rad->inf.dataEmiterii, rad->inf.denumireClient, rad->inf.nrProduseFacturate, rad->inf.valoareFactura);
    }
}



void dezalocareAVL(nodAVL* rad) {
    if (rad != NULL) {
        dezalocareAVL(rad->stanga);
        dezalocareAVL(rad->dreapta);
        free(rad->inf.dataEmiterii);
        free(rad->inf.denumireClient);
        free(rad);
    }
}

void main() {
    nodAVL* rad = NULL;
    Factura c;
    int nrFacturi;
    char buffer1[256], buffer2[256];
    FILE* f = fopen("facturi.txt", "r");
    fscanf(f, "%d", &nrFacturi);
    for (int i = 0; i < nrFacturi; i++) {
        
		fscanf(f, "%d", &c.nrFactura);
		fscanf(f, "%s", buffer1);
		c.dataEmiterii = (char*)malloc((strlen(buffer1) + 1) * sizeof(char));
		strcpy(c.dataEmiterii, buffer1);

		fscanf(f, "%s", buffer2);
		c.denumireClient = (char*)malloc((strlen(buffer2) + 1) * sizeof(char));
		strcpy(c.denumireClient, buffer2);

		fscanf(f, "%d", &c.nrProduseFacturate);
		fscanf(f, "%f", &c.valoareFactura);


        
        rad = inserareAVL(rad, c);
       
		free(c.dataEmiterii);
		free(c.denumireClient);

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
