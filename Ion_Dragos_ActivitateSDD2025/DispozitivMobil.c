#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct DispozitivMobil DispozitivMobil;
struct DispozitivMobil {
	unsigned int idDispozitiv;
	char* sistemOperare;
	float pret;
	char* defecte;
	unsigned int nrZileInService;
};

typedef struct CoadaPrioritati CoadaPrioritati;
struct CoadaPrioritati {
	DispozitivMobil** arr;
	unsigned int size;
};

typedef struct NodStiva NodStiva;
struct NodStiva {
	NodStiva* next;
	DispozitivMobil* dispozitiv;
};

char* copiazaString(const char* str) {
	char* newStr = (char*)malloc(sizeof(char) * (1 + strlen(str)));
	strcpy(newStr, str);

	return newStr;
}

DispozitivMobil* citesteNextDispozitiv(FILE* fisier) {
	DispozitivMobil* dispozitiv = (DispozitivMobil*)malloc(sizeof(DispozitivMobil));
	char buffer[256];

	fscanf(fisier, "%u", &dispozitiv->idDispozitiv);
	fscanf(fisier, "%s", buffer);
	dispozitiv->sistemOperare = copiazaString(buffer);
	fscanf(fisier, "%f", &dispozitiv->pret);
	fscanf(fisier, "%s", buffer);
	dispozitiv->defecte = copiazaString(buffer);
	fscanf(fisier, "%u", &dispozitiv->nrZileInService);

	return dispozitiv;
}

unsigned int parinteHeap(unsigned int i) {
	return i != 0 ? (i - 1) / 2 : 0;
}

unsigned int stangaHeap(unsigned int i) {
	return 2 * i + 1;
}

unsigned int dreaptaHeap(unsigned int i) {
	return 2 * i + 2;
}

int conditieHeapify(DispozitivMobil* rad, DispozitivMobil* cand) {
	return rad->nrZileInService < cand->nrZileInService;
}

