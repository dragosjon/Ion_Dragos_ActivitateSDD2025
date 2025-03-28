#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <malloc.h>
#include <stdio.h>

typedef struct {
	unsigned int idCursa;
	char* destinatie;
	char* dataPlecare;
	unsigned char pasageriInregistrati;
}CursaAeriana;