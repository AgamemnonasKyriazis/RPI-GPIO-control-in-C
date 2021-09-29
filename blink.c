#include "gpio_functions.h"

int main()
{
    signal(SIGIN, handle_interrupt); //interrupt handler for Ctrl-C.
    
    export_pin("24"); //Open gpio 24.
 
    pin_mode("24", "out"); //Declare gpio 24 as output.
	
	//Turn on and off gpio 24 every 1 second.
    for (int i = 0; i < 5; i++) {
        set_pin_state("24", "1"); //On
        sleep(1);

        set_pin_state("24", "0"); //Off
        sleep(1);
    }

    unexport_pin("24"); //Close gpio 24.
    return 0;
}
