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


void score_init(int update_rate)
{
    tinygl_init (update_rate);
    tinygl_font_set (&font3x5_1);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_STEP);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
}


void show_score(Game* game)
{
    char score[3];
    sprintf(score, "%d%d", game->your_score, game->their_score);
    tinygl_text (score);
}
