#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "api_c.h"

enum {
  NUM_RUNS= 10000,
  NUM_LOOPS = 100000,
  NUM_LOOPS_WARMUP = 100
};

#define GET_CYCLES(high, low) \
  asm volatile ("LFENCE\n\t" \
                "RDTSC\n\t" \
                "MOV %%edx, %0\n\t" \
                "MOV %%eax, %1\n\t" \
                "LFENCE\n\t" \
                : "=r" (high), "=r" (low) \
                :: "%rax", "%rbx", "%rcx", "%rdx");

__attribute__((noinline))
static int64_t ipc_call(int64_t a, int64_t b, int64_t c)
{
  int64_t res;

#ifdef HANDWRITTEN
  char ko_mem[profile_ko_sz];
  profile_ko_t ko = profile_kobject_new(ko_mem, a);

  profile_kobject_call(ko, b, c, &res);

  profile_kobject_delete(ko);
#else
  struct profile_kobject ko = profile_kobject_new(a);

  struct profile_cap_kobject cap = profile_cap_kobject_new_2(&ko);
  struct profile_kobject ko_accessed = profile_cap_kobject_access(&cap);

  profile_kobject_call(&ko_accessed, b, c, &res);

  profile_kobject_delete(&ko);
#endif

  return res;
}

int main()
{
  volatile int64_t a = 1, b = 2, c = 3, res;

  uint64_t cycles[NUM_LOOPS + NUM_LOOPS_WARMUP];
  uint64_t cycles_mins[NUM_RUNS];

  int32_t cycles_low_start, cycles_high_start, cycles_low_end, cycles_high_end;

  for (int r = 0; r < NUM_RUNS; ++r) {
    for (int l = 0; l < NUM_LOOPS + NUM_LOOPS_WARMUP; ++l) {
      GET_CYCLES(cycles_high_start, cycles_low_start);

      res = ipc_call(a, b, c);

      GET_CYCLES(cycles_high_end, cycles_low_end);

      uint64_t start = ((uint64_t)cycles_high_start << 32) | ((uint64_t)cycles_low_start & 0xffffffff);
      uint64_t end = ((uint64_t)cycles_high_end << 32) | ((uint64_t)cycles_low_end & 0xffffffff);

      cycles[l] = end - start;
    }

    cycles_mins[r] = cycles[NUM_LOOPS_WARMUP];
    for (int l = NUM_LOOPS_WARMUP + 1; l < NUM_LOOPS + NUM_LOOPS_WARMUP; ++l) {
      if (cycles[l] < cycles_mins[r])
        cycles_mins[r] = cycles[l];
    }
  }

  for (int r = 0; r < NUM_RUNS; ++r)
    printf("%" PRIu64 "\n", cycles_mins[r]);
}
