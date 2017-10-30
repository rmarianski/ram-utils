#include <string.h>
#include <assert.h>
#define RAM_IMPLEMENTATION 1
#include "ram-str.h"

int main() {
    char *s = "hello world!";

    ram_str rs = ram_make_str_walk_length(s);
    assert(rs.length == strlen(s));

    unsigned int pos;
    ram_str needle = ram_make_str_walk_length("hell");
    pos = ram_find_pos(&rs, &needle);
    assert(pos == 0);

    needle = ram_make_str_walk_length("hi");
    pos = ram_find_pos(&rs, &needle);
    assert(pos == -1);

    needle = ram_make_str_walk_length("world");
    pos = ram_find_pos(&rs, &needle);
    unsigned int exp_substr_pos = 6;
    assert(pos == exp_substr_pos);
    ram_str substr = ram_find_str(&rs, &needle);
    assert(s + exp_substr_pos == substr.string);
    unsigned int exp_substr_length = 6;
    assert(substr.length == exp_substr_length);

    return 0;
}
