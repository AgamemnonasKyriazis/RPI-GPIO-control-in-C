#include "gpio_functions.h"

int main()
{
	signal(SIGINT, handle_interrupt); //interrupt handler for Ctrl-C
	
	export_pin("24"); //Open gpio 24.

	set_pin_mode("24", "in"); //Declare gpio 24 as input.
	//Loop for some time...
	for(int i = 0; i < 1000; i++){
		printf("gpio24 = %d\n", read_pin_state("24")); //Read gpio 24 and print its value.
		usleep(10*1000); //Sleep for 10ms.
	}

	unexport_pin("24"); //Close gpio 24.
	return 0;
}
