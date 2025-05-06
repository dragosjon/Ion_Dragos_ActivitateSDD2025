#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <string.h>
#include <stdio.h>

typedef struct {
	char* denumire;
	float suprafata;
	unsigned char nrAngajati;
	char* program;
}Farmacie;

typedef struct {
	Farmacie inf;
	struct nodLS* next;
	struct nodLS* prev;
}nodLS;

void inserareNodLS(nodLS** cap, nodLS** ultim, Farmacie f) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));

	nou->next = NULL;
	nou->prev = NULL;

	nou->inf.denumire = (char*)malloc((strlen(f.denumire) + 1) * sizeof(char));
	strcpy(nou->inf.denumire, f.denumire);

	nou->inf.suprafata = f.suprafata;

	nou->inf.nrAngajati = f.nrAngajati;

	nou->inf.program = (char*)malloc((strlen(f.program) + 1) * sizeof(char));
	strcpy(nou->inf.program, f.program);

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
		printf("Denumire = %s, Suprafata = %f, NrAngajati = %hhu, Program = %s",
			temp->inf.denumire, temp->inf.suprafata, temp->inf.nrAngajati, temp->inf.program);
		printf("\n");
		temp = temp->next;
	}
	
}

void traversareInversa(nodLS* ultim) {
	nodLS* temp = ultim;
	while (temp) {
		printf("Denumire = %s, Suprafata = %f, NrAngajati = %hhu, Program = %s",
			temp->inf.denumire, temp->inf.suprafata, temp->inf.nrAngajati, temp->inf.program);
		printf("\n");
		temp = temp->prev;
	}
	
}

Farmacie citireFarmacie(FILE* file) {
	Farmacie f;
	char buffer[100];

	fscanf(file, "%s", buffer);
	f.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(f.denumire, buffer);

	fscanf(file, "%f", &f.suprafata);

	fscanf(file, "%hhu", &f.nrAngajati);

	fscanf(file, "%s", buffer);
	f.program = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(f.program, buffer);

	return f;
}

//implementati functia care determina numarul de farmacii din lista de mai sus care sunt deschise la o anumita ora specificata ca parametru de intrare

void afisareFarmaciiDeschiseLaOra(nodLS* cap, int ora) {
	nodLS* temp = cap;
	while (temp) {
		if (temp->inf.nrAngajati > ora) {
			printf("Denumire = %s, Suprafata = %f, NrAngajati = %hhu, Program = %s",
				temp->inf.denumire, temp->inf.suprafata, temp->inf.nrAngajati, temp->inf.program);
			printf("\n");
		}
		temp = temp->next;
	}
}


//implementare functie care determina 2 farmacii cu cea mai mare suprafata a suprafetei

void afisareFarmacieMaxSuprafata(nodLS* cap) {
	nodLS* temp = cap;
	float max1 = 0, max2 = 0;
	char* denumire1 = NULL;
	char* denumire2 = NULL;

	while (temp) {
		if (temp->inf.suprafata > max1) {
			max2 = max1;
			denumire2 = denumire1;
			max1 = temp->inf.suprafata;
			denumire1 = temp->inf.denumire;
		}
		else if (temp->inf.suprafata > max2) {
			max2 = temp->inf.suprafata;
			denumire2 = temp->inf.denumire;
		}
		temp = temp->next;
	}

	printf("Cele mai mari suprafete sunt: %s si %s\n", denumire1, denumire2);
}



//implementare functie care extrage intr-un vector toate farmaciile din lista al caror numar de angajati este mai mic decat valoare specificata ca paraemetru de intrare. functia implementata se apeleaza in main.
void extragereFarmaciiAngajati(nodLS* cap, unsigned char nrAngajati, nodLS** capNou, int* n) {
	nodLS* temp = cap;
	*n = 0;

	while (temp) {
		if (temp->inf.nrAngajati < nrAngajati) {
			inserareNodLS(capNou, capNou, temp->inf);
			(*n)++;
		}
		temp = temp->next;
	}
}



void dezalocare(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		nodLS* aux = temp->next;
		temp = temp->next;
		free(temp->inf.denumire);
		free(temp->inf.program);
		free(temp);
		temp = aux;
	}
}


int main() {
	int n = 3;
	nodLS* cap = NULL, * ultim = NULL;

	FILE* file = fopen("farmacie.txt", "r");

	Farmacie f;
	for (int i = 0; i < n; i++) {
		f = citireFarmacie(file);
		inserareNodLS(&cap, &ultim, f);
		free(f.denumire);
		free(f.program);
	}
	fclose(file);

	traversareNod(cap);
	printf("\n");
	traversareInversa(ultim);
	printf("\n");

	afisareFarmaciiDeschiseLaOra(cap, 2);
	printf("\n");

	
	afisareFarmacieMaxSuprafata(cap);
	printf("\n");

	nodLS* capNou = NULL;
	int nNou = 0;
	extragereFarmaciiAngajati(cap, 5, &capNou, &nNou);
	printf("Farmaciile cu nr angajati < 5 sunt:\n");
	traversareNod(capNou);
	printf("\n");
	//dezalocare lista noua
	
	dezalocare(cap);
	
}