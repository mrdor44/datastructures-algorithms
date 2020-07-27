//
// Created by dor on 26/07/2020.
//

#include <cstdlib>
#include <cstring>
#include "inc/string_builder.hpp"
#include "inc/common.h"

struct s_node {
    char* string;
    struct s_node* next;
};

typedef struct s_node* t_node;

struct s_stringbuilder {
    t_node strings;
    t_node last;
    int length;
};

static t_node stringbuilder_node_create(const char*);

static void stringbuilder_node_destroy(t_node);

#define STRINGBUILDER_NODE_DESTROY(node) CLOSE((node), stringbuilder_node_destroy)

t_stringbuilder STRINGBUILDER_create() {
    t_stringbuilder sb = nullptr;
    bool created_successfully = false;

    sb = static_cast<t_stringbuilder>(malloc(sizeof(*sb)));
    if (nullptr == sb) {
        goto l_cleanup;
    }

    sb->strings = stringbuilder_node_create("");
    if (nullptr == sb->strings) {
        goto l_cleanup;
    }

    sb->last = sb->strings;
    sb->length = 0;

    created_successfully = true;

l_cleanup:
    if (!created_successfully) {
        STRINGBUILDER_DESTROY(sb);
    }
    return sb;
}

t_returncode STRINGBUILDER_append(t_stringbuilder sb, const char* string) {
    t_returncode returncode = RETURNCODE_INVALID_VALUE;
    t_node new_node = nullptr;

    if ((nullptr == sb) || (nullptr == string)) {
        returncode = RETURNCODE_STRINGBUILDER_APPEND_INVALID_PARAMETERS;
        goto l_cleanup;
    }

    new_node = stringbuilder_node_create(string);
    if (nullptr == new_node) {
        returncode = RETURNCODE_STRINGBUILDER_APPEND_NODE_CREATE_FAILED;
        goto l_cleanup;
    }

    sb->length += strlen(string);

    sb->last->next = new_node;
    sb->last = new_node;
    new_node = nullptr;

    returncode = RETURNCODE_SUCCESS;

l_cleanup:
    STRINGBUILDER_NODE_DESTROY(new_node);
    return returncode;
}

t_returncode STRINGBUILDER_str(t_stringbuilder sb, char** p_string) {
    t_returncode returncode = RETURNCODE_INVALID_VALUE;
    char* string = nullptr;
    int next_pos = 0;

    if ((nullptr == sb) || (nullptr == p_string)) {
        returncode = RETURNCODE_STRINGBUILDER_STR_INVALID_PARAMETERS;
        goto l_cleanup;
    }

    string = static_cast<char*>(malloc((sb->length + 1) * sizeof(*string)));
    if (nullptr == string) {
        returncode = RETURNCODE_STRINGBUILDER_STR_MALLOC_FAILED;
        goto l_cleanup;
    }

    for (t_node node = sb->strings; nullptr != node; node = node->next) {
        (void) strcpy(&string[next_pos], node->string);
        next_pos += strlen(node->string);
    }

    *p_string = string;
    string = nullptr;

    returncode = RETURNCODE_SUCCESS;

l_cleanup:
    FREE(string);
    return returncode;
}

void STRINGBUILDER_destroy(t_stringbuilder sb) {
    if (nullptr == sb) {
        return;
    }
    for (t_node current = sb->strings; nullptr != current;) {
        t_node next = current->next;
        STRINGBUILDER_NODE_DESTROY(current);
        current = next;
    }
    sb->last = nullptr;
    sb->length = 0;
    FREE(sb);
}

t_node stringbuilder_node_create(const char* string) {
    t_node node = nullptr;
    bool created_successfully = false;

    node = static_cast<t_node>(malloc(sizeof(*node)));
    if (nullptr == node) {
        goto l_cleanup;
    }

    node->string = static_cast<char*>(malloc((strlen(string) + 1) * sizeof(*node->string)));
    if (nullptr == node->string) {
        goto l_cleanup;
    }

    (void) strcpy(node->string, string);
    node->next = nullptr;

    created_successfully = true;

l_cleanup:
    if (!created_successfully) {
        STRINGBUILDER_NODE_DESTROY(node);
    }
    return node;
}

void stringbuilder_node_destroy(t_node node) {
    if (nullptr == node) {
        return;
    }
    FREE(node->string);
    FREE(node);
}
