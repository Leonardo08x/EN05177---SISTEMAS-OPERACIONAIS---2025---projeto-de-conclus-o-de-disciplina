#include "display.h"   // Header do display

#include <stdio.h>     // Para printf
#include <stdlib.h>    // Para system

// Função para limpar o terminal
void display_clear_terminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Função para exibir o prompt de entrada da palavra secreta
void display_prompt_for_secret_word() {
    printf("\nDigite a palavra secreta (apenas letras, sem espacos): ");
}

// Função para exibir o erro de entrada maior que a permitida
void display_error_input_overflow() {
    printf("Entrada invalida. Tente novamente.\n");
}

// Função para exibir o erro de entrada vazia
void display_error_input_empty() {
    printf("Entrada vazia. Tente novamente.\n");
}

// Função para exibir o erro de entrada incorreta
void display_error_input_invalid() {
    printf("Entrada invalida, não é uma letra. Tente novamente.\n");
}

// Função para exibir o desenho da forca
void display_draw_forca(int attempts_left) {
    display_clear_terminal();
    printf("\n");
    printf("  +---+\n");
    printf("  |   |\n");
    printf("  |   %c\n", attempts_left < 6 ? 'O' : ' ');
    printf("  |  %c%c%c\n", attempts_left < 4 ? '/' : ' ', attempts_left < 5 ? '|' : ' ', attempts_left < 3 ? '\\' : ' ');
    printf("  |   %c\n", attempts_left < 5 ? '|' : ' ');
    printf("  |  %c %c\n", attempts_left < 2 ? '/' : ' ', attempts_left < 1 ? '\\' : ' ');
    printf("  |\n");
    printf("  +---\n\n");
}

// Função para exibir o status do jogo
void display_game_status(const GameState* state) {
    display_draw_forca(state->attempts_left);
    printf("Palavra: %s\n", state->word_display);
    printf("Letras adivinhadas: ");
    for (int i = 0; i < state->guessed_letters_count; i++) {
        printf("%c ", state->guessed_letters[i]);
    }
    printf("\nTentativas restantes: %d\n", state->attempts_left);
    printf("\nDigite uma letra: ");
}

// Função para exibir a mensagem de letra repetida
void display_repeated_letter_message(char current_letter) {
    printf("\nLetra escolhida ja foi adivinhada: %c\n", current_letter);
}

// Função para exibir a mensagem de letra errada
void display_wrong_letter_message(char current_letter) {
    printf("\nLetra escolhida nao existe na palavra: %c\n", current_letter);
}

// Função para exibir a mensagem de vitória
void display_win_message(const GameState* state) {
    display_draw_forca(state->attempts_left);
    printf("Parabens! Voce adivinhou a palavra: %s\n", state->word_secret);
}

// Função para exibir a mensagem de derrota
void display_lose_message(const GameState* state) {
    display_draw_forca(state->attempts_left);
    printf("Que pena! Voce perdeu. A palavra era: %s\n", state->word_secret);
}