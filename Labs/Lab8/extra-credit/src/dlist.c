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

#include <stdlib.h>
#include <stdio.h>

#include "dnode.h"
#include "dlist.h"

struct dlist *
dlist_create() {
	return calloc(1, sizeof(struct dlist));
}

void 
dlist_destroy(struct dlist *l) {
	struct dnode *p = l->front;
	do {
		l->front = l->front->next;
		free(p->ptr);
		free(p);
		p = l->front;
	} while (l->front != NULL);
	l->front = l->back = NULL;
	l->counter = 0;
}

void 
dlist_obliterate(struct dlist *l) {
	dlist_destroy(l);
	free(l);
}

void 
dlist_add_front(struct dlist *l, void *ptr, size_t size) {
	struct dnode *n = dnode_create();
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
	printf("front= %s\n", (char *) l->front->ptr);
	printf("back= %s\n\n", (char *) l->back->ptr);
#endif /* DEBUG */
}

void 
dlist_add_back(struct dlist *l, void *ptr, size_t size) {
	struct dnode *n = dnode_create();
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
	printf("front= %s\n", (char *) l->front->ptr);
	printf("back= %s\n\n", (char *) l->back->ptr);
#endif /* DEBUG */
}

void 
dlist_add_in_place(struct dlist *l, void *ptr, size_t size) {
        struct dnode* n = dnode_create();
        n->ptr = ptr;
        n->size = size;

        if (0 == l->counter) {
                l->front = l->back = n;
                l->counter = 1;
        } else {
                struct dnode* iter = NULL;
		struct dnode* iter_prev = NULL;
                do {
                        if (iter == NULL) { iter = dlist_iter_begin(l); }
                        else { iter = dlist_iter_next(l); }
                        if (ptr < iter->ptr) {
                                if (l->front == l->iter) {
                                        l->front = n;
                                } else {
					iter_prev = iter->prev;
					iter_prev->next = n;
					n->prev = iter_prev;
				}
				n->next = iter;
                                iter->prev = n;
                                
				(l->counter)++;
                                break;
                        }
                } while (dlist_iter_has_next(l));
                if (l->iter == l->back && ptr >= iter->ptr) {
                        dlist_add_back(l, ptr, size);
                }
        }
}

void
dlist_append_adjacent_nodes(struct dlist *l) {
	if (l->counter >= 2) {
		struct dnode* iter = NULL;
		struct dnode* iter_prev = NULL;
		do {
			if (iter == NULL) { iter = dlist_iter_begin(l); }
			else { iter = dlist_iter_next(l); }
			if (iter != NULL && iter_prev != NULL) {
				if (iter_prev->ptr+iter_prev->size == iter->ptr) {
					iter_prev->size += iter->size;
				        iter_prev->next = iter->next;
					if (l->back == iter) 
						l->back = iter_prev;
					free(iter);
				} 
			}
			iter_prev = iter;	
		} while (dlist_iter_has_next(l));
	}
}

struct dnode *
dlist_remove_front(struct dlist *l) {
	struct dnode *n = l->front;

	if (1 == l->counter) {
		l->front = l->back = NULL;
	} else {
		l->front = l->front->next;
		l->front->prev = NULL;
	}

	(l->counter)--;
	return n;
}

struct dnode *
dlist_remove_back(struct dlist *l) {
	struct dnode *n = l->back;

	if (1 == l->counter) {
		l->front = l->back = NULL;
	} else {
		l->back = l->back->prev;
		l->back->next = NULL;
	}

	(l->counter)--;
	return n;
}

struct dnode *
dlist_find_remove(struct dlist *l, void *ptr) {
	struct dnode *n = l->front;

	while ((n != NULL) && (n->ptr != ptr)) {
	  n = n->next;
	}
	if (n != NULL) {
	  if (l->front == n) {
	    return dlist_remove_front(l);
	  } else if (l->back == n) {
	    return dlist_remove_back(l);
	  } else {
	    if (1 == l->counter) {
	      l->front = l->back = NULL;
	    } else {
	      n->prev->next = n->next;
	      n->next->prev = n->prev;
	    }
	    (l->counter)--;
	  }
	}
	return n;
}

uint32_t 
dlist_num_elems(struct dlist *l) {
	return l->counter;
}

struct dnode *
dlist_iter_begin(struct dlist *l) {
	l->iter = l->front;
	return l->iter;
}

struct dnode *
dlist_iter_next(struct dlist *l) {
	if (l->iter != NULL) {
		l->iter = l->iter->next;
	}
	return l->iter;
}

bool 
dlist_iter_has_next(struct dlist *l) {
	bool ret_val = false;

	if (l->iter != NULL) {
		ret_val = (l->iter->next != NULL);
	}

#ifdef DEBUG
	if (ret_val) {
		printf("dlist_has_next: current is %s\n", (char *) l->iter->ptr);
		printf("dlist_has_next: returning %d\n\n", ret_val);
	}
#endif /* DEBUG */

	return ret_val;
}


struct dnode *
dlist_iter_end(struct dlist *l) {
	l->iter = l->back;

	return l->iter;
}

struct dnode *
dlist_iter_prev(struct dlist *l) {
	if (l->iter != NULL) {
		l->iter = l->iter->prev;
	}

	return l->iter;
}

bool 
dlist_iter_has_prev(struct dlist *l) {
	bool ret_val = false;

	if (l->iter != NULL) {
		ret_val = (l->iter->prev != NULL);
	}

	return ret_val;
}
