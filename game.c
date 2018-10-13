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
#define BALL_MOVE_RATE 3
#define PADDLE_REFRESH 100
#define SWITCH_REFRESH 100
#define GAME_UPDATE 250

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
    Paddle* paddle = game->paddle;
    Ball* ball = game->ball;

    /*
    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        ball->state = !ball->state;
    }*/

    if (alternate && !game->show_text) {
        paddle_off(paddle);
        ball_update(ball); // Display ball position
    }
}


static void ball_move_task (void *data)
{
    Game* game = data;
    Paddle* player = game->paddle;
    Ball* ball = game->ball;

    move_ball(ball, player);
}


static void paddle_task (void *data)
{
    Game* game = data;
    Paddle* paddle = game->paddle;
    Ball* ball = game->ball;

    // Check for button press events and change paddle position
    if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
        increase_row(paddle);
    }

    if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
        decrease_row(paddle);
    }

    if (!alternate && !game->show_text) {
        ball_off(ball);
        paddle_update(paddle); // Display ball position
    }
}



void run_game(void *data)
{
    Game* game = data;
    Ball* ball = game->ball;
    static bool wait_for_turn = false;
    static int reply = 0;
    static bool game_over = false;
    bool finished_show_score = false;
    static bool reset = false;
    static bool displaying_score = false;


    // If ball goes to either end increase score or send ball
    if (ball->col == 0 && ball->movement_dir == -1 && !game_over) {
        ball->state = false;
        ball->col = -1;
        send_ball(ball);
        wait_for_turn = true;
    } else if (ball->col == 4 && !game_over) {
        game->their_score++;
        ball_reset_pos(ball);
        displaying_score = true;
        send_score(game);
    }

    if (displaying_score) {
        reset = show_score(game);
        if (reset) {
            displaying_score = false;
        }
    }



    // Either wait for ball or update score
    if (wait_for_turn && !game_over) {
        reply = wait_for_reply(game);
    }


    // Test send score.
    // if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
    //     reply = 2;
    //     game->your_score = 2;
    // }

    // Test wait_for reply
    // if (navswitch_push_event_p(NAVSWITCH_EAST)) {
    //     wait_for_turn = true;
    //     reply = wait_for_reply(game);
    // }


    // If either person has reached three points game over
    if (game->your_score == 3 && !game_over) {
        game_over = true;
        send_score(game);
        show_win(game);
    } else if (game->their_score == 3 && !game_over) {
        game_over = true;
        send_score(game);
        show_loss(game);
    }



    if (reply) {
        wait_for_turn = false;
        // If score sent back show score unless game_over.
        if (reply == 2 && !game_over) {
            finished_show_score = show_score(game);
            if (finished_show_score) {
                reply = 0;
                finished_show_score = 0;
            }
        }

        // If ball sent back turn back on.
        if (reply == 1) {
            ball->state = true;
            reply = 0;
        }
    }


    // If displaying text, update display
    if (game->show_text) {
        text_update();
    }
}


int main (void)
{
    // Init ball in centre
    Ball ball;
    ball_init (&ball);

    // Init paddle on bottom column
    Paddle paddle;
    paddle_init (&paddle);

    Game game = {.ball = &ball, .paddle = &paddle, .your_score = 0, .their_score = 0};

    // Initialise system and set inital dot positions
    system_init ();
    navswitch_init ();
    ledmat_init ();
    transfer_init();
    score_init(GAME_UPDATE);

    // Define tasks to run
    task_t tasks[5] =
    {
        {.func = run_game, .period = TASK_RATE / GAME_UPDATE, .data = &game},
        {.func = paddle_task, .period = TASK_RATE / PADDLE_REFRESH, .data = &game},
        {.func = ball_move_task, .period = TASK_RATE / BALL_MOVE_RATE, .data = &game},
        {.func = ball_display_task, .period = TASK_RATE / BALL_REFRESH, .data = &game},
        {.func = navswitch_task, .period = TASK_RATE / SWITCH_REFRESH}
    };

    // Run program
    task_schedule (tasks, ARRAY_SIZE (tasks));
    return 0;
}
