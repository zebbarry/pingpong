/** @file paddle.c
 *  @author Zeb Barry
 *  @date 8 October 2018
 *  @brief Paddle class
 *  @note Defines paddle for game of pong.
 */

#include "system.h"
#include "pio.h"
#include "ledmat.h"
#include "paddle.h"
#include <stdbool.h>



// Initialise the paddle and turn on the respective leds.
void paddle_init (Paddle* paddle)
{
    paddle->rows[0] = 2;
    paddle->rows[1] = 3;
    paddle->rows[2] = 4;
    paddle->col = 4;
    paddle->moved = false;
    paddle->state = true;
}



// Move the paddles location up and down the display.
void increase_row (Paddle* paddle)
{
    if (paddle->rows[2] < 6) {
        paddle->prev_rows[0] = paddle->rows[0];
        paddle->prev_rows[1] = paddle->rows[1];
        paddle->prev_rows[2] = paddle->rows[2];
        paddle->moved = true;
        paddle->rows[0]++;
        paddle->rows[1]++;
        paddle->rows[2]++;
    }
}


void decrease_row (Paddle* paddle)
{
    if (paddle->rows[0] > 0) {
        paddle->prev_rows[0] = paddle->rows[0];
        paddle->prev_rows[1] = paddle->rows[1];
        paddle->prev_rows[2] = paddle->rows[2];
        paddle->moved = true;
        paddle->rows[0]--;
        paddle->rows[1]--;
        paddle->rows[2]--;
    }
}


void increase_col (Paddle* paddle)
{
    if (paddle->col < 4) {
        paddle->prev_col = paddle->col;
        paddle->moved = true;
        paddle->col++;
    }
}


void decrease_col (Paddle* paddle)
{
    if (paddle->col > 0) {
        paddle->prev_col = paddle->col;
        paddle->moved = true;
        paddle->col--;
    }
}


// Update the led display to show the new paddle location
void paddle_update(Paddle* paddle)
{
    if (paddle->state) {
        if (paddle->moved) {
            pio_output_high(ledmat_cols[paddle->prev_col]);
            pio_output_high(ledmat_rows[paddle->prev_rows[0]]);
            pio_output_high(ledmat_rows[paddle->prev_rows[1]]);
            pio_output_high(ledmat_rows[paddle->prev_rows[2]]);
            paddle->moved = false;
        }
        paddle_on(paddle);
    } else {
        paddle_off(paddle);
    }
}


void paddle_on(Paddle* paddle)
{
    pio_output_low(ledmat_rows[paddle->rows[0]]);
    pio_output_low(ledmat_rows[paddle->rows[1]]);
    pio_output_low(ledmat_rows[paddle->rows[2]]);
    pio_output_low(ledmat_cols[paddle->col]);
}


void paddle_off(Paddle* paddle)
{
    pio_output_high(ledmat_rows[paddle->rows[0]]);
    pio_output_high(ledmat_rows[paddle->rows[1]]);
    pio_output_high(ledmat_rows[paddle->rows[2]]);
    pio_output_high(ledmat_cols[paddle->col]);
}
