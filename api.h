#pragma once

#include <cinttypes>
#include <cstdio>

namespace profile
{

// TODO: Clang doesn't know noclone...
//#define NOOPT __attribute__((noinline)) \
//              __attribute__((noclone))

#define NOOPT __attribute__((noinline))

class Kobject
{
public:
  NOOPT Kobject(int64_t state) noexcept
  : _state(state)
  {}

  NOOPT ~Kobject() noexcept
  {
    asm("nop"); // XXX
    _state = 0;
  }

  NOOPT int64_t call(int64_t a, int64_t b, int64_t *res) noexcept
  {
    _state = 0;

    *res = a + b;

    return 0;
  }

private:
  int64_t _state = 0;
};

class Cap_base
{
public:
  explicit Cap_base(uint64_t c) noexcept : _c(c) {}

  uint64_t cap() { return _c; }

protected:
  uint64_t _c;
};

template<typename T>
class Cap : public Cap_base
{
public:
  explicit Cap(uint64_t c) noexcept
  : Cap_base(c) {}

  explicit Cap(T const *p) noexcept
  : Cap_base(reinterpret_cast<uint64_t>(p)) {}

  T *operator -> () const noexcept { return reinterpret_cast<T*>(_c); }
};

} // namespace profile
