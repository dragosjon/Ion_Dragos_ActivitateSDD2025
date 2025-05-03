#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

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



void inserareNod(nodLS** cap, nodLS** ultim, Proiect c) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));

	nou->next = NULL;
	nou->prev = NULL;

	nou->inf.codProiect = c.codProiect;

	nou->inf.titluProiect = (char*)malloc((strlen(c.titluProiect) + 1) * sizeof(char));
	strcpy(nou->inf.titluProiect, c.titluProiect);

	nou->inf.beneficiar = (char*)malloc((strlen(c.beneficiar) + 1) * sizeof(char));
	strcpy(nou->inf.beneficiar, c.beneficiar);

	nou->inf.nrExecutanti = c.nrExecutanti;

	nou->inf.bugetAlocat = c.bugetAlocat;

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
	p.titluProiect = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(p.titluProiect, buffer);

	fscanf(file, "%s", buffer);
	p.beneficiar = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(p.beneficiar, buffer);

	fscanf(file, "%hhu", &p.nrExecutanti);

	fscanf(file, "%f", &p.bugetAlocat);

	return p;
}

void traversareNod(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		printf("Proiect = %u, titluProiect = %s, beneficiar = %s, nrExecutanti = %hhu, bugetAlocat = %f",
			temp->inf.codProiect, temp->inf.titluProiect, temp->inf.beneficiar, temp->inf.nrExecutanti, temp->inf.bugetAlocat);
		printf("\n");
		temp = temp->next;
	}
}


void traversareInversa(nodLS* ultim) {
	nodLS* temp = ultim;
	while (temp) {
		printf("Proiect = %u, titluProiect = %s, beneficiar = %s, nrExecutanti = %hhu, bugetAlocat = %f",
			temp->inf.codProiect, temp->inf.titluProiect, temp->inf.beneficiar, temp->inf.nrExecutanti, temp->inf.bugetAlocat);
		printf("\n");
		temp = temp->prev;
	}
}

//Implementati functia care determina fondurile de investitii ale unui beneficiar specificat. Se iau in considerare bugetele alocate pentru proiectele initiale de beneficiarul respectiv, conform datelor din lista dubla creata.

void fonduriBeneficiar(nodLS* cap, char* beneficiar) {
	nodLS* temp = cap;
	float total = 0;
	while (temp) {
		if (strcmp(temp->inf.beneficiar, beneficiar) == 0) {
			total += temp->inf.bugetAlocat;

		}
		temp = temp->next;
	}
	printf("Fondurile de investitii pentru beneficiar %s sunt: %.2f\n", beneficiar, total);
}

//Implementati functia care modifica bugetul alocat in lista creata cu un procent specificat pentru mai multe proiecte incluse intr-un vector de intrate(coduri proiect)
void modificareBuget(nodLS* cap, unsigned int* coduri, int n, float procent) {
	nodLS* temp = cap;
	while (temp) {
		for (int i = 0; i < n; i++) {
			if (temp->inf.codProiect == coduri[i]) {
				temp->inf.bugetAlocat += temp->inf.bugetAlocat * (procent / 100);
				printf("Bugetul alocat pentru proiectul %u a fost modificat la: %.2f\n", temp->inf.codProiect, temp->inf.bugetAlocat);
			}
		}
		temp = temp->next;
	}
}



//Functia care determina proiectele cu un buget peste un nivel specificat. Proiectele identificate, sunt salvate intr-un vector returnat in apelator
Proiect* proiecteBuget(nodLS* cap, float bugetMinim, int* n) {
	nodLS* temp = cap;
	*n = 0;
	Proiect* proiecte = NULL;

	while (temp) {
		if (temp->inf.bugetAlocat > bugetMinim) {
			proiecte = (Proiect*)realloc(proiecte, (*n + 1) * sizeof(Proiect));
			proiecte[*n] = temp->inf;
			(*n)++;
		}
		temp = temp->next;
	}
	return proiecte;
}



--//Implementati functia care determina numarul de camere pentru un hotel specificat










