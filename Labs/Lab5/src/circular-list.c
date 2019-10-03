/*
 * Copyright (c) 2013 Bucknell University
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: L. Felipe Perrone (perrone@bucknell.edu)
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/circular-list.h" 

int circular_list_create(struct circular_list *l, int size) {
  l->buffer = calloc(size, sizeof(item));
  l->start = -1;
  l->end = -1;
  l->elems = 0;
  l->size = size;
  return 0;
}

int circular_list_insert(struct circular_list *l, item i) {
  if (l->elems < l->size) {
      l->start++;
      if (l->start == l->size) l->start = 0;
      l->buffer[l->start] = i;
      l->elems++;
  } else { 
      printf("Circular list is full; could not insert %f into list.\n", i);
      return -1;
  }

  return 0;
}

int circular_list_remove(struct circular_list *l, item *i) {
    if (l->elems > 0) {
        l->end++;
        if (l->end == l->size) l->end = 0;
        *i = l->buffer[l->end];
        l->elems--; 
    } else {
        printf("Circular list is full; could not remove item from list.\n");
        return -1;
    } 
  
  return 0;
}
