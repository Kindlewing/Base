#include "arena.h"
#include "macros.h"
#include <stdlib.h>
#include <string.h>

#define ALLOCATION_THRESHOLD KiB(64)

static inline b8 is_power_of_two(usize x) {
	return x && ((x & (x - 1)) == 0);
}

static inline usize align_forward_usize(usize offset, usize align) {
	assert(is_power_of_two(align));
	usize mask = align - 1;
	return (offset + mask) & ~mask;
}

arena *arena_create(u64 capacity) {
	arena *arena;
	if(capacity <= ALLOCATION_THRESHOLD) {
		arena = malloc(sizeof *arena + capacity);
	} else {
		arena = mmap(NULL, sizeof *arena + capacity, PROT_READ | PROT_WRITE,
					 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
		if(arena == MAP_FAILED)
			return NULL;
	}

	arena->base = (u8 *)arena + sizeof *arena;
	arena->capacity = capacity;
	arena->offset = 0;
	return arena;
}

void *arena_push(arena *arena, u64 size) {
	return arena_push_aligned(arena, size, DEFAULT_ALIGNMENT);
}

void *arena_push_aligned(arena *arena, u64 size, size_t align) {
	usize aligned_offset = align_forward_usize(arena->offset, align);

	if(aligned_offset + size > arena->capacity) {
		return NULL;
	}
	void *result = arena->base + aligned_offset;
	arena->offset = aligned_offset + size;
	return result;
}

void *arena_push_zero(arena *arena, u64 size) {
	void *ptr = arena_push(arena, size);

	if(!ptr)
		return NULL;

	u8 *p = (u8 *)ptr;
	memset(p, 0, size);
	return ptr;
}

void arena_clear(arena *arena) {
	arena->offset = 0;
}

void arena_free(arena *arena) {
	if(arena->capacity <= ALLOCATION_THRESHOLD) {
		free(arena);
	} else {
		munmap(arena, sizeof *arena + arena->capacity);
	}
}
