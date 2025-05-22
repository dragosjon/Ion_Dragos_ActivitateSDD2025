#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structura Pacient
typedef struct {
    int cod;
    char* nume;
    char* descriereProblema;
    float varsta;
    int prioritate;
} Pacient;

// Structura nodului din coadă
typedef struct nodCoada {
    Pacient inf;
    struct nodCoada* next;
} nodCoada;

// Funcția de inserare în coada de priorități
void inserarePacient(nodCoada** prim, nodCoada** ultim, Pacient p) {
    nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));
    nou->inf = p;
    nou->next = NULL;

    if (*prim == NULL || p.prioritate > (*prim)->inf.prioritate) {
        // Inserare la început
        nou->next = *prim;
        *prim = nou;
        if (*ultim == NULL) {
            *ultim = nou;
        }
    }
    else {
        // Inserare în interior sau la final
        nodCoada* temp = *prim;
        while (temp->next != NULL && temp->next->inf.prioritate >= p.prioritate) {
            temp = temp->next;
        }
        nou->next = temp->next;
        temp->next = nou;
        if (nou->next == NULL) {
            *ultim = nou;
        }
    }
}

// Funcția de traversare și afișare
void afisarePacienti(nodCoada* prim) {
    if (prim == NULL) {
        printf("Coada este goala.\n");
        return;
    }
    nodCoada* temp = prim;
    while (temp) {
        printf("Cod: %d, Nume: %s, Problema: %s, Varsta: %.2f, Prioritate: %d\n",
            temp->inf.cod, temp->inf.nume, temp->inf.descriereProblema,
            temp->inf.varsta, temp->inf.prioritate);
        temp = temp->next;
    }
}

// Funcția pentru citirea pacienților din fișier
void citirePacientiDinFisier(const char* numeFisier, nodCoada** prim, nodCoada** ultim) {
    FILE* f = fopen(numeFisier, "r");
    if (f == NULL) {
        perror("Eroare la deschiderea fisierului");
        return;
    }

    Pacient p;
    char bufferNume[100], bufferProblema[100];
    while (fscanf(f, "%d %s %s %f %d", &p.cod, bufferNume, bufferProblema, &p.varsta, &p.prioritate) == 5) {
        p.nume = (char*)malloc(strlen(bufferNume) + 1);
        strcpy(p.nume, bufferNume);
        p.descriereProblema = (char*)malloc(strlen(bufferProblema) + 1);
        strcpy(p.descriereProblema, bufferProblema);
        inserarePacient(prim, ultim, p);
    }

    fclose(f);
}

// Funcția pentru numărarea gravidelor și copiilor sub 1 an
int numarGravideSiCopii(nodCoada* prim) {
    int count = 0;
    nodCoada* temp = prim;
    while (temp) {
        if (temp->inf.prioritate == 5) {
            count++;
        }
        temp = temp->next;
    }
    return count;
}

// Funcția pentru creșterea priorității
void cresterePrioritate(nodCoada* prim) {
    nodCoada* temp = prim;
    while (temp) {
        if (temp->inf.prioritate <= 3) {
            temp->inf.prioritate++;
        }
        temp = temp->next;
    }
}

// Funcția pentru statistici
void statisticiProbleme(nodCoada* prim, const char* numeFisier) {
    FILE* f = fopen(numeFisier, "w");
    if (!f) {
        perror("Eroare la deschiderea fisierului");
        return;
    }

    nodCoada* temp = prim;
    while (temp) {
        fprintf(f, "Problema: %s - Pacient: %s\n", temp->inf.descriereProblema, temp->inf.nume);
        temp = temp->next;
    }

    fclose(f);
}

// Funcția pentru extragerea unui pacient
int extragerePacient(nodCoada** prim, nodCoada** ultim, Pacient* p) {
    if (*prim == NULL) {
        return -1; // Coada este goală
    }

    nodCoada* temp = *prim;
    *p = temp->inf;
    *prim = (*prim)->next;
    if (*prim == NULL) {
        *ultim = NULL;
    }
    free(temp);
    return 0;
}

// Funcția pentru dezalocarea cozii
void dezalocareCoada(nodCoada** prim) {
    nodCoada* temp;
    while (*prim) {
        temp = *prim;
        *prim = (*prim)->next;
        free(temp->inf.nume);
        free(temp->inf.descriereProblema);
        free(temp);
    }
}

// Funcția main
int main() {
    nodCoada* prim = NULL, * ultim = NULL;

    // Citirea pacienților din fișier
    citirePacientiDinFisier("pacient.txt", &prim, &ultim);

    // Afișare pacienți
    printf("Pacienti in coada:\n");
    afisarePacienti(prim);

    // Număr gravide și copii sub 1 an
    int numar = numarGravideSiCopii(prim);
    printf("\nNumar gravide si copii sub 1 an: %d\n", numar);

    // Creștere prioritate
    cresterePrioritate(prim);
    printf("\nPacienti dupa cresterea prioritatii:\n");
    afisarePacienti(prim);

    // Statistici probleme
    statisticiProbleme(prim, "statistici.txt");

    // Extragere pacient
    Pacient extras;
    if (extragerePacient(&prim, &ultim, &extras) == 0) {
        printf("\nPacient extras: %s\n", extras.nume);
        free(extras.nume);
        free(extras.descriereProblema);
    }

    // Afișare pacienți rămași
    printf("\nPacienti ramasi in coada:\n");
    afisarePacienti(prim);

    // Dezalocare coadă
    dezalocareCoada(&prim);
    return 0;
}


1234 Ionescu_Gigel Raceala 23 3
5678 Popescu_Elena Gripa 0.5 5
9101 Vasilescu_Andrei Dureri_de_cap 12 4
1123 Georgescu_Maria Dureri_de_spate 35 2
1415 Dumitrescu_Alina Febra 2 1
