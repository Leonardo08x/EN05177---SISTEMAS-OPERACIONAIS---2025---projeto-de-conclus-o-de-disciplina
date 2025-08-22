#ifndef DISPLAY_H
#define DISPLAY_H

#include "forca.h" // Precisa da definição de GameState

// Protótipos para todas as funções que imprimem algo na tela
void display_clear_terminal();
void display_prompt_for_secret_word();
void display_error_input_overflow();
void display_error_input_empty();
void display_error_input_invalid();
void display_draw_forca(int attempts_left);
void display_game_status(const GameState* state);
void display_repeated_letter_message(char current_letter);
void display_wrong_letter_message(char current_letter);
void display_win_message(const GameState* state);
void display_lose_message(const GameState* state);

#endif