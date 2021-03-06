/** @file display.c
 *  @author Zeb Barry, Max Harrison
 *  @date 9 October 2018
 *  @brief Show score and end game
 *  @note Dispays score and other text.
 */

#include "system.h"
#include "modules/text.h"
#include "modules/transfer.h"
#include "modules/paddle.h"
#include "modules/ball.h"
#include "modules/pong.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"
#include <stdio.h>
#include <stdbool.h>


#define MESSAGE_RATE 10

static int REFRESH_RATE = 0;

// Displays the start screen rolling text
void start_screen(Game* game)
{
    char* message = "PUSH TO START";
    tinygl_clear();
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text(message);
    game->show_text = true;
}


// Initialiser
void score_init(int update_rate)
{
    REFRESH_RATE = update_rate;
    tinygl_init (update_rate);
    tinygl_font_set (&font3x5_1);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_STEP);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
}


// Shows the current scores for each player on the screen
bool show_score(Game* game)
{
    bool finished = false;
    static int counter;
    Ball* ball = game->ball;
    Paddle* paddle = game->paddle;
    if (!game->show_text) {
        game->show_text = true;
        paddle->state = false; // Disabling ball and paddle while
        paddle_off(paddle);    // displaying text
        ball->state = false;
        ball_off(ball);
        counter = 0;

        tinygl_clear();
        tinygl_text_mode_set (TINYGL_TEXT_MODE_STEP);
        char score[3];
        sprintf(score, "%d%d", game->your_score, game->their_score);
        score[2] = '\0';
        tinygl_text (score);
        counter++;

    } else {
        // If three seconds have passed
        counter++;
        if (counter >= (3 * REFRESH_RATE)) {
            finished = true;
            counter = 0;
            game->show_text = false;
            text_clear();
            paddle_init(paddle);
        }
    }
    return finished;
}


// Shows the winning message and disables ball and paddle
void show_win(Game* game)
{
    Paddle* paddle = game->paddle;
    Ball* ball = game->ball;

    game->show_text = true;
    paddle->state = false; // Disable game objects
    paddle_off(paddle);
    ball->state = false;
    ball_off(ball);

    tinygl_clear();
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);

    char message[13];
    sprintf(message, "YOU WON! %d-%d", game->your_score, game->their_score);
    message[12] = '\0';
    tinygl_text(message);
}


// Shows the losing message and disables ball and paddle
void show_loss(Game* game)
{
    Paddle* paddle = game->paddle;
    Ball* ball = game->ball;
    game->show_text = true;
    paddle->state = false; // Disable game objects
    paddle_off(paddle);
    ball->state = false;
    ball_off(ball);

    tinygl_clear();
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);

    char message[14];
    sprintf(message, "YOU LOST! %d-%d", game->your_score, game->their_score);
    message[13] = '\0';
    tinygl_text(message);
}


// Calls tinygl update
void text_update(void)
{
    tinygl_update();
}


// clearn text being displayed
void text_clear(void)
{
    tinygl_clear();
}
