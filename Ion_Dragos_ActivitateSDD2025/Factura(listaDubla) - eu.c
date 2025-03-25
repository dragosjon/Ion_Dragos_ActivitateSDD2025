#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>;

typedef struct {
	unsigned int nrFactura;
	char* dataEmitere;
	char* beneficiar;
	float sumaPlata;
	unsigned int nrZileScadenta;
} Factura;

typedef struct nodLS{
	Factura inf;
	struct nodLS* next;
	struct nodLS* prev;
}nodLS;

void inserareNod(nodLS** cap, nodLS** ultim, Factura f) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));

	nou->next = NULL;
	nou->prev = NULL;

	nou->inf.nrFactura = f.nrFactura;

	nou->inf.dataEmitere = (char*)malloc((strlen(f.dataEmitere) + 1) * sizeof(char));
	strcpy(nou->inf.dataEmitere, f.dataEmitere);

	nou->inf.beneficiar = (char*)malloc((strlen(f.beneficiar) + 1) * sizeof(char));
	strcpy(nou->inf.beneficiar, f.beneficiar);

	nou->inf.sumaPlata = f.sumaPlata;

	nou->inf.nrZileScadenta = f.nrZileScadenta;

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

Factura citireFisier(FILE* file) {
	Factura f;
	char buffer[100];
	
	fscanf(file, "%u", &f.nrFactura);

	fscanf(file, "%s", buffer);
	f.dataEmitere = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(f.dataEmitere, buffer);

	fscanf(file, "%s", buffer);
	f.beneficiar = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(f.beneficiar, buffer);

	fscanf(file, "%f", &f.sumaPlata);

	fscanf(file, "%u", &f.nrZileScadenta);

	return f;
}

void traversareNod(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		printf("NrFactura = %u, Data = %s, Beneficiar = %s, Suma = %.2f, ZileScadente = %u",
			temp->inf.nrFactura, temp->inf.dataEmitere, temp->inf.beneficiar, temp->inf.sumaPlata, temp->inf.nrZileScadenta);
		printf("\n");
		temp = temp->next;
	}
}

void traversareInversa(nodLS* ultim) {
	nodLS* temp = ultim;
	while (temp) {
		printf("NrFactura = %u, Data = %s, Beneficiar = %s, Suma = %.2f, ZileScadente = %u",
			temp->inf.nrFactura, temp->inf.dataEmitere, temp->inf.beneficiar, temp->inf.sumaPlata, temp->inf.nrZileScadenta);
		printf("\n");
		temp = temp->prev;
	}
}

void dezalocareLista(nodLS* cap) {
	nodLS* temp = cap;

	while (temp != NULL) {
		nodLS* aux = temp->next;
		free(temp->inf.beneficiar);
		free(temp->inf.dataEmitere);
		free(temp);
		temp = aux;
	}
}

void main() {
	int n = 7;
	nodLS* cap = NULL, * ultim = NULL;

	FILE* file = fopen("factura.txt", "r");

	Factura f;
	for (int i = 0; i < n; i++) {
		f = citireFisier(file);
		inserareNod(&cap, &ultim, f);
		free(f.beneficiar);
		free(f.dataEmitere);
	}

	traversareNod(cap);
	printf("\n");
	traversareInversa(ultim);
	printf("\n");

	dezalocareLista(cap);
	fclose(file);
}