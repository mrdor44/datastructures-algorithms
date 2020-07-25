//
// Created by dor on 25/07/2020.
//

#include <stdlib.h>
#include <assert.h>
#include "inc/merge_sort.h"

typedef struct {
    int* array;
    int length;
} t_array;

static t_array merge_sort_from_to(t_array, int begin, int end);
static t_array merge(t_array, t_array);

int* merge_sort(int array[], int length) { // NOLINT(readability-non-const-parameter)
    const t_array input_array = {.array = array, .length = length};
    return merge_sort_from_to(input_array, 0, length).array;
}

static t_array merge_sort_from_to(t_array array, int begin, int end) {
    t_array sorted = {.array = NULL, .length = 0};
    t_array left = {.array = NULL, .length = 0};
    t_array right = {.array = NULL, .length = 0};

    if (begin >= end) {
        goto l_cleanup;
    }

    if (1 == end - begin) {
        sorted.length = 1;
        sorted.array = malloc(sorted.length * sizeof(*sorted.array));
        sorted.array[0] = array.array[begin];
        goto l_cleanup;
    }

    const int middle = (begin + end) / 2;
    left = merge_sort_from_to(array, begin, middle);
    right = merge_sort_from_to(array, middle, end);
    sorted = merge(left, right);

l_cleanup:
    FREE(right.array);
    FREE(left.array);
    return sorted;
}

static t_array merge(t_array array1, t_array array2) {
    t_array result = {.array = NULL, .length = 0};

    result.length = array1.length + array2.length;
    result.array = malloc(result.length * sizeof(*result.array));
    if (NULL == result.array) {
        goto l_cleanup;
    }

    int it1 = 0;
    int it2 = 0;
    int it_result = 0;
    for (; it1 < array1.length && it2 < array2.length; ++it_result) {
        if (array1.array[it1] < array2.array[it2]) {
            result.array[it_result] = array1.array[it1];
            ++it1;
            continue;
        }
        assert(array2.array[it2] <= array1.array[it1]);
        result.array[it_result] = array2.array[it2];
        ++it2;
    }
    for (; it1 < array1.length; ++it1, ++it_result) {
        result.array[it_result] = array1.array[it1];
    }
    for (; it2 < array2.length; ++it2, ++it_result) {
        result.array[it_result] = array2.array[it2];
    }

l_cleanup:
    return result;
}