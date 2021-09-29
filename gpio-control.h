#ifndef GPIO_Control

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

void handle_interrupt(int signum);

void export_pin(char* pin_number);
void unexport_pin(char* pin_number);

void set_pin_mode(char* pin_number, char* mode);

void set_pin_state(char* pin_number, char* value);
char read_pin_state(char* pin_number);

#endif