//
// Created by dor on 27/07/2020.
//

#include <memory>
#include "inc/array_list.hpp"
#include "inc/min_heap.hpp"

struct s_minheap {
    std::unique_ptr<ArrayList<int>> array;
};

static inline int minheap_parent(int);
static inline int minheap_left(int);
static inline int minheap_right(int);
static void minheap_sift_up(t_minheap);

t_minheap MINHEAP_create() {
    t_minheap heap = nullptr;
    bool is_success = false;

    heap = static_cast<t_minheap>(malloc(sizeof(*heap)));
    if (nullptr == heap) {
        goto l_cleanup;
    }

    heap->array = std::make_unique<ArrayList<int>>();

    is_success = true;

l_cleanup:
    if (!is_success) {
        MINHEAP_DESTROY(heap);
    }
    return heap;
}

void MINHEAP_destroy(t_minheap heap) {
    if (nullptr == heap) {
        return;
    }
    heap->array.reset(nullptr);
    FREE(heap);
}

t_returncode MINHEAP_push(t_minheap heap, int value) {
    t_returncode returncode = RETURNCODE_INVALID_VALUE;

    if (nullptr == heap) {
        returncode = RETURNCODE_MINHEAP_PUSH_INVALID_PARAMETERS;
        goto l_cleanup;
    }

    heap->array->push_back(value);
    minheap_sift_up(heap);

    returncode = RETURNCODE_SUCCESS;

l_cleanup:
    return returncode;
}

t_returncode MINHEAP_get_min(t_minheap heap, int* min) {
    t_returncode returncode = RETURNCODE_INVALID_VALUE;

    if ((nullptr == heap) || (nullptr == min)) {
        returncode = RETURNCODE_MINHEAP_GET_MIN_INVALID_PARAMETERS;
        goto l_cleanup;
    }

    if (0 == heap->array->length()) {
        returncode = RETURNCODE_MINHEAP_GET_MIN_HEAP_EMPTY;
        goto l_cleanup;
    }

    *min = (*heap->array)[0];
    returncode = RETURNCODE_SUCCESS;

l_cleanup:
    return returncode;
}

int minheap_parent(int n) {
    return (n - 1) / 2;
}

int minheap_left(int n) {
    return 2 * n + 1;
}

int minheap_right(int n) {
    return minheap_left(n) + 1;
}

void minheap_sift_up(t_minheap heap) {
    auto& array = *heap->array;
    for (int current = array.length() - 1;
         current != 0 && array[current] < array[minheap_parent(current)];
         current = minheap_parent(current)) {
        SWAP(int, array[current], array[minheap_parent(current)]);
    }
}
