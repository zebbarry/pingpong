/** @file paddle.c
 *  @author Zeb Barry
 *  @date 8 October 2018
 *  @brief Paddle class
 *  @note Defines paddle for game of pong.
 */

#ifndef PADDLE_H
#define PADDLE_H

#include "system.h"

typedef struct paddle_s Paddle;

void paddle_init (Paddle* paddle);

void increase_row (Paddle* paddle);

void increase_col (Paddle* paddle);

void decrease_row (Paddle* paddle);

void decrease_col (Paddle* paddle);

void paddle_update (Paddle* paddle);

#endif
