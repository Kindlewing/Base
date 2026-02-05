#ifndef ARENA_H
#define ARENA_H

#include <assert.h>
#include <unistd.h>
#include <sys/mman.h>
#include "macros.h"
#include "typedefs.h"

#ifndef DEFAULT_ALIGNMENT
#define DEFAULT_ALIGNMENT (2 * sizeof(void *))
#endif

typedef struct arena_t {
	u8 *base;
	u64 capacity;
	u64 offset;

} arena;

typedef struct arena_scratch_t {
	arena *parent;
	usize saved_offset;
} arena_scratch;

arena *arena_create(u64 capacity);
void arena_clear(arena *arena);
void arena_free(arena *arena);

void *arena_push(arena *arena, u64 size);
void *arena_push_aligned(arena *arena, u64 size, size_t align);
void *arena_push_zero(arena *arena, u64 size);

static inline arena_scratch arena_scratch_begin(arena *parent) {
	arena_scratch scratch;
	scratch.parent = parent;
	scratch.saved_offset = parent->offset;
	return scratch;
}

static inline void arena_scratch_end(arena_scratch *scratch) {
	scratch->parent->offset = scratch->saved_offset;
}

#define arena_push_struct(a, type)                                                       \
	((type *)arena_push_aligned((a), sizeof(type), DEFAULT_ALIGNMENT))

#define arena_push_array(a, type, count)                                                 \
	((type *)arena_push_aligned((a), sizeof(type) * (count), DEFAULT_ALIGNMENT))

#define arena_push_struct_zero(a, type) ((type *)arena_push_zero(a, sizeof(type)))

#endif // ARENA_H