void swap(DispozitivMobil** arr, unsigned int i, unsigned int j) {
	DispozitivMobil* temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void maxHeapify(CoadaPrioritati* coadaPrioritati, unsigned int i) {
	if (!coadaPrioritati) {
		return;
	}

	unsigned int pozStanga = stangaHeap(i), pozDreapta = dreaptaHeap(i);
	unsigned int pozMax = i;

	if (pozStanga < coadaPrioritati->size && conditieHeapify(coadaPrioritati->arr[pozMax], coadaPrioritati->arr[pozStanga])) {
		pozMax = pozStanga;
	}
	if (pozDreapta < coadaPrioritati->size && conditieHeapify(coadaPrioritati->arr[pozMax], coadaPrioritati->arr[pozDreapta])) {
		pozMax = pozDreapta;
	}

	if (pozMax != i) {
		swap(coadaPrioritati->arr, i, pozMax);
		maxHeapify(coadaPrioritati, pozMax);
	}
}

CoadaPrioritati* creazaCoadaPrioritatiDinFisier(const char* numeFisier) {
	FILE* fisier = fopen(numeFisier, "r");

	unsigned int nrDispozitive;
	fscanf(fisier, "%u", &nrDispozitive);

	DispozitivMobil** arrDispozitive = (DispozitivMobil**)malloc(sizeof(DispozitivMobil*) * nrDispozitive);
	for (int i = 0; i < nrDispozitive; ++i) {
		arrDispozitive[i] = citesteNextDispozitiv(fisier);
	}
	fclose(fisier);

	CoadaPrioritati* coadaPrioritati = (CoadaPrioritati*)malloc(sizeof(CoadaPrioritati));
	coadaPrioritati->size = nrDispozitive;
	coadaPrioritati->arr = arrDispozitive;

	for (int i = parinteHeap(coadaPrioritati->size); i >= 0; --i) {
		maxHeapify(coadaPrioritati, i);
	}

	return coadaPrioritati;
}

void afisareDispozitiv(const DispozitivMobil* dispozitiv) {
	if (dispozitiv == NULL) {
		return;
	}

	printf("\n");
	printf("Id dispozitiv: %u \n", dispozitiv->idDispozitiv);
	printf("Sistem operare: %s \n", dispozitiv->sistemOperare);
	printf("Pret: %.2f \n", dispozitiv->pret);
	printf("Defecte: %s \n", dispozitiv->defecte);
	printf("Nr zile in service: %u \n", dispozitiv->nrZileInService);
	printf("\n");
}

void afisareCoadaPrioritati(CoadaPrioritati* coadaPrioritati) {
	printf("\nAfisare dispozitive (total %u)\n", coadaPrioritati->size);
	for (int i = 0; i < coadaPrioritati->size; ++i) {
		afisareDispozitiv(coadaPrioritati->arr[i]);
	}
	printf("\n");
}

unsigned int obtineNrDispozitiveDupaOs(CoadaPrioritati* coadaPrioritati, const char* os) {
	unsigned int nrDispozitive = 0;
	for (unsigned int i = 0; i < coadaPrioritati->size; ++i) {
		if (0 == strcmp(os, coadaPrioritati->arr[i]->sistemOperare)) {
			++nrDispozitive;
		}
	}

	return nrDispozitive;
}

void actualizeazaDefecteDispozitiv(CoadaPrioritati* coadaPrioritati, unsigned int idDispozitiv, const char* newDefecte) {
	for (unsigned int i = 0; i < coadaPrioritati->size; ++i) {
		if (idDispozitiv == coadaPrioritati->arr[i]->idDispozitiv) {
			free(coadaPrioritati->arr[i]->defecte);
			coadaPrioritati->arr[i]->defecte = copiazaString(newDefecte);
			return;
		}
	}
}

void dezalocareDispozitiv(DispozitivMobil* dispozitiv) {
	if (dispozitiv->sistemOperare) {
		free(dispozitiv->sistemOperare);
	}
	if (dispozitiv->defecte) {
		free(dispozitiv->defecte);
	}

	free(dispozitiv);
}

void dezalocareHeap(CoadaPrioritati* coadaPrioritati) {
	for (int i = 0; i < coadaPrioritati->size; ++i) {
		dezalocareDispozitiv(coadaPrioritati->arr[i]);
	}
	free(coadaPrioritati->arr);
	free(coadaPrioritati);
}

DispozitivMobil* copiazaDispozitiv(DispozitivMobil* org) {
	DispozitivMobil* copieDispozitiv = (DispozitivMobil*)malloc(sizeof(DispozitivMobil));
	copieDispozitiv->idDispozitiv = org->idDispozitiv;
	copieDispozitiv->pret = org->pret;
	copieDispozitiv->nrZileInService = org->nrZileInService;
	copieDispozitiv->defecte = copiazaString(org->defecte);
	copieDispozitiv->sistemOperare = copiazaString(org->sistemOperare);

	return copieDispozitiv;
}

DispozitivMobil* popCoadaPrioritati(CoadaPrioritati* coadaPrioritati) {
	DispozitivMobil* dispozitivMaxim = copiazaDispozitiv(coadaPrioritati->arr[0]);

	swap(coadaPrioritati->arr, 0, coadaPrioritati->size - 1);
	dezalocareDispozitiv(coadaPrioritati->arr[coadaPrioritati->size - 1]);
	coadaPrioritati->size--;

	maxHeapify(coadaPrioritati, 0);

	return dispozitivMaxim;
}

void testHeapExtrageMax(CoadaPrioritati* coadaPrioritati, unsigned int nrIteratii) {
	while (coadaPrioritati->size && nrIteratii) {
		DispozitivMobil* maxim1 = popCoadaPrioritati(coadaPrioritati);
		printf("\nA fost extras elementul cu nrZile = %u \n", maxim1->nrZileInService);
		dezalocareDispozitiv(maxim1);
		--nrIteratii;
	}
}

NodStiva* creareNod(DispozitivMobil* dispozitiv, NodStiva* next) {
	NodStiva* nodStiva = (NodStiva*)malloc(sizeof(NodStiva));
	nodStiva->next = next;
	nodStiva->dispozitiv = dispozitiv;

	return nodStiva;
}

NodStiva* pushStiva(NodStiva* head, DispozitivMobil* dispozitiv) {
	NodStiva* nodNou = creareNod(dispozitiv, head);

	return nodNou;
}

CoadaPrioritati* copiazaCoadaPrioritati(CoadaPrioritati* coadaPrioritati) {
	CoadaPrioritati* coadaCopie = (CoadaPrioritati*)malloc(sizeof(CoadaPrioritati));

	coadaCopie->size = coadaPrioritati->size;
	coadaCopie->arr = (DispozitivMobil**)malloc(sizeof(DispozitivMobil*) * coadaCopie->size);
	for (unsigned int i = 0; i < coadaCopie->size; ++i) {
		coadaCopie->arr[i] = copiazaDispozitiv(coadaPrioritati->arr[i]);
	}

	return coadaCopie;
}

NodStiva* construiesteStivaDinCoadaPrioritati(CoadaPrioritati* coadaPrioritati) {
	if (NULL == coadaPrioritati) {
		return NULL;
	}

	NodStiva* headStiva = NULL;
	CoadaPrioritati* copieCoada = copiazaCoadaPrioritati(coadaPrioritati);

	while (copieCoada->size) {
		DispozitivMobil* dispozitivMaxim = popCoadaPrioritati(copieCoada);
		headStiva = pushStiva(headStiva, dispozitivMaxim);
	}
	dezalocareHeap(copieCoada);

	return headStiva;
}

void afisareStiva(NodStiva* head) {
	printf("\nAfisare stiva\n");
	while (head) {
		afisareDispozitiv(head->dispozitiv);
		head = head->next;
	}
}

void dezalocareNod(NodStiva* nod) {
	dezalocareDispozitiv(nod->dispozitiv);
	free(nod);
}

void dezalocareStiva(NodStiva* head) {
	if (!head) {
		return;
	}

	dezalocareStiva(head->next);
	dezalocareNod(head);
}

int main() {
	CoadaPrioritati* coadaPrioritati = creazaCoadaPrioritatiDinFisier("dispozitivMobil.txt");
	afisareCoadaPrioritati(coadaPrioritati);

	char androidStr[] = "Android";
	char iosStr[] = "iOS";
	char windowsPhoneStr[] = "WindowsPhone";
	printf("\nExista %u dispozitive cu sistemul de operare %s \n", obtineNrDispozitiveDupaOs(coadaPrioritati, androidStr), androidStr);
	printf("\nExista %u dispozitive cu sistemul de operare %s \n", obtineNrDispozitiveDupaOs(coadaPrioritati, iosStr), iosStr);
	printf("\nExista %u dispozitive cu sistemul de operare %s \n", obtineNrDispozitiveDupaOs(coadaPrioritati, windowsPhoneStr), windowsPhoneStr);

	actualizeazaDefecteDispozitiv(coadaPrioritati, 1, "EcranDistrusComplet");
	actualizeazaDefecteDispozitiv(coadaPrioritati, 3, "Hacked");
	actualizeazaDefecteDispozitiv(coadaPrioritati, 9, "OricumNuExista");

	printf("\nAfisam coada dupa actualizari\n");
	afisareCoadaPrioritati(coadaPrioritati);

	testHeapExtrageMax(coadaPrioritati, 2);
	printf("\nCoada prioritati dupa extragere\n");
	afisareCoadaPrioritati(coadaPrioritati);

	NodStiva* stiva = construiesteStivaDinCoadaPrioritati(coadaPrioritati);

	dezalocareHeap(coadaPrioritati);

	afisareStiva(stiva);
	dezalocareStiva(stiva);

	return 0;
}