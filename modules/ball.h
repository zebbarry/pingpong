/** @file ball.h
 *  @author Max Harrison
 *  @date 8 October 2018
 *  @brief Ball class header
 */

#ifndef BALL_H
#define BALL_H

#include "system.h"
#include "paddle.h"

#define STOPPED 0
#define TOWARDS 1
#define AWAY -1
#define STRAIGHT 0
#define LEFT 1
#define RIGHT -1

typedef struct ball_s Ball;

struct ball_s
{
    int row;
    int col;
    int prev_row;
    int prev_col;
    int movement_dir; // -1 for away, 1 for towards.
    int angle; // 1 = left, 0 = straight, -1 = right.
    bool moved;
    bool state; // Turns on or off the ball.
};


void ball_init (Ball* ball);

// Move the ball one step.
void move_ball (Ball* ball, Paddle* paddle);
void ball_reset_pos(Ball* ball);

void check_paddle_collision(Ball* ball, Paddle* paddle);
void check_wall_collision(Ball* ball);

void ball_update (Ball* ball);

void ball_off(Ball* ball);

void ball_on(Ball* ball);

#endif
