#include <stdio.h>

union Data {
    int i;
    float f;
    char str[20];
};

int main() {
    printf("Size of union: %zu\n", sizeof(union Data));
    return 0;
}