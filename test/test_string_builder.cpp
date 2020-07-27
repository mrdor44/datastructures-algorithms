#include "inc/string_builder.hpp"
#include "mock.hpp"
#include "test/common.hpp"

using testing::NotNull;

TEST(StringBuilder, Build) {
    t_stringbuilder sb = STRINGBUILDER_create();
    EXPECT_THAT(sb, NotNull());
    EXPECT_SUCCESS(STRINGBUILDER_append(sb, "GREAT "));
    EXPECT_SUCCESS(STRINGBUILDER_append(sb, "SUCCESS!"));
    char* str = nullptr;
    EXPECT_SUCCESS(STRINGBUILDER_str(sb, &str));
    EXPECT_STREQ("GREAT SUCCESS!", str);
    FREE(str);
    STRINGBUILDER_DESTROY(sb);
}