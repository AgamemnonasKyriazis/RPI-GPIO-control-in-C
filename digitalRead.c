#include "gpio_functions.h"

int main()
{
	export_pin("24"); //Open gpio 24.

	pin_mode("gpio24", "in"); //Declare gpio 24 as input.

	for(int i = 0; i < 1000; i++){
		printf("gpio24 = %d\n", digital_read("gpio24"));
		usleep(10*1000);
	}

	unexport_pin("24"); //Close gpio 24.
	return 0;
}
