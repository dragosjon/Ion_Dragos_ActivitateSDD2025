#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <string.h>
#include <stdio.h>

typedef struct {
	char* denumire;
	float suprafata;
	unsigned char nrAngajati;
	char* program;
}Farmacie;

typedef struct {
	Farmacie inf;
	struct nodLS* next;
	struct nodLS* prev;
}nodLS;

void inserareNodLS(nodLS** cap, nodLS** ultim, Farmacie f) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));

	nou->next = NULL;
	nou->prev = NULL;

	nou->inf.denumire = (char*)malloc((strlen(f.denumire) + 1) * sizeof(char));
	strcpy(nou->inf.denumire, f.denumire);

	nou->inf.suprafata = f.suprafata;

	nou->inf.nrAngajati = f.nrAngajati;

	nou->inf.program = (char*)malloc((strlen(f.program) + 1) * sizeof(char));
	strcpy(nou->inf.program, f.program);

	if (*cap == NULL) {
		*cap = nou;
		*ultim = nou;
	}
	else {
		nodLS* temp = *cap;
		while (temp->next) {
			temp = temp->next;
			temp->next = nou;
			nou->prev = temp;
			*ultim = nou;
		}
	}
}

void traversareNod(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		printf("Denumire = %s, Suprafata = %f, NrAngajati = %hhu, Program = %s",
			temp->inf.denumire, temp->inf.suprafata, temp->inf.nrAngajati, temp->inf.program);
		printf("\n");
	}
	temp = temp->next;
}

void traversareInversa(nodLS* ultim) {
	nodLS* temp = ultim;
	while (temp) {
		printf("Denumire = %s, Suprafata = %f, NrAngajati = %hhu, Program = %s",
			temp->inf.denumire, temp->inf.suprafata, temp->inf.nrAngajati, temp->inf.program);
		printf("\n");
	}
	temp = temp->prev;
}

Farmacie citireFarmacie(FILE* file) {
	Farmacie f;
	char buffer[100];

	fscanf(file, "%s", buffer);
	f.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(f.denumire, buffer);

	fscanf(file, "%f", &f.suprafata);

	fscanf(file, "%hhu", &f.nrAngajati);

	fscanf(file, "%s", buffer);
	f.program = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(f.program, buffer);

	return f;
}

void dezalocare(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		nodLS* aux = temp->next;
		temp = temp->next;
		free(temp->inf.denumire);
		free(temp->inf.program);
		free(temp);
		temp = aux;
	}
}


int main() {
	int n = 1;
	nodLS* cap = NULL, * ultim = NULL;

	FILE* file = fopen("farmacie.txt", "r");

	Farmacie f;
	for (int i = 0; i < n; i++) {
		f = citireFarmacie(file);
		inserareNodLS(&cap, &ultim, f);
		free(f.denumire);
		free(f.program);
	}
	fclose(file);

	traversareNod(cap);
	printf("\n");
	traversareInversa(ultim);
	printf("\n");

	dezalocare(cap);
	
}