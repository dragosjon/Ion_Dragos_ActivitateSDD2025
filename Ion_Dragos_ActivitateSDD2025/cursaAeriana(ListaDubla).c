#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct {
	unsigned int idCursa;
	char* destinatie;
	char* dataPlecare;
	unsigned char pasageriInregistrati;
} CursaAeriana;

typedef struct nodLs {
	CursaAeriana info;
	struct nodLs* next;
	struct nodLs* prev;
} nodLs;



void inserarenodLs(nodLs** cap, nodLs** ultim, CursaAeriana c) {
	nodLs* nou = (nodLs*)malloc(sizeof(nodLs));
	nou->next = NULL;
	nou->prev = NULL;

	nou->info.idCursa = c.idCursa;

	nou->info.destinatie = (char*)malloc((strlen(c.destinatie) + 1) * sizeof(char));
	strcpy(nou->info.destinatie, c.destinatie);

	nou->info.dataPlecare = (char*)malloc((strlen(c.dataPlecare) + 1) * sizeof(char));
	strcpy(nou->info.dataPlecare, c.dataPlecare);

	nou->info.pasageriInregistrati = c.pasageriInregistrati;

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

CursaAeriana citireFactura(FILE* file) {
	CursaAeriana f;
	char buffer[100];

	fscanf(file, "%u", &f.idCursa);

	fscanf(file, "%s", buffer);
	f.destinatie = (char*)malloc((strlen(buffer) + 1) * sizeof(char));  // Corectat: folosim buffer în loc de f.destinatie
	strcpy(f.destinatie, buffer);

	fscanf(file, "%s", buffer);  // Corectat: folosim %s în loc de %u pentru string
	f.dataPlecare = (char*)malloc((strlen(buffer) + 1) * sizeof(char));  // Corectat: folosim buffer în loc de f.dataPlecare
	strcpy(f.dataPlecare, buffer);  // Corectat: copiem din buffer în loc de f.dataPlecare

	fscanf(file, "%hhu", &f.pasageriInregistrati);

	return f;
}

void traversareNod(nodLs* cap) {
	nodLs* temp = cap;
	while (temp) {
		printf("Id Cursa = %u, Destinatie = %s, DataPlecare = %u, NrPasageriInregistrati = %hhu",
			temp->info.idCursa, temp->info.destinatie, temp->info.dataPlecare, temp->info.pasageriInregistrati);
		printf("\n");
		temp = temp->next;
	}
}

void stergereNod(nodLs** cap, nodLs** ultim, nodLs* sters) {
	if (*cap == sters) {
		*cap = sters->next;
		if (*cap != NULL) 
			(*cap)->prev = NULL;
		
	}

	else if (*ultim == sters) {
		*ultim = sters->prev;
		if (*ultim != NULL) 
			(*ultim)->next = NULL;
		
	}
	

	else {
		nodLs* urmator = sters->next;
		nodLs* anterior = sters->prev;
		urmator->prev = anterior;
		anterior->next = urmator;
	}

		free(sters->info.destinatie);
		free(sters->info.dataPlecare);
		free(sters);
	

}


void stergereNodCod(nodLs** cap, nodLs** ultim, unsigned int cod) {
	nodLs* temp = *cap;
	while (temp) {
		if (temp->info.idCursa == cod) {
			stergereNod(cap, ultim, temp);
			break;
		}
		else {
			temp = temp->next;
		}
	}
}


void traversareInversa(nodLs* ultim) {
	nodLs* temp = ultim;
	while (temp) {
		printf("Id Cursa = %u, Destinatie = %s, DataPlecare = %u, NrPasageriInregistrati = %hhu", 
			temp->info.idCursa, temp->info.destinatie, temp->info.dataPlecare, temp->info.pasageriInregistrati);
		printf("\n");
		temp = temp->prev;
	}
}

void dezalocare(nodLs* cap) {
	nodLs* temp = cap;
	while (temp) {
		free(temp->info.destinatie);
		free(temp->info.dataPlecare);
		nodLs* temp1 = temp;
		temp = temp->prev;
		free(temp1);
	}

}


int main() {

	//cati bytes ocupa structura CursaAeriana
	printf("CursaAeriana ocupa %zu bytes\n", sizeof(void*));

	int n = 3;
	nodLs* cap = NULL, * ultim = NULL;

	FILE* file = fopen("txtCursaAeriana.txt", "r");
	if (file == NULL) {
		printf("Nu s-a putut deschide fisierul!\n");
		return 1;
	}

	CursaAeriana f;
	for (int i = 0; i < n; i++) {
		f = citireFactura(file);
		inserarenodLs(&cap, &ultim, f);
		free(f.destinatie);
		free(f.dataPlecare);
	}

	traversareNod(cap);
	printf("\n");
	traversareInversa(ultim);
	printf("\n");
	
}