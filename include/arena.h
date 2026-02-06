#ifndef ARENA_H
#define ARENA_H

#include <assert.h>
#include <unistd.h>
#include <sys/mman.h>
#include "typedefs.h"

#ifndef DEFAULT_ALIGNMENT
#define DEFAULT_ALIGNMENT (2 * sizeof(void *))
#endif

typedef struct arena_t {
	u8 *base;
	u64 capacity;
	u64 offset;

} arena;

typedef struct scratch_arena_t {
	arena *parent;
	usize saved_offset;
} scratch_arena;

arena *arena_create(u64 capacity);
void arena_clear(arena *arena);
void arena_free(arena *arena);

void *arena_push(arena *arena, u64 size);
void *arena_push_aligned(arena *arena, u64 size, size_t align);
void *arena_push_zero(arena *arena, u64 size);

scratch_arena scratch_begin(arena *parent);
void scratch_end(scratch_arena *scratch);
void *scratch_push(scratch_arena *scratch, u64 size);
void *scratch_push_aligned(scratch_arena *s, u64 size, size_t align);
void *scratch_push_zero(scratch_arena *s, u64 size);

#define arena_push_struct(a, type)                                                       \
	((type *)arena_push_aligned((a), sizeof(type), DEFAULT_ALIGNMENT))

#define arena_push_array(a, type, count)                                                 \
	((type *)arena_push_aligned((a), sizeof(type) * (count), DEFAULT_ALIGNMENT))

#define arena_push_struct_zero(a, type) ((type *)arena_push_zero(a, sizeof(type)))

#define scratch_push_struct(scratch, type)                                               \
	((type *)scratch_push_aligned((scratch), sizeof(type), DEFAULT_ALIGNMENT))

#define scratch_push_array(scratch, type, count)                                         \
	((type *)scratch_push_aligned((scratch), sizeof(type) * (count), DEFAULT_ALIGNMENT))

#define scratch_push_struct_zero(scratch, type)                                          \
	((type *)scratch_push_zero((scratch), sizeof(type)))

#endif // ARENA_H
