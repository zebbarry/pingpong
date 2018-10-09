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


void transfer_init(void)
{
    ir_uart_init();
}


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


void send_ball(Ball* ball)
{
    if (ir_uart_write_ready_p()) {
        ir_uart_putc('B');
        while (!ir_uart_write_finished_p()) {
            continue;
        }
        ir_uart_putc(ball->row);
        while (!ir_uart_write_finished_p()) {
            continue;
        }
        ir_uart_putc(ball->col);
        while (!ir_uart_write_finished_p()) {
            continue;
        }
        ir_uart_putc(ball->angle);
    }
}


void wait_for_reply(Game* game)
{
    Ball* ball = game->ball;
    char reply;

    if (ir_uart_read_ready_p()) {
        reply = ir_uart_getc();

        if (reply == 'B') {
            ball->row = ir_uart_getc();
            ball->col = ir_uart_getc();
            ball->angle = ir_uart_getc();

        } else if (reply == 'S') {
            game->your_score = ir_uart_getc();
            game->their_score = ir_uart_getc();
        }
    }
}
