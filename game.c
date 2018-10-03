#include "system.h"
#include "pio.h"
#include "navswitch.h"
#include "ledmat.h"
#include <stdbool.h>


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


int main (void)
{
    // Initialise system and set inital dot positions
    system_init ();
    navswitch_init ();
    ledmat_init ();
    int dot[2] = {3, 2};
    int prev_dot[2] = {0, 0};
    bool changed = false;
    
    pio_output_low(ledmat_rows[dot[0]]);
    pio_output_low(ledmat_cols[dot[1]]);

    while (1)
    {
        navswitch_update();
        
        // Check for button press events and change dot position
        if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
            if (dot[0] < 6) {
                prev_dot[0] = dot[0];
                changed = true;
                dot[0]++;
            }
        }
        
        if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
            if (dot[0] > 0) {
                prev_dot[0] = dot[0];
                changed = true;
                dot[0]--;
            }
        }
        
        if (navswitch_push_event_p(NAVSWITCH_EAST)) {
            if (dot[1] < 4) {
                prev_dot[1] = dot[1];
                changed = true;
                dot[1]++;
            }
        }
        
        if (navswitch_push_event_p(NAVSWITCH_WEST)) {
            if (dot[1] > 0) {
                prev_dot[1] = dot[1];
                changed = true;
                dot[1]--;
            }
        }
        
        
        // Update LED display
        if (changed) {
            pio_output_low(ledmat_rows[dot[0]]);
            pio_output_low(ledmat_cols[dot[1]]);
            pio_output_high(ledmat_rows[prev_dot[0]]);
            pio_output_high(ledmat_cols[prev_dot[1]]);
            changed = false;
        }
    }
}
