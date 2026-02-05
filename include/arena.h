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

static inline void *scratch_arena_push(arena_scratch *scratch, u64 size) {
	void *result = arena_push(scratch->parent, size);
	return result;
}

static inline void *scratch_arena_push_aligned(arena_scratch *s, u64 size, size_t align) {
	return arena_push_aligned(s->parent, size, align);
}

static inline void *scratch_arena_push_zero(arena_scratch *s, u64 size) {
	return arena_push_zero(s->parent, size);
}

#define arena_push_struct(a, type)                                                       \
	((type *)arena_push_aligned((a), sizeof(type), DEFAULT_ALIGNMENT))

#define arena_push_array(a, type, count)                                                 \
	((type *)arena_push_aligned((a), sizeof(type) * (count), DEFAULT_ALIGNMENT))

#define arena_push_struct_zero(a, type) ((type *)arena_push_zero(a, sizeof(type)))

#define scratch_push_struct(scratch, type)                                               \
	((type *)scratch_arena_push_aligned((scratch), sizeof(type), DEFAULT_ALIGNMENT))

#define scratch_push_array(scratch, type, count)                                         \
	((type *)scratch_arena_push_aligned((scratch), sizeof(type) * (count),               \
										DEFAULT_ALIGNMENT))

#define scratch_push_struct_zero(scratch, type)                                          \
	((type *)scratch_arena_push_zero((scratch), sizeof(type)))

#endif // ARENA_H
