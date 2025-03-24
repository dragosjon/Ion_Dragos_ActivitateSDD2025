#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <malloc.h>
#include <stdio.h>

typedef struct {
	unsigned int idComanda;
	char* statusComanda;
	char* numeClient;
	unsigned char numarProduse;
	float sumaDePlata;
}Comanda;

typedef struct {
	Comanda inf;
	struct nodLS* next;
	struct nodLS* prev;
}nodLS;



void inserareNod(nodLS** cap, nodLS** ultim, Comanda c) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));

	 nou->next = NULL;
	 nou->prev = NULL;

	 nou->inf.idComanda = c.idComanda;

	 nou->inf.statusComanda = (char*)malloc((strlen(c.statusComanda) + 1) * sizeof(char));
	 strcpy(nou->inf.statusComanda, c.statusComanda);

	 nou->inf.numeClient = (char*)malloc((strlen(c.numeClient) + 1) * sizeof(char));
	 strcpy(nou->inf.numeClient, c.numeClient);

	 nou->inf.numarProduse = c.numarProduse;

	 nou->inf.sumaDePlata = c.sumaDePlata;

	 if (*cap == NULL) {
		 *cap = nou;
		 *ultim = nou;
	 }
	 else {
		 nou->prev = *ultim;
		 (*ultim)->next = nou;
		 *ultim = nou;
	 }
	 
}

Comanda citireComanda(FILE* file) {
	Comanda p;
	char buffer[100];

	fscanf(file, "%u", &p.idComanda);

	fscanf(file, "%s", buffer);
	p.statusComanda = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(p.statusComanda, buffer);

	fscanf(file, "%s", buffer);
	p.numeClient = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(p.numeClient, buffer);

	fscanf(file, "%hhu", &p.numarProduse);

	fscanf(file, "%f", &p.sumaDePlata);

	return p;
}

void traversareNod(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		printf("Comanda = %u, StatusComanda = %s, NumeClient = %s, NumarProduse = %hhu, SumaDePlata = %f",
			temp->inf.idComanda, temp->inf.statusComanda, temp->inf.numeClient, temp->inf.numarProduse, temp->inf.sumaDePlata);
		printf("\n");
		temp = temp->next;
	}
}


void traversareInversa(nodLS* ultim) {
	nodLS* temp = ultim;
	while (temp) {
		printf("Comanda = %u, StatusComanda = %s, NumeClient = %s, NumarProduse = %hhu, SumaDePlata = %f",
			temp->inf.idComanda, temp->inf.statusComanda, temp->inf.numeClient, temp->inf.numarProduse, temp->inf.sumaDePlata);
		printf("\n");
		temp = temp->prev;
	}
}

void dezalocareLista(nodLS* cap) {
	nodLS* temp = cap;
	while (temp != NULL) {
		nodLS* aux = temp->next;
		free(temp->inf.statusComanda);
		free(temp->inf.numeClient);
		free(temp);
		temp = aux;
	}
}

void main() {
	int n = 5;
	nodLS* cap = NULL, * ultim = NULL;
	FILE* file = fopen("comanda.txt", "r");

	Comanda c;
	for (int i = 0; i < n; i++) {
		c = citireComanda(file);
		inserareNod(&cap, &ultim, c);
		free(c.statusComanda);
		free(c.numeClient);
	}

	traversareNod(cap);
	printf("\n");
	traversareInversa(ultim);
	printf("\n");

	dezalocareLista(cap);
	fclose(file);
}