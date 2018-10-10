#include <stdlib.h>
#include "system.h"
#include "pio.h"
#include "navswitch.h"
#include "task.h"
#include "modules/ledmat.h"
#include "paddle.h"
#include "ball.h"
#include "transfer.h"
#include "text.h"
#include <stdbool.h>


#define BALL_REFRESH 100
#define BALL_MOVE_RATE 2
#define PADDLE_REFRESH 100
#define SWITCH_REFRESH 100
#define TEXT_REFRESH 250

static bool alternate = false;

static void navswitch_task (__unused__ void *data)
{
    navswitch_update(); // Check for button presses
    alternate = !alternate; // Alternate showing ball and paddle.
}


// Set ball in postion.
static void ball_display_task (void *data)
{
    Game* game = data;
    Paddle* player = game->paddle;
    Ball* ball = game->ball;

    /*
    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        ball->state = !ball->state;
    }*/

    if (alternate && !game->show_text) {
        paddle_off(player);
        ball_update(ball); // Display ball position
    }
}


static void ball_move_task (void *data)
{
    Game* game = data;
    Ball* ball = game->ball;

    move_ball(ball);
}


static void paddle_task (void *data)
{
    Game* game = data;
    Paddle* player = game->paddle;
    Ball* ball = game->ball;

    // Check for button press events and change paddle position
    if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
        increase_row(player);
    }

    if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
        decrease_row(player);
    }

    if (!alternate && !game->show_text) {
        ball_off(ball);
        paddle_update(player); // Display ball position
    }
}



void run_game(void *data)
{
    Game* game = data;

    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        game->show_text = !game->show_text;
        if (game->show_text) {
            show_loss(game);
        } else {
            text_clear();
        }
    }

    if (game->show_text) {
        text_update();
    }
}


int main (void)
{
    // Init ball in centre
    static Ball ball;
    ball_init (&ball);

    // Init paddle on bottom column
    static Paddle paddle;
    paddle_init (&paddle);

    static Game game = {.ball = &ball, .paddle = &paddle, .your_score = 0, .their_score = 0};

    // Initialise system and set inital dot positions
    system_init ();
    navswitch_init ();
    ledmat_init ();
    transfer_init();
    score_init(TEXT_REFRESH);

    // Define tasks to run
    task_t tasks[5] =
    {
        {.func = paddle_task, .period = TASK_RATE / PADDLE_REFRESH, .data = &game},
        {.func = ball_move_task, .period = TASK_RATE / BALL_MOVE_RATE, .data = &game},
        {.func = ball_display_task, .period = TASK_RATE / BALL_REFRESH, .data = &game},
        {.func = navswitch_task, .period = TASK_RATE / SWITCH_REFRESH},
        {.func = run_game, .period = TASK_RATE / TEXT_REFRESH, .data = &game}
    };

    // Run program
    task_schedule (tasks, ARRAY_SIZE (tasks));
    return 0;
}
