#include "linked-list.h"

node_t* head = NULL; //head of the ll

char* pop() { //returns head value but does not delete it
    if(head == NULL) {
        return NULL;
    }
    return head->value;
}

void insert_element(char* value_t) {
    char* value = strdup(value_t);
    node_t* node = (node_t*)malloc(sizeof(node_t));
    node->value = value;
    node->next = NULL;
    if(head == NULL) {
        head = node;
        return;
    }
    node_t* temp = head;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = node;
    return;
}

void remove_element(char* value_t) {
    char* value = NULL;
    if(head == NULL) {
        return;
    }
    value = strdup(value_t);
    if(strcmp(head->value, value) == 0) {
        head = head->next;
        return;
    }
    node_t* temp = head;
    while(temp->next != NULL) {
        if(strcmp(temp->next->value, value) == 0) {
            temp->next = temp->next->next;
            return;
        }
        temp = temp->next;
    }
}

int contains_element(char* value_t) {
    char* value = NULL;
    int index = 0;
    if(head == NULL) {
        return -1;
    }
    value = strdup(value_t);
    if(strcmp(head->value, value) == 0) {
        return index;
    }
    node_t* temp = head->next;
    index++;
    while(temp != NULL) {
        if(strcmp(temp->value, value) == 0) {
            return index;
        }
        temp = temp->next;
        index++;
    }
    return -1;
}