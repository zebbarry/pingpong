/** @file display.h
 *  @author Zeb Barry, Max Harrison
 *  @date 9 October 2018
 *  @brief Display module for pong.
 */

#ifndef TEXT_H
#define TEXT_H

#include "system.h"
#include "modules/pong.h"
#include <stdbool.h>

// Displays the start screen rolling text
void start_screen(Game* game);

// Initialiser
void score_init(int update_rate);

// Shows the current scores for each player on the screen
bool show_score(Game* game);

// Shows the winning message and disables ball and paddle
void show_win(Game* game);

// Shows the losing message and disables ball and paddle
void show_loss(Game* game);

// Calls tinygl update
void text_update(void);

// clearn text being displayed
void text_clear(void);

#endif
