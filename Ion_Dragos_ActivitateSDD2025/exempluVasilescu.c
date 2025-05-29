struct Student {
    int id;
    char* nume;
    float medie;
};

Student stud;
stud.nume = (char*)malloc((strlen("Ionescu") + 1) * sizeof(char));
strcpy(stud.nume, "Ionescu");
if (stud.nume)
free(stud.nume);
stud.nume = (char*)malloc((strlen("Vasilescu") + 1) * sizeof(char));
strcpy(stud.nume, "Vasilescu");
