/** @file ball.c
 *  @author Max Harrison, Zeb Barry
 *  @date 8 October 2018
 *  @brief Ball class
 *  @note Defines ball for game of pong.
 */

#include "system.h"
#include "pio.h"
#include "ledmat.h"
#include "ledscreen.h"
#include "ball.h"
#include "paddle.h"
#include <stdbool.h>
#include <stdio.h>


void ball_init (Ball* ball)
{
    ball->state = false;
    ball->row = 3;
    ball->col = 0;
    ball->prev_row = 0;
    ball->prev_col = 0;
    ball->angle = STRAIGHT; // Straight down
    ball->movement_dir = TOWARDS; // Towards
    ball->moved = false;
}

// Checks if ball will hit a wall, changes angle if so
void check_wall_collision(Ball* ball)
{
    if (ball->row == 0) {        // Righthand wall
        ball->angle = LEFT;
    } else if (ball->row == 6) { // Lefthand wall
        ball->angle = RIGHT;
    }
}

// Check if ball will collide with the baddle, if so, change direction.
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

// Move the ball one step as long as state is true
void move_ball (Ball* ball, Paddle* paddle)
{
    if (ball->state) {
        ball->prev_row = ball->row;
        ball->prev_col = ball->col;
        ball->col += ball->movement_dir;
        ball->row += ball->angle;
        if (ball->col == 3 && ball->movement_dir == TOWARDS) {
            check_paddle_collision(ball, paddle);
        }
        check_wall_collision(ball);
        ball->moved = true;
    }
}

// Sets ball position to the middle top of the display
void ball_reset_pos(Ball* ball) {
    ball->prev_row = ball->row;
    ball->prev_col = ball->col;
    ball->moved = true;
    ball->row = 3;
    ball->col = 0;
    ball->movement_dir = STOPPED;
    ball->angle = STRAIGHT;
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

// Turn off ball on display
void ball_off(Ball* ball)
{
    pio_output_high(ledmat_rows[ball->row]);
    pio_output_high(ledmat_cols[ball->col]);
}
