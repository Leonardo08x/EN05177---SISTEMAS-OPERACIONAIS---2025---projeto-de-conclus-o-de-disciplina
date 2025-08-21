    #include "forca.h"

    // Variáveis globais
    char word[MAX_WORD];
    char display[MAX_WORD];
    char wrong_letters[MAX_ATTEMPTS];
    int wrong_count;
    int word_length;
    int attempts_left;
    int game_over;

    // Semáforos globais
    sem_t sem_word;
    sem_t sem_input;
    sem_t sem_check;


    // Funções
    void* choose_word(void* arg) {
        // Thread para escolher a palavra
        printf("Digite a palavra secreta (apenas letras, sem espacos): ");
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

        attempts_left = MAX_ATTEMPTS;
        wrong_count = 0;
        game_over = 0;

        sem_post(&sem_input); // Libera a thread de inserção
        return NULL;
    }

    void* input_letter(void* arg) {
        // Thread para inserção de letras
        while (!game_over) {
            sem_wait(&sem_input); // Espera o semáforo de inserção
            if (game_over) break;

            // Limpa a tela
            clear_terminal();

            // Imprime o desenho da forca
            draw_forca(attempts_left);

            printf("\nPalavra: %s\n", display); // Palavra exibida
            printf("Letras erradas: ");
            for (int i = 0; i < wrong_count; i++) {
                printf("%c ", wrong_letters[i]);
            }
            printf("\nTentativas restantes: %d\n", attempts_left); // Tentativas restantes
            printf("Digite uma letra: ");

            // Lê a letra do usuário e trata ela
            char letter;
            scanf(" %c", &letter);
            letter = tolower(letter);
            
            // Passa a letra para a thread de checagem
            *(char*)arg = letter;
            sem_post(&sem_check); // Libera a thread de checagem
        }
        return NULL;
    }

    void* check_letter(void* arg) {
        // Thread para checagem de letras
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
                printf("Letra '%c' nao esta na palavra!\n", letter);
                wrong_letters[wrong_count] = letter;
                wrong_count++;
            }
            
            // Verifica condições de fim de jogo
            if (is_word_guessed(display, word_length)) {
                clear_terminal();
                draw_forca(attempts_left);
                printf("\nParabens! Voce adivinhou a palavra: %s\n", display);
                game_over = 1;
            } else if (attempts_left <= 0) {
                clear_terminal();
                draw_forca(attempts_left);
                printf("\nGame Over! A palavra era: %s\n", word);
                game_over = 1;
            }
            
            sem_post(&sem_input); // Libera a thread de inserção
        }
        return NULL;
    }
