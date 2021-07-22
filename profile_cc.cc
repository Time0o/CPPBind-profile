#include <cassert>
#include <cinttypes>
#include <cstdio>
#include <cstdlib>

#include "api.h"

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
static int64_t ipc_call(int64_t state, int64_t a, int64_t b)
{
  using namespace profile;

  int64_t res;

  {
    Kobject ko(state);

    Cap<Kobject> cap(&ko);
    cap->call(a, b, &res);
  }

  return res;
}

int main()
{
  volatile int64_t state = 0, a = 0, b = 0, res;

  uint64_t cycles[NUM_LOOPS + NUM_LOOPS_WARMUP];
  uint64_t cycles_mins[NUM_RUNS];

  int32_t cycles_low_start, cycles_high_start, cycles_low_end, cycles_high_end;

  for (int r = 0; r < NUM_RUNS; ++r) {
    for (int l = 0; l < NUM_LOOPS + NUM_LOOPS_WARMUP; ++l) {
      GET_CYCLES(cycles_high_start, cycles_low_start);

      res = ipc_call(state, a, b);

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
