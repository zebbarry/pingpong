/** @file ball.h
 *  @author Zeb Barry
 *  @date 8 October 2018
 *  @brief Ball class header
 */

#ifndef BALL_H
#define BALL_H

#include "system.h"

typedef struct ball_s Ball;

struct ball_s
{
    int row;
    int col;
    int prev_row;
    int prev_col;
    bool moved;
    bool state;
};


void ball_init (Ball* ball);

void increase_row_ball (Ball* ball);
void decrease_row_ball (Ball* ball);
void increase_col_ball (Ball* ball);
void decrease_col_ball (Ball* ball);

void ball_update (Ball* ball);

#endif
