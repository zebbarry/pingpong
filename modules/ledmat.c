/** @file   ledmat.c
    @author M. P. Hayes, UCECE
    @date   23 August 2010
    @brief  LED matrix driver.
*/
#include "system.h"
#include "pio.h"
#include "ledmat.h"


/** Initialise PIO pins to drive LED matrix.  */
void ledmat_init (void)
{
    uint8_t row;
    uint8_t col;

    for (row = 0; row < LEDMAT_ROWS_NUM; row++)
    {
        /* The rows are active low so configure PIO as an initially
           high output.  */
        pio_config_set (ledmat_rows[row], PIO_OUTPUT_HIGH);
    }

    for (col = 0; col < LEDMAT_COLS_NUM; col++)
    {
        /* The columns are active low so configure PIO as an initially
           high output.  */
        pio_config_set (ledmat_cols[col], PIO_OUTPUT_HIGH);
    }
}


/** Display pattern on specified column.
    @param pattern bit pattern to display for selected column
    @param col selected column.  */
void ledmat_display_column (uint8_t pattern, uint8_t col)
{
    static uint8_t col_prev = 0;
    uint8_t row;

    /* Disable previous column to prevent ghosting while rows modified.  */
    pio_output_high (ledmat_cols[col_prev]);

    /* Activate desired rows based on desired pattern.  */
    for (row = 0; row < LEDMAT_ROWS_NUM; row++)
    {
        /* The rows are active low.  */
        if (pattern & 1)
            pio_output_low (ledmat_rows[row]);
        else
            pio_output_high (ledmat_rows[row]);

        pattern >>= 1;
    }

    /* Enable new column.  */
    pio_output_low (ledmat_cols[col]);
    col_prev = col;
}


// Clear display
void ledmat_clear(void)
{
    for (int i = 0; i < LEDMAT_ROWS_NUM; i++) {
        pio_output_high(ledmat_rows[i]);
    }
    for (int i = 0; i < LEDMAT_COLS_NUM; i++) {
        pio_output_high(ledmat_cols[i]);
    }
}
