#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <string.h>
#include <stdio.h>

typedef struct {
	unsigned int codProiect;
	char* titluProiect;
	char* beneficiar;
	unsigned char nrExecutanti;
	float bugetAlocat;
}Proiect;

typedef struct {
	Proiect inf;
	struct nodLS* next;
	struct nodLS* prev;
}nodLS;

void inserareNodLS(nodLS** cap, nodLS** ultim, Proiect f) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));

	nou->next = NULL;
	nou->prev = NULL;

	nou->inf.codProiect = f.codProiect;

	nou->inf.beneficiar = (char*)malloc((strlen(f.beneficiar) + 1) * sizeof(char));
	strcpy(nou->inf.beneficiar, f.beneficiar);

	nou->inf.bugetAlocat = f.bugetAlocat;

	nou->inf.nrExecutanti = f.nrExecutanti;

	nou->inf.titluProiect = (char*)malloc((strlen(f.titluProiect) + 1) * sizeof(char));
	strcpy(nou->inf.titluProiect, f.titluProiect);

	if (*cap == NULL) {
		*cap = nou;
		*ultim = nou;
	}
	else {
		nodLS* temp = *cap;
		while (temp->next)
			temp = temp->next;

		temp->next = nou;
		nou->prev = temp;
		*ultim = nou;
	}
}

void traversareNod(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		printf("codProiect = %u ,beneficiar = %s, bugetAlocat = %f, nrExecutanti = %hhu, titluProiect = %s",
			temp->inf.codProiect, temp->inf.beneficiar, temp->inf.bugetAlocat, temp->inf.nrExecutanti, temp->inf.titluProiect);
		printf("\n");
		temp = temp->next;
	}

}

void traversareInversa(nodLS* ultim) {
	nodLS* temp = ultim;
	while (temp) {
		printf("codProiect = %u ,beneficiar = %s, bugetAlocat = %f, nrExecutanti = %hhu, titluProiect = %s",
			temp->inf.codProiect, temp->inf.beneficiar, temp->inf.bugetAlocat, temp->inf.nrExecutanti, temp->inf.titluProiect);
		printf("\n");
		temp = temp->prev;
	}

}

Proiect citireProiect(FILE* file) {
	Proiect f;
	char buffer[100];

	fscanf(file, "%u", &f.codProiect);

	fscanf(file, "%s", buffer);
	f.beneficiar = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(f.beneficiar, buffer);

	fscanf(file, "%f", &f.bugetAlocat);

	fscanf(file, "%hhu", &f.nrExecutanti);

	fscanf(file, "%s", buffer);
	f.titluProiect = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(f.titluProiect, buffer);

	return f;
}

//implementati functia care determina fondurile de investitii ale unui beneficiar specificat

void fonduriInvestitiiBeneficiar(nodLS* cap, char* beneficiar, float* suma) {
	nodLS* temp = cap;
	*suma = 0;

	while (temp) {
		if (strcmp(temp->inf.beneficiar, beneficiar) == 0) {
			*suma += temp->inf.bugetAlocat;
		}
		temp = temp->next;
	}
}


//implementati functia care modifica bugetul alocat cu un procent specificat pentru mai multe proiecte incluse intr un voctor de intrare(coduri proiect)

void modificareBuget(nodLS* cap, unsigned int* coduri, int n, float procent) {
	nodLS* temp = cap;

	while (temp) {
		for (int i = 0; i < n; i++) {
			if (temp->inf.codProiect == coduri[i]) {
				temp->inf.bugetAlocat += temp->inf.bugetAlocat * procent / 100;
			}
		}
		temp = temp->next;
	}
}


//implementati functia care determina proiectele cu un buget alocat peste un nivel specificat. Proiectele identificate sunt salvate intr-un vector returnat in apelator

void proiecteBuget(nodLS* cap, float buget, Proiect** vector, int* n) {
	nodLS* temp = cap;
	*n = 0;

	while (temp) {
		if (temp->inf.bugetAlocat > buget) {
			(*n)++;
		}
		temp = temp->next;
	}

	*vector = (Proiect*)malloc((*n) * sizeof(Proiect));
	temp = cap;
	int index = 0;

	while (temp) {
		if (temp->inf.bugetAlocat > buget) {
			(*vector)[index] = temp->inf;
			index++;
		}
		temp = temp->next;
	}
}



void dezalocare(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		nodLS* aux = temp->next;
		temp = temp->next;
		free(temp->inf.beneficiar);
		free(temp->inf.titluProiect);
		free(temp);
		temp = aux;
	}
}


int main() {
	int n = 5;
	nodLS* cap = NULL, * ultim = NULL;

	FILE* file = fopen("proiect.txt", "r");

	Proiect f;
	for (int i = 0; i < n; i++) {
		f = citireProiect(file);
		inserareNodLS(&cap, &ultim, f);
		free(f.beneficiar);
		free(f.titluProiect);
	}
	fclose(file);

	traversareNod(cap);
	printf("\n");
	traversareInversa(ultim);
	printf("\n");

	//functia care determina fondurile de investitii ale unui beneficiar specificat
	char beneficiar[20] = "Casa";
	float suma = 0;
	fonduriInvestitiiBeneficiar(cap, beneficiar, &suma);
	printf("Suma totala alocata beneficiarului %s este %f\n", beneficiar, suma);

	//functia care modifica bugetul alocat cu un procent specificat pentru mai multe proiecte incluse intr un voctor de intrare(coduri proiect)
	unsigned int coduri[3] = { 1, 2, 3 };
	float procent = 10;
	modificareBuget(cap, coduri, 3, procent);
	traversareNod(cap);
	printf("\n");
	
	//functie care determina proiectele cu un buget alocat peste un nivel specificat. Proiectele identificate sunt salvate intr-un vector returnat in apelator
	printf("Determina proiectele cu bugetul mai mare de 1000\n");
	Proiect* vector = NULL;
	int numarProiecte = 0;
	proiecteBuget(cap, 3000, &vector, &numarProiecte);
	for (int i = 0; i < numarProiecte; i++) {
		printf("codProiect = %u ,beneficiar = %s, bugetAlocat = %f, nrExecutanti = %hhu, titluProiect = %s",
			vector[i].codProiect, vector[i].beneficiar, vector[i].bugetAlocat, vector[i].nrExecutanti, vector[i].titluProiect);
		printf("\n");
	}



	//dezalocare lista noua
	dezalocare(cap);

}