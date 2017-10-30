#ifndef RAM_STR_H
#define RAM_STR_H

typedef struct {
    char *string;
    unsigned int length;
} ram_str;

ram_str ram_make_str(char *string, unsigned int length);
ram_str ram_make_str_walk_length(char *string);
unsigned int ram_find_pos(ram_str *haystack, ram_str *needle);
ram_str ram_find_str(ram_str *haystack, ram_str *needle);

#ifdef RAM_IMPLEMENTATION

ram_str ram_make_str(char *string, unsigned int length) {
    ram_str result = {
        .string=string,
        .length=length,
    };
    return result;
}

ram_str ram_make_str_walk_length(char *string) {
    ram_str result;
    result.string = string;
    char *p;
    for (p = string; *p; p++);
    result.length = p - string;
    return result;
}

unsigned int ram_find_pos(ram_str *haystack, ram_str *needle) {
    unsigned int pos = -1;
    char *h = haystack->string;
    for (unsigned int i = 0; i < haystack->length; i++) {
        unsigned int check_pos = i;
        char *n = needle->string;
        unsigned int j;
        for (j = 0; j < needle->length; j++) {
            if (*h++ != *n++) {
                break;
            }
        }
        if (j == needle->length) {
            pos = check_pos;
            break;
        }
    }
    return pos;
}

ram_str ram_find_str(ram_str *haystack, ram_str *needle) {
    ram_str result = {0};
    unsigned int pos = ram_find_pos(haystack, needle);
    if (pos >= 0) {
        result.string = haystack->string + pos;
        result.length = haystack->length - pos;
    }
    return result;
}

#endif

#endif
