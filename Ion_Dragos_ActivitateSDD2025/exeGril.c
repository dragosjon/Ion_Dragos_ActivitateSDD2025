#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char* nume;
    float medie;
} Student;

typedef struct Nod {
    Student st;
    struct Nod* next;
} Nod;

void functie(Nod* p) {
    while (p) {
        printf("%d %s %5.2f\n", p->st.id, p->st.nume, p->st.medie);
        p = p->next;
    }
}

// funcție pentru creare nod nou
Nod* creareNod(int id, const char* nume, float medie) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->st.id = id;
    nou->st.nume = (char*)malloc(strlen(nume) + 1);
    strcpy(nou->st.nume, nume);
    nou->st.medie = medie;
    nou->next = NULL;
    return nou;
}

int main() {
    // Creăm manual o listă de studenți
    Nod* prim = creareNod(1, "Ana", 8.75);
    prim->next = creareNod(2, "Bogdan", 9.40);
    prim->next->next = creareNod(3, "Clara", 7.80);

    // Apelăm funcția
    functie(prim);

    // Eliberăm memoria
    Nod* p = prim;
    while (p) {
        Nod* temp = p;
        p = p->next;
        free(temp->st.nume);
        free(temp);
    }

    return 0;
}
