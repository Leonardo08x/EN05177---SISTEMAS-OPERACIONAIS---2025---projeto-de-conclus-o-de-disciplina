#include "forca.h"     // Head do projeto
#include "display.h"   // Para chamar as funções de exibição

#include <stdio.h>     // Para fgets
#include <string.h>    // Para strlen, strcspn
#include <ctype.h>     // Para tolower, isalpha

// Thread para escolher a palavra
void* choose_word(void* arg) {
    GameState* state = (GameState*)arg; // Converte o ponteiro

    int is_word_valid = 0; // Variável para verificar se a palavra é válida

    // Loop para garantir que a palavra seja válida
    do {
        // Pede a palavra secreta no terminal
        display_prompt_for_secret_word();

        // Verifica se a entrada é inválida (maior do que o permitido)
        if (fgets(state->word_secret, MAX_WORD, stdin) == NULL) {
            // Informa no terminal que a entrada é inválida
            display_error_input_overflow();
            continue;
        }

        // Elimina a quebra de linha no final e guarda o tamanho dela
        state->word_secret[strcspn(state->word_secret, "\n")] = 0;
        state->word_length = strlen(state->word_secret);
        
        // Verifica se a palavra não é vazia
        if (state->word_length == 0) {
            display_error_input_empty();
            continue;
        }
        
        is_word_valid = 1; // Presume a validade da palavra

        // Percorre a palavra
        for (int i = 0; i < state->word_length; i++) {
            // Verifica se cada elemento é de fato uma letra
            if (!isalpha(state->word_secret[i])) {
                is_word_valid = 0;
                display_error_input_invalid();
                break;
            }
            // Converte a letra para minúscula
            state->word_secret[i] = tolower(state->word_secret[i]);
            state->word_display[i] = '_'; // Inicializa a palavra exibida com '_'
        }
    } while (!is_word_valid);
    
    // Inicializa o estado do jogo
    state->word_display[state->word_length] = '\0';
    state->guessed_letters_count = 0;    
    state->attempts_left = MAX_ATTEMPTS;

    return NULL;
}
