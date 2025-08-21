#include "forca.h"

int main() {
    pthread_t t_word, t_input, t_check;
    char letter; // Variável compartilhada para a letra inserida
    
    // Inicializa os semáforos
    sem_init(&sem_word, 0, 1);  // Começa com a escolha da palavra
    sem_init(&sem_input, 0, 0); // Input começa bloqueado
    sem_init(&sem_check, 0, 0); // Checagem começa bloqueada
    
    // Cria as threads
    pthread_create(&t_word, NULL, choose_word, NULL);
    pthread_create(&t_input, NULL, input_letter, &letter);
    pthread_create(&t_check, NULL, check_letter, &letter);
    
    // Aguarda as threads terminarem
    pthread_join(t_word, NULL);
    pthread_join(t_input, NULL);
    pthread_join(t_check, NULL);
    
    // Destroi os semáforos
    sem_destroy(&sem_word);
    sem_destroy(&sem_input);
    sem_destroy(&sem_check);
    
    return 0;
}

/*
 TODO:
 Verificar palavras erradas repetidas,
 Adicionar Dicas
*/