#include "forca.h"     // Head do projeto
#include "display.h"   // Para chamar as funções de exibição

#include <ctype.h>     // Para tolower
#include <stdio.h>     // Para scanf

// Thread para inserir a letra
void* input_letter(void* arg) {
    GameState* state = (GameState*)arg; // Converte o ponteiro

    while (!state->game_over) {
        sem_wait(&state->sem_input); // Espera o semáforo de inserção
        if (state->game_over) break;

        // Atualiza o estado do jogo no terminal
        display_game_status(state);

        // Pede a letra no terminal
        scanf(" %c", &state->current_letter);
        state->current_letter = tolower(state->current_letter);

        // Libera a thread de checagem
        sem_post(&state->sem_check);
    }
    return NULL;
}