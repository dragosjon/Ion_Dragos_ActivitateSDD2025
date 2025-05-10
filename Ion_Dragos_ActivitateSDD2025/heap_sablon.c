#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>	


typedef struct {

	int cod;
	char* denumire;
	float prioritate;
}platforma;

typedef struct {
	platforma* vect;
	int nrElem;
}heap;

//filtrare, inserare, extragere, afisare

void filtrare(heap h, int index) {
	int indexMax = index;
	int indexS = index * 2 + 1;
	int indexD = index * 2 + 2;

	if (indexS < h.nrElem) {
		if (h.vect[indexS].prioritate < h.vect[indexMax].prioritate) {
			indexMax = indexS;
		}
	}

	if (indexD < h.nrElem) {
		if (h.vect[indexD].prioritate < h.vect[indexMax].prioritate) {
			indexMax = indexD;
		}
	}

	if (indexMax != index) {

		platforma temp = h.vect[index];
		h.vect[index] = h.vect[indexMax];
		h.vect[indexMax] = temp;

		filtrare(h, indexMax);
	}
}

void afisare(heap h) {

	for (int i = 0; i < h.nrElem; i++) {
		printf("\nPrioritate:%f", h.vect[i].prioritate);
	}
}

void dezalocare(heap h) {
	for (int i = 0; i < h.nrElem; i++) {
		free(h.vect[i].denumire);
	}
	free(h.vect);
}

void inserare(heap* h, platforma p) {

	platforma* vectorNou = (platforma*)malloc(sizeof(platforma) * (h->nrElem + 1));
	for (int i = 0; i < h->nrElem; i++) {
		vectorNou[i] = h->vect[i];
	}

	free(h->vect);
	h->nrElem++;
	vectorNou[h->nrElem - 1] = p;
	h->vect = vectorNou;

	for (int i = (h->nrElem - 1) / 2; i >= 0; i--) {
		filtrare(*h, i);
	}
}

void extragere(heap* h, platforma* p) {

	platforma* vectorNou = (platforma*)malloc(sizeof(platforma) * (h->nrElem - 1));
	platforma temp = h->vect[0];
	h->vect[0] = h->vect[h->nrElem - 1];
	h->vect[h->nrElem - 1] = temp;

	*p = h->vect[h->nrElem - 1];
	h->nrElem--;

	for (int i = 0; i < h->nrElem; i++) {
		vectorNou[i] = h->vect[i];
	}

	free(h->vect);
	h->vect = vectorNou;

	for (int i = (h->nrElem - 1) / 2; i >= 0; i--) {
		filtrare(*h, i);
	}

}

int main() {

	int nrElem;
	FILE* f = fopen("platforma.txt", "r");
	fscanf(f, "%d", &nrElem);
	heap heap;
	heap.nrElem = nrElem;
	heap.vect = (platforma*)malloc(sizeof(platforma) * heap.nrElem);

	char buffer[30];
	for (int i = 0; i < heap.nrElem; i++) {

		fscanf(f, "%d", &heap.vect[i].cod);
		fscanf(f, "%s", buffer);
		heap.vect[i].denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(heap.vect[i].denumire, buffer);

		fscanf(f, "%f", &heap.vect[i].prioritate);

	}

	fclose(f);

	for (int i = ((heap.nrElem / 2) - 1); i >= 0; i--) {
		filtrare(heap, i);
	}

	afisare(heap);

	printf("\n---------------------------------------------------------------------\n");

	platforma p;
	extragere(&heap, &p);

	afisare(heap);
	dezalocare(heap);
}