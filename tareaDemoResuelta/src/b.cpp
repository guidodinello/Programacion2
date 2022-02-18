#include <string.h>

void b(char p1[100], char p2[100], char concat[100]) {
    strcpy(concat, p1);
    strcat(concat, p2);
}
