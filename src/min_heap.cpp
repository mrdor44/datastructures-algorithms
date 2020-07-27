//
// Created by dor on 27/07/2020.
//

#include <memory>
#include "inc/array_list.hpp"
#include "inc/min_heap.hpp"

struct s_minheap {
    std::unique_ptr<ArrayList<int>> array;
};

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
