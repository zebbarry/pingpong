#include <stdlib.h>
#include "system.h"
#include "pio.h"
#include "navswitch.h"
#include "task.h"
#include "modules/ledmat.h"
#include "paddle.h"
#include "ball.h"
#include "transfer.h"
#include "modules/text.h"


#define BALL_REFRESH 100
#define PADDLE_REFRESH 100
#define SWITCH_REFRESH 50


static void navswitch_task (__unused__ void *data)
{
    navswitch_update(); // Check for button presses
}


// Set ball in postion.
static void ball_task (void *data)
{
    Game* game = data;
    Paddle* player_1 = game->paddle;
    Ball* ball = game->ball;

    /*
    // Check for button press events and change ball position
    if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
        increase_row_ball(ball);
    }

    if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
        decrease_row_ball(ball);
    }

    if (navswitch_push_event_p(NAVSWITCH_EAST)) {
        increase_col_ball(ball);
    }

    if (navswitch_push_event_p(NAVSWITCH_WEST)) {
        decrease_col_ball(ball);
    }
    */

    // Turn ball on or off
    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        ball->state = !ball->state;
    }

    paddle_off(player_1);
    ball_update(ball); // Display ball position
}


static void paddle_task (void *data)
{
    Game* game = data;
    Paddle* player_1 = game->paddle;
    Ball* ball = game->ball;

    // Check for button press events and change paddle position
    if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
        increase_row(player_1);
    }

    if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
        decrease_row(player_1);
    }

    ball_off(ball);
    paddle_update(player_1); //Display new paddle position
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

    // Define tasks to run
    task_t tasks[3] =
    {
        {.func = paddle_task, .period = TASK_RATE / PADDLE_REFRESH, .data = &game},
        {.func = ball_task, .period = TASK_RATE / BALL_REFRESH, .data = &game},
        {.func = navswitch_task, .period = TASK_RATE / SWITCH_REFRESH}
    };


    // Initialise system and set inital dot positions
    system_init ();
    navswitch_init ();
    ledmat_init ();
    transfer_init();


    // Run program
    task_schedule (tasks, ARRAY_SIZE (tasks));
    return 0;
}
