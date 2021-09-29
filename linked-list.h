#ifndef Linked_List

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

void insert_element(char* value);
void remove_element(char* value);
int contains_element(char* value);
char* pop();

struct node_s {
    char* value;
    struct node_s* next;
};
typedef struct node_s node_t;

extern node_t* head;

#endif