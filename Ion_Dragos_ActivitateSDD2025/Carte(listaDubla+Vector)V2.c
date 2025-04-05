#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <stdio.h>
#include <string.h>

typedef struct {
	int cod; //4B
	char* titlu; //4B
	float* vectPreturi; //4B
	int nrPreturi;
}Carte;

typedef struct {
	Carte inf;
	struct nodLS* next;
	struct nodLS* prev;
}nodLS;

void inserareNodLS(nodLS** cap, nodLS** ultim, Carte c) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));

	nou->next = NULL;
	nou->prev = NULL;

	nou->inf.cod = c.cod;

	nou->inf.titlu = (char*)malloc((strlen(c.titlu) + 1) * sizeof(char));
	strcpy(nou->inf.titlu, c.titlu);

	nou->inf.nrPreturi = c.nrPreturi;

	nou->inf.vectPreturi = (float*)malloc(c.nrPreturi * sizeof(float));
	for (int i = 0; i < c.nrPreturi; i++) {
		nou->inf.vectPreturi[i] = c.vectPreturi[i];
	}


	if (*cap == NULL) {
		*cap = nou;
		*ultim = nou;
	}
	else {
		nodLS* temp = *cap;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
		nou->prev = temp;
		*ultim = nou;
	}
}


void traversareNodLS(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		printf("\nCod = %d, Titlu = %s, NrPreturi = %d",
			temp->inf.cod, temp->inf.titlu, temp->inf.nrPreturi);
		for (int i = 0; i < temp->inf.nrPreturi; i++) {
			printf("\nPreturi = %f", temp->inf.vectPreturi[i]);
		}
		printf("\n");
		temp = temp->next;
	}
}

void traversareInversa(nodLS* ultim) {
	nodLS* temp = ultim;
	while (temp) {
		printf("\nCod = %d, Titlu = %s, NrPreturi = %d",
			temp->inf.cod, temp->inf.titlu, temp->inf.nrPreturi);
		for (int i = 0; i < temp->inf.nrPreturi; i++) {
			printf("\nPreturi = %f", temp->inf.vectPreturi[i]);
		}
		printf("\n");
		temp = temp->prev;
	}
}

Carte citireCarte(FILE* file) {
	Carte c;
	char buffer[100];

	fscanf(file, "%d", &c.cod);

	fscanf(file, "%s", buffer);
	c.titlu = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(c.titlu, buffer);

	fscanf(file, "%d", &c.nrPreturi);

	c.vectPreturi = (float*)malloc(c.nrPreturi* sizeof(float));
	for (int i = 0; i < c.nrPreturi; i++) {
		fscanf(file, "%f", &c.vectPreturi[i]);
	}


	return c;
}

void salvareCartiInVector(nodLS* cap, Carte* vect, int* n) {
	nodLS* temp = cap;
	while (temp) {
		vect[*n] = temp->inf;
		(*n)++;
		temp = temp->next;
	}
}

void citireCartiDinVector(Carte* vect, int n, int limit) {
	for (int i = 0; i < n && i < limit; i++) {
		printf("\nCod = %d, Titlu = %s, NrPreturi = %d",
			vect[i].cod, vect[i].titlu, vect[i].nrPreturi);

		for(int i = 0; i < vect[i].nrPreturi; i++)
			printf("Preturi = %f", vect[i].vectPreturi[i]);
		printf("\n");
	}
}

void dezalocare(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		nodLS* aux = temp->next;
		temp = temp->next;
		free(temp->inf.titlu);
		free(temp->inf.vectPreturi);
		free(temp);
		temp = aux;
	}
}

int main() {
	int n = 3;
	nodLS* cap = NULL, * ultim = NULL;

	FILE* file = fopen("carte.txt", "r");

	Carte c;

	for (int i = 0; i < n; i++) {
		c = citireCarte(file);
		inserareNodLS(&cap, &ultim, c);
		free(c.titlu);
		free(c.vectPreturi);
	}
	fclose(file);

	traversareNodLS(cap);
	printf("\n");
	traversareInversa(ultim);


	printf("\n------------VECTOR---------------\n");
	Carte* vect = (Carte*)malloc(n * sizeof(Carte));
	int nr = 0;
	salvareCartiInVector(cap, vect, &nr);
	citireCartiDinVector(vect, nr, 1);

	dezalocare(cap);
}