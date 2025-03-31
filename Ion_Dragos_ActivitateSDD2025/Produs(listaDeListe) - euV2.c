#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <string.h>
#include <stdio.h>

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

	nou->inf.denumire = (char*)malloc((strlen(sizeof(p.denumire) + 1) * sizeof(char));
	strcpy(nou->inf.denumire, p.denumire);

	nou->inf.pret = p.pret;

	if (*capLS == NULL) {
		*capLS = nou;
	}
	else {
		nodLS* temp = *capLS;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nou;
	}
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