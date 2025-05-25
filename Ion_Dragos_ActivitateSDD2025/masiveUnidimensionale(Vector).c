#include <stdio.h>
#include <stdlib.h> // Pentru malloc și free

int main() {
    // Declararea unui pointer pentru masiv
    int *numbers;

    // Alocarea dinamică a unui masiv de 5 elemente pe heap
    numbers = (int *)malloc(5 * sizeof(int));
    if (numbers == NULL) {
        // Verificăm dacă alocarea a eșuat
        printf("Eroare la alocarea memoriei!\n");
        return 1;
    }

    // Inițializarea elementelor masivului
    for (int i = 0; i < 5; i++) {
        numbers[i] = (i + 1) * 10; // Exemplu: 10, 20, 30, 40, 50
    }

    // Afișarea elementelor masivului
    printf("Elementele masivului sunt:\n");
    for (int i = 0; i < 5; i++) {
        printf("Elementul %d: %d\n", i, numbers[i]);
    }

    // Eliberarea memoriei alocate
    free(numbers);

    return 0;
}
