#include "gpio_functions.h"

int main()
{
    export_pin("24"); //Open gpio 24.
 
    pin_mode("gpio24", "out"); //Declare gpio 24 as output.
	
	//Turn on and off gpio 24 every 1 second.
    for (int i = 0; i < 100; i++) {
        digital_write("gpio24", "1"); //On
        sleep(1);

        digital_write("gpio24", "0"); //Off
        sleep(1);
    }

    unexport_pin("24"); //Close gpio 24.
    return 0;
}
