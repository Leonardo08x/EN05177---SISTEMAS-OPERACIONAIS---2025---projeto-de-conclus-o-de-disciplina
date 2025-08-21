#ifndef FORCA_H
#define FORCA_H

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <ctype.h>
#include "utils.h"

#define MAX_WORD 100
#define MAX_ATTEMPTS 6

// Variáveis globais
extern char word[MAX_WORD]; // palavra secreta
extern char display[MAX_WORD]; // palavra exibida
extern char wrong_letters[MAX_ATTEMPTS]; // Armazena as letras erradas
extern int wrong_count; // Contador de letras erradas
extern int word_length; // comprimento da palavra
extern int attempts_left; // tentativas restantes
extern int game_over; // flag de fim de jogo

// Semáforos globais
extern sem_t sem_word; // escolha da palavra
extern sem_t sem_input; // entrada de letras
extern sem_t sem_check; // verificação de letras

// Funções
void* choose_word(void* arg);
void* input_letter(void* arg);
void* check_letter(void* arg);

#endif