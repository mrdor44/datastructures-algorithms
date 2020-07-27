#ifndef DATASTRUCTURES_ALGORITHMS_COMMON_H
#define DATASTRUCTURES_ALGORITHMS_COMMON_H

#include <stdlib.h>
#include "inc/common.h"

#define CLOSE(p, pfn)       \
do {                        \
    if (NULL != (p)) {      \
        (pfn)((p));         \
        (p) = NULL;         \
    }                       \
} while (false)

#define FREE(p) CLOSE((p), free)

#define SWAP(type, a, b)    \
do {                        \
    type temp = (a);        \
    (a) = (b);              \
    (b) = temp;             \
} while (false)

typedef enum {
    RETURNCODE_INVALID_VALUE = -1,
    RETURNCODE_SUCCESS = 0,

    RETURNCODE_STRINGBUILDER_APPEND_INVALID_PARAMETERS,
    RETURNCODE_STRINGBUILDER_APPEND_NODE_CREATE_FAILED,
    RETURNCODE_STRINGBUILDER_STR_INVALID_PARAMETERS,
    RETURNCODE_STRINGBUILDER_STR_MALLOC_FAILED,

    RETURNCODE_MINHEAP_PUSH_INVALID_PARAMETERS,
    RETURNCODE_MINHEAP_GET_MIN_INVALID_PARAMETERS,
    RETURNCODE_MINHEAP_GET_MIN_HEAP_EMPTY,
} t_returncode;

#endif //DATASTRUCTURES_ALGORITHMS_COMMON_H