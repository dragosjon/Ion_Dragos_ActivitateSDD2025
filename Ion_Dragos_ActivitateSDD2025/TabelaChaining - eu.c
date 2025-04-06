#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
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
	struct nodLS** vect;
	int nrElem;
}hashT;

int functieDispersie(hashT tabela, int cheie) {
	return cheie % tabela.nrElem;
}

int functieDispersie2(hashT tabela, char nume[20]) {
	return nume[0] % tabela.nrElem;
}

void inserareLS(nodLS** capLS, Produs p) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->inf.cod = p.cod;
	nou->inf.denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
	strcpy(nou->inf.denumire, p.denumire);
	nou->inf.pret = p.pret;
	nou->next = NULL;
	if (*capLS == NULL)
		*capLS = nou;
	else
	{
		nodLS* temp = *capLS;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
	}
}

void inserareTabela(hashT tabela, Produs p) {
	int pozitie = functieDispersie2(tabela, p.denumire);
	inserareLS(&tabela.vect[pozitie], p);
}

void traversareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp)
	{
		printf("\nCod = %d, Denumire = %s, Pret = %5.2f",
			temp->inf.cod, temp->inf.denumire, temp->inf.pret);
		temp = temp->next;
	}
}

void traversareHash(hashT tabela) {
	for(int i = 0; i < tabela.nrElem; i++)
		if (tabela.vect[i] != NULL) {
			printf("\nPozitia = %d", i);
			traversareLS(tabela.vect[i]);
		}
}



void dezalocareLS(nodLS* capLS) {
	nodLS* temp = capLS;
	while (temp) {
		nodLS* aux = temp->next;
		free(temp->inf.denumire);
		free(temp);
		temp = aux;
	}
}

void dezalocareHash(hashT tabela) {
	for (int i = 0; i < tabela.nrElem; i++)
		if (tabela.vect[i] != NULL)
			dezalocareLS(tabela.vect[i]);
	free(tabela.vect);
}

int main() { 
	hashT tabela;
	tabela.nrElem = 101;
	tabela.vect = (nodLS**)malloc(tabela.nrElem * sizeof(nodLS*));
	for (int i = 0; i < tabela.nrElem; i++)
		tabela.vect[i] = NULL;

	Produs p;
	int nrProd;
	char buffer[20];
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrProd);
	for (int i = 0; i < nrProd; i++)
	{
		fscanf(f, "%d", &p.cod);
		fscanf(f, "%s", buffer);
		p.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.denumire, buffer);
		fscanf(f, "%f", &p.pret);
		inserareTabela(tabela, p);
		free(p.denumire);
	}
	fclose(f);

	traversareHash(tabela);

	dezalocareHash(tabela);

}