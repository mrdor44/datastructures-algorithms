//
// Created by dor on 27/07/2020.
//

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "inc/hash_table.h"

typedef struct s_node* t_node;
struct s_node {
    int key;
    int value;
    t_node next;
};

struct s_hashtable {
    t_node* buckets;
    int num_buckets;
    hash_function hash;
};

static unsigned int hashtable_hash(t_hashtable, int key);
static t_node* hashtable_get_previous_node(t_hashtable, int key);

t_hashtable HASHTABLE_create(int num_buckets, hash_function hash) {
    t_hashtable htable = NULL;
    bool is_success = false;

    if ((0 == num_buckets) || (NULL == hash)) {
        goto l_cleanup;
    }

    htable = malloc(sizeof(*htable));
    if (NULL == htable) {
        goto l_cleanup;
    }
    htable->buckets = NULL;
    htable->num_buckets = 0;
    htable->hash = NULL;

    htable->buckets = malloc(num_buckets * sizeof(htable->buckets[0])); // NOLINT(bugprone-sizeof-expression)
    if (NULL == htable->buckets) {
        goto l_cleanup;
    }

    memset(htable->buckets, 0, num_buckets * sizeof(htable->buckets[0])); // NOLINT(bugprone-sizeof-expression)
    htable->num_buckets = num_buckets;
    htable->hash = hash;

    is_success = true;

l_cleanup:
    if (!is_success) {
        HASHTABLE_DESTROY(htable);
    }
    return htable;
}

void HASHTABLE_destroy(t_hashtable htable) {
    if (NULL == htable) {
        return;
    }
    for (int bucket = 0; bucket < htable->num_buckets; ++bucket) {
        while (NULL != htable->buckets[bucket]) {
            (void) HASHTABLE_remove(htable, htable->buckets[bucket]->key);
        }
    }
    FREE(htable->buckets);
    FREE(htable);
}

t_returncode HASHTABLE_insert(t_hashtable htable, int key, int value) {
    t_returncode returncode = RETURNCODE_INVALID_VALUE;
    t_node node = NULL;

    if (NULL == htable) {
        returncode = RETURNCODE_HASHTABLE_INSERT_INVALID_PARAMETERS;
        goto l_cleanup;
    }

    node = malloc(sizeof(*node));
    if (NULL == node) {
        returncode = RETURNCODE_HASHTABLE_INSERT_MALLOC_FAILED;
        goto l_cleanup;
    }

    unsigned int bucket = hashtable_hash(htable, key);
    node->key = key;
    node->value = value;
    node->next = htable->buckets[bucket];

    htable->buckets[bucket] = node;
    node = NULL;

    returncode = RETURNCODE_SUCCESS;

l_cleanup:
    FREE(node);
    return returncode;
}

t_returncode HASHTABLE_remove(t_hashtable htable, int key) {
    t_returncode returncode = RETURNCODE_INVALID_VALUE;

    if (NULL == htable) {
        returncode = RETURNCODE_HASHTABLE_REMOVE_INVALID_PARAMETERS;
        goto l_cleanup;
    }

    t_node* previous = hashtable_get_previous_node(htable, key);
    if (NULL == previous) {
        returncode = RETURNCODE_HASHTABLE_REMOVE_KEY_NOT_FOUND;
        goto l_cleanup;
    }

    t_node node = *previous;
    *previous = node->next;
    FREE(node);

    returncode = RETURNCODE_SUCCESS;

l_cleanup:
    return returncode;
}

t_returncode HASHTABLE_get(t_hashtable htable, int key, int* value) {
    t_returncode returncode = RETURNCODE_INVALID_VALUE;

    if (NULL == htable) {
        returncode = RETURNCODE_HASHTABLE_GET_INVALID_PARAMETERS;
        goto l_cleanup;
    }

    t_node* previous = hashtable_get_previous_node(htable, key);
    if (NULL == previous) {
        returncode = RETURNCODE_HASHTABLE_GET_KEY_NOT_FOUND;
        goto l_cleanup;
    }

    if (NULL != value) {
        *value = (*previous)->value;
    }

    returncode = RETURNCODE_SUCCESS;

l_cleanup:
    return returncode;
}

unsigned int hashtable_hash(t_hashtable htable, int key) {
    assert(NULL != htable);
    return htable->hash(key) % htable->num_buckets;
}

t_node* hashtable_get_previous_node(t_hashtable htable, int key) {
    assert(NULL != htable);

    const unsigned int bucket = hashtable_hash(htable, key);
    t_node* previous = &htable->buckets[bucket];
    assert(NULL != previous);
    t_node current = *previous;
    for (; NULL != current; previous = &current->next, current = *previous) {
        if (current->key == key) {
            return previous;
        }
    }
    return NULL;
}
