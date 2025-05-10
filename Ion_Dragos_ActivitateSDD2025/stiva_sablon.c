#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct {

	int cod;
	char* denumire;
	float pret;
} produs;

typedef struct {

	produs inf;
	struct nodStiva* next;

}nodStiva;


void push(nodStiva** varf, produs p) {

	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->next = NULL;

	nou->inf.cod = p.cod;
	nou->inf.pret = p.pret;
	nou->inf.denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
	strcpy(nou->inf.denumire, p.denumire);

	if (*varf == NULL) {
		*varf = nou;
	}
	else {
		nou->next = *varf;
		*varf = nou;
	}
}

int pop(nodStiva** varf, produs* p) {

	nodStiva* vf = *varf;
	if (*varf == NULL)
		return -1;

	p->cod = vf->inf.cod;
	p->pret = vf->inf.pret;
	p->denumire = (char*)malloc(((strlen(vf->inf.denumire) + 1) * sizeof(char)));
	strcpy(p->denumire, vf->inf.denumire);

	nodStiva* temp = *varf;
	*varf = (*varf)->next;
	free(temp->inf.denumire);
	free(temp);
	return 0;


}

void afisareStiva(nodStiva* varf) {

	nodStiva* temp = varf;
	while (temp) {
		printf("Codul=%d, Denumire=%s, Pret=%5.2f", temp->inf.cod, temp->inf.denumire, temp->inf.pret);
		printf("\n");
		temp = temp->next;
	}
}

int main() {

	int nr;
	nodStiva* varf = NULL;
	char buffer[30];
	produs p;
	FILE* f = fopen("produs2.txt", "r");
	fscanf(f, "%d", &nr);

	for (int i = 0; i < nr; i++)
	{
		fscanf(f, "%d", &p.cod);
		fscanf(f, "%s", buffer);
		fscanf(f, "%f", &p.pret);

		p.denumire = (char*)malloc(((strlen(buffer) + 1) * sizeof(char)));
		strcpy(p.denumire, buffer);
		push(&varf, p);
		free(p.denumire);

	}
	afisareStiva(varf);

}