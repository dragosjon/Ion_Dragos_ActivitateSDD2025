#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    unsigned int idComanda;
    char* dataLansareComanda;
    char* dataLivrareProgramata;
    char* numeClient;
    float sumaPlata;

}comanda;


typedef struct nodLS {
    comanda inf;
    struct nodLS* next;
} nodLS;

typedef struct {
    nodLS** vect;
    int nrElem;
} hashT;

int functieHash(hashT tabela, int cheie) {
    return cheie % tabela.nrElem;
}


void inserareNodLS(nodLS** cap, comanda p) {
    nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
    nou->next = NULL;

    nou->inf.idComanda = p.idComanda;
    nou->inf.dataLansareComanda = (char*)malloc((strlen(p.dataLansareComanda) + 1) * sizeof(char));
    strcpy(nou->inf.dataLansareComanda, p.dataLansareComanda);
    nou->inf.dataLivrareProgramata = (char*)malloc((strlen(p.dataLivrareProgramata) + 1) * sizeof(char));
    strcpy(nou->inf.dataLivrareProgramata, p.dataLivrareProgramata);

    nou->inf.numeClient = (char*)malloc((strlen(p.numeClient) + 1) * sizeof(char));
    strcpy(nou->inf.numeClient, p.numeClient);

    nou->inf.sumaPlata = p.sumaPlata;


    if (*cap == NULL) {
        *cap = nou;
    }
    else {
        nodLS* temp = *cap;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = nou;
    }

}

void inserareHash(hashT tabela, comanda c) {
    int poz = functieHash(tabela, c.idComanda);
    inserareNodLS(&tabela.vect[poz], c);
}

hashT creareTabelaGoala(int dim) {
    hashT tabela;
    tabela.nrElem = dim;
    tabela.vect = (nodLS**)malloc(dim * sizeof(nodLS*));

    for (int i = 0; i < dim; i++) {
        tabela.vect[i] = NULL;
    }

    return tabela;
}

hashT creareTabelaDinFisier(int dim) {
    hashT tabela = creareTabelaGoala(dim);


    FILE* file = fopen("tabelaChaining.txt", "r");

    int n;
    fscanf(file, "%d", &n);
    for (int i = 0; i < n; i++) {
        comanda c;
        fscanf(file, "%u", &c.idComanda);

        char buffer[100];
        fscanf(file, "%s", buffer);
        c.dataLansareComanda = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(c.dataLansareComanda, buffer);

        fscanf(file, "%s", buffer);
        c.dataLivrareProgramata = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(c.dataLivrareProgramata, buffer);

        fscanf(file, "%s", buffer);
        c.numeClient = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(c.numeClient, buffer);

        fscanf(file, "%f", &c.sumaPlata);

        inserareHash(tabela, c);

    }

    fclose(file);
    return tabela;
}

void traversareLS(nodLS* cap) {
    nodLS* temp = cap;
    while (temp) {
        printf("IdComanda = %u, DataPlasare = %s, DataLivrare = %s, Nume = %s, Suma = %f\n",
            temp->inf.idComanda, temp->inf.dataLansareComanda, temp->inf.dataLivrareProgramata, temp->inf.numeClient, temp->inf.sumaPlata);
        temp = temp->next;
    }
}

void traversareHash(hashT tabela) {
    for (int i = 0; i < tabela.nrElem; i++) {
        if (tabela.vect[i] != NULL) {
            printf("\nPozitia = %d\n", i);
            traversareLS(tabela.vect[i]);
        }
    }
}

// implementati functia care determina numarul de comenzi din tabela creata mai sus care sunt programate pentru livrare la o data calendaristica specificata 
void comenziLivrareLaData(hashT tabela, char* data) {
	int count = 0;
	for (int i = 0; i < tabela.nrElem; i++) {
		nodLS* temp = tabela.vect[i];
		while (temp) {
			if (strcmp(temp->inf.dataLivrareProgramata, data) == 0) {
				count++;
			}
			temp = temp->next;
		}
	}
	printf("Numarul de comenzi programate pentru livrare la data %s este: %d\n", data, count);
}






