/** @file display.c
 *  @author Zeb Barry
 *  @date 9 October 2018
 *  @brief Show score and end game
 *  @note Dispays score and other text.
 */

#include "system.h"
#include "modules/text.h"
#include "modules/transfer.h"
#include "modules/paddle.h"
#include "modules/ball.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"
#include <stdio.h>
#include <stdbool.h>


#define MESSAGE_RATE 10

static int REFRESH_RATE = 0;

void score_init(int update_rate)
{
    REFRESH_RATE = update_rate;
    tinygl_init (update_rate);
    tinygl_font_set (&font3x5_1);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_STEP);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
}


bool show_score(Game* game)
{
    bool finished = false;
    static int counter = 0;
    Ball* ball = game->ball;
    Paddle* paddle = game->paddle;
    if (counter == 0) {
        game->show_text = true;
        paddle->state = false;
        ball->state = false;
        tinygl_clear();
        char score[3];
        sprintf(score, "%d%d", game->your_score, game->their_score);
        score[2] = '\0';
        tinygl_text (score);
    } else {
        counter++;
        // If five seconds have passed
        if (counter == (5 * REFRESH_RATE)) {
            finished = true;
            counter = 0;
            game->show_text = false;
            text_clear();
            ball_on(ball);
            paddle_on(paddle);
        }
    }

    return finished;
}


void show_win(Game* game)
{
    game->show_text = true;
    tinygl_clear();
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);

    char message[13];
    sprintf(message, "YOU WON! %d-%d", game->your_score, game->their_score);
    message[12] = '\0';
    tinygl_text(message);
}



void show_loss(Game* game)
{
    game->show_text = true;
    tinygl_clear();
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);

    char message[14];
    sprintf(message, "YOU LOST! %d-%d", game->your_score, game->their_score);
    message[13] = '\0';
    tinygl_text(message);
}


void text_update(void)
{
    tinygl_update();
}


void text_clear(void)
{
    tinygl_clear();
}