#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <stdio.h>
#include <string.h>

typedef struct  {
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
    dezalocareHash(tabela);
    return 0;
}