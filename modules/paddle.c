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



/** Define PIO pins driving LED matrix rows.  */
static const pio_t ledmat_rows[] =
{
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO, 
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};


/** Define PIO pins driving LED matrix columns.  */
static const pio_t ledmat_cols[] =
{
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};



// Initialise the paddle and turn on the respective leds.
void paddle_init (Paddle* paddle)
{
    paddle->rows[0] = 3;
    paddle->rows[1] = 4;
    paddle->col = 4;
    paddle->moved = false;
    pio_output_low(ledmat_rows[paddle->rows[0]]);
    pio_output_low(ledmat_rows[paddle->rows[1]]);
    pio_output_low(ledmat_cols[paddle->col]);
}



// Move the paddles location up and down the display.
void increase_row (Paddle* paddle)
{
    if (paddle->rows[1] < 6) {
        paddle->prev_rows[0] = paddle->rows[0];
        paddle->prev_rows[1] = paddle->rows[1];
        paddle->moved = true;
        paddle->rows[0]++;
        paddle->rows[1]++;
    }
}


void decrease_row (Paddle* paddle)
{
    if (paddle->rows[0] > 0) {
        paddle->prev_rows[0] = paddle->rows[0];
        paddle->prev_rows[1] = paddle->rows[1];
        paddle->moved = true;
        paddle->rows[0]--;
        paddle->rows[1]--;
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
    if (paddle->moved) {    
        pio_output_high(ledmat_cols[paddle->prev_col]);
        pio_output_high(ledmat_rows[paddle->prev_rows[0]]);
        pio_output_high(ledmat_rows[paddle->prev_rows[1]]);
        paddle->moved = false;
    }
    
    pio_output_low(ledmat_cols[paddle->col]);
    pio_output_low(ledmat_rows[paddle->rows[0]]);
    pio_output_low(ledmat_rows[paddle->rows[1]]);
}


void paddle_on(Paddle* paddle)
{    
    pio_output_low(ledmat_rows[paddle->rows[0]]);
    pio_output_low(ledmat_rows[paddle->rows[1]]);
    pio_output_low(ledmat_cols[paddle->col]);
}


void paddle_off(Paddle* paddle)
{    
    pio_output_high(ledmat_rows[paddle->rows[0]]);
    pio_output_high(ledmat_rows[paddle->rows[1]]);
    pio_output_high(ledmat_cols[paddle->col]);
}
