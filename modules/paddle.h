/** @file paddle.h
 *  @author Zeb Barry, Max Harrison
 *  @date 8 October 2018
 *  @brief Paddle class header
 */

#ifndef PADDLE_H
#define PADDLE_H

#include "system.h"

typedef struct paddle_s Paddle;

struct paddle_s
{
    int rows[3];
    int col;
    int prev_rows[3];
    int prev_col;
    bool moved;
    bool state;

};
// Initialise the paddle and turn on the respective leds.
void paddle_init (Paddle* paddle);

// Move the paddles location up and down the display.
void increase_row (Paddle* paddle);
void decrease_row (Paddle* paddle);

// Update the led display to show the new paddle location
void paddle_update (Paddle* paddle);

// Turns paddle on and off from being displayed
void paddle_off (Paddle* paddle);
void paddle_on (Paddle* paddle);

#endif
