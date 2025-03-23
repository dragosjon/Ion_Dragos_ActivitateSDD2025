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
		nou->prev = *ultim;
		(*ultim)->next = nou;
		*ultim = nou;
	}
	

}


Voucher citireVoucher(FILE* file) {
	Voucher v;
	char buffer[100];

	fscanf(file, "%u", &v.nrVoucher);

	fscanf(file, "%s", buffer);
	v.nrBeneficiar = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(v.nrBeneficiar, buffer);

	fscanf(file, "%s", buffer);
	v.dataExpirare = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(v.dataExpirare, buffer);


	fscanf(file, "%f", &v.valoare);

	return v;

}

void traversareNod(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		printf("Voucher = %u, Beneficiar = %s, DataExpirare = %s, Valoare = %f",
			temp->inf.nrVoucher, temp->inf.nrBeneficiar, temp->inf.dataExpirare, temp->inf.valoare);
		printf("\n");
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

	return;
}

void stergereNodCod(nodLS** cap, nodLS** ultim, unsigned int cod) {
	nodLS* sters = NULL;
	nodLS* temp = *cap;

	while (temp) {
		if (temp->inf.nrVoucher == cod) {
			sters = temp;
			stergereNod(cap, ultim, sters);
			break;
		}
		else {
			temp = temp->next;
		}
	}
}

void traversareInversa(nodLS* ultim) {
	nodLS* temp = ultim;
	while (temp) {
		printf("Voucher = %u, Beneficiar = %s, DataExpirare = %s, Valoare = %f",
			temp->inf.nrVoucher, temp->inf.nrBeneficiar, temp->inf.dataExpirare, temp->inf.valoare);
		printf("\n");
		temp = temp->prev;
	
	}
}


void dezalocare(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		free(temp->inf.dataExpirare);
		free(temp->inf.nrBeneficiar);
		nodLS* temp1 = temp;
		temp = temp->next;
		free(temp1);
	}
}

int main() {
	int n = 5;
	nodLS* cap = NULL, * ultim = NULL;

	FILE* file = fopen("voucher.txt", "r");


	Voucher v;
	for (int i = 0; i < n; i++) {
		v = citireVoucher(file);
		inserareNod(&cap, &ultim, v);
		free(v.dataExpirare);
		free(v.nrBeneficiar);
	}

	traversareNod(cap);
	printf("\n");
	traversareInversa(ultim);
	printf("\n");
	


	dezalocare(cap);

}