#include "forca.h"

int main() {
    pthread_t t_word, t_input, t_check;
    GameState game; // Unica instancia do estado do jogo
    
    // Inicializa os semáforos bloqueados
    sem_init(&game.sem_input, 0, 0);
    sem_init(&game.sem_check, 0, 0);

    // Inicializa o estado do jogo
    game.game_over = 0;
    
    // Cria a thread inicial e passa o ponteiro para a struct
    pthread_create(&t_word, NULL, choose_word, &game);

    // Aguarda a thread de escolha da palavra terminar
    pthread_join(t_word, NULL);

    if (!game.game_over) {
        // Cria as threads de input e checagem somente se o jogo for iniciado corretamente
        pthread_create(&t_input, NULL, input_letter, &game);
        pthread_create(&t_check, NULL, check_letter, &game);

        // Libera a thread de inserção
        sem_post(&game.sem_input);

        // Aguarda as threads terminarem
        pthread_join(t_input, NULL);
        pthread_join(t_check, NULL);
    }
    
    
    // Destroi os semáforos
    sem_destroy(&game.sem_input);
    sem_destroy(&game.sem_check);

    return 0;
}

/*
 TODO:
 Verificar palavras erradas repetidas,
 Adicionar Dicas
*/