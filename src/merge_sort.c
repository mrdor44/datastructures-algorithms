//
// Created by dor on 25/07/2020.
//

#include <stdlib.h>
#include <assert.h>
#include <memory.h>
#include "inc/merge_sort.h"

typedef struct {
    int* array;
    int length;
} t_array;

static t_array merge(t_array, t_array);
static int min(int, int);

void merge_sort(int array[], int length) { // NOLINT(readability-non-const-parameter)
    for (int current_length = 1; current_length <= length; current_length *= 2) {
        int begin1 = 0;
        int begin2 = current_length;
        for (; begin2 < length; begin1 = begin2 + current_length, begin2 = begin1 + current_length) {
            int end2 = min(begin2 + current_length, length);
            t_array array1 = {.array = &array[begin1], .length = current_length};
            t_array array2 = {.array = &array[begin2], .length = end2 - begin2};
            t_array merged = merge(array1, array2);
            memcpy(array1.array, merged.array, merged.length * sizeof(merged.array[0]));
            FREE(merged.array);
        }
    }
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

static int min(int x, int y) {
    return x < y ? x : y;
}
