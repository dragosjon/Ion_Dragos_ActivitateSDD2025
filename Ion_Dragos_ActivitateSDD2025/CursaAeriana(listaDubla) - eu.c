#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <malloc.h>
#include <stdio.h>

typedef struct {
	unsigned int idCursa;
	char* destinatie;
	char* dataPlecare;
	unsigned char pasageriInregistrati;
}CursaAeriana;

typedef struct {
	CursaAeriana inf;
	struct nodLS* next;
	struct nodLS* prev;
}nodLS;

void inserareNodLS(nodLS** cap, nodLS** ultim, CursaAeriana c) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));

	nou->next = NULL;
	nou->prev = NULL;

	nou->inf.idCursa = c.idCursa;
	
	nou->inf.destinatie = (char*)malloc((strlen(c.destinatie) + 1) * sizeof(char));
	strcpy(nou->inf.destinatie, c.destinatie);

	nou->inf.dataPlecare = (char*)malloc((strlen(c.dataPlecare) + 1) * sizeof(char));
	strcpy(nou->inf.dataPlecare, c.dataPlecare);

	nou->inf.pasageriInregistrati = c.pasageriInregistrati;

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

CursaAeriana citireCursaAeriana(FILE* file) {
	CursaAeriana c;
	char buffer[100];

	fscanf(file, "%u", &c.idCursa);

	fscanf(file, "%s", buffer);
	c.destinatie = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(c.destinatie, buffer);

	fscanf(file, "%s", buffer);
	c.dataPlecare = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(c.dataPlecare, buffer);

	fscanf(file, "%hhu", &c.pasageriInregistrati);

	return c;
}

void traversareNod(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		printf("IdCursa = %u, Destinatie = %s, DataPlecare = %s, PasageriInregistrati = %hhu",
			temp->inf.idCursa, temp->inf.destinatie, temp->inf.dataPlecare, temp->inf.pasageriInregistrati);
		temp = temp->next;
	}
}

void traversareInversaNod(nodLS* ultim) {
	nodLS* temp = ultim;
	while (temp) {
		printf("IdCursa = %u, Destinatie = %s, DataPlecare = %s, PasageriInregistrati = %hhu",
			temp->inf.idCursa, temp->inf.destinatie, temp->inf.dataPlecare, temp->inf.pasageriInregistrati);
		temp = temp->prev;
	}
}

void dezalocare(nodLS* cap) {
	nodLS* temp = cap;
	while (temp != NULL) {
		nodLS* aux = temp->next;
		free(temp->inf.destinatie);
		free(temp->inf.dataPlecare);
		free(temp);
		temp = aux;
	}
}

int main() {

}