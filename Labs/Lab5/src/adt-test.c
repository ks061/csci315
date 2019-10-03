#include <stdlib.h>
#include <stdio.h>
#include "../include/circular-list.h"

int main(void) {
    // creating circular array
    struct circular_list clist;
    circular_list_create(&clist, 3);
    
    // creating items to put in circular array
    item item_1 = 1.2;
    item item_2 = 2.4;
    item item_3 = 3.6;
    item item_4 = 4.8;
    item item_received;

    // inserting elements into the array
    circular_list_insert(&clist, item_1);
    circular_list_insert(&clist, item_2);
    circular_list_insert(&clist, item_3);
    circular_list_insert(&clist, item_4); 
    circular_list_remove(&clist, &item_received);
    printf("%f\n", item_received);
    circular_list_remove(&clist, &item_received);
    printf("%f\n", item_received);
    circular_list_remove(&clist, &item_received);
    printf("%f\n", item_received);
    circular_list_remove(&clist, &item_received);
}
