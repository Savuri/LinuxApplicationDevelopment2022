#include <stdio.h>

int main(void) {
    char c = getchar();
    printf("Hello, ");
    while (c != '\n' && c != EOF) {
        putchar(c);
        c = getchar();
    }

    printf("!\n");
}