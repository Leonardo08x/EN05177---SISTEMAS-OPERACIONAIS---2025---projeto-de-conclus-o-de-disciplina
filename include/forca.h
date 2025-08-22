#ifndef FORCA_H
#define FORCA_H

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

#define MAX_WORD 100
#define MAX_ATTEMPTS 6

// Estrutura que centraliza todo o estado do jogo
typedef struct {
    // Variáveis de estado do jogo
    char current_letter; // Variável para comunicação entre threads
    char word_secret[MAX_WORD]; // palavra secreta
    char word_display[MAX_WORD]; // palavra exibida
    char guessed_letters[26]; // letras adivinhadas
    char hint[MAX_WORD]; // dica
    int word_length; // comprimento da palavra
    int guessed_letters_count; // contagem de letras adivinhadas
    int attempts_left; // tentativas restantes
    int game_over; // flag de fim de jogo

    // Semáforos de sincronização
    sem_t sem_input;
    sem_t sem_check;

} GameState;

// Protótipos das funções de thread
void* choose_word(void* arg);
void* input_letter(void* arg);
void* check_letter(void* arg);

#endif