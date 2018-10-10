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


#define MESSAGE_RATE 10


void score_init(int update_rate)
{
    tinygl_init (update_rate);
    tinygl_font_set (&font3x5_1);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_STEP);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
}


void show_score(Game* game)
{
    tinygl_clear();
    char score[3];
    sprintf(score, "%d%d", game->your_score, game->their_score);
    score[2] = '\0';
    tinygl_text (score);
    tinygl_update();
}


void show_win(Game* game)
{
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
