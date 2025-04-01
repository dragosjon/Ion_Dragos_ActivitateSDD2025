#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <stdio.h>
#include <string.h>

typedef struct {
	int cod;
	char* denumire;
	float pret;
}Produs;

typedef struct {
	Produs inf;
	struct nodLS* next;
	struct nodLS* prev;
}nodLS;

void inserareNodLS(nodLS** cap, nodLS** ultim, Produs p) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));

	nou->next = NULL;
	nou->prev = NULL;

	nou->inf.cod = p.cod;

	nou->inf.denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
	strcpy(nou->inf.denumire, p.denumire);

	nou->inf.pret = p.pret;

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

Produs citireProdus(FILE* file) {
	Produs p;
	char buffer[100];

	fscanf(file, "%d", &p.cod);

	fscanf(file, "%s", buffer);
	p.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(p.denumire, buffer);

	fscanf(file, "%f", &p.pret);

	return p;
}


void traversareNodLS(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		printf("Cod = %d, Denumire = %s, Pret = %d",
			temp->inf.cod, temp->inf.denumire, temp->inf.pret);
		printf("\n");
		temp = temp->next;
	}
}

void traversareInversa(nodLS* ultim) {
	nodLS* temp = ultim;
	while (temp) {
		printf("Cod = %d, Denumire = %s, Pret = %d",
			temp->inf.cod, temp->inf.denumire, temp->inf.pret);
		printf("\n");
		temp = temp->prev;
	}
}


void adaugaProdusInVector(Produs** vector, int* dimensiune, Produs p) {
	*vector = (Produs*)realloc(*vector, (*dimensiune + 1) * sizeof(Produs));
	(*vector)[*dimensiune].cod = p.cod;
	(*vector)[*dimensiune].denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
	strcpy((*vector)[*dimensiune].denumire, p.denumire);
	(*vector)[*dimensiune].pret = p.pret;
	(*dimensiune)++;
}


void salvareProduseInVector(nodLS* cap, Produs** vector, int* dimensiune) {
	nodLS* temp = cap;
	while (temp) {
		adaugaProdusInVector(vector, dimensiune, temp->inf);
		temp = temp->next;
	}
}

void afiseazaVector(Produs* vector, int dimensiune) {
	for (int i = 0; i < dimensiune; i++) {
		printf("Cod = %d, Denumire = %s, Pret = %f\n", vector[i].cod, vector[i].denumire, vector[i].pret);
	}
}

void elibereazaVector(Produs* vector, int dimensiune) {
	for (int i = 0; i < dimensiune; i++) {
		free(vector[i].denumire);
	}
	free(vector);
}

void dezalocare(nodLS* cap) {
	nodLS* temp = cap;
	while (temp->next) {
		nodLS* aux = temp->next;
		free(temp->inf.denumire);
		free(temp);
		temp = aux;
	}
}


int main() {
	
		int n = 3;

		nodLS* cap = NULL, * ultim = NULL;
		Produs* vector = NULL;
		int dimensiune = 0;

		FILE* file = fopen("produs.txt", "r");

		if (!file) {
			printf("Nu s-a putut deschide fișierul.\n");
			return -1;
		}

		Produs p;
		for (int i = 0; i < n; i++) {
			p = citireProdus(file);
			inserareNodLS(&cap, &ultim, p);
			free(p.denumire);
		}
		fclose(file);

		// Traversează și afișează lista
		printf("Traversing the list:\n");
		traversareNodLS(cap);
		printf("\n");

		// Traversează și afișează lista invers
		printf("Traversing the list in reverse:\n");
		traversareInversa(ultim);
		printf("\n");

		// Salvează produsele din lista dublu înlănțuită în vector
		salvareProduseInVector(cap, &vector, &dimensiune);

		// Afișează produsele din vector
		printf("Produsele din vector:\n");
		afiseazaVector(vector, dimensiune);
		printf("\n");

		// Eliberează memoria
		elibereazaVector(vector, dimensiune);
		dezalocare(cap);

		return 0;



}