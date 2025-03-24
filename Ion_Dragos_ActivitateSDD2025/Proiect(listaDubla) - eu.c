#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct {
	unsigned int codProiect;
	char* titluProiect;
	char* beneficiar;
	unsigned char nrExecutanti;
	float buget;

} Proiect;

typedef struct {
	Proiect info;
	struct nodLS* next;
	struct nodLS* prev;
}nodLS;

void inserareNodLS(nodLS** cap, nodLS** ultim, Proiect p) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));

	nou->next = NULL;
	nou->prev = NULL;

	nou->info.codProiect = p.codProiect;

	nou->info.titluProiect = (char*)malloc(strlen(p.titluProiect) + 1 * sizeof(char));
	strcpy(nou->info.titluProiect, p.titluProiect);

	nou->info.beneficiar = (char*)malloc(strlen(p.beneficiar) + 1 * sizeof(char));
	strcpy(nou->info.beneficiar, p.beneficiar);

	nou->info.nrExecutanti = p.nrExecutanti;
	nou->info.buget = p.buget;

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


Proiect citireProiect(FILE* file) {
	Proiect p;


	char buffer[100];

	fscanf(file, "%u", &p.codProiect);

	fscanf(file, "%s", buffer);
	p.titluProiect  = (char*)malloc(strlen(buffer) + 1 * sizeof(char));
	strcpy(p.titluProiect, buffer);

	fscanf(file, "%s", buffer);
	p.beneficiar = (char*)malloc(strlen(buffer) + 1 * sizeof(char));
	strcpy(p.beneficiar, buffer);
	
	fscanf(file, "%hhu", &p.nrExecutanti);

	fscanf(file, "%f", &p.buget);



	return p;
	
}

void traversareNod(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		printf("Cod proiect = %u, TitluProiect = %s, Beneficiar = %s, NrExecutanti = %hhu, Buget= %f",
			temp->info.codProiect, temp->info.titluProiect, temp->info.beneficiar, temp->info.nrExecutanti, temp->info.buget);
		printf("\n");
		temp = temp->next;
	}
}

void stergereNod(nodLS** cap, nodLS** ultim, nodLS* sters) {
	if (*cap == NULL) {
		*cap = sters->next;
		if (*cap != NULL) {
			(*cap)->prev = NULL;
		}
	}


	else if (*ultim == NULL) {
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

	free(sters->info.titluProiect);
	free(sters->info.beneficiar);
	free(sters);


}


void stergereNodCod(nodLS** cap, nodLS** ultim, unsigned int cod) {
	nodLS* temp = *cap;
	while (temp) {
		if (temp->info.codProiect == cod) {
			stergereNod(cap, ultim, temp);
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
		printf("Cod proiect = %u, TitluProiect = %s, Beneficiar = %s, NrExecutanti = %hhu, Buget= %f",
			temp->info.codProiect, temp->info.titluProiect, temp->info.beneficiar, temp->info.nrExecutanti, temp->info.buget);
		printf("\n");
		temp = temp->prev;
	}
}

void dezalocare(nodLS* cap) {
	nodLS* temp = cap;
	while (temp)
	{
		free(temp->info.beneficiar);
		free(temp->info.titluProiect);
		nodLS* temp1 = temp;
		temp = temp->prev;
		free(temp1);
	}
}

int main() {
	int n = 5;
	nodLS* cap = NULL, * ultim = NULL;

	FILE* file = fopen("proiect.txt", "r");
	if (file == NULL) {
		printf("Nu s-a putut deschide fisierul!");
		return 1;
	}

	Proiect p;
	for (int i = 0; i < n; i++) {
		p = citireProiect(file);
		inserareNodLS(&cap, &ultim, p);
		free(p.titluProiect);
		free(p.beneficiar);
	}
	fclose(file);

	traversareNod(cap);
	printf("\n");
	traversareInversa(ultim);
	printf("\n");


}