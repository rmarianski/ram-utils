#ifndef RAM_MEM_H
#define RAM_MEM_H

typedef enum {
    RAM_ARENA_OVERFLOW_ASSERT,
    RAM_ARENA_OVERFLOW_ALLOC,
} ram_arena_overflow_option;

typedef struct {
    ram_arena_overflow_option overflow_option;
    unsigned int alignment;
} ram_arena_options;

typedef struct {
    char *addr;
    size_t used;
    size_t total;
    ram_arena_options options;
} ram_arena;

typedef struct {
    bool no_zero;
    unsigned int alignment;
} ram_arena_options_alloc;

typedef struct {
    ram_arena *arena;
    size_t used_snapshot;
} ram_arena_snapshot;

ram_arena ram_arena_mk(size_t size, void *memory);
ram_arena ram_arena_mk_options(size_t size, void *memory, ram_arena_options options);
void *ram_arena_alloc(ram_arena *arena, size_t size);
void *ram_arena_alloc_options(ram_arena *arena, size_t size, ram_arena_options_alloc options);
ram_arena_snapshot ram_arena_begin_temporary_memory(ram_arena *arena);
void ram_arena_end_temporary_memory(ram_arena_snapshot *snapshot);
ram_arena ram_arena_subarena(ram_arena *arena, size_t size);

#define ram_arena_alloc_struct(arena, struct_type) ram_arena_alloc(arena, sizeof(struct_type))
#define ram_arena_alloc_array(arena, array_type, n_items) ram_arena_alloc(arena, sizeof(array_type) * n_items)

#ifdef RAM_IMPLEMENTATION

ram_arena ram_arena_mk_options(size_t size, void *memory, ram_arena_options options) {
    ram_arena result = {
        .addr = memory,
        .used = 0,
        .total = size,
        .options = options,
    };
    return result;
}

ram_arena ram_arena_mk(size_t size, void *memory) {
    ram_arena_options options = {0};
    return ram_arena_mk_options(size, memory, options);
}

void *ram_arena_alloc_options(ram_arena *arena, size_t size, ram_arena_options_alloc options) {
    // TODO alloc options
    assert(arena->used + size <= arena->total);
    void *result = arena->addr + arena->used;
    arena->used += size;
    return result;
}

void *ram_arena_alloc(ram_arena *arena, size_t size) {
    ram_arena_options_alloc options = {0};
    return ram_arena_alloc_options(arena, size, options);
}

ram_arena_snapshot ram_arena_begin_temporary_memory(ram_arena *arena) {
    ram_arena_snapshot result = {
        .arena=arena,
        .used_snapshot=arena->used,
    };
    return result;
}

void ram_arena_end_temporary_memory(ram_arena_snapshot *snapshot) {
    snapshot->arena->used = snapshot->used_snapshot;
}

ram_arena ram_arena_subarena(ram_arena *arena, size_t size) {
    assert(arena->used + size <= arena->total);
    ram_arena result = {
        .addr=arena->addr + arena->used,
        .used=0,
        .total=size,
    };
    return result;
}

#endif

#endif
