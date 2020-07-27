#ifndef DATASTRUCTURES_ALGORITHMS_COMMON_H
#define DATASTRUCTURES_ALGORITHMS_COMMON_H

#include <stdlib.h>

#define CLOSE(p, pfn)       \
do {                        \
    if (NULL != (p)) {      \
        (pfn)((p));         \
        (p) = NULL;         \
    }                       \
} while (false)

#define FREE(p) CLOSE((p), free)

#endif //DATASTRUCTURES_ALGORITHMS_COMMON_H