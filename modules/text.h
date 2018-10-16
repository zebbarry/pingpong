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

void start_screen(Game* game);

void score_init(int update_rate);

bool show_score(Game* game);

void show_win(Game* game);

void show_loss(Game* game);

void text_update(void);

void text_clear(void);

#endif
