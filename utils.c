#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

void draw_forca(int attempts) {
    // Desenha a forca
    printf("\n");
    printf("  +---+\n");
    printf("  |   |\n");
    printf("  |   %c\n", attempts < 6 ? 'O' : ' ');
    printf("  |  %c%c%c\n", attempts < 4 ? '/' : ' ', attempts < 5 ? '|' : ' ', attempts < 3 ? '\\' : ' ');
    printf("  |   %c\n", attempts < 5 ? '|' : ' ');
    printf("  |  %c %c\n", attempts < 2 ? '/' : ' ', attempts < 1 ? '\\' : ' ');
    printf("  |\n");
    printf("  +---\n");
    printf("\n");
}

int is_word_guessed(char* display, int word_length) {
    for (int i = 0; i < word_length; i++) {
        if (display[i] == '_') return 0;
    }
    return 1;
}

void clear_terminal() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}