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
    int movement_dir; // -1 for away, 1 for towards.
    int angle; // Angle - 0 = 45 left, 1 = straight, 2 = 45 right
    bool moved;
    bool state; // Turns on or off the ball.
};


void ball_init (Ball* ball);

// Move the ball one step.
void move_ball (Ball* ball);

void ball_update (Ball* ball);

void ball_off(Ball* ball);

void ball_on(Ball* ball);

#endif
