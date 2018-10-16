/** @file pong.h
 *  @author Zeb Barry, Max Harrison
 *  @date 17 October 2018
 *  @brief Define pong game struct
 */

 #ifndef PONG_H
 #define PONG_H

 #include "system.h"
 #include "paddle.h"
 #include "ball.h"

 typedef struct game_s Game;

 struct game_s
 {
     Paddle* paddle;
     Ball* ball;
     int your_score;
     int their_score;
     bool show_text;
     bool start;
     bool wait_turn;
 };


 void game_init(Game* game);

#endif
