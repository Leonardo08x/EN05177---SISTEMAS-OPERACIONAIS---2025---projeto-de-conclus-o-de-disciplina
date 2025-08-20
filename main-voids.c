#include "utils/util-variables.c"
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <stdlib.h>
#include "utils/util-desenha-forca.c"
// Thread para escolher a palavra
void* choose_word(void* arg) {
    printf("Digite a palavra secreta (apenas letras, sem espaços): ");
    scanf("%s", word);
    word_length = strlen(word);
    
    // Inicializa a palavra exibida com '_'
    for (int i = 0; i < word_length; i++) {
        display[i] = '_';
    }
    display[word_length] = '\0';
    
    // Converte a palavra para minúsculas para simplificar a comparação
    for (int i = 0; i < word_length; i++) {
        word[i] = tolower(word[i]);
    }
    system("clear");
    sem_post(&sem_input); // Libera a thread de inserção
    return 0;
}
// Thread para inserção de letras
void* input_letter(void* arg) {
    while (!game_over) {
        sem_wait(&sem_input); // Espera o semáforo de inserção
        if (game_over) break;
        desenha_forca(attempts_left);
        printf("\nPalavra: %s\n", display);
        printf("Tentativas restantes: %d\n", attempts_left);
        printf("Digite uma letra: ");
        char letter;
        scanf(" %c", &letter);
        letter = tolower(letter);
        
        // Passa a letra para a thread de checagem
        *(char*)arg = letter;
        sem_post(&sem_check); // Libera a thread de checagem
    }
    return 0;
}
// Thread para checagem de letras
void* check_letter(void* arg) {
    while (!game_over) {
        sem_wait(&sem_check); // Espera o semáforo de checagem
        if (game_over) break;
        
        char letter = *(char*)arg;
        int found = 0;
        
        // Verifica se a letra está na palavra
        for (int i = 0; i < word_length; i++) {
            if (word[i] == letter) {
                display[i] = letter;
                found = 1;
            }
        }
        
        // Se a letra não foi encontrada, decrementa tentativas
        if (!found) {
            attempts_left--;
            printf("Letra '%c' não está na palavra!\n", letter);
        }
        
        // Verifica condições de fim de jogo
        if (is_word_guessed()) {
            printf("\nParabéns! Você adivinhou a palavra: %s\n", display);
            game_over = 1;
        } else if (attempts_left <= 0) {
            printf("\nGame Over! A palavra era: %s\n", word);
            game_over = 1;
        }
        
        sem_post(&sem_input); // Libera a thread de inserção
    }
    return 0;
}