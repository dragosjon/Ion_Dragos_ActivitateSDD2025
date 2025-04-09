#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Vagon {
    int numarVagon;
    int numarLocuri;
    int numarPasageri;
    char* companieTransport;
    // Alte câmpuri la alegere
    struct Vagon* prev;
    struct Vagon* next;
} Vagon;

// Functie pentru crearea unui nod "vagon"
Vagon* creareVagon(int numarVagon, int numarLocuri, int numarPasageri, const char* companieTransport) {
    Vagon* vagon = (Vagon*)malloc(sizeof(Vagon));
    if (vagon == NULL) {
        printf("Eroare la alocarea memoriei pentru nodul vagon.\n");
        return NULL;
    }

    vagon->numarVagon = numarVagon;
    vagon->numarLocuri = numarLocuri;
    vagon->numarPasageri = numarPasageri;

    vagon->companieTransport = (char*)malloc((strlen(companieTransport) + 1) * sizeof(char));
    if (vagon->companieTransport == NULL) {
        printf("Eroare la alocarea memoriei pentru compania de transport.\n");
        free(vagon);
        return NULL;
    }
    strcpy(vagon->companieTransport, companieTransport);

    vagon->prev = NULL;
    vagon->next = NULL;

    return vagon;
}

// Functie pentru adaugarea unui nod "vagon" la sfarsitul listei dublu inlantuite
void adaugaVagon(Vagon** cap, Vagon* vagon) {
    if (*cap == NULL) {
        *cap = vagon;
    }
    else {
        Vagon* temp = *cap;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = vagon;
        vagon->prev = temp;
    }
}

// Functie pentru afisarea listei dublu inlantuite
void afisareListaVagoane(Vagon* cap) {
    printf("Lista de vagoane:\n");
    Vagon* temp = cap;
    while (temp != NULL) {
        printf("Numar vagon: %d\n", temp->numarVagon);
        printf("Numar locuri: %d\n", temp->numarLocuri);
        printf("Numar pasageri: %d\n", temp->numarPasageri);
        printf("Companie transport: %s\n", temp->companieTransport);
        printf("\n");
        temp = temp->next;
    }
}

// Functie pentru interschimbarea numarului de pasageri intre nodurile de pe pozitiile k-1 si k
void interschimbarePasageri(Vagon* cap, int k) {
    Vagon* nod1 = cap;
    Vagon* nod2 = NULL;

    int count = 0;
    while (nod1 != NULL && count < k - 1) {
        nod1 = nod1->next;
        count++;
    }

    if (nod1 == NULL || nod1->next == NULL) {
        printf("Nu exista suficiente noduri in lista pentru interschimbare.\n");
        return;
    }

    nod2 = nod1->next;

    int temp = nod1->numarPasageri;
    nod1->numarPasageri = nod2->numarPasageri;
    nod2->numarPasageri = temp;
}

// Functie pentru afisarea listei dublu inlantuite in ordine inversa intr-un fisier text
void afisareInversaFisier(Vagon* cap, const char* numeFisier) {
    FILE* fisier = fopen(numeFisier, "w");
    if (fisier == NULL) {
        printf("Nu s-a putut deschide fisierul pentru scriere.\n");
        return;
    }

    Vagon* temp = cap;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    fprintf(fisier, "Lista de vagoane in ordine inversa:\n");
    while (temp != NULL) {
        fprintf(fisier, "Numar vagon: %d\n", temp->numarVagon);
        fprintf(fisier, "Numar locuri: %d\n", temp->numarLocuri);
        fprintf(fisier, "Numar pasageri: %d\n", temp->numarPasageri);
        fprintf(fisier, "Companie transport: %s\n", temp->companieTransport);
        fprintf(fisier, "\n");
        temp = temp->prev;
    }

    fclose(fisier);
}


// Functie pentru verificarea simetriei listei dublu inlantuite in ceea ce priveste numarul de pasageri
int listaDublaSimetrica(Vagon* cap) {
    Vagon* stanga = cap;
    Vagon* dreapta = NULL;

    // Găsim nodul din mijloc
    while (stanga != NULL && stanga->next != NULL) {
        stanga = stanga->next;
    }
    dreapta = stanga;

    // Comparăm nodurile din stânga și dreapta
    while (stanga != NULL && dreapta != NULL) {
        if (stanga->numarPasageri != dreapta->numarPasageri) {
            return 0;  // Lista nu este simetrică
        }
        stanga = stanga->prev;
        dreapta = dreapta->next;
    }

    return 1;  // Lista este simetrică
}

// Functie pentru dezalocarea memoriei listei dublu inlantuite
void dezalocareLista(Vagon* cap) {
    while (cap != NULL) {
        Vagon* temp = cap;
        cap = cap->next;
        free(temp->companieTransport);
        free(temp);
    }
}

int main() {
    Vagon* cap = NULL;  // Capul listei dublu inlantuite

    // Deschidem fisierul text pentru citire
    FILE* fisier = fopen("vagoane.txt", "r");
    if (fisier == NULL) {
        printf("Nu s-a putut deschide fisierul pentru citire.\n");
        return 1;
    }

    // Citim informatiile din fisier si cream nodurile "vagon"
    int numarVagon, numarLocuri, numarPasageri;
    char companieTransport[100];

    while (fscanf(fisier, "%d %d %d %s", &numarVagon, &numarLocuri, &numarPasageri, companieTransport) == 4) {
        Vagon* vagon = creareVagon(numarVagon, numarLocuri, numarPasageri, companieTransport);
        if (vagon != NULL) {
            adaugaVagon(&cap, vagon);
        }
    }

    // Inchidem fisierul
    fclose(fisier);

    // Afisam lista dublu inlantuita
    afisareListaVagoane(cap);

    // Interschimbam numarul de pasageri intre nodurile de pe pozitiile k-1 si k
    int k = 3;
    interschimbarePasageri(cap, k);

    // Afisam lista dublu inlantuita in ordine inversa intr-un fisier text
	const char* numeFisier = "vagoane_invers.txt";
	afisareInversaFisier(cap, numeFisier);

    // Verificam simetria listei dublu inlantuite
    int simetrica = listaDublaSimetrica(cap);
    if (simetrica) {
        printf("Lista dubla este simetrica.\n");
    }
    else {
        printf("Lista dubla nu este simetrica.\n");
    }

    // Dezalocam memoria ocupata de lista dublu inlantuita
    dezalocareLista(cap);

    return 0;
}
