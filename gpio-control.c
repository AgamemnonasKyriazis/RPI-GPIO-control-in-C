#include "gpio-control.h"
#include "linked-list.h"

void handle_interrupt(int signum) { //signal control method. Ctrl-C will now unexport all pins if used on main
	char* pin_number;
	fprintf(stderr, "Recieved %d signal, unexporting all used pins...\n", signum);
	while( (pin_number = pop()) != NULL) {
		unexport_pin(pin_number);
		fprintf(stderr, "Unexported pin %s...\n", pin_number);
	}
	exit(1);
}

void export_pin(char* pin_number){ //export the desired pin and add it to the ll
	int fd = open("/sys/class/gpio/export", O_WRONLY);
	if(fd == -1){
		perror("Unable to open /sys/class/gpio/export");
		close(fd);
		exit(1);
	}
	if(write(fd, pin_number, 2) < 0){
        perror("Error writing to /sys/class/gpio/export");
		close(fd);
		exit(1);
	}
	close(fd);
	insert_element(pin_number);
}

void unexport_pin(char* pin_number){ //unexport the desired pin and remove it from the ll
    int fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if(fd == -1) {
        perror("Unable to open /sys/class/gpio/unexport");
	    close(fd);
        exit(1);
    }
    if(write(fd, pin_number, 2) < 0){
		perror("Error writing to /sys/class/gpio/export");
		close(fd);
		exit(1);
    }
    close(fd);
	remove_element(pin_number);
}

void set_pin_mode(char* pin_number, char* mode){ //input or output
	char* pin_file = (char*)malloc(sizeof(char)*64);
    sprintf(pin_file, "/sys/class/gpio/gpio%s/direction", pin_number);
	int fd = open(pin_file, O_WRONLY);
	if(contains_element(pin_number) == -1) {
		fprintf(stderr, "Unable to set mode, non exported pin\n");
		exit(1);
	}
	if(fd == -1){
        perror("Unable to open pin direction file");
		free(pin_file);
        close(fd);
		exit(1);
	}
	if(write(fd, mode, 3) < 0){
		perror("Error writing to pin direction file");
        free(pin_file);
		close(fd);
		exit(1);
	}
	close(fd);
	free(pin_file);
}

void set_pin_state(char* pin_number, char* value){ //0 or 1
    char* pin_file = (char*)malloc(sizeof(char)*64);
    sprintf(pin_file, "/sys/class/gpio/gpio%s/value", pin_number);
    int fd = open(pin_file, O_WRONLY);
		if(contains_element(pin_number) == -1) {
		fprintf(stderr, "Unable to set state, non exported pin\n");
		exit(1);
	}
    if(fd == -1){
        perror("Unable to open pin value file");
       	free(pin_file);
        close(fd);
        exit(1);
	}
	if(write(fd, value, 1) < 0){
        perror("Error writing to pin value file");
		free(pin_file);
        close(fd);
		exit(1);
	}
	close(fd);
	free(pin_file);
}

char read_pin_state(char* pin_number){ //read a 0 or an 1
	char v;
	char* pin_file = (char*)malloc(sizeof(char)*64);
	sprintf(pin_file, "/sys/class/gpio/gpio%s/value", pin_number);
	int fd = open(pin_file, O_RDONLY);
	if(contains_element(pin_number) == -1) {
		fprintf(stderr, "Unable to read state, non exported pin\n");
		exit(1);
	}
	if(fd == -1){
		perror("Unable to open pin value file");
		free(pin_file);
		close(fd);
		exit(1);
	}
	if(read(fd, &v, 1) < 0){
        perror("Error reading pin value file");
		free(pin_file);
		close(fd);
		exit(1);
	}
	close(fd);
	free(pin_file);
	return v;
}