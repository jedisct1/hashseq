#ifndef hashseq_H
#define hashseq_H

#include <stdint.h>
#include <stdlib.h>

typedef struct HashSeqArena_ {
    uint32_t *base;
    uint32_t  mask;
    uint32_t  size;
} HashSeqArena;

typedef struct HashSeqSolution_ {
    uint32_t s0;
    uint32_t s1;
} HashSeqSolution;

/**
 * Initialize the memory region used for computations.
 */
int hashseq_arena_init(HashSeqArena *arena, uint32_t *base, size_t size);

/**
 * Solve the hash sequence for the random suffix `suffix`, from levels
 * `level_first` to `level_last` (included), with `iterations` puzzles
 * for each level, and put the solution for each level into `solutions`.
 *
 * `solutions` will store (`level_last` - `level_first` + 1) * iterations
 * solutions.
 */
int hashseq_solve(HashSeqArena *arena, HashSeqSolution *solutions,
                  const uint32_t suffix[8], uint32_t level_first,
                  uint32_t level_last, uint32_t iterations);

/**
 * Verify that the solutions `solutions` are valid for the suffix `suffix`,
 * and for levels from `level_first` to `level_last` (included), with
 * `iterations` puzzles per level.
 *
 * Returns `1` on success, `0` if the solutions don't appear to be correct.
 */
int hashseq_verify(HashSeqArena *arena, const HashSeqSolution *solutions,
                   const uint32_t suffix[8], uint32_t level_first,
                   uint32_t level_last, uint32_t iterations);

#endif
