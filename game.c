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
#include "led.h"


#define BALL_MOVE_RATE 2
#define DISPLAY_REFRESH 100
#define GAME_UPDATE 250

static bool alternate = false;


bool start_sequence(Game* game)
{
    Paddle* paddle = game->paddle;
    Ball* ball = game->ball;
    bool start_with_ball = false;

    // Wait for other board before starting
    if (!game->start) {
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            text_clear();
            ledmat_clear();
            game->show_text = false;
            ball->state = true;
            paddle_init(paddle);
            paddle->state = true;
            game->start = true;
            start_with_ball = true;
            led_set(LED1, 1);
            send_connection();
        }

        if (!start_with_ball) {
            game->start = recieve_connection();
        }
    }


    return start_with_ball;
}


void run(Game* game, bool game->wait_turn)
{
    Ball* ball = game->ball;
    static int reply = 0;
    static bool game_over = false;
    static bool reset = false;
    static bool displaying_score = false;


    // If ball goes to either end increase score or send ball
    if (ball->col == 0 && ball->movement_dir == AWAY && !game_over) {
        ball->state = false;
        ball->movement_dir = STOPPED; // Stop moving
        send_ball(ball);
        game->wait_turn = true;
    } else if (ball->col == 4 && !game_over) {
        game->their_score++;
        if (game->their_score != 3) {  // Check wasn't winning point
            displaying_score = true;
            send_score(game);
            ball_reset_pos(ball);
        }
    }


    // Either wait for ball or update score
    if (game->wait_turn && !game_over) {
        reply = wait_for_reply(game);
    }


    // If either person has reached three points game over
    if (game->your_score == 3 && !game_over) {
        game_over = true;
        ball_reset_pos(ball);
        send_score(game);
        show_win(game);
        ball_reset_pos(ball);
    } else if (game->their_score == 3 && !game_over) {
        game_over = true;
        send_score(game);
        show_loss(game);
        ball_reset_pos(ball);
    }


    if (reply) {
        game->wait_turn = false;
        // If score sent back show score unless game_over.
        if (reply == 2 && !game_over) {
            displaying_score = true;
        }

        // If ball sent back turn back on.
        if (reply == 1) {
            ball->state = true;
            reply = 0;
        }
    }


    // Show score for set time.
    if (displaying_score) {
        reset = show_score(game);
        if (reset) {
            displaying_score = false;
            reply = 0;
            ledmat_clear();
            ball->movement_dir = TOWARDS;
        }
    }


    // Reset game, for debugging purposes.
    if (game_over) {
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            game_over = false;
            game->show_text = false;
            text_clear();
            ledmat_clear();
            ball_init(ball);
            paddle_init(game->paddle);
            ball_on(ball);
            paddle_on(game->paddle);
            game->your_score = 0;
            game->their_score = 0;
        }
    }
}


static void ball_move_task (void *data)
{
    Game* game = data;
    Paddle* paddle = game->paddle;
    Ball* ball = game->ball;

    if (game->start) {
        move_ball(ball, paddle);
    }
}


static void display_task (void *data)
{
    Game* game = data;
    Paddle* paddle = game->paddle;
    Ball* ball = game->ball;
    navswitch_update(); // Check for button presses

    // Check for button press events and change paddle position
    if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
        increase_row(paddle);
    }

    if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
        decrease_row(paddle);
    }


    alternate = !alternate; // Alternate showing ball and paddle.
    if (alternate && !game->show_text) {
        ledmat_clear();
        ball_update(ball); // Display ball position
    } else if (!alternate && !game->show_text) {
        ledmat_clear();
        paddle_update(paddle); // Display paddle position
    }
}



void controller(void *data)
{
    Game* game = data;
    bool begin_with_ball = false;

    if (!game->start) {
        begin_with_ball = start_sequence(game);
        if (game->start && !begin_with_ball) {
            game->wait_turn = true;
            text_clear();
            ledmat_clear();
            game->show_text = false;
            ball->state = true;
            paddle_init(paddle);
            paddle->state = true;
        }
    } else {
        run(game);
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
    ball.state = false;

    // Init paddle on bottom column
    Paddle paddle;
    paddle_init (&paddle);
    paddle.state = false;

    Game game;
    game_init(&game);

    // Initialise system and set inital dot positions
    system_init ();
    navswitch_init ();
    ledmat_init ();
    transfer_init();
    led_init();
    led_set(LED1, 0);
    score_init(GAME_UPDATE);

    // Define tasks to run
    task_t tasks[3] =
    {
        {.func = controller, .period = TASK_RATE / GAME_UPDATE, .data = &game},
        {.func = display_task, .period = TASK_RATE / DISPLAY_REFRESH, .data = &game},
        {.func = ball_move_task, .period = TASK_RATE / BALL_MOVE_RATE, .data = &game},
    };

    // Show title
    start_screen(&game);

    // Run program
    task_schedule (tasks, ARRAY_SIZE (tasks));
    return 0;
}
