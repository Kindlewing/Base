#ifndef STRING8_H
#define STRING8_H
#include "arena.h"
#include "typedefs.h"

#define STRING8_MAX 1024

typedef struct {
	u8 *data;
	size_t length;
} string8;

string8 string8_lit(const char *str);
string8 string8_make(arena *a, const char *cstring);

string8 string8_read_file(arena *a, int fd, i64 size);
b8 string8_eq(string8 *s1, string8 *s2);

static inline char *string8_to_cstr(arena *a, string8 s) {
	char *cstr = arena_push_array(a, char, s.length + 1);
	for(size_t i = 0; i < s.length; i++) {
		cstr[i] = s.data[i];
	}
	cstr[s.length] = '\0';
	return cstr;
}

#endif // STRING8_H
