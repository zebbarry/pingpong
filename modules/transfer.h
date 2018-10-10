/** @file transfer.h
 *  @author Zeb Barry
 *  @date 8 October 2018
 *  @brief Communications header
 */

#ifndef TRANSFER_H
#define TRANSFER_H

#include "system.h"
#include "ball.h"
#include "text.h"

void transfer_init(void);

void send_score(Game* game);

void send_ball(Ball* ball);

int wait_for_reply(Game* game);

#endif
