#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <stdio.h>
#include <string.h>

typedef struct {
	int cod;
	char* nume;
	float medie;
}Student;

typedef struct {
	Student inf;
	struct nodLS* next;
}nodLS;

typedef struct {
	nodLS** vect;
	int nrElem;
}hashT;

int functieHash(hashT tabela, char* nume) {
	return nume[0] % tabela.nrElem;
}

void inserareNodLS(nodLS** cap, Student s) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->next = NULL;

	nou->inf.cod = s.cod;

	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);

	nou->inf.medie = s.medie;

	if (*cap == NULL) {
		*cap = nou;
	}
	else {
		nodLS* temp = *cap;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nou;

	}
}

void inserareHash(hashT tabela, Student s) {
	int poz = functieHash(tabela, s.nume);
	inserareNodLS(&tabela.vect[poz], s);
}

hashT creareHashGoala(int dim) {
	hashT tabela;
	tabela.nrElem = dim;
	tabela.vect = (nodLS**)malloc(dim * sizeof(nodLS*));

	for (int i = 0; i < dim; i++) {
		tabela.vect[i] = NULL;
	}

	return tabela;
}

hashT creeareTabelaDinFisier(int dim) {
	hashT tabela = creareHashGoala(dim);

	FILE* file = fopen("tabelaChaining.txt", "r");

	int n;
	fscanf(file, "%d", &n);
	for (int i = 0; i < n; i++) {
		Student s;
		fscanf(file, "%d", &s.cod);
		char buffer[100];
		fscanf(file, "%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		fscanf(file, "%f", &s.medie);

		inserareHash(tabela, s);
		free(s.nume);
	}
	fclose(file);
	return tabela;
}

void traversareLS(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		printf("Cod = %d, Nume = %s, Medie = %f",
			temp->inf.cod, temp->inf.nume, temp->inf.medie);
		temp = temp->next;
	}
}

void traversareHash(hashT tabela) {
	for (int i = 0; i < tabela.nrElem; i++)
		if (tabela.vect[i] != NULL) {
			printf("\nPozitia = %d\n", i);
			traversareLS(tabela.vect[i]);
		}

}

void dezalocareLS(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		nodLS* aux = temp->next;
		free(temp->inf.nume);
		free(temp);
		temp = aux;
	}
}

void dezalocareHash(hashT tabela) {
	for (int i = 0; i < tabela.nrElem; i++) {
		if (tabela.vect != NULL) {
			dezalocareLS(tabela.vect[i]);
		}
		
	}
	free(tabela.vect);
}

int main() {
	hashT tabela = creeareTabelaDinFisier(10);
	traversareHash(tabela);
	dezalocareHash(tabela);
	return 0;
	
}