#include <stdio.h>
#include <stdlib.h>

int main() {
    int rows = 2; // Numărul de rânduri
    int cols = 3; // Numărul de coloane

    // Alocăm un vector de pointeri pentru rânduri
    int** pnumem = (int**)malloc(rows * sizeof(int*));
    if (pnumem == NULL) {
        printf("Eroare la alocarea memoriei pentru vectorul de pointeri!\n");
        return 1;
    }

    // Alocăm memorie pentru fiecare rând
    for (int i = 0; i < rows; i++) {
        pnumem[i] = (int*)malloc(cols * sizeof(int));
        if (pnumem[i] == NULL) {
            printf("Eroare la alocarea memoriei pentru rândul %d!\n", i);
            return 1;
        }
    }

    // Inițializăm matricea
    int value = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            pnumem[i][j] = value++; // Exemplu: 1, 2, 3, 4, 5, 6
        }
    }

    // Afișăm matricea folosind aritmetica de pointeri
    printf("Matricea este:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Accesăm elementul folosind aritmetica de pointeri
            printf("%d ", *(*(pnumem + i) + j));
        }
        printf("\n");
    }

    // Explicăm accesul la elemente folosind aritmetica de pointeri
    printf("\nExplicație pentru accesul la elemente:\n");
    printf("Adresa primului rAnd (pnumem): %p\n", (void*)pnumem);
    printf("Adresa celui de-al doilea rand (pnumem + 1): %p\n", (void*)(pnumem + 1));
    printf("Adresa primului element din al doilea rand (*(pnumem + 1)): %p\n", (void*)*(pnumem + 1));
    printf("Adresa celui de-al treilea element din al doilea rand (*(pnumem + 1) + 2): %p\n", (void*)(*(pnumem + 1) + 2));
    printf("Valoarea celui de-al treilea element din al doilea rand (*(*(pnumem + 1) + 2)): %d\n", *(*(pnumem + 1) + 2));

    // Eliberăm memoria alocată
    for (int i = 0; i < rows; i++) {
        free(pnumem[i]); // Eliberăm fiecare rând
    }
    free(pnumem); // Eliberăm vectorul de pointeri

    return 0;
}
