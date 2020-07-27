//
// Created by dor on 27/07/2020.
//

#ifndef DATASTRUCTURES_ALGORITHMS_HASH_TABLE_H
#define DATASTRUCTURES_ALGORITHMS_HASH_TABLE_H

#include <stdbool.h>
#include "common.h"

#define HASHTABLE_DESTROY(htable) CLOSE((htable), HASHTABLE_destroy)

typedef unsigned int (* hash_function)(int key);

typedef struct s_hashtable* t_hashtable;

t_hashtable HASHTABLE_create(int num_buckets, hash_function);

void HASHTABLE_destroy(t_hashtable);

t_returncode HASHTABLE_insert(t_hashtable, int key, int value);

t_returncode HASHTABLE_remove(t_hashtable, int key);

t_returncode HASHTABLE_get(t_hashtable, int key, int* value);

#endif //DATASTRUCTURES_ALGORITHMS_HASH_TABLE_H
