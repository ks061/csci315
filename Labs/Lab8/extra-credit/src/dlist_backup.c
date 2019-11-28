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
 * Edited by: Kartikeya Sharma (ks061@bucknell.edu)
 */

#include <stdlib.h>
#include <stdio.h>

#include "dnode.h"
#include "dlist.h"

struct dlist* dlist_create() {
	return calloc(1, sizeof(struct dlist));
}

void dlist_destroy(struct dlist* l) {
	struct dnode* p = l->front;
	while (l->front != NULL) {
		l->front = l->front->next;
		free(p->ptr);
		free(p);
		p = l->front;
	}
	l->front = l->back = NULL;
	l->counter = 0;
}


void dlist_obliterate(struct dlist* l) {
	dlist_destroy(l);
	free(l);
}

void dlist_add_front(struct dlist* l, void* ptr, size_t size) {
	struct dnode* n = dnode_create();
	n->ptr = ptr;
        n->size = size;

	if (0 == l->counter) {
		l->front = l->back = n;	
		l->counter = 1;
	} else {
		n->next = l->front;
		l->front->prev = n;
		l->front = n;
		(l->counter)++;
	}

#ifdef DEBUG
	printf("counter= %d, %s\n", l->counter, (char *) ptr);
	printf("front= %s\n", (char *) l->front->data);
	printf("back= %s\n\n", (char *) l->back->data);
#endif /* DEBUG */
}

void dlist_add_back(struct dlist* l, void* ptr, size_t size) {
	struct dnode* n = dnode_create();
	n->ptr = ptr;
        n->size = size;

	if (0 == l->counter) {
		l->front = l->back = n;	
		l->counter = 1;
	} else {
		n->prev = l->back;
		l->back->next = n;
		l->back = n;
		(l->counter)++;
	}

#ifdef DEBUG
	printf("counter= %d, %s\n", l->counter, (char *) ptr);
	printf("front= %s\n", (char *) l->front->data);
	printf("back= %s\n\n", (char *) l->back->data);
#endif /* DEBUG */
}

void dlist_add_in_place(struct dlist* l, void* ptr, size_t size) {
	struct dnode* n = dnode_create();
	n->ptr = ptr;
	n->size = size;

	if (0 == l->counter) {
		l->front = l->back = n;
		l->counter = 1;
	} else {
		struct dnode* iter = NULL;
		do {
			if (iter == NULL) { iter = dlist_iter_begin(l); }
			else { iter = dlist_iter_next(l); }
			if (ptr < iter->ptr) { 
				n->next = iter;
				iter->prev = n;
				if (l->front == l->iter) {
					l->front = n;
				}
				(l->counter)++;
				break;
			} 
		} while (dlist_iter_has_next(l));
		if (l->iter == l->back && ptr >= iter->ptr) {
			dlist_add_back(l, ptr, size);
		}
	}
}

struct dnode* dlist_remove_front(struct dlist* l) {
	struct dnode* front_node = l->front;

	if (1 == l->counter) {
		l->front = l->back = NULL;
	} else {
		l->front = l->front->next;
		l->front->prev = NULL;
	}

	(l->counter)--;
	return front_node;
}

struct dnode* dlist_remove_back(struct dlist* l) {
	struct dnode* back_node = l->back;

	if (1 == l->counter) {
		l->front = l->back = NULL;
	} else {
		l->back = l->back->prev;
		l->back->next = NULL;
	}

	(l->counter)--;
	return back_node;
}

struct dnode* dlist_find_remove(struct dlist* l, void* ptr) {
	struct dnode* iter_node = l->front;

	while ((iter_node != NULL) && (iter_node->ptr != ptr)) {
	  iter_node = iter_node->next;
	}

	if (iter_node != NULL) {
	  if (l->front == iter_node) {
	    return dlist_remove_front(l);
	  } else if (l->back == iter_node) {
	    return dlist_remove_back(l);
	  } else {
	    if (1 == l->counter) {
	      l->front = l->back = NULL;
	    } else {
	      iter_node->prev->next = iter_node->next;
	      iter_node->next->prev = iter_node->prev;
	    }
	    (l->counter)--;
	  }
	}
	return iter_node;
}

uint32_t dlist_num_elems(struct dlist* l) {
	return l->counter;
}

struct dnode* dlist_iter_begin(struct dlist* l) {
	return l->iter;
}

struct dnode* dlist_iter_next(struct dlist* l) {
	if (l->iter != NULL) { 
		l->iter = l->iter->next; 
		return l->iter;
	} 
	return NULL; 
}

bool dlist_iter_has_next(struct dlist* l) {
	if (l->iter != NULL) {
		return l->iter->next != NULL;
	}
        return false;
#ifdef DEBUG
	if (ret_val) {
		printf("dlist_has_next: current is %s\n", (char *) l->iter->data);
		printf("dlist_has_next: returning %d\n\n", ret_val);
	}
#endif /* DEBUG */
}


struct dnode* dlist_iter_end(struct dlist* l) {
        return l->iter;
}

struct dnode* dlist_iter_prev(struct dlist* l) {
	if (l->iter != NULL) {
		l->iter = l->iter->prev;
		return l->iter;
	}
	return NULL;
}

bool dlist_iter_has_prev(struct dlist* l) {
	if (l->iter != NULL) {
		return l->iter->prev != NULL;
	}
	return false;
}
