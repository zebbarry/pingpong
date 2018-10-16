/** @file transfer.h
 *  @author Zeb Barry, Max Harrison
 *  @date 8 October 2018
 *  @brief Communications header
 */

#ifndef TRANSFER_H
#define TRANSFER_H

#include "system.h"
#include "ball.h"
#include "pong.h"
#include <stdbool.h>

// Initialises infra-red transmitter
void transfer_init(void);

// Sends score to other board
void send_score(Game* game);

// Sends ball to other board, calculating mirrored row and angle
void send_ball(Ball* ball);

// Checks for reply, returning 0 for no reply, 1 for ball and 2 for score
// Updates score or ball position and angle based on reply
int wait_for_reply(Game* game);

//  Initial recieve state waiting for a second board to send start command
bool recieve_connection(void);

// Sends start command to second board
bool send_connection(void);

#endif
