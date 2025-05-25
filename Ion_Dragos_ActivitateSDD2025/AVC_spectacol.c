#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structura Spectacol
typedef struct Spectacol {
    int id;
    int nrSpectatori;
    char* titlu;
    int durata; // Durata spectacolului în minute
} Spectacol;

// Structura nodului pentru arborele binar de căutare
typedef struct Nod {
    Spectacol spectacol;
    struct Nod* stanga;
    struct Nod* dreapta;
} Nod;

// Funcție pentru crearea unui spectacol
Spectacol creareSpectacol(int id, int nrSpectatori, const char* titlu, int durata) {
    Spectacol s;
    s.id = id;
    s.nrSpectatori = nrSpectatori;
    s.titlu = (char*)malloc(strlen(titlu) + 1);
    strcpy(s.titlu, titlu);
    s.durata = durata;
    return s;
}

// Funcție pentru inserarea unui spectacol în arbore
Nod* inserare(Nod* radacina, Spectacol spectacol) {
    if (radacina == NULL) {
        Nod* nou = (Nod*)malloc(sizeof(Nod));
        nou->spectacol = spectacol;
        nou->stanga = nou->dreapta = NULL;
        return nou;
    }
    if (spectacol.id < radacina->spectacol.id) {
        radacina->stanga = inserare(radacina->stanga, spectacol);
    }
    else if (spectacol.id > radacina->spectacol.id) {
        radacina->dreapta = inserare(radacina->dreapta, spectacol);
    }
    return radacina;
}

// Funcție pentru citirea spectacolelor dintr-un fișier și inserarea lor în arbore
Nod* citireDinFisier(const char* numeFisier, Nod* radacina) {
    FILE* fisier = fopen(numeFisier, "r");
    if (!fisier) {
        printf("Eroare la deschiderea fișierului %s\n", numeFisier);
        return radacina;
    }

    int id, nrSpectatori, durata;
    char titlu[100];

    while (fscanf(fisier, "%d %d %d %[^\n]", &id, &nrSpectatori, &durata, titlu) == 4) {
        Spectacol spectacol = creareSpectacol(id, nrSpectatori, titlu, durata);
        radacina = inserare(radacina, spectacol);
    }

    fclose(fisier);
    return radacina;
}

// Funcție pentru parcurgerea postordine
void parcurgerePostordine(Nod* radacina) {
    if (radacina) {
        parcurgerePostordine(radacina->stanga);
        parcurgerePostordine(radacina->dreapta);
        printf("ID: %d, Nr Spectatori: %d, Titlu: %s, Durata: %d minute\n",
            radacina->spectacol.id, radacina->spectacol.nrSpectatori,
            radacina->spectacol.titlu, radacina->spectacol.durata);
    }
}

// Funcție pentru eliberarea memoriei
void eliberareArbore(Nod* radacina) {
    if (radacina) {
        eliberareArbore(radacina->stanga);
        eliberareArbore(radacina->dreapta);
        free(radacina->spectacol.titlu);
        free(radacina);
    }
}

// Funcția main
int main() {
    Nod* radacina = NULL;

    // Citirea spectacolelor din fișier și inserarea lor în arbore
    const char* numeFisier = "spectacole.txt";
    radacina = citireDinFisier(numeFisier, radacina);

    // Parcurgere postordine
    printf("Parcurgere postordine:\n");
    parcurgerePostordine(radacina);

    // Eliberare memorie
    eliberareArbore(radacina);

    return 0;
}
