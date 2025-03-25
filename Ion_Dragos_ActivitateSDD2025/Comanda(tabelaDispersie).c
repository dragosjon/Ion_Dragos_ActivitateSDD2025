#include <stdio.h>
#include "malloc.h"
#include "string.h"

typedef struct comanda {
    unsigned int idComanda;
    char* dataLansareComanda;
    char* dataLivrareProgramata;
    char* numeClient;
    float sumaPlata;

}comanda;

typedef struct nodLS {
    comanda info;
    struct nodLS* urmatorul;
}nodLS;

typedef struct tabelaH {

    nodLS** vector;
    int dim;
}tabelaH;

char* copiazaString(char* string) {
    char* newString = (char*)malloc((strlen(string) + 1) * sizeof(char));
    strcpy(newString, string);
    return newString;
}

tabelaH creareTabelaGoala(int dim) {
    tabelaH tabelaNoua;
    tabelaNoua.dim = dim;
    tabelaNoua.vector = (nodLS**)malloc(sizeof(nodLS*));

    for (int i = 0; i < dim; ++i) {
        tabelaNoua.vector[i] = NULL;

    }

    return tabelaNoua;
}

int functiaHash(tabelaH tabelaH1, char* numeC) {
    int poz = strlen(numeC) % tabelaH1.dim; /*key%size;*/
    return poz;
}

nodLS* inserareInLS(nodLS* cap, comanda c) {
    nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
    nou->info = c;
    nou->urmatorul = NULL;

    if (!cap) { return nou; }
    else {
        nodLS* curent = cap;
        while (curent->urmatorul) {
            curent = curent->urmatorul;
        }

        curent->urmatorul = nou;
    }

    return cap;
}

void inserareHashT(tabelaH hastT, comanda c) {
    int poz = functiaHash(hastT, c.numeClient);

    hastT.vector[poz] = inserareInLS(hastT.vector[poz], c);
}

tabelaH  creareTabelaDinFisier(int dim) {
    tabelaH tabelaNoua = creareTabelaGoala(dim);
    FILE* f = fopen("com.txt", "r");

    int n;
    fscanf(f, "%d", &n);
    char buffer[250];
    for (int i = 0; i < n; ++i) {
        comanda c;

        fscanf(f, "%u", &c.idComanda);
        fscanf(f, "%s", buffer);
        c.dataLansareComanda = copiazaString(buffer);
        fscanf(f, "%s", buffer);
        c.dataLivrareProgramata = copiazaString(buffer);
        fscanf(f, "%s", buffer);
        c.numeClient = copiazaString(buffer);
        fscanf(f, "%f", &c.sumaPlata);

        inserareHashT(tabelaNoua, c);
    }

    fclose(f);
    return tabelaNoua;
}

void afisareComanda(comanda c) {
    printf("%u\n", c.idComanda);
    printf("%s\n", c.dataLansareComanda);
    printf("%s\n", c.dataLivrareProgramata);
    printf("%s\n", c.numeClient);
    printf("%.2f\n", c.sumaPlata);
}

void afisareLS(nodLS* cap) {
    nodLS* curent = cap;

    while (curent) {
        afisareComanda(curent->info);
        curent = curent->urmatorul;
    }
}

void afisareTabela(tabelaH t) {
    for (int i = 0; i < t.dim; ++i) {
        afisareLS(t.vector[i]);
    }
}


int nrComenziClient(tabelaH t, char* numeC) {
    int nrComenzi = 0;
    for (int i = 0; i < t.dim; ++i) {
        nodLS* curent = t.vector[i];

        while (curent) {
            if (strcmp(numeC, curent->info.numeClient) == 0) {
                nrComenzi++;
            }
            curent = curent->urmatorul;
        }
    }

    return nrComenzi;
}

void modifComanda(tabelaH t, int idComada, char* dataLivrareNoua) {
    for (int i = 0; i < t.dim; ++i) {
        nodLS* curent = t.vector[i];

        while (curent) {
            if (idComada == curent->info.idComanda) {
                if (curent->info.dataLivrareProgramata) { free(curent->info.dataLivrareProgramata); }
                curent->info.dataLivrareProgramata = copiazaString(dataLivrareNoua);
            }
            curent = curent->urmatorul;
        }
    }
}


int main() {
    tabelaH t = creareTabelaDinFisier(3);
    afisareTabela(t);
    printf("  \n Cleintul are %d comenzii: \n", nrComenziClient(t, "Test"));
    modifComanda(t, 18, "2024-07-16");
    afisareTabela(t);
    return 0;
}
