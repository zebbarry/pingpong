/** @file ball.c
 *  @author Zeb Barry
 *  @date 8 October 2018
 *  @brief Ball class
 *  @note Defines ball for game of pong.
 */

#include "system.h"
#include "pio.h"
#include "ledmat.h"
#include "ball.h"
#include <stdbool.h>
#include <stdio.h>


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



void ball_init (Ball* ball)
{
    ball->state = true;
    ball->row = 3;
    ball->col = 2;
    ball->prev_row = 0;
    ball->prev_col = 0;
    ball->moved = false;
    pio_output_low(ledmat_rows[ball->row]);
    pio_output_low(ledmat_cols[ball->col]);
}


// Move the paddles location up and down the display.
void increase_row_ball (Ball* ball)
{
    if (ball->col < 6) {
        ball->prev_row = ball->row;
        ball->moved = true;
        ball->row++;
    }
}


void decrease_row_ball (Ball* ball)
{
    if (ball->row > 0) {
        ball->prev_row = ball->row;
        ball->moved = true;
        ball->row--;
    }
}


void increase_col_ball (Ball* ball)
{
    if (ball->col < 4) {
        ball->prev_col = ball->col;
        ball->moved = true;
        ball->col++;
    }
}


void decrease_col_ball (Ball* ball)
{
    if (ball->col > 0) {
        ball->prev_col = ball->col;
        ball->moved = true;
        ball->col--;
    }
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

