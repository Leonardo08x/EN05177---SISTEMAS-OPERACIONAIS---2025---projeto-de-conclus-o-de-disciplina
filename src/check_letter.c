#include "forca.h"     // Head do projeto
#include "display.h"   // Para chamar as funções de exibição

#include <ctype.h>     // Para isalpha
#include <unistd.h>    // Para sleep

// Thread para checar a letra escolhida
void* check_letter(void* arg) {
    GameState* state = (GameState*)arg; // Converte o ponteiro

    while (!state->game_over) {
        sem_wait(&state->sem_check); // Espera o semáforo de checagem
        if (state->game_over) break;

        // Verifica se a letra já foi adivinhada
        int guessed = 0;

        for (int i = 0; i < state->guessed_letters_count; i++) {
            if (state->guessed_letters[i] == state->current_letter) {
                display_repeated_letter_message(state->current_letter);
                sleep(2);
                guessed = 1;
                break;
            } else if (!isalpha(state->current_letter)) {
                display_error_input_invalid();
                sleep(2);
                guessed = 1;
                break;
            }
        }

        // Se a letra já foi adivinhada, continua para a próxima iteração
        if (guessed) {
            sem_post(&state->sem_input);
            continue;
        } else {
            state->guessed_letters[state->guessed_letters_count++] = state->current_letter;
        }

        int found = 0; // Variável para verificar se a letra foi encontrada
        int is_word_guessed = 1; // Variável para verificar se a palavra foi adivinhada

        // Verifica se a letra está na palavra
        for (int i = 0; i < state->word_length; i++) {
            if (state->word_secret[i] == state->current_letter) {
                state->word_display[i] = state->current_letter;
                found = 1;
            } else if (state->word_display[i] == '_') {
                is_word_guessed = 0; // Se ainda houver letras não adivinhadas
            }
        }
        
        // Se a letra não foi encontrada, decrementa tentativas
        if (!found) {
            state->attempts_left--;
            display_wrong_letter_message(state->current_letter);
            sleep(2);
        }
        
        // Verifica condições de fim de jogo
        if (state->attempts_left == 0) { // Se não houver mais tentativas
            display_lose_message(state);
            state->game_over = 1;
        } else if (is_word_guessed) { // Se todas as letras foram adivinhadas
            display_win_message(state);
            state->game_over = 1;
        }

        sem_post(&state->sem_input); // Libera a thread de inserção
    }
    return NULL;
}
