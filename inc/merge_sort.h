//
// Created by dor on 24/07/2020.
//

#ifndef DATASTRUCTURES_ALGORITHMS_MERGE_SORT_H
#define DATASTRUCTURES_ALGORITHMS_MERGE_SORT_H

#include <stddef.h>
#include <stdbool.h>

#define FREE(p)         \
do {                    \
    if (NULL != (p)) {  \
        free((p));      \
        (p) = NULL;     \
    }                   \
} while (false)

void merge_sort(int array[], int length);

#endif //DATASTRUCTURES_ALGORITHMS_MERGE_SORT_H
