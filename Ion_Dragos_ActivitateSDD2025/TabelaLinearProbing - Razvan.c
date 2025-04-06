#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>


typedef struct {

	int cod;
	char* denumire;
	float pret;
} produs;

//typedef struct {
//
//	produs inf;
//	struct nodLs* next;
//
//}nodLs;


typedef struct {
	produs** vector;
	int size;
} hashT;


int functieDispersie(int cheie, hashT tabela) {
	return cheie % tabela.size;
}

int functieDispersie2(int cheie, hashT tabela) {

}

void inserare(produs* p, hashT tabela) {
	if (tabela.vector != NULL) {

		int pozitie = functieDispersie(p->pret, tabela);

		if (tabela.vector[pozitie] == NULL) {
			tabela.vector[pozitie] = p;
			return;
		}
		else {
			printf("\nS-A PRODUS COLIZIUNE!");
			int index = 1;
			while (tabela.size > (pozitie + index)) {

				pozitie += index;
				if (tabela.vector[pozitie] == NULL) {
					tabela.vector[pozitie] = p;
					return;
				}
				//index++;

			}
			printf("COULD NOT ADD TO TABLE");
		}
	}
}

afisareElement(produs* p) {
	printf("Codul=%d, Denumire=%s, Pret=%5.2f", p->cod, p->denumire, p->pret);
	printf("\n");
}

void traversareTabela(hashT tabela) {
	if (tabela.vector != NULL) {

		for (int i = 0; i < tabela.size; i++) {
			if (tabela.vector[i] != NULL) {
				printf("\nPozitia: %d, ", i);
				afisareElement(tabela.vector[i]);

			}
		}
	}
}

void dezalocareTabela(hashT tabela) {
	if (tabela.vector != NULL) {

		for (int i = 0; i < tabela.size; i++) {
			free(tabela.vector[i]->denumire);
			free(tabela.vector[i]);
		}

		free(tabela.vector);
	}
}

void main() {

	int nrProduse;
	char buffer[30];

	hashT tabela;
	tabela.size = 101;
	tabela.vector = (produs**)malloc(tabela.size * sizeof(produs*));

	for (int i = 0; i < tabela.size; i++) {
		tabela.vector[i] = NULL;
	}


	produs* p;
	FILE* f = fopen("text1.txt", "r");

	if (f == NULL)
		return -1;

	fscanf(f, "%d", &nrProduse);

	for (int i = 0; i < nrProduse; i++) {

		p = (produs*)malloc(sizeof(produs));
		fscanf(f, "%d", &(p->cod));
		fscanf(f, "%s", buffer);
		fscanf(f, "%f", &(p->pret));

		p->denumire = (char*)malloc(((strlen(buffer) + 1) * sizeof(char)));
		strcpy(p->denumire, buffer);

		inserare(p, tabela);
	}

	fclose(f);

	traversareTabela(tabela);
	dezalocareTabela(tabela);


}