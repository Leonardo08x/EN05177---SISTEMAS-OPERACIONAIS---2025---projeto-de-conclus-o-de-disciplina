void* desenha_forca(int* erros) {
    printf("\n");
    printf("  +---+\n");
    printf("  |   |\n");
    printf("  |   %c\n", erros < 6 ? 'O' : ' ');
    printf("  |  %c%c%c\n", erros <= 4 ? '/' : ' ', erros <= 5 ? '|' : ' ', erros <= 3 ? '\\' : ' ');
    printf("  |   %c\n", erros <= 5 ? '|' : ' ');
    printf("  |  %c %c\n", erros <= 2 ? '/' : ' ', erros <= 1 ? '\\' : ' ');
    printf("  |\n");
    printf("  +---\n");
    printf("\n");
};
