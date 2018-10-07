#include <stdlib.h>
#include "system.h"
#include "pio.h"
#include "navswitch.h"
#include "modules/ledmat.h"
#include "modules/paddle.h"


int main (void)
{
    // Initialise system and set inital dot positions
    system_init ();
    navswitch_init ();
    ledmat_init ();
    Paddle* player_1 = NULL;
    paddle_init( player_1 );

    while (1)
    {
        navswitch_update();
        
        // Check for button press events and change dot position
        if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
            increase_row(player_1);
        }
        
        if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
            decrease_row(player_1);
        }
        
        if (navswitch_push_event_p(NAVSWITCH_EAST)) {
            increase_col(player_1);
        }
        
        if (navswitch_push_event_p(NAVSWITCH_WEST)) {
            decrease_col(player_1);
        }
        
        
        // Update LED display
        paddle_update(player_1);
    }
}
