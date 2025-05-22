#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structura pentru filme
typedef struct {
    int idFilm;
    char* denumire;
    float pret;
    float nrBilete;
} Filme;

// Structura pentru nodul arborelui
typedef struct nodArb {
    int BF;
    Filme inf;
    struct nodArb* stanga;
    struct nodArb* dreapta;
} NodArb;

// Funcția pentru crearea unui nod
NodArb* creareNod(NodArb* stanga, NodArb* dreapta, Filme f) {
    NodArb* nou = (NodArb*)malloc(sizeof(NodArb));
    nou->inf.idFilm = f.idFilm;
    nou->inf.denumire = (char*)malloc(strlen(f.denumire) + 1);
    strcpy(nou->inf.denumire, f.denumire);
    nou->inf.pret = f.pret;
    nou->inf.nrBilete = f.nrBilete;
    nou->stanga = stanga;
    nou->dreapta = dreapta;
    return nou;
}

// Funcția pentru inserare
NodArb* inserare(Filme f, NodArb* rad) {
    if (rad != NULL) {
        if (f.idFilm < rad->inf.idFilm) {
            rad->stanga = inserare(f, rad->stanga);
            return rad;
        }
        else if (f.idFilm > rad->inf.idFilm) {
            rad->dreapta = inserare(f, rad->dreapta);
            return rad;
        }
        else {
            return rad;
        }
    }
    else {
        return creareNod(NULL, NULL, f);
    }
}

// Funcția pentru traversare preordine
void traversarePreordine(NodArb* rad) {
    if (rad) {
        printf("\nidFilm: %d, denumire: %s, pret: %.2f, nrBilete: %.2f, BF=%d",
            rad->inf.idFilm, rad->inf.denumire, rad->inf.pret, rad->inf.nrBilete, rad->BF);
        traversarePreordine(rad->stanga);
        traversarePreordine(rad->dreapta);
    }
}

// Funcția pentru traversare inordine
void traversareInordine(NodArb* root) {
    if (root) {
        traversareInordine(root->stanga);
        printf("\nidFilm: %d, denumire: %s, pret: %.2f, nrBilete: %.2f, BF=%d",
            root->inf.idFilm, root->inf.denumire, root->inf.pret, root->inf.nrBilete, root->BF);
        traversareInordine(root->dreapta);
    }
}

// Funcția pentru traversare postordine
void traversarePostordine(NodArb* root) {
    if (root) {
        traversarePostordine(root->stanga);
        traversarePostordine(root->dreapta);
        printf("\nidFilm: %d, denumire: %s, pret: %.2f, nrBilete: %.2f, BF=%d",
            root->inf.idFilm, root->inf.denumire, root->inf.pret, root->inf.nrBilete, root->BF);
    }
}

// Funcția pentru dezalocare
void dezalocare(NodArb* root) {
    if (root) {
        NodArb* stang = root->stanga;
        NodArb* drep = root->dreapta;
        free(root->inf.denumire);
        free(root);
        dezalocare(stang);
        dezalocare(drep);
    }
}

// Funcția pentru calcularea numărului de niveluri
int maxim(int x, int y) {
    return (x > y) ? x : y;
}

int nrNiveluri(NodArb* root) {
    if (root) {
        int st = nrNiveluri(root->stanga);
        int dr = nrNiveluri(root->dreapta);
        return 1 + maxim(st, dr);
    }
    else {
        return 0;
    }
}

// Funcția pentru calcularea factorului de echilibru
void calcBF(NodArb* root) {
    if (root != NULL) {
        root->BF = nrNiveluri(root->dreapta) - nrNiveluri(root->stanga);
        calcBF(root->stanga);
        calcBF(root->dreapta);
    }
}

// Funcțiile pentru rotații
NodArb* rotatieDreapta(NodArb* root) {
    NodArb* nod1 = root->stanga;
    root->stanga = nod1->dreapta;
    nod1->dreapta = root;
    return nod1;
}

NodArb* rotatieStanga(NodArb* root) {
    NodArb* nod1 = root->dreapta;
    root->dreapta = nod1->stanga;
    nod1->stanga = root;
    return nod1;
}

