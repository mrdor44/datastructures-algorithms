#include "inc/string_builder.hpp"
#include "mock.hpp"

using testing::NotNull;

#define EXPECT_STRINGBUILDER_SUCEESS(expr) EXPECT_EQ(STRINGBUILDER_RETURNCODE_SUCCESS, (expr))

TEST(StringBuilder, Build) {
    t_stringbuilder sb = STRINGBUILDER_create();
    EXPECT_THAT(sb, NotNull());
    EXPECT_STRINGBUILDER_SUCEESS(STRINGBUILDER_append(sb, "GREAT "));
    EXPECT_STRINGBUILDER_SUCEESS(STRINGBUILDER_append(sb, "SUCCESS!"));
    char* str = nullptr;
    EXPECT_STRINGBUILDER_SUCEESS(STRINGBUILDER_str(sb, &str));
    EXPECT_STREQ("GREAT SUCCESS!", str);
    FREE(str);
    STRINGBUILDER_DESTROY(sb);
}