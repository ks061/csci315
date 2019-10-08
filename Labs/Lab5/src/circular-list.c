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
#include "circular-list.h" 

int circular_list_create(struct circular_list *l, int size) {
  sem_init(&(l->empty), 0, size);
  sem_init(&(l->full), 0, 0);
  pthread_mutex_init(&(l->mutex), NULL);

  l->buffer = calloc(size, sizeof(item));
  l->start = -1;
  l->end = -1;
  l->elems = 0;
  l->size = size;
  return 0;
}

int circular_list_insert(struct circular_list *l, item i) {
  sem_wait(&(l->empty));
  pthread_mutex_lock(&(l->mutex));

  if (l->elems < l->size) {
      l->start++;
      if (l->start == l->size) l->start = 0;
      l->buffer[l->start] = i;
      l->elems++;
  } 
  // no longer needed due to blocking until there is at least one empty spot
  else { 
      printf("Circular list is full; could not insert %f into list.\n", i);
      return -1;
  }
  
  pthread_mutex_unlock(&(l->mutex));  
  sem_post(&(l->full));

  return 0;
}

int circular_list_remove(struct circular_list *l, item *i) {
    sem_wait(&(l->full));
    pthread_mutex_lock(&(l->mutex));    

    if (l->elems > 0) {
        l->end++;
        if (l->end == l->size) l->end = 0;
        *i = l->buffer[l->end];
        l->elems--; 
    } 
    // no longer needed due to blocking until there is at least one full spot
    else {
        printf("Circular list is full; could not remove item from list.\n");
        return -1;
    } 

    pthread_mutex_unlock(&(l->mutex));
    sem_post(&(l->empty));
    
  return 0;
}
