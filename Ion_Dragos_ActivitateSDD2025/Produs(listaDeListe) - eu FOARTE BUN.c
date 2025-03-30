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
}nodLS;

typedef struct {
	nodLS* capLS;
	struct nodLP* next;
}nodLP;

void inserareNodLS(nodLS** capLS, Produs p) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));

	nou->next = NULL;

	nou->inf.cod = p.cod;

	nou->inf.denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
	strcpy(nou->inf.denumire, p.denumire);

	nou->inf.pret = p.pret;

	if (*capLS == NULL) {
		*capLS = nou;
	}
	else {
		nodLS* temp = *capLS;
		while (temp->next) 
			temp = temp->next;
	}
	temp->next = nou;

}

void inserareNodLP(nodLP** capLP, nodLS* capLS) {
	nodLP* nou = (nodLP*)malloc(sizeof(nodLP));
	nou->capLS = capLS;
	nou->next = NULL;	

	if (*capLP == NULL) {
		*capLP = nou;
	}
	else {
		nodLP* temp = *capLP;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nou;
	}
}

void traversareLS(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		printf("Cod = %d, Denumire = %s, Pret = %f",
			temp->inf.cod, temp->inf.denumire, temp->inf.pret);
		printf("\n");
		temp = temp->next;
	}
}

void traversareLP(nodLP* cap) {
	nodLP* temp = cap;
	while (temp){
		printf("\nSublista: ");
		traversareLS(temp->capLS);
		temp = temp->next;

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

void dezalocareLS(nodLS* cap) {
	nodLS* temp = cap;

	while (temp) {
		nodLS* aux = temp->next;
		free(temp->inf.denumire);
		free(temp);
		temp = aux;
	}
}

void dezalocareLP(nodLP* cap) {
	nodLP* temp = cap;

	while (temp) {
		nodLP* aux = temp->next;
		dezalocareLS(temp->capLS);
		free(temp);
		temp = aux;
	}
}


int main() {
	int n = 3;

	nodLP* capLP = NULL;
	nodLS* scumpe = NULL, * ieftine = NULL;

	
	FILE* f = fopen("produs.txt", "r");
	

	Produs p;
	for (int i = 0; i < n; i++) {
		
		p = citireProdus(f);
		
		if (p.pret > 100)
			inserareNodLS(&scumpe, p);
		else
			inserareNodLS(&ieftine, p);
		free(p.denumire);

		
	}


	inserareNodLP(&capLP, scumpe);
	inserareNodLP(&capLP, ieftine);

	traversareLP(capLP);

	
	dezalocareLP(capLP);
}