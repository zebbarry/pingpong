/** @file display.h
 *  @author Zeb Barry
 *  @date 9 October 2018
 *  @brief Display module for pong.
 */

#ifndef SCORE_H
#define SCORE_H

#include "system.h"
#include "paddle.h"
#include "ball.h"
#include <stdbool.h>

typedef struct game_s Game;

struct game_s
{
    Paddle* paddle;
    Ball* ball;
    int your_score;
    int their_score;
    bool show_text;
};

void score_init(int update_rate);

void show_score(Game* game);

void show_win(Game* game);

void show_loss(Game* game);

void text_update(void);

void text_clear(void);

#endif
