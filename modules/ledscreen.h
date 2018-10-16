/** @file ledscreen.h
 *  @author Zeb Barry, Max Harrison
 *  @date 17 October 2018
 *  @brief Define ledmat support functions
 */

 #ifndef LEDSCREEN_H
 #define LEDSCREEN_H

 #include "system.h"
 #include "ledmat.h"
 #include "pio.h"

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

/** Clear ledmat display */
void ledmat_clear(void);

#endif
