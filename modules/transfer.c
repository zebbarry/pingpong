/** @file transfer.c
 *  @author Zeb Barr
 *  @date 9 October 2018
 *  @brief Transfer between boards
 *  @note Module for transmitting ball position and score between boards.
 */

#include "system.h"
#include "ir_uart.h"
#include "modules/paddle.h"
#include "modules/ball.h"
#include "modules/text.h"
#include <stdbool.h>
#include <stdlib.h>


// Initialises infra-red transmitter
void transfer_init(void)
{
    ir_uart_init();
}


// Sends score to other board
void send_score(Game* game)
{
    if (ir_uart_write_ready_p()) {
        ir_uart_putc('S');
        while (!ir_uart_write_finished_p()) {
            continue;
        }
        ir_uart_putc(game->their_score);
        while (!ir_uart_write_finished_p()) {
            continue;
        }
        ir_uart_putc(game->your_score);
    }
}


// Sends ball to other board, calculating mirrored row and angle
void send_ball(Ball* ball)
{
    int mirror_row = 0;
    int mirror_angle = -1 * ball->angle;
    if (ir_uart_write_ready_p()) {
        ir_uart_putc('B');
        while (!ir_uart_write_finished_p()) {
            continue;
        }

        // Reflect row
        mirror_row = abs(ball->row + ball->angle - 6);
        ir_uart_putc(mirror_row);
        while (!ir_uart_write_finished_p()) {
            continue;
        }
        ir_uart_putc(ball->col);
        while (!ir_uart_write_finished_p()) {
            continue;
        }

        // Invert angle if sent into edge columns
        if (mirror_row == 0 || mirror_row == 6) {
            mirror_angle = mirror_angle * -1;
        }
        ir_uart_putc(mirror_angle);
    }
}

// Checks for reply, returning 0 for no reply, 1 for ball and 2 for score
// Updates score or ball position and angle based on reply
int wait_for_reply(Game* game)
{
    Ball* ball = game->ball;
    char reply;
    int result = 0;

    // Check for reply
    if (ir_uart_read_ready_p()) {
        reply = ir_uart_getc();

        // If ball is about to be sent, recieve ball data
        if (reply == 'B') {
            result = 1;
            while (!ir_uart_read_ready_p()) {
                continue;
            }
            ball->row = ir_uart_getc();
            while (!ir_uart_read_ready_p()) {
                continue;
            }
            ball->col = ir_uart_getc();
            while (!ir_uart_read_ready_p()) {
                continue;
            }
            ball->angle = ir_uart_getc();

        } else if (reply == 'S') { // Otherwise if score sent back switch scores.
            result = 2;
            while (!ir_uart_read_ready_p()) {
                continue;
            }
            game->your_score = ir_uart_getc();
            while (!ir_uart_read_ready_p()) {
                continue;
            }
            game->their_score = ir_uart_getc();
        }
    }

    return result;
}


//  Initial recieve state waiting for a second board to send start command
bool recieve_connection(void)
{
    bool result = false;
    char ready = 'N';
    if (ir_uart_read_ready_p()) {
        ready = ir_uart_getc();
        if (ready == 'Y') {
            result = true;
        }
    }
    return result;
}


// Sends start command to second board
void send_connection(void)
{
    ir_uart_putc('Y');
    while (!ir_uart_write_finished_p()) {
        continue;
    }
}
