#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    int cod;
    char* denumire;
    float pret;
} Produs;

typedef struct nodLS {
    Produs inf;
    struct nodLS* next;
} nodLS;

typedef struct {
    nodLS** vect;
    int nrElem;
} hashT;

int functieHash(hashT tabela, int cheie) {
	return cheie % tabela.nrElem;
}


void inserareNodLS(nodLS** cap, Produs p) {
    nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
    nou->next = NULL;

    nou->inf.cod = p.cod;
    nou->inf.denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
    strcpy(nou->inf.denumire, p.denumire);
    nou->inf.pret = p.pret;

    if (*cap == NULL) {
        *cap = nou;
    } else {
        nodLS* temp = *cap;
        while (temp->next) {
            temp = temp->next;
        }
		temp->next = nou;
    }
    
}

void inserareHash(hashT tabela, Produs p) {
    int poz = functieHash(tabela, p.cod);
    inserareNodLS(&tabela.vect[poz], p);
}

hashT creareTabelaGoala(int dim) {
	hashT tabela;
	tabela.nrElem = dim;
	tabela.vect = (nodLS**)malloc(dim * sizeof(nodLS*));

	for (int i = 0; i < dim; i++) {
		tabela.vect[i] = NULL;
	}

	return tabela;
}

hashT creareTabelaDinFisier(int dim) {
	hashT tabela = creareTabelaGoala(dim);


	FILE* file = fopen("tabelaChaining.txt", "r");

    int n;
	fscanf(file, "%d", &n);
	for (int i = 0; i < n; i++) {
		Produs p;
		fscanf(file, "%d", &p.cod);

		char buffer[20];
		fscanf(file, "%s", buffer);
		p.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.denumire, buffer);

		fscanf(file, "%f", &p.pret);

		inserareHash(tabela, p);
		free(p.denumire);
	}

	fclose(file);
	return tabela;
}

void traversareLS(nodLS* cap) {
    nodLS* temp = cap;
    while (temp) {
        printf("Cod = %d, Denumire = %s, Pret = %f\n",
            temp->inf.cod, temp->inf.denumire, temp->inf.pret);
        temp = temp->next;
    }
}

void traversareHash(hashT tabela) {
    for (int i = 0; i < tabela.nrElem; i++) {
        if (tabela.vect[i] != NULL) {
            printf("\nPozitia = %d\n", i);
            traversareLS(tabela.vect[i]);
        }
    }
}

void dezalocareLS(nodLS* cap) {
    nodLS* temp = cap;
    while (temp) {
        nodLS* aux = temp->next;
        free(temp->inf.denumire);
        free(temp);
        temp = aux;
    }
}

void dezalocareHash(hashT tabela) {
    for (int i = 0; i < tabela.nrElem; i++) {
        if (tabela.vect[i] != NULL)
            dezalocareLS(tabela.vect[i]);
    }
    free(tabela.vect);
}

int main() {
	hashT tabela = creareTabelaDinFisier(10);
	traversareHash(tabela);
	dezalocareHash(tabela);
	return 0;
}