//Comaparare cu functiile din testul cu Rezervare
// 
// 
// 
// 
// 
////Implementati functia care determina numarul de camere pentru un hotel specificat
//void numarCamereHotel(nodLS* cap, char* titluProiect) {
//	nodLS* temp = cap;
//	int camere = 0;
//	while (temp) {
//		if (strcmp(temp->inf.titluProiect, titluProiect) == 0) {
//			camere += temp->inf.nrExecutanti;
//		}
//		temp = temp->next;
//	}
//	printf("Numarul total de camere rezervate pentru hotelul %s este: %d\n", titluProiect, camere);
//}
//
//
//
////Implementati functia care aplica un procent de discount pentru un client specificat care a efectuat Proiect la un hotel specificat. Suma nou de plata este actualizata in lista conform procentului de discount.
//void discountProiect(nodLS* cap, char* titluProiect, char* beneficiar, float discount) {
//	nodLS* temp = cap;
//	while (temp) {
//		if (strcmp(temp->inf.beneficiar, beneficiar) == 0) {
//			temp->inf.bugetAlocat -= temp->inf.bugetAlocat * (discount / 100);
//			printf("Suma de plata actualizata pentru clientul %s la hotelul %s este: %.2f\n", beneficiar, titluProiect, temp->inf.bugetAlocat);
//			return;
//		}
//		temp = temp->next;
//	}
//	printf("Proiecta nu a fost gasita.\n");
//}
//
//
//
//
//
////Implementati functia care extrage intr-o structura lista diferita/separata toate rezervarile din lista dubla creata mai sus pentru care numarul de camere rezervate este minim 
//void extragereRezervariMinim2(nodLS* cap) {
//	nodLS* temp = cap;
//	nodLS* capNou = NULL, * ultimNou = NULL;
//
//	while (temp) {
//		if (temp->inf.nrExecutanti >= 2) {
//			Proiect c = temp->inf;
//			inserareNod(&capNou, &ultimNou, c);
//		}
//		temp = temp->next;
//	}
//
//	printf("Lista rezervarilor cu minim 2 camere:\n");
//	traversareNod(capNou);
//}
//
//


void dezalocareLista(nodLS* cap) {
	nodLS* temp = cap;
	while (temp != NULL) {
		nodLS* aux = temp->next;
		free(temp->inf.titluProiect);
		free(temp->inf.beneficiar);
		free(temp);
		temp = aux;
	}
}

void main() {
	int n = 5;
	nodLS* cap = NULL, * ultim = NULL;
	FILE* file = fopen("proiect.txt", "r");

	Proiect c;
	for (int i = 0; i < n; i++) {
		c = citireProiect(file);
		inserareNod(&cap, &ultim, c);
		free(c.titluProiect);
		free(c.beneficiar);
	}
	fclose(file);

	printf("Lista rezervarilor:\n");
	traversareNod(cap);
	printf("\n");
	traversareInversa(ultim);
	printf("\n");

	//// Afisati fondurile de investitii pentru un beneficiar specificat
	char beneficiar[100];
	printf("Introduceti numele beneficiarului pentru care doriti sa aflati fondurile de investitii: ");
	scanf("%s", beneficiar);
	fonduriBeneficiar(cap, beneficiar);
	printf("\n");

	

	//// Afisati numarul total de camere rezervate pentru un hotel specificat
	//char titluProiect[100];
	//printf("Introduceti denumirea hotelului pentru care doriti sa aflati numarul de camere rezervate: ");
	//scanf("%s", titluProiect);
	//numarCamereHotel(cap, titluProiect);
	//printf("\n");


	//// Aplicati un discount pentru un client specificat
	//char beneficiar[100];
	//float discount;
	//printf("Introduceti numele clientului pentru care doriti sa aplicati discount: ");
	//scanf("%s", beneficiar);
	//printf("Introduceti discountul dorit: ");
	//scanf("%f", &discount);
	//discountProiect(cap, titluProiect, beneficiar, discount);
	//printf("\n");

	//// Afisati lista rezervarilor dupa aplicarea discountului
	//printf("Lista rezervarilor dupa aplicarea discountului:\n");
	//traversareNod(cap);
	//printf("\n");

	//// Extrageti rezervarile cu minim 2 camere
	//extragereRezervariMinim2(cap);
	//printf("\n");


	dezalocareLista(cap);

}