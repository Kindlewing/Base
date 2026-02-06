#include "arena.h"
#include <string.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#endif

static inline b8 is_power_of_two(usize x) {
	return x && ((x & (x - 1)) == 0);
}

static inline usize align_forward_usize(usize offset, usize align) {
	assert(is_power_of_two(align));
	usize mask = align - 1;
	return (offset + mask) & ~mask;
}

arena *arena_create(u64 capacity) {
	arena *arena = VirtualAlloc(NULL, sizeof *arena + capacity, MEM_RESERVE | MEM_COMMIT,
								PAGE_READWRITE);

	if(!arena) {
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

arena_scratch scratch_begin(arena *parent) {
	arena_scratch scratch;
	scratch.parent = parent;
	scratch.saved_offset = parent->offset;
	return scratch;
}

void scratch_end(arena_scratch *scratch) {
	scratch->parent->offset = scratch->saved_offset;
}

void *scratch_push(arena_scratch *scratch, u64 size) {
	void *result = arena_push(scratch->parent, size);
	return result;
}

void *scratch_push_aligned(arena_scratch *s, u64 size, size_t align) {
	return arena_push_aligned(s->parent, size, align);
}

void *scratch_push_zero(arena_scratch *s, u64 size) {
	return arena_push_zero(s->parent, size);
}

void arena_clear(arena *arena) {
	arena->offset = 0;
}

void arena_free(arena *arena) {
	VirtualFree(arena, 0, MEM_RELEASE);
}
