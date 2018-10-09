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
    int angle; // Angle - 0 = 45 left, 1 = straight, 2 = 45 right
    bool moved;
    bool state; // Turns on or off the ball.
};


void ball_init (Ball* ball);

// Symantic not going to be used just made for testing purposes.
void increase_row_ball (Ball* ball);
void decrease_row_ball (Ball* ball);
void increase_col_ball (Ball* ball);
void decrease_col_ball (Ball* ball);

void ball_update (Ball* ball);

void ball_off(Ball* ball);

void ball_on(Ball* ball);

#endif
