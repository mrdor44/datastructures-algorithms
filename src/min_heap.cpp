//
// Created by dor on 27/07/2020.
//

#include "inc/array_list.hpp"
#include "inc/min_heap.hpp"

struct s_minheap {
    ArrayList<int>* array;
};

static inline int minheap_parent(int);
static inline int minheap_left(int);
static inline int minheap_right(int);
static void minheap_sift_up(t_minheap);
static void minheap_sift_down(t_minheap, int node = 0);

t_minheap MINHEAP_create() {
    t_minheap heap = nullptr;
    bool is_success = false;

    heap = static_cast<t_minheap>(malloc(sizeof(*heap)));
    if (nullptr == heap) {
        goto l_cleanup;
    }

    heap->array = new(std::nothrow) ArrayList<int>;
    if (nullptr == heap->array) {
        goto l_cleanup;
    }

    is_success = true;

l_cleanup:
    if (!is_success) {
        MINHEAP_DESTROY(heap);
    }
    return heap;
}

t_minheap MINHEAP_create(const int* begin, const int* end) {
    t_minheap heap = nullptr;
    bool is_success = false;

    heap = MINHEAP_create();
    if (nullptr == heap) {
        goto l_cleanup;
    }

    try {
        heap->array->push_back(begin, end);
    } catch (...) {
        goto l_cleanup;
    }

    for (int current = heap->array->length() - 1; current >= 0; --current) {
        minheap_sift_down(heap, current);
    }

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
    if (nullptr != heap->array) {
        delete heap->array;
    }
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

t_returncode MINHEAP_pop_min(t_minheap heap, int* min) {
    t_returncode returncode = RETURNCODE_INVALID_VALUE;
    auto& array = *heap->array;

    if (nullptr == heap) {
        returncode = RETURNCODE_MINHEAP_POP_MIN_INVALID_PARAMETERS;
        goto l_cleanup;
    }

    if (0 == array.length()) {
        returncode = RETURNCODE_MINHEAP_POP_MIN_HEAP_EMPTY;
        goto l_cleanup;
    }

    (void) MINHEAP_get_min(heap, min);
    SWAP(int, array[0], array.back());
    array.pop_back();
    minheap_sift_down(heap);

    returncode = RETURNCODE_SUCCESS;

l_cleanup:
    return returncode;
}

bool MINHEAP_is_empty(t_minheap heap) {
    if (nullptr == heap) {
        return true;
    }
    return heap->array->length() == 0;
}

int minheap_parent(int n) {
    assert(n > 0);
    return (n - 1) / 2;
}

int minheap_left(int n) {
    assert(n >= 0);
    return 2 * n + 1;
}

int minheap_right(int n) {
    assert(n >= 0);
    return minheap_left(n) + 1;
}

void minheap_sift_up(t_minheap heap) {
    assert(nullptr != heap);
    auto& array = *heap->array;
    for (int current = array.length() - 1;
         current != 0 && array[current] < array[minheap_parent(current)];
         current = minheap_parent(current)) {
        SWAP(int, array[current], array[minheap_parent(current)]);
    }
}

void minheap_sift_down(t_minheap heap, int node) {
    assert(nullptr != heap);
    auto& array = *heap->array;
    for (int current = node; minheap_left(current) < array.length();) {
        const int left_value = array[minheap_left(current)];
        const int right_value = minheap_right(current) < array.length() ?
                                array[minheap_right(current)] :
                                max(left_value, array[current]) + 1;
        int min_child = left_value < right_value ?
                        minheap_left(current) : minheap_right(current);
        if (array[current] <= array[min_child]) {
            assert(array[current] <= left_value);
            assert(array[current] <= right_value);
            break;
        }
        SWAP(int, array[current], array[min_child]);
        current = min_child;
    }
}
