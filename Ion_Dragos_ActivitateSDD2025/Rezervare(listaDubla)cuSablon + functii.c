#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct {
	unsigned int idRezervare;
	char* denumireHotel;
	char* numeClient;
	unsigned char camereRezervate;
	float sumaDePlata;
}Rezervare;

typedef struct {
	Rezervare inf;
	struct nodLS* next;
	struct nodLS* prev;
}nodLS;



void inserareNod(nodLS** cap, nodLS** ultim, Rezervare c) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));

	nou->next = NULL;
	nou->prev = NULL;

	nou->inf.idRezervare = c.idRezervare;

	nou->inf.denumireHotel = (char*)malloc((strlen(c.denumireHotel) + 1) * sizeof(char));
	strcpy(nou->inf.denumireHotel, c.denumireHotel);

	nou->inf.numeClient = (char*)malloc((strlen(c.numeClient) + 1) * sizeof(char));
	strcpy(nou->inf.numeClient, c.numeClient);

	nou->inf.camereRezervate = c.camereRezervate;

	nou->inf.sumaDePlata = c.sumaDePlata;

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

Rezervare citireRezervare(FILE* file) {
	Rezervare p;
	char buffer[100];

	fscanf(file, "%u", &p.idRezervare);

	fscanf(file, "%s", buffer);
	p.denumireHotel = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(p.denumireHotel, buffer);

	fscanf(file, "%s", buffer);
	p.numeClient = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(p.numeClient, buffer);

	fscanf(file, "%hhu", &p.camereRezervate);

	fscanf(file, "%f", &p.sumaDePlata);

	return p;
}

void traversareNod(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		printf("Rezervare = %u, denumireHotel = %s, NumeClient = %s, camereRezervate = %hhu, SumaDePlata = %f",
			temp->inf.idRezervare, temp->inf.denumireHotel, temp->inf.numeClient, temp->inf.camereRezervate, temp->inf.sumaDePlata);
		printf("\n");
		temp = temp->next;
	}
}


void traversareInversa(nodLS* ultim) {
	nodLS* temp = ultim;
	while (temp) {
		printf("Rezervare = %u, denumireHotel = %s, NumeClient = %s, camereRezervate = %hhu, SumaDePlata = %f",
			temp->inf.idRezervare, temp->inf.denumireHotel, temp->inf.numeClient, temp->inf.camereRezervate, temp->inf.sumaDePlata);
		printf("\n");
		temp = temp->prev;
	}
}




//Implementati functia care determina numarul de camere pentru un hotel specificat
void numarCamereHotel(nodLS* cap, char* denumireHotel) {
	nodLS* temp = cap;
	int camere = 0;
	while (temp) {
		if (strcmp(temp->inf.denumireHotel, denumireHotel) == 0) {
			camere += temp->inf.camereRezervate;
		}
		temp = temp->next;
	}
	printf("Numarul total de camere rezervate pentru hotelul %s este: %d\n", denumireHotel, camere);
}



//Implementati functia care aplica un procent de discount pentru un client specificat care a efectuat rezervare la un hotel specificat. Suma nou de plata este actualizata in lista conform procentului de discount.
void discountRezervare(nodLS* cap, char* denumireHotel, char* numeClient, float discount) {
	nodLS* temp = cap;
	while (temp) {
		if (strcmp(temp->inf.numeClient, numeClient) == 0) {
			temp->inf.sumaDePlata -= temp->inf.sumaDePlata * (discount / 100);
			printf("Suma de plata actualizata pentru clientul %s la hotelul %s este: %.2f\n", numeClient, denumireHotel, temp->inf.sumaDePlata);
			return;
		}
		temp = temp->next;
	}
	printf("Rezervarea nu a fost gasita.\n");
}





//Implementati functia care extrage intr-o structura lista diferita/separata toate rezervarile din lista dubla creata mai sus pentru care numarul de camere rezervate este minim 
void extragereRezervariMinim2(nodLS* cap) {
	nodLS* temp = cap;
	nodLS* capNou = NULL, * ultimNou = NULL;

	while (temp) {
		if (temp->inf.camereRezervate >= 2) {
			Rezervare c = temp->inf;
			inserareNod(&capNou, &ultimNou, c);
		}
		temp = temp->next;
	}

	printf("Lista rezervarilor cu minim 2 camere:\n");
	traversareNod(capNou);
}




void dezalocareLista(nodLS* cap) {
	nodLS* temp = cap;
	while (temp != NULL) {
		nodLS* aux = temp->next;
		free(temp->inf.denumireHotel);
		free(temp->inf.numeClient);
		free(temp);
		temp = aux;
	}
}

void main() {
	int n = 5;
	nodLS* cap = NULL, * ultim = NULL;
	FILE* file = fopen("rezervare.txt", "r");

	Rezervare c;
	for (int i = 0; i < n; i++) {
		c = citireRezervare(file);
		inserareNod(&cap, &ultim, c);
		free(c.denumireHotel);
		free(c.numeClient);
	}
	fclose(file);

	printf("Lista rezervarilor:\n");
	traversareNod(cap);
	printf("\n");
	traversareInversa(ultim);
	printf("\n");


	// Afisati numarul total de camere rezervate pentru un hotel specificat
	char denumireHotel[100];
	printf("Introduceti denumirea hotelului pentru care doriti sa aflati numarul de camere rezervate: ");
	scanf("%s", denumireHotel);
	numarCamereHotel(cap, denumireHotel);
	printf("\n");


	// Aplicati un discount pentru un client specificat
	char numeClient[100];
	float discount;
	printf("Introduceti numele clientului pentru care doriti sa aplicati discount: ");
	scanf("%s", numeClient);
	printf("Introduceti discountul dorit: ");
	scanf("%f", &discount);
	discountRezervare(cap, denumireHotel, numeClient, discount);
	printf("\n");

	// Afisati lista rezervarilor dupa aplicarea discountului
	printf("Lista rezervarilor dupa aplicarea discountului:\n");
	traversareNod(cap);
	printf("\n");

	// Extrageti rezervarile cu minim 2 camere
	extragereRezervariMinim2(cap);
	printf("\n");


	dezalocareLista(cap);
	
}