//
// Created by dor on 27/07/2020.
//

#ifndef DATASTRUCTURES_ALGORITHMS_MIN_HEAP_HPP
#define DATASTRUCTURES_ALGORITHMS_MIN_HEAP_HPP

extern "C" {
#include "common.h"
}

#define MINHEAP_DESTROY(minheap) CLOSE((minheap), MINHEAP_destroy)

typedef struct s_minheap* t_minheap;

t_minheap MINHEAP_create();

t_minheap MINHEAP_create(const int*, const int*);

void MINHEAP_destroy(t_minheap);

t_returncode MINHEAP_push(t_minheap, int);

t_returncode MINHEAP_get_min(t_minheap, int*);

t_returncode MINHEAP_pop_min(t_minheap, int*);

bool MINHEAP_is_empty(t_minheap);

#endif //DATASTRUCTURES_ALGORITHMS_MIN_HEAP_HPP
