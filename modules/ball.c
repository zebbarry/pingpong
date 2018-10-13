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
    ball->angle = 1; // Straight down
    ball->movement_dir = 1; // Towards
    ball->moved = false;
}


void check_wall_collision(Ball* ball)
{
    if (ball->row == 0) {        // Righthand wall
        ball->angle = 0;
    } else if (ball->row == 6) { // Lefthand wall
        ball->angle = 2;
    }
}

void check_end_collision(Ball* ball)
{
    if (ball->col == 0) {        // Far end
        ball->movement_dir = 1;
    } else if (ball->col == 4) { // Paddle end
        ball->movement_dir = -1;
    }
}

void check_paddle_collision(Ball* ball, Paddle* paddle)
{
    if (ball->row == paddle->rows[1] - 1) {
        ball->angle = 2;
        ball->movement_dir = -1;
    } else if (ball->row == paddle->rows[1]) {
        ball->angle = 1;
        ball->movement_dir = -1;
    } else if (ball->row == paddle->rows[1] + 1) {
        ball->angle = 0;
        ball->movement_dir = -1;
    }
}

// Move the ball one step.
void move_ball (Ball* ball, Paddle* paddle)
{
    if (ball->movement_dir) {
        ball->prev_row = ball->row;
        ball->prev_col = ball->col;
        if (ball->movement_dir == -1) {
            ball->col--;
        } else if (ball->movement_dir == 1) {
            ball->col++;
        }
        if (ball->angle == 0) {
            ball->row++;
        } else if (ball->angle == 2) {
            ball->row--;
        }
        if (ball->col == 3 && ball->movement_dir == 1) {
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
    ball->movement_dir = 0;
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
