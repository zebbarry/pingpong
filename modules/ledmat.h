/** @file   ledmat.h
    @author M. P. Hayes, UCECE
    @date   23 August 2010
    @brief  LED matrix driver.

    @defgroup ledmat LED matrix driver

    This module implements a simple hardware abstraction of a LED matrix.
*/
#ifndef LEDMAT_H
#define LEDMAT_H

#include "system.h"


/** Define PIO pins driving LED matrix rows.  */
static const pio_t ledmat_rows[] =
{
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO,
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};


/** Define PIO pins driving LED matrix columns.  */
static const pio_t ledmat_cols[] =
{
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};



/** Initialise PIO pins to drive LED matrix.  */
void ledmat_init (void);


/** Display pattern on specified column.
    @param pattern bit pattern to display for selected column
    @param col selected column.  */
void ledmat_display_column (uint8_t pattern, uint8_t col);


void ledmat_clear(void);

#endif
