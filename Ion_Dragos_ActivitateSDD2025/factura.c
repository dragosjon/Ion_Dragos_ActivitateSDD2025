#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:6001)
#pragma warning(disable:4996)
#pragma warning(disable:6031)
#pragma warning(disable:6011)

typedef struct Factura Factura;
struct Factura
{
	unsigned int nrFactura;
	char* dataEmitere;
	char* beneficiar;
	float sumaPlata;
	unsigned int nrZileScadenta;
};

typedef struct NodDublu NodDublu;
struct NodDublu
{
	Factura info;
	NodDublu* next, * prev;
};

Factura citesteFacturaDinFisier(FILE* fisier)
{
	Factura f;

	fscanf(fisier, "%u", &f.nrFactura);

	char buf[100];

	fscanf(fisier, "%s", buf);
	f.dataEmitere = malloc(sizeof(char) * (strlen(buf) + 1));
	strcpy(f.dataEmitere, buf);

	fscanf(fisier, "%s", buf);
	f.beneficiar = malloc(sizeof(char) * (strlen(buf) + 1));
	strcpy(f.beneficiar, buf);

	fscanf(fisier, "%f", &f.sumaPlata);

	fscanf(fisier, "%u", &f.nrZileScadenta);

	return f;
}

Factura copieFactura(Factura f)
{
	Factura cf;

	cf.nrFactura = f.nrFactura;
	cf.sumaPlata = f.sumaPlata;
	cf.nrZileScadenta = f.nrZileScadenta;

	cf.dataEmitere = malloc(sizeof(char) * (strlen(f.dataEmitere) + 1));
	strcpy(cf.dataEmitere, f.dataEmitere);

	cf.beneficiar = malloc(sizeof(char) * (strlen(f.beneficiar) + 1));
	strcpy(cf.beneficiar, f.beneficiar);

	return cf;
}

void afisareFactura(Factura f)
{
	printf("Nr factura: %u\nData emiterii: %s\nBeneficiar: %s\nSuma de plata: %.2f\nNr zile scadenta: %u",
		f.nrFactura, f.dataEmitere, f.beneficiar, f.sumaPlata, f.nrZileScadenta);

	printf("\n\n");
}

void dezalocareFactura(Factura* f)
{
	if (f->dataEmitere)
		free(f->dataEmitere);

	if (f->beneficiar)
		free(f->beneficiar);
}

NodDublu* inserareNod(NodDublu* cap, Factura info)
{
	NodDublu* noulNod = malloc(sizeof(NodDublu));
	noulNod->info = info;
	noulNod->next = NULL;
	noulNod->prev = NULL;

	if (!cap)
		return noulNod;

	NodDublu* aux = cap;

	while (aux->next)
		aux = aux->next;

	aux->next = noulNod;
	noulNod->prev = aux;

	return cap;
}

NodDublu* creareLista(const char* numeFisier)
{
	NodDublu* lista = NULL;

	FILE* fisier = fopen(numeFisier, "r");

	int nrFacturi = 0;

	fscanf(fisier, "%d", &nrFacturi);

	for (int j = 0; j < nrFacturi; j++)
	{
		Factura f = citesteFacturaDinFisier(fisier);
		lista = inserareNod(lista, f);
	}

	fclose(fisier);

	return lista;
}

void afisareLista(NodDublu* cap)
{
	if (!cap)
	{
		printf("Lista este goala!\n\n");
		return;
	}

	while (cap)
	{
		afisareFactura(cap->info);
		cap = cap->next;
	}
}

void afisareListaInvers(NodDublu* cap)
{
	if (!cap)
	{
		printf("Lista este goala!\n\n");
		return;
	}

	NodDublu* aux = cap;

	while (aux->next)
		aux = aux->next;

	NodDublu* ultim = aux;

	while (ultim)
	{
		afisareFactura(ultim->info);
		ultim = ultim->prev;
	}
}

float valoareTotalaFactura(NodDublu* cap, const char* beneficiar)
{
	if (!cap)
		return 0;

	float total = 0;

	while (cap)
	{
		if (strcmp(cap->info.beneficiar, beneficiar) == 0)
			total += cap->info.sumaPlata;

		cap = cap->next;
	}

	return total;
}