NodArb* rotatieDreaptaStanga(NodArb* root) {
    root->dreapta = rotatieDreapta(root->dreapta);
    return rotatieStanga(root);
}

NodArb* rotatieStangaDreapta(NodArb* root) {
    root->stanga = rotatieStanga(root->stanga);
    return rotatieDreapta(root);
}

// Funcția pentru reechilibrare
NodArb* reechilibrare(NodArb* root) {
    calcBF(root);
    if (root->BF <= -2 && root->stanga->BF <= -1) {
        root = rotatieDreapta(root);
    }
    else if (root->BF >= 2 && root->dreapta->BF >= 1) {
        root = rotatieStanga(root);
    }
    else if (root->BF >= 2 && root->dreapta->BF <= -1) {
        root = rotatieDreaptaStanga(root);
    }
    else if (root->BF <= -2 && root->stanga->BF >= 1) {
        root = rotatieStangaDreapta(root);
    }
    return root;
}

//2. Sa se implementeze functia pentru afisarea elementelor de pe un anumit nivel din arbore,
//iar apoi sa se traverseze arborele pe niveluri.
void afisareNivel(NodArb* root, int nivel) {
	if (root == NULL) {
		return;
	}
	if (nivel == 1) {
		printf("\nidFilm: %d, denumire: %s, pret: %.2f, nrBilete: %.2f, BF=%d",
			root->inf.idFilm, root->inf.denumire, root->inf.pret, root->inf.nrBilete, root->BF);
	}
	else {
		afisareNivel(root->stanga, nivel - 1);
		afisareNivel(root->dreapta, nivel - 1);
	}
}

//3. Sa se implementeze functia pentru determinarea elementelor din nodurile frunza ale 
//arborelui si salvarea acestora intr - o alta structura de date. 
 
void afisareFrunze(NodArb* root) {
	if (root == NULL) {
		return;
	}
	if (root->stanga == NULL && root->dreapta == NULL) {
		printf("\nidFilm: %d, denumire: %s, pret: %.2f, nrBilete: %.2f, BF=%d",
			root->inf.idFilm, root->inf.denumire, root->inf.pret, root->inf.nrBilete, root->BF);
	}
	else {
		afisareFrunze(root->stanga);
		afisareFrunze(root->dreapta);
	}
}


// Funcția main
int main() {
    NodArb* root = NULL;
    int nrFilme;
    char buffer[100];
    Filme f;

    FILE* fis = fopen("filme.txt", "r");
    if (!fis) {
        printf("Eroare la deschiderea fisierului.\n");
        return -1;
    }

    fscanf(fis, "%d", &nrFilme);
    for (int i = 0; i < nrFilme; i++) {
        fscanf(fis, "%d", &f.idFilm);
        fscanf(fis, "%s", buffer);
        f.denumire = (char*)malloc(strlen(buffer) + 1);
        strcpy(f.denumire, buffer);
        fscanf(fis, "%f", &f.pret);
        fscanf(fis, "%f", &f.nrBilete);
        root = inserare(f, root);
        root = reechilibrare(root);
        free(f.denumire);
    }
    fclose(fis);

    printf("------- Preordine -------\n");
    traversarePreordine(root);

    printf("\n------- Inordine -------\n");
    traversareInordine(root);

    printf("\n------- Postordine -------\n");
    traversarePostordine(root);

    printf("\n------- Numar niveluri -------\n");
    printf("%d\n", nrNiveluri(root));

	printf("\n------- Afișare pe nivel -------\n");
	int nivel;
	printf("Introduceti nivelul dorit: ");
	scanf("%d", &nivel);
	afisareNivel(root, nivel);
	printf("\n------- Traversare pe niveluri -------\n");
	int i;
    for (i = 1; i <= nrNiveluri(root); i++) {

		printf("Nivel %d: ", i);
		afisareNivel(root, i);
		printf("\n");

    }


	printf("\n------- Frunze -------\n");
	afisareFrunze(root);
	printf("\n");

	

    dezalocare(root);
    return 0;
}
