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

void traversare(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		printf("Cod = %d, Denumire = %s, Pret = %f",
			temp->inf.cod, temp->inf.denumire, temp->inf.pret);
		printf("\n");
		temp = temp->next;
	}
}

void traversareInversa(nodLS* ultim) {
	nodLS* temp = ultim;
	while (temp) {
		printf("Cod = %d, Denumire = %s, Pret = %f",
			temp->inf.cod, temp->inf.denumire, temp->inf.pret);
		printf("\n");
		temp = temp->prev;
	}
}

void dezalocare(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		nodLS* aux = temp->next;
		free(temp->inf.denumire);
		free(temp);
		temp = aux;
	}
}

int main() {
	int n = 4;
	nodLS* cap = NULL, * ultim = NULL;

	FILE* file = fopen("produs.txt", "r");

	Produs p;
	for (int i = 0; i < n; i++) {
		p = citireProdus(file);
		inserareNodLS(&cap, &ultim, p);
		free(p.denumire);
	}

	traversare(cap);
	printf("\n");
	traversareInversa(ultim);

	dezalocare(cap);
}