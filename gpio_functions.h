#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int export_pin(char *pin){
	char *pin_file = (char *)malloc(sizeof(char)*64);
	int w = 0;
	int fd = open("/sys/class/gpio/export", O_WRONLY);
	strcpy(pin_file, "/sys/class/gpio/gpio");
	strcat(pin_file, pin);
	if(fd == -1){
		free(pin_file);
		perror("Unable to open /sys/class/gpio/export");
		close(fd);
		return 1;
	}
	if((w = write(fd, pin, 2)) < 0){
		free(pin_file);
		close(fd);
		return 1;
	}
	close(fd);
	free(pin_file);
	return 0;
}

int pin_mode(char *pin, char *mode){
	char *pin_file = (char *)malloc(sizeof(char)*64);
	strcpy(pin_file, "/sys/class/gpio/");
	strcat(pin_file, pin);
	strcat(pin_file, "/direction");
	int fd = open(pin_file, O_WRONLY);
	int w = 0;
	if(fd == -1){
		free(pin_file);
		perror("Unable to open pin file");
		return 1;
	}
	if((w = write(fd, mode, 3)) < 0){
		free(pin_file);
		close(fd);
		return 1;
	}
	close(fd);
	free(pin_file);
	return 0;
}

int unexport_pin(char *pin){
    int w = 0;
    int fd = open("/sys/class/gpio/unexport", O_WRONLY);
    char *pin_file = (char *)malloc(sizeof(char)*64);
    strcpy(pin_file, "/sys/class/gpio/gpio");
    strcat(pin_file, pin);
    if(fd == -1) {
        perror("Unable to open /sys/class/gpio/unexport");
        free(pin_file);
	close(fd);
        return 1;
    }
    if((w = write(fd, pin, 2)) < 0){
		free(pin_file);
		close(fd);
		return 1;
    }
    close(fd);
    free(pin_file);
    return 0;
}

int digital_write(char *pin, char *value){
    int w;
    char *pin_file = (char *)malloc(sizeof(char)*64);
    sprintf(pin_file, "/sys/class/gpio/%s/value", pin);
    int fd = open(pin_file, O_WRONLY);
    if(fd == -1){
        	perror("Unable to open pin_file");
       		free(pin_file);
        	return 1;
	}
	if((w = write(fd, value, 1)) < 0){
		free(pin_file);
		return 1;
	}
	close(fd);
	free(pin_file);
	return 0;
}

int digital_read(char *pin){
	int r;
	char v;
	char *pin_file = (char *)malloc(sizeof(char)*64);
	sprintf(pin_file, "/sys/class/gpio/%s/value", pin);
	int fd = open(pin_file, O_RDONLY);
	if(fd == -1){
		perror("Unable to open pin_file");
		free(pin_file);
		close(fd);
		return -1;
	}
	if((r = read(fd, &v, 1)) < 0){
		free(pin_file);
		close(fd);
		return -1;
	}
	close(fd);
	free(pin_file);
	return (int)v-'0';
}
