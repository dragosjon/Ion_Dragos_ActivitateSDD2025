#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <string.h>
#include <stdio.h>

typedef struct
{
	int varsta;
	char* nume;
	float medie;
} Student;

typedef struct {
	Student inf;
	struct nodLS* next;
}nodLS;

typedef struct {
	struct nodLS* capLS;
	struct nodLP* next;
}nodLP;

void inserareNodLS(nodLS** capLS, Student s) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));

	nou->next = NULL;
	
	nou->inf.varsta = s.varsta;

	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);

	nou->inf.medie = s.medie;

	if (*capLS == NULL) {
		*capLS = nou;
	}
	else {
		nodLS* temp = *capLS;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nou;

	}
}

void inserareNodLP(nodLP** capLP, nodLS* capLS) {
	nodLP* nou = (nodLP*)malloc(sizeof(nodLP));

	nou->capLS = capLS;

	nou->next = NULL;

	if (*capLP == NULL) {
		*capLP = nou;
	}
	else {
		nodLP* temp = *capLP;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nou;

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

void traversareNodLP(nodLP* cap) {
	nodLP* temp = cap;
	while (temp){
		printf("\nSublista:");
		traversareNodLS(temp->capLS);
		temp = temp->next;
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

void dezalocareLS(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		nodLS* aux = temp->next;
		free(temp->inf.nume);
		free(temp);
		temp = aux;
	}
}

void dezalocareLP(nodLP* cap) {
	nodLP* temp = cap;
	while (temp){
		nodLP* aux = temp->next;
		dezalocareLS(temp->capLS);
		free(temp);
		temp = aux;
	}
}

int main() {
	int n = 3;
	nodLP* capLP = NULL;
	nodLS* promovat = NULL, *nepromovat = NULL;

	FILE* file = fopen("student.txt", "r");

	Student s;
	for (int i = 0; i < n; i++) {
		s = citireStudent(file);

		if (s.medie > 5.0) {
			inserareNodLS(&promovat, s);
		}
		else {
			inserareNodLS(&nepromovat, s);
		}

		free(s.nume);
	}

	inserareNodLP(&capLP, promovat);
	inserareNodLP(&capLP, nepromovat);

	traversareNodLP(capLP);

	dezalocareLP(capLP);
}