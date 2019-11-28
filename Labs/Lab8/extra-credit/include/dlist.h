/*
 * Copyright (c) 2012 Bucknell University
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

#ifndef _DLIST_H_
#define _DLIST_H_

#include <stdint.h>
#include <stdbool.h>
#include "dnode.h"

/**
 * Doubly-linked list.
 */
struct dlist {
	struct dnode *front;
	struct dnode *back;
	struct dnode *iter;
	uint32_t counter;
};

/**
 * Allocates new dlist dynamically.
 * 
 * @return pointer to the list.
 */
struct dlist *dlist_create();

/**
 * Deallocates all nodes in a dlist and the data they point to, but
 * preserve the list.
 *
 * @param l pointer to the list (non-NULL)
 */
void dlist_destroy(struct dlist *l);

/**
 * Deallocates all nodes in a dlist and the data they point to; deallocate
 * the list itself as well. This is the inverse of dlist_create.
 * @param l pointer to the list (non-NULL)
 */
void dlist_obliterate(struct dlist *l);

/** 
 * Inserts new node in dlist before the first node.
 *
 * @param l pointer to the list (non_NULL)
 * @param ptr pointer to generic data to store in new list node
 * @param size size of the memory chunk
 */
void dlist_add_front(struct dlist *l, void *ptr, size_t size);

/** 
 * Inserts new node in dlist after the last node.
 *
 * @param l pointer to the list (non-NULL)
 * @param ptr pointer to generic data to store in new list node
 * @param size size of the memory chunk
 */
void dlist_add_back(struct dlist *l, void *ptr, size_t size);

/**
 * Inserts new node in dlist such that the pointers' addresses are sorted.
 *
 * @param l pointer to the list (non-NULL)
 * @param ptr pointer to start of memory chunk
 * @param size size of the memory chunk
 */
void dlist_add_in_place(struct dlist *l, void *ptr, size_t size);

/**
 * Combines neighboring chunks of memory as represented by dnodes
 * together
 *
 * @param l pointer to the list (non-NULL)
 */
void
dlist_append_adjacent_nodes(struct dlist *l);

/**
 * Remove the first node and return pointer to the data. It is the
 * responsibility of the caller to free the memory pointed to by the return
 * value.
 * 
 * @param l pointer to the list (non-NULL)
 * @return pointer to data stored in front node
 */
struct dnode *dlist_remove_front(struct dlist *l);

/**
 * Remove the last node and return pointer to the data. It is the
 * responsibility of the caller to free the memory pointed to by the return
 * value.
 * 
 * @param l pointer to the list (non-NULL)
 * @return pointer to data stored in back node
 */
struct dnode *dlist_remove_back(struct dlist *l);

/**
 * Seek out the node that contains a pointer and remove from list returning
 * the pointer to the node. It is the responsibility of the caller to free
 * the memory pointed to by the return value.
 *
 * @param l pointer to the list (non-NULL)
 * @param ptr pointer to the data item been sought
 * @return pointer to the node that had a particular data pointer
 */

struct dnode *dlist_find_remove(struct dlist *l, void *ptr);

/**
 * Returns the number of elements in the list (nodes).
 *
 * @param l pointer to the list (non-NULL)
 */
uint32_t dlist_num_elems(struct dlist *l);

/**
 * Initialize iterator for traversing a dlist forwards.
 *
 * @return pointer to head node in list; NULL if list is empty
 */
struct dnode *dlist_iter_begin(struct dlist *l);

/** 
 * Advances iterator to next node in list.
 * 
 * @return pointer to next node in list; NULL if end 
 *         of list has already been reached
 */
struct dnode *dlist_iter_next(struct dlist *l);

/**
 * Check if iterator has reached the end of the list.
 */
bool dlist_iter_has_next(struct dlist *l);

/**
 * Initialize iterator for traversing a dlist backwards.
 * 
 * @return pointer to tail node in list; NULL if list is empty
 */
struct dnode *dlist_iter_end(struct dlist *l);

/** 
 * Returns current item and advances iterator to previous item in list.
 * 
 * @return pointer to the previous node in the list;
 *         NULL if the beginning of the list has already been reached
 */
struct dnode *dlist_iter_prev(struct dlist *l);

/**
 * Check if iterator has reached the start of the list.
 */
bool dlist_iter_has_prev(struct dlist *l);

#endif /* _DLIST_H_ */
