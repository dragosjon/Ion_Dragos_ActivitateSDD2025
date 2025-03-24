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

	fscanf(file, "%d", buffer);
	p.statusComanda = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(p.statusComanda, buffer);

	fscanf(file, "%d", buffer);
	p.numeClient = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(p.numeClient, buffer);

	fscanf(file, "%hhu", &p.numarProduse);

	fscanf(file, "%f", &p.sumaDePlata);

	return p;
}

void traversareNod(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		printf("Comanda = %u, StatusComanda = %d, NumeClient = %d, NumarProduse = %hhu, SumaDePlata = %f",
			temp->inf.idComanda, temp->inf.statusComanda, temp->inf.numeClient, temp->inf.numarProduse, temp->inf.sumaDePlata);
		printf("\n");
		temp = temp->next;
	}
}

void stergereNod(nodLS** cap, nodLS** ultim, nodLS* sters) {
	if (*cap == sters) {
		*cap = sters->next;
		if (*cap != NULL) {
			(*cap)->prev = NULL;
		}
	}

	else if (*ultim == sters) {
		*ultim = sters->prev;
		if (*ultim != NULL) {
			(*ultim)->next = NULL;
		}
	}

	else {
		nodLS* urmator = sters->next;
		nodLS* anterior = sters->prev;
		urmator->prev = anterior;
		anterior->next = urmator;
	}

	free(sters->inf.statusComanda);
	free(sters->inf.numeClient);
	free(sters);
}

