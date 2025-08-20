#define MAX_WORD 100
#define MAX_ATTEMPTS 6
#include <semaphore.h>

char word[MAX_WORD];           // Palavra secreta
char display[MAX_WORD];        // Palavra exibida com '_' para letras não adivinhadas
int attempts_left = MAX_ATTEMPTS; // Tentativas restantes
int word_length;
int game_over = 0;            // Flag para indicar fim do jogo
sem_t sem_word, sem_input, sem_check; // Semáforos para sincronização
int is_word_guessed() {
    for (int i = 0; i < word_length; i++) {
        if (display[i] == '_') return 0;
    }
    return 1;
}