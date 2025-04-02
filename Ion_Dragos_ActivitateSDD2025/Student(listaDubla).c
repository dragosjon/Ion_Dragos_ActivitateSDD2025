#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <string.h>
#include <stdio.h>

typedef struct{
	int varsta;
	char* nume;
	float medie;
}Student;

typedef struct {
	Student inf;
	struct nodLS* next;
	struct nodLS* prev;
}nodLS;

void inserareNodLS(nodLS** cap, nodLS** ultim, Student s) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));

	nou->next = NULL;
	nou->prev = NULL;

	nou->inf.varsta = s.varsta;

	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);

	nou->inf.medie = s.medie;

	if (*cap == NULL) {
		*cap = nou;
		*ultim = nou;
	}
	else {
		nodLS* temp = *cap;

		while(temp->next)
			temp = temp->next;

			temp->next = nou;
			nou->prev = temp;
			*ultim = nou;
		
	}
}

void traversareNodLS(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		printf("Varsta = %d, Nume = %s, Medie = %f",
			temp->inf.varsta, temp->inf.nume, temp->inf.medie);
		printf("\n");
		temp = temp->next;
	}
}

void traversareInversaNodLS(nodLS* ultim) {
	nodLS* temp = ultim;
	while (temp) {
		printf("Varsta = %d, Nume = %s, Medie = %f",
			temp->inf.varsta, temp->inf.nume, temp->inf.medie);
		printf("\n");
		temp = temp->prev;
	}
}

Student citireStudent(FILE* file) {
	Student s;
	char buffer[100];

	fscanf(file, "%d", &s.varsta);

	fscanf(file, "%s", buffer);
	s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(s.nume, buffer);

	fscanf(file, "%f", &s.medie);

	return s;
}


void dezalocare(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		nodLS* aux = temp->next;
		free(temp->inf.nume);
		free(temp);
		temp = aux;
	}
}

int main() {
	int n = 3;
	nodLS* cap = NULL, * ultim = NULL;

	FILE* file = fopen("student.txt", "r");

	Student s;
	for (int i = 0; i < n; i++) {
		s = citireStudent(file);
		inserareNodLS(&cap, &ultim, s);
		free(s.nume);
	}

	traversareNodLS(cap);
	printf("\n");
	traversareInversaNodLS(cap);
	printf("\n");
	
	dezalocare(cap);
}