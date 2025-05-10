#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct {

	int cod;
	char* denumire;
	float pret;
} produs;

typedef struct {

	produs inf;
	struct nodCoada* next;

}nodCoada;

void put(nodCoada** prim, nodCoada** ultim, produs p) {

	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));
	nou->next = NULL;

	nou->inf.cod = p.cod;
	nou->inf.pret = p.pret;
	nou->inf.denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
	strcpy(nou->inf.denumire, p.denumire);

	if (*prim == NULL || *ultim == NULL) {
		*prim = nou;
		*ultim = nou;
	}
	else {
		(*ultim)->next = nou;
		*ultim = nou;
	}

}

int get(nodCoada** prim, nodCoada** ultim, produs* p) {

	if (*prim == NULL) {
		*ultim = NULL;
		return -1; // is it ok?
	}

	if (*prim != NULL && *ultim != NULL) {
		p->cod = (*prim)->inf.cod;
		p->pret = (*prim)->inf.pret;
		p->denumire = (char*)malloc(((strlen((*prim)->inf.denumire) + 1) * sizeof(char)));
		strcpy(p->denumire, (*prim)->inf.denumire);



		nodCoada* temp = *prim;
		*prim = (*prim)->next;
		free(temp->inf.denumire);
		free(temp);
		return 0;
	}
}

void afisareCoada(nodCoada* prim) {
	if (prim != NULL) {
		nodCoada* temp = prim;
		while (temp) {
			printf("Codul=%d, Denumire=%s, Pret=%5.2f", temp->inf.cod, temp->inf.denumire, temp->inf.pret);
			printf("\n");
			temp = temp->next;
		}
	}
}

int main() {

	nodCoada* prim = NULL, * ultim = NULL;


	int nr;
	char buffer[20];
	produs p;

	FILE* f = fopen("produs2.txt", "r");
	fscanf(f, "%d", &nr);

	for (int i = 0; i < nr; i++)
	{
		fscanf(f, "%d", &p.cod);
		fscanf(f, "%s", buffer);
		fscanf(f, "%f", &p.pret);

		p.denumire = (char*)malloc(((strlen(buffer) + 1) * sizeof(char)));
		strcpy(p.denumire, buffer);
		put(&prim, &ultim, p);
		free(p.denumire);

	}
	afisareCoada(prim);
}