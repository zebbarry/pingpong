/** @file pong.c
 *  @author Zeb Barry, Max Harrison
 *  @date 17 October 2018
 *  @brief Define game and led matrix
 *  @note Defines game struct and matrix arrays.
 */

#include "system.h"
#include "pong.h"
#include "paddle.h"
#include "ball.h"

 void game_init(Game* game)
 {
     game->your_score = 0;
     game->their_score = 0;
     game->start = false;
     game->wait_turn = false;
 }