NodDublu* modificareSumaDePlata(NodDublu* cap, unsigned int nrFactura, float sumaNoua)
{
	if (!cap)
		return;

	NodDublu* aux = cap;

	while (aux)
	{
		if (aux->info.nrFactura == nrFactura)
			aux->info.sumaPlata = sumaNoua;

		aux = aux->next;
	}

	return cap;
}

NodDublu* stergeFacturiSubPrag(NodDublu* cap, unsigned int prag)
{
	if (!cap)
		return cap;

	NodDublu* curent = cap;
	NodDublu* aux = NULL;

	while (curent)
	{
		aux = curent->prev;

		if (curent == cap && curent->info.nrZileScadenta < prag)
		{
			NodDublu* nodDeSters = curent;

			aux = curent->next;
			cap = aux;
			cap->prev = NULL;
			curent = cap;

			dezalocareFactura(&nodDeSters->info);
			free(nodDeSters);
		}

		if (!curent->next && curent->info.nrZileScadenta < prag)
		{
			NodDublu* nodDeSters = curent;

			curent = aux;

			curent->next = NULL;

			dezalocareFactura(&nodDeSters->info);
			free(nodDeSters);
		}

		if (curent->info.nrZileScadenta < prag)
		{
			NodDublu* nodDeSters = curent;

			if (curent->next)
				aux->next = curent->next;

			if (curent->next->prev)
				curent->next->prev = aux;

			curent = aux;

			dezalocareFactura(&nodDeSters->info);
			free(nodDeSters);
		}

		curent = curent->next;
	}

	return cap;
}

int getNrNoduriLista(NodDublu* cap, char* data)
{
	if (!cap)
		return 0;

	int nrNoduriDorite = 0;

	NodDublu* aux = cap;

	int ascii = 0;

	for (int j = 0; j < strlen(data); j++)
		ascii += (int)data[j];

	while (aux)
	{
		int asc = 0;

		for (int i = 0; i < strlen(aux->info.dataEmitere); i++)
			asc += (int)aux->info.dataEmitere[i];

		if (asc > ascii)
			nrNoduriDorite++;

		aux = aux->next;
	}

	return nrNoduriDorite;
}

Factura* conversieListaVector(NodDublu* cap, char* data)
{
	int size = getNrNoduriLista(cap, data);

	Factura* vector = malloc(sizeof(Factura) * size);

	int index = 0;

	NodDublu* aux = cap;

	while (aux)
	{
		vector[index] = copieFactura(aux->info);

		index++;

		aux = aux->next;
	}

	return vector;
}

void dezalocareLista(NodDublu* cap)
{
	if (!cap)
		return;

	while (cap)
	{
		dezalocareFactura(&cap->info);
		cap = cap->next;
	}
}

int main()
{
	NodDublu* lista = creareLista("factura.txt");

	afisareLista(lista);

	printf("=============================\n\n");

	//afisareListaInvers(lista);

	printf("Beneficiarul specificat ca parametru are un total de plata de: %.2f\n\n", valoareTotalaFactura(lista, "Alexandra"));

	printf("=============================\n\n");

	afisareLista(lista);

	lista = modificareSumaDePlata(lista, 17, 600);

	printf("Factura al carei nr a fost dat ca parametru a avut o modificare a platii acest lucru se va vedea mai jos in lista!\n\n");

	afisareLista(lista);

	printf("\n\n=============================\n\n");

	lista = stergeFacturiSubPrag(lista, 10);

	afisareLista(lista);

	printf("Nr noduri cu data mai mare este: %d", getNrNoduriLista(lista, "01.01.2021"));

	int size = getNrNoduriLista(lista, "12.03.2021");

	Factura* v = conversieListaVector(lista, "12.03.2021");

	printf("\n\n=============================\n\n");

	for (int j = 0; j < size; j++)
		afisareFactura(v[j]);

	for (int j = 0; j < size; j++)
		dezalocareFactura(&v[j]);

	free(v);

	dezalocareLista(lista);

	return 0;
}