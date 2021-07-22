#include <cassert>
#include <cinttypes>
#include <cstdio>
#include <cstdlib>

extern "C" {
#ifdef JIT
  #include "luajit-2.0/lua.h"
  #include "luajit-2.0/lualib.h"
  #include "luajit-2.0/lauxlib.h"
#else
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
#endif
}

enum {
  NUM_RUNS = 100,
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

int main()
{
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);

#ifdef JIT
  lua_getglobal(L, "require");
#ifdef HANDWRITTEN
  lua_pushliteral(L, "profile_lua_handwritten");
#else
  lua_pushliteral(L, "profile_lua");
#endif
  if (lua_pcall(L, 1, 0, 0)) {
    fprintf(stderr, "error: %s\n", lua_tostring(L, -1));
    return -1;
  }

  lua_getglobal(L, "ipc_call");
  assert(!lua_isnil(L, -1));
#else
#ifdef HANDWRITTEN
  assert(luaL_loadfile(L, "profile_lua_handwritten.lua") == 0);
#else
  assert(luaL_loadfile(L, "profile_lua.lua") == 0);
#endif
  assert(lua_pcall(L, 0, 1, 0) == 0);
#endif

  volatile int64_t state = 0, a = 1, b = 2, res;

  uint64_t cycles[NUM_LOOPS + NUM_LOOPS_WARMUP];
  uint64_t cycles_mins[NUM_RUNS];

  int32_t cycles_low_start, cycles_high_start, cycles_low_end, cycles_high_end;

  for (int r = 0; r < NUM_RUNS; ++r) {
    for (int l = 0; l < NUM_LOOPS + NUM_LOOPS_WARMUP; ++l) {
      lua_pushvalue(L, -1);  // ipc_call
      lua_pushinteger(L, 0); // state
      lua_pushinteger(L, 1); // a
      lua_pushinteger(L, 2); // b

      GET_CYCLES(cycles_high_start, cycles_low_start);

      lua_call(L, 3, 1);
      res = lua_tointeger(L, -1);

      GET_CYCLES(cycles_high_end, cycles_low_end);

      lua_pop(L, 1);

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
