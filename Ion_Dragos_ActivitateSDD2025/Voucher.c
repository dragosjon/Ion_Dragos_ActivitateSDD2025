#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <malloc.h>
#include <stdio.h>

typedef struct {
	unsigned int nrVoucher;
	char* nrBeneficiar;
	char* dataExpirare;
	float valoare;
}Voucher;

typedef struct {

	Voucher inf;
	struct nodLS* next;
	struct nodLS* prev;

}nodLS;

void inserareNod(nodLS** cap, nodLS** ultim, Voucher v) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));

	nou->next = NULL;
	nou->prev = NULL;

	nou->inf.nrVoucher = v.nrVoucher;
	
	nou->inf.nrBeneficiar = (char*)malloc(strlen(v.nrBeneficiar) + 1 * sizeof(char));
	strcpy(nou->inf.nrBeneficiar, v.nrBeneficiar);

	nou->inf.dataExpirare = (char*)malloc(strlen(v.dataExpirare) + 1 * sizeof(char));
	strcpy(nou->inf.dataExpirare, v.dataExpirare);


	nou->inf.valoare = v.valoare;

	if (*cap == NULL) {
		*cap = nou;
		*ultim = nou;
	}
	else {
		nodLS* temp = *cap;
		while (temp->next)

			temp = temp->next;

		temp->next = nou;
		temp->prev = nou;
		*ultim = nou;


	}
	

}


Voucher citireVoucher(FILE* file) {
	Voucher v;
	char buffer[100];

	fscanf(file, "%u", v.nrVoucher);

	fscanf(file, "%s", buffer);
	v.nrBeneficiar = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(v.nrBeneficiar, buffer);

	fscanf(file, "%s", buffer);
	v.dataExpirare = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(v.dataExpirare, buffer);


	fscanf(file, "%f", v.valoare);

	return v;

}

void traversareNod(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		printf("Voucher = %u, Beneficiar = %s, DataExpirare = %s, Valoare = %f",
			temp->inf.nrVoucher, temp->inf.nrBeneficiar, temp->inf.dataExpirare, temp->inf.valoare);
		temp = temp->next;
	}
}


void stergereNod(nodLS** cap, nodLS** ultim, nodLS* sters) {
	if (*cap == sters) {
		*cap = sters->next;
		if (*cap != NULL)
			(*cap)->prev = NULL;
	}
	else if (*ultim == sters) {
		*ultim = sters->prev;
		if (*ultim != NULL)
			(*ultim)->next = NULL;
	}

	else {
		nodLS* urmator = sters->next;
		nodLS* anterior = sters->prev;

		urmator->prev = anterior;
		anterior->next = urmator;
	}

	free(sters->inf.nrBeneficiar);
	free(sters->inf.dataExpirare);
	free(sters);

}

int main() {

}