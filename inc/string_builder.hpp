//
// Created by dor on 26/07/2020.
//

#ifndef DATASTRUCTURES_ALGORITHMS_STRING_BUILDER_HPP
#define DATASTRUCTURES_ALGORITHMS_STRING_BUILDER_HPP

extern "C" {
#include "inc/common.h"
};

typedef struct s_stringbuilder* t_stringbuilder;

typedef enum {
    STRINGBUILDER_RETURNCODE_INVALID_VALUE = -1,
    STRINGBUILDER_RETURNCODE_SUCCESS = 0,
    STRINGBUILDER_RETURNCODE_APPEND_INVALID_PARAMETERS,
    STRINGBUILDER_RETURNCODE_APPEND_NODE_CREATE_FAILED,
    STRINGBUILDER_RETURNCODE_STR_INVALID_PARAMETERS,
    STRINGBUILDER_RETURNCODE_STR_MALLOC_FAILED
} t_stringbuilder_returncode;

t_stringbuilder STRINGBUILDER_create();

t_stringbuilder_returncode STRINGBUILDER_append(t_stringbuilder, const char*);

t_stringbuilder_returncode STRINGBUILDER_str(t_stringbuilder, char**);

void STRINGBUILDER_destroy(t_stringbuilder);

#define STRINGBUILDER_DESTROY(sb) CLOSE((sb), STRINGBUILDER_destroy)

#endif //DATASTRUCTURES_ALGORITHMS_STRING_BUILDER_HPP