// implementati functia care sterge toate comenzile cu data de livrare mai mica decat data curenta
void stergeComenziLivrate(hashT tabela) {
	char dataCurenta[100];
	printf("Introduceti data curenta: ");
	scanf("%s", dataCurenta);

	for (int i = 0; i < tabela.nrElem; i++) {
		nodLS* temp = tabela.vect[i];
		nodLS* prev = NULL;

		while (temp) {
			if (strcmp(temp->inf.dataLivrareProgramata, dataCurenta) < 0) {
				if (prev == NULL) {
					tabela.vect[i] = temp->next;
					free(temp->inf.dataLivrareProgramata);
					free(temp->inf.dataLansareComanda);
					free(temp->inf.numeClient);
					free(temp);
					temp = tabela.vect[i];
				}
				else {
					prev->next = temp->next;
					free(temp->inf.dataLivrareProgramata);
					free(temp->inf.dataLansareComanda);
					free(temp->inf.numeClient);
					free(temp);
					temp = prev->next;
				}
			}
			else {
				prev = temp;
				temp = temp->next;
			}
		}
	}
}


//implementati functia care salveaza intr-o structura lista diferita/separata toate comenzile din tabela de dispersie creata

void salvareComenziInListaSeparata(hashT tabela, nodLS** cap) {
	for (int i = 0; i < tabela.nrElem; i++) {
		nodLS* temp = tabela.vect[i];
		while (temp) {
			comanda c;
			c.idComanda = temp->inf.idComanda;
			c.dataLansareComanda = (char*)malloc((strlen(temp->inf.dataLansareComanda) + 1) * sizeof(char));
			strcpy(c.dataLansareComanda, temp->inf.dataLansareComanda);
			c.dataLivrareProgramata = (char*)malloc((strlen(temp->inf.dataLivrareProgramata) + 1) * sizeof(char));
			strcpy(c.dataLivrareProgramata, temp->inf.dataLivrareProgramata);
			c.numeClient = (char*)malloc((strlen(temp->inf.numeClient) + 1) * sizeof(char));
			strcpy(c.numeClient, temp->inf.numeClient);
			c.sumaPlata = temp->inf.sumaPlata;

			inserareNodLS(cap, c);
			temp = temp->next;
		}
	}
}


void dezalocareLS(nodLS* cap) {
    nodLS* temp = cap;
    while (temp) {
        nodLS* aux = temp->next;
        free(temp->inf.dataLivrareProgramata);
        free(temp->inf.dataLansareComanda);
        free(temp->inf.numeClient);
        free(temp);
        temp = aux;
    }
}

void dezalocareHash(hashT tabela) {
    for (int i = 0; i < tabela.nrElem; i++) {
        if (tabela.vect[i] != NULL)
            dezalocareLS(tabela.vect[i]);
    }
    free(tabela.vect);
}

int main() {
    hashT tabela = creareTabelaDinFisier(10);
    traversareHash(tabela);


	// implementati functia care determina numarul de comenzi din tabela creata mai sus care sunt programate pentru livrare la o data calendaristica specificata
	char data[100];
	printf("Introduceti data pentru livrare: ");
	scanf("%s", data);
	comenziLivrareLaData(tabela, data);
	printf("\n");

	// implementati functia care sterge toate comenzile cu data de livrare mai mica decat data curenta
	stergeComenziLivrate(tabela);
	printf("\n");
	traversareHash(tabela);


	// implementati functia care salveaza intr-o structura lista diferita/separata toate comenzile din tabela de dispersie creata
	nodLS* cap = NULL;
	salvareComenziInListaSeparata(tabela, &cap);
	printf("\nLista separata:\n");
	traversareLS(cap);
	dezalocareLS(cap);



	printf("\n");
    dezalocareHash(tabela);
    return 0;
}