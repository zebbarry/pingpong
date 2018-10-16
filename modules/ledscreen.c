/** @file ledscreen.h
 *  @author Zeb Barry, Max Harrison
 *  @date 17 October 2018
 *  @brief Define ledmat support functions
 *  @note Clears display
 */

 #include "system.h"
 #include "ledscreen.h"
 #include "ledmat.h"
 #include "pio.h"

// Clear display
void ledmat_clear(void)
{
    int i = 0;
    for (i = 0; i < LEDMAT_ROWS_NUM; i++) {
        pio_output_high(ledmat_rows[i]);
    }

    for (i = 0; i < LEDMAT_COLS_NUM; i++) {
        pio_output_high(ledmat_cols[i]);
    }
}
