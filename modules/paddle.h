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

void paddle_init (Paddle* paddle);

void increase_row (Paddle* paddle);
void decrease_row (Paddle* paddle);

void paddle_update (Paddle* paddle);

void paddle_off (Paddle* paddle);
void paddle_on (Paddle* paddle);

#endif
