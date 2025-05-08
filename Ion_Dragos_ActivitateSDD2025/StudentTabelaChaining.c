#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    int cod;
    char* nume;
    int varsta;
    float medie;
}Student;


typedef struct nodLS {
    Student inf;
    struct nodLS* next;
} nodLS;

typedef struct {
    nodLS** vect;
    int nrElem;
} hashT;

int functieHash(hashT tabela, int cheie) {
    return cheie % tabela.nrElem;
}


void inserareNodLS(nodLS** cap, Student p) {
    nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
    nou->next = NULL;

    nou->inf.cod = p.cod;

    nou->inf.nume = (char*)malloc((strlen(p.nume) + 1) * sizeof(char));
    strcpy(nou->inf.nume, p.nume);

    nou->inf.varsta = p.varsta;

    nou->inf.medie = p.medie;


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

void inserareHash(hashT tabela, Student c) {
    int poz = functieHash(tabela, c.cod);
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


    FILE* file = fopen("tabelaStudent.txt", "r");

    int n;
    fscanf(file, "%d", &n);
    for (int i = 0; i < n; i++) {
        Student c;
        fscanf(file, "%d", &c.cod);

        char buffer[100];
        fscanf(file, "%s", buffer);
        c.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(c.nume, buffer);

        fscanf(file, "%d", &c.varsta);
        

        fscanf(file, "%f", &c.medie);

        inserareHash(tabela, c);

    }

    fclose(file);
    return tabela;
}

void traversareLS(nodLS* cap) {
    nodLS* temp = cap;
    while (temp) {
        printf("Cod = %d, Nume = %s, Varsta = %d, Medie = %f\n",
            temp->inf.cod, temp->inf.nume, temp->inf.varsta, temp->inf.medie);
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

//functie de stergere a studentului cu cea mai mare medie

void stergereStudentMedieMaxima(hashT tabela) {
	float medieMax = 0;
	int poz = 0;

	for (int i = 0; i < tabela.nrElem; i++) {
		nodLS* temp = tabela.vect[i];
		while (temp) {
			if (temp->inf.medie > medieMax) {
				medieMax = temp->inf.medie;
				poz = i;
			}
			temp = temp->next;
		}
	}

	if (poz != 0) {
		nodLS* temp = tabela.vect[poz];
		nodLS* prev = NULL;

		while (temp && temp->inf.medie != medieMax) {
			prev = temp;
			temp = temp->next;
		}

		if (prev == NULL) {
			tabela.vect[poz] = temp->next;
		}
		else {
			prev->next = temp->next;
		}

		free(temp->inf.nume);
		free(temp);
	}
}

//sa se realizeze conversia elemntelor din tabela de dispersie intr-o structura de tip lista de liste pring gruparea lementelor initial la nivel de medie adica studentii cu media peste 5 sunt intr-o sublista, iar cei cu media sub 5 in alta sublista

void conversieListaDeListe(hashT tabela) {
	nodLS* listaMediePeste5 = NULL;
	nodLS* listaMedieSub5 = NULL;

	for (int i = 0; i < tabela.nrElem; i++) {
		nodLS* temp = tabela.vect[i];
		while (temp) {
			if (temp->inf.medie >= 5) {
				inserareNodLS(&listaMediePeste5, temp->inf);
			}
			else {
				inserareNodLS(&listaMedieSub5, temp->inf);
			}
			temp = temp->next;
		}
	}

	printf("Lista studentilor cu media peste 5:\n");
	traversareLS(listaMediePeste5);

	printf("\nLista studentilor cu media sub 5:\n");
	traversareLS(listaMedieSub5);
}


void dezalocareLS(nodLS* cap) {
    nodLS* temp = cap;
    while (temp) {
        nodLS* aux = temp->next;
        free(temp->inf.nume);
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
	//stergereStudentMedieMaxima(tabela);
	printf("\nDupa stergerea studentului cu media cea mai mare\n");
	traversareHash(tabela);
	printf("\nLista de studenti cu media peste 5 si sub 5\n");

	conversieListaDeListe(tabela);



   


    dezalocareHash(tabela);
    return 0;
}