#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    unsigned int nrRetetei;
    unsigned char nrMedicamente;
    char* numelePacientului;
    char* numeleMedicului;
    float sumaPlata;

}Reteta;


typedef struct nodLS {
    Reteta inf;
    struct nodLS* next;
} nodLS;

typedef struct {
    nodLS** vect;
    int nrElem;
} hashT;

int functieHash(hashT tabela, int cheie) {
    return cheie % tabela.nrElem;
}


void inserareNodLS(nodLS** cap, Reteta p) {
    nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
    nou->next = NULL;

    nou->inf.nrRetetei = p.nrRetetei;
    nou->inf.nrMedicamente = p.nrMedicamente;
    nou->inf.numelePacientului = (char*)malloc((strlen(p.numelePacientului) + 1) * sizeof(char));
    strcpy(nou->inf.numelePacientului, p.numelePacientului);

    nou->inf.numeleMedicului = (char*)malloc((strlen(p.numeleMedicului) + 1) * sizeof(char));
    strcpy(nou->inf.numeleMedicului, p.numeleMedicului);

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

void inserareHash(hashT tabela, Reteta c) {
    int poz = functieHash(tabela, c.nrRetetei);
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


    FILE* file = fopen("reteta.txt", "r");

    int n;
    fscanf(file, "%d", &n);
    for (int i = 0; i < n; i++) {
        Reteta c;
        fscanf(file, "%u", &c.nrRetetei);

		fscanf(file, "%hhu", &c.nrMedicamente);

        char buffer[100];

        fscanf(file, "%s", buffer);
        c.numelePacientului = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(c.numelePacientului, buffer);

        fscanf(file, "%s", buffer);
        c.numeleMedicului = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(c.numeleMedicului, buffer);

        fscanf(file, "%f", &c.sumaPlata);

        inserareHash(tabela, c);

    }

    fclose(file);
    return tabela;
}

void traversareLS(nodLS* cap) {
    nodLS* temp = cap;
    while (temp) {
        printf("nrRetetei = %u, nrMedicamente = %hhu, NumePacient = %s, NumeMedic = %s, Suma = %f\n",
            temp->inf.nrRetetei, temp->inf.nrMedicamente, temp->inf.numelePacientului, temp->inf.numeleMedicului, temp->inf.sumaPlata);
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

//implementati functia care returneaza o valoare double corespunzatoare valorii retetelor din tabela de dispersie creata mai sus pentru un pacient specificat
void afisareSumaPacient(hashT tabela, const char* numePacient) {
	double suma = 0;
	for (int i = 0; i < tabela.nrElem; i++) {
		nodLS* temp = tabela.vect[i];
		while (temp) {
			if (strcmp(temp->inf.numelePacientului, numePacient) == 0) {
				suma += temp->inf.sumaPlata;
			}
			temp = temp->next;
		}
	}
	printf("Suma totala pentru pacientul %s este: %.2f\n", numePacient, suma);
}

//implementati functia care determina numarul de medicamente prescrise de un medic specfiat
void afisareNrMedicamenteMedici(hashT tabela, const char* numeMedic) {
	int nrMedicamente = 0;
	for (int i = 0; i < tabela.nrElem; i++) {
		nodLS* temp = tabela.vect[i];
		while (temp) {
			if (strcmp(temp->inf.numeleMedicului, numeMedic) == 0) {
				nrMedicamente += temp->inf.nrMedicamente;
			}
			temp = temp->next;
		}
	}
	printf("Numarul total de medicamente prescrise de medicul %s este: %d\n", numeMedic, nrMedicamente);
}

//implementati functia care creeaza evidenta a pacientilor pentru care au fost emise retete cu 3 medicamente prescrise

void afisarePacienti3Medicamente(hashT tabela) {
	printf("Pacientii pentru care au fost emise retete cu 3 medicamente prescrise:\n");
	for (int i = 0; i < tabela.nrElem; i++) {
		nodLS* temp = tabela.vect[i];
		while (temp) {
			if (temp->inf.nrMedicamente == 3) {
				printf("Nume pacient: %s\n", temp->inf.numelePacientului);
			}
			temp = temp->next;
		}
	}
}



void dezalocareLS(nodLS* cap) {
    nodLS* temp = cap;
    while (temp) {
        nodLS* aux = temp->next;
        free(temp->inf.numelePacientului);
        free(temp->inf.numeleMedicului);
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

    
	char numePacient[100];
	printf("Introduceti numele pacientului: ");
	scanf("%s", numePacient);
	afisareSumaPacient(tabela, numePacient);
	printf("\n");

	char numeMedic[100];
	printf("Introduceti numele medicului: ");
	scanf("%s", numeMedic);
	afisareNrMedicamenteMedici(tabela, numeMedic);
	printf("\n");

	afisarePacienti3Medicamente(tabela);
	printf("\n");

    dezalocareHash(tabela);
    return 0;
}