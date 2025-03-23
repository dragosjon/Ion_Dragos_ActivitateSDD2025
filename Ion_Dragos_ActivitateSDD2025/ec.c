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

typedef struct nodLS {
	Proiect info;
	struct nodLS* next;
	struct nodLS* prev;
} nodLS;

void inserareNodLS(nodLS** cap, nodLS** ultim, Proiect p) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));

	nou->next = NULL;
	nou->prev = NULL;

	nou->info.codProiect = p.codProiect;

	nou->info.titluProiect = (char*)malloc((strlen(p.titluProiect) + 1) * sizeof(char));
	strcpy(nou->info.titluProiect, p.titluProiect);

	nou->info.beneficiar = (char*)malloc((strlen(p.beneficiar) + 1) * sizeof(char));
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
	char titlu[100], beneficiar[100];

	// Citirea corect? a datelor din fi?ier
	fscanf(file, "%u", &p.codProiect);
	fscanf(file, "%s", titlu);
	fscanf(file, "%s", beneficiar);
	fscanf(file, "%hhu", &p.nrExecutanti);
	fscanf(file, "%f", &p.buget);

	// Alocare corect? bazat? pe buffer-ele citite
	p.titluProiect = (char*)malloc((strlen(titlu) + 1) * sizeof(char));
	strcpy(p.titluProiect, titlu);

	p.beneficiar = (char*)malloc((strlen(beneficiar) + 1) * sizeof(char));
	strcpy(p.beneficiar, beneficiar);

	return p;
}

void traversareNod(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		printf("Cod proiect = %u, TitluProiect = %s, Beneficiar = %s, NrExecutanti = %hhu, Buget = %.2f",
			temp->info.codProiect, temp->info.titluProiect, temp->info.beneficiar, temp->info.nrExecutanti, temp->info.buget);
		printf("\n");
		temp = temp->next;
	}
}

void stergereNod(nodLS** cap, nodLS** ultim, nodLS* sters) {
	if (sters == *cap) {
		*cap = sters->next;
		if (*cap != NULL) {
			(*cap)->prev = NULL;
		}
	}
	else if (sters == *ultim) {
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
		nodLS* current = temp;
		temp = temp->next;  // Salv?m nodul urm?tor înainte de a ?terge nodul curent

		if (current->info.codProiect == cod) {
			stergereNod(cap, ultim, current);
			break;
		}
	}
}

void traversareInversa(nodLS* ultim) {
	nodLS* temp = ultim;
	while (temp) {
		printf("Cod proiect = %u, TitluProiect = %s, Beneficiar = %s, NrExecutanti = %hhu, Buget = %.2f",
			temp->info.codProiect, temp->info.titluProiect, temp->info.beneficiar, temp->info.nrExecutanti, temp->info.buget);
		printf("\n");
		temp = temp->prev;
	}
}

void dezalocare(nodLS** cap) {
	nodLS* temp = *cap;
	while (temp) {
		nodLS* temp1 = temp;
		temp = temp->next;  // Trebuie s? mearg? înainte, nu înapoi
		free(temp1->info.beneficiar);
		free(temp1->info.titluProiect);
		free(temp1);
	}
	*cap = NULL;  // Set?m capul la NULL dup? dezalocare
}

int main() {
	int n = 5;  // Avem 5 proiecte în fi?ier
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
		// Nu dezaloca memoria aici, deoarece am copiat-o în noduri
	}
	fclose(file);  // Închide fi?ierul dup? utilizare

	printf("Traversare în ordine direct?:\n");
	traversareNod(cap);
	printf("\nTraversare în ordine invers?:\n");
	traversareInversa(ultim);

	// Eliber?m memoria la final
	dezalocare(&cap);

	return 0;
}