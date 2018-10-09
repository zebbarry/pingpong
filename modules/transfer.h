/** @file transfer.h
 *  @author Zeb Barry
 *  @date 8 October 2018
 *  @brief Communications header
 */

#ifndef TRANSFER_H
#define TRANSFER_H

#include "system.h"
#include "ball.h"

void transfer_init(void);

void send_score(int score);

void send_ball(Ball* ball);

void wait_for_reply(void);

#endif
