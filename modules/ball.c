/** @file ball.c
 *  @author Zeb Barry
 *  @date 8 October 2018
 *  @brief Ball class
 *  @note Defines ball for game of pong.
 */

#include "system.h"
#include "pio.h"
#include "modules/ledmat.h"
#include "ball.h"
#include "paddle.h"
#include <stdbool.h>
#include <stdio.h>


void ball_init (Ball* ball)
{
    ball->state = true;
    ball->row = 3;
    ball->col = 0;
    ball->prev_row = 0;
    ball->prev_col = 0;
    ball->angle = STRAIGHT; // Straight down
    ball->movement_dir = TOWARDS; // Towards
    ball->moved = false;
}


void check_wall_collision(Ball* ball)
{
    if (ball->row == 0) {        // Righthand wall
        ball->angle = LEFT;
    } else if (ball->row == 6) { // Lefthand wall
        ball->angle = RIGHT;
    }
}

void check_end_collision(Ball* ball)
{
    if (ball->col == 0) {        // Far end
        ball->movement_dir = TOWARDS;
    } else if (ball->col == 4) { // Paddle end
        ball->movement_dir = AWAY;
    }
}

void check_paddle_collision(Ball* ball, Paddle* paddle)
{
    if (ball->row == paddle->rows[0]) {
        ball->angle = RIGHT;
        ball->movement_dir = AWAY;
    } else if (ball->row == paddle->rows[1]) {
        ball->angle = STRAIGHT;
        ball->movement_dir = AWAY;
    } else if (ball->row == paddle->rows[2]) {
        ball->angle = LEFT;
        ball->movement_dir = AWAY;
    }
}

// Move the ball one step.
void move_ball (Ball* ball, Paddle* paddle)
{
    if (ball->state) {
        ball->prev_row = ball->row;
        ball->prev_col = ball->col;
        if (ball->movement_dir == AWAY) {
            ball->col--;
        } else if (ball->movement_dir == TOWARDS) {
            ball->col++;
        }
        if (ball->angle == LEFT) {
            ball->row++;
        } else if (ball->angle == RIGHT) {
            ball->row--;
        }
        if (ball->col == 3 && ball->movement_dir == TOWARDS) {
            check_paddle_collision(ball, paddle);
        }
        check_wall_collision(ball);
        check_end_collision(ball);
        ball->moved = true;
    }
}

// sets ball position to row 3, col 2
void ball_reset_pos(Ball* ball) {
    ball->prev_row = ball->row;
    ball->prev_col = ball->col;
    ball->moved = true;
    ball->row = 3;
    ball->col = 0;
    ball->movement_dir = STOPPED;
}

// Update display to show new ball position.
void ball_update(Ball* ball)
{
    if (ball->state) {
        if (ball->moved) {
            pio_output_high(ledmat_cols[ball->prev_col]);
            pio_output_high(ledmat_rows[ball->prev_row]);
            ball->moved = false;
        }
        pio_output_low(ledmat_rows[ball->row]);
        pio_output_low(ledmat_cols[ball->col]);

    } else {
        pio_output_high(ledmat_rows[ball->row]);
        pio_output_high(ledmat_cols[ball->col]);
    }

}


void ball_off(Ball* ball)
{
    pio_output_high(ledmat_rows[ball->row]);
    pio_output_high(ledmat_cols[ball->col]);
}



void ball_on(Ball* ball)
{
    if (ball->state) {
        pio_output_low(ledmat_rows[ball->row]);
        pio_output_low(ledmat_cols[ball->col]);
    }
}
