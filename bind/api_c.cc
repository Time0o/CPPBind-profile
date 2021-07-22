#include <cassert>
#include <cerrno>
#include <exception>
#include <stdexcept>
#include <utility>

#include "cppbind/c/c_bind_error_cc.h"
#include "cppbind/c/c_util_cc.h"

#include "/home/timo/github/projects/CPPBind-profile/api.h"
#include "/home/timo/github/projects/CPPBind-profile/api.h"

extern "C" {

#include "/home/timo/github/projects/CPPBind-profile/bind/api_c.h"

struct profile_kobject profile_kobject_new(int_64_t state)
{
  using namespace profile;

  int64_t _state;

  _state = state;

  char __buf[8];

  auto __out = new (__buf) profile::Kobject(_state);

  struct profile_kobject __ret;

  static_cast<void>(__out);

  struct profile_kobject __tmp;
  cppbind::c::make_owning_struct_mem<profile::Kobject>(&__tmp, __buf);
  __ret = __tmp;

  return __ret;
}

void profile_kobject_delete(const struct profile_kobject * __self)
{
  using namespace profile;

  const profile::Kobject * ___self;

  ___self = cppbind::c::struct_cast<const profile::Kobject>(__self);

  ___self->~Kobject();
}

int_64_t profile_kobject_call(struct profile_kobject * __self, int_64_t a, int_64_t b, int_64_t * res)
{
  using namespace profile;

  profile::Kobject * ___self;
  int64_t _a;
  int64_t _b;
  int64_t * _res;

  ___self = cppbind::c::struct_cast<profile::Kobject>(__self);

  _a = a;

  _b = b;

  _res = res;

  auto __out = ___self->call(_a, _b, _res);

  int_64_t __ret;

  __ret = __out;

  return __ret;
}

struct profile_cap_base profile_cap_base_new(uint_64_t c)
{
  using namespace profile;

  uint64_t _c;

  _c = c;

  char __buf[8];

  auto __out = new (__buf) profile::Cap_base(_c);

  struct profile_cap_base __ret;

  static_cast<void>(__out);

  struct profile_cap_base __tmp;
  cppbind::c::make_owning_struct_mem<profile::Cap_base>(&__tmp, __buf);
  __ret = __tmp;

  return __ret;
}

uint_64_t profile_cap_base_cap(struct profile_cap_base * __self)
{
  using namespace profile;

  profile::Cap_base * ___self;

  ___self = cppbind::c::struct_cast<profile::Cap_base>(__self);

  auto __out = ___self->cap();

  uint_64_t __ret;

  __ret = __out;

  return __ret;
}

struct profile_cap_base profile_cap_base_copy(const struct profile_cap_base * _1)
{
  using namespace profile;

  const profile::Cap_base * __1;

  __1 = cppbind::c::struct_cast<const profile::Cap_base>(_1);

  char __buf[8];

  auto __out = new (__buf) profile::Cap_base(*__1);

  struct profile_cap_base __ret;

  static_cast<void>(__out);

  struct profile_cap_base __tmp;
  cppbind::c::make_owning_struct_mem<profile::Cap_base>(&__tmp, __buf);
  __ret = __tmp;

  return __ret;
}

struct profile_cap_base profile_cap_base_move(struct profile_cap_base * _1)
{
  using namespace profile;

  profile::Cap_base * __1;

  __1 = cppbind::c::struct_cast<profile::Cap_base>(_1);

  char __buf[8];

  auto __out = new (__buf) profile::Cap_base(std::move(*__1));

  struct profile_cap_base __ret;

  static_cast<void>(__out);

  struct profile_cap_base __tmp;
  cppbind::c::make_owning_struct_mem<profile::Cap_base>(&__tmp, __buf);
  __ret = __tmp;

  return __ret;
}

void profile_cap_base_delete(const struct profile_cap_base * __self)
{
  using namespace profile;

  const profile::Cap_base * ___self;

  ___self = cppbind::c::struct_cast<const profile::Cap_base>(__self);

  ___self->~Cap_base();
}

struct profile_cap_kobject profile_cap_kobject_new_1(uint_64_t c)
{
  using namespace profile;

  uint64_t _c;

  _c = c;

  char __buf[8];

  auto __out = new (__buf) profile::Cap<profile::Kobject>(_c);

  struct profile_cap_kobject __ret;

  static_cast<void>(__out);

  struct profile_cap_kobject __tmp;
  cppbind::c::make_owning_struct_mem<profile::Cap<profile::Kobject>>(&__tmp, __buf);
  __ret = __tmp;

  return __ret;
}

struct profile_cap_kobject profile_cap_kobject_new_2(const struct profile_kobject * p)
{
  using namespace profile;

  const profile::Kobject * _p;

  _p = cppbind::c::struct_cast<const profile::Kobject>(p);

  char __buf[8];

  auto __out = new (__buf) profile::Cap<profile::Kobject>(_p);

  struct profile_cap_kobject __ret;

  static_cast<void>(__out);

  struct profile_cap_kobject __tmp;
  cppbind::c::make_owning_struct_mem<profile::Cap<profile::Kobject>>(&__tmp, __buf);
  __ret = __tmp;

  return __ret;
}

struct profile_kobject profile_cap_kobject_access(const struct profile_cap_kobject * __self)
{
  using namespace profile;

  const profile::Cap<profile::Kobject> * ___self;

  ___self = cppbind::c::struct_cast<const profile::Cap<profile::Kobject>>(__self);

  auto __out = ___self->operator->();

  struct profile_kobject __ret;

  struct profile_kobject __tmp;
  cppbind::c::make_non_owning_struct(&__tmp, __out);
  __ret = __tmp;

  return __ret;
}

void profile_cap_kobject_delete(const struct profile_cap_kobject * __self)
{
  using namespace profile;

  const profile::Cap<profile::Kobject> * ___self;

  ___self = cppbind::c::struct_cast<const profile::Cap<profile::Kobject>>(__self);

  ___self->~Cap<profile::Kobject>();
}

uint_64_t profile_cap_kobject_cap(struct profile_cap_kobject * __self)
{
  using namespace profile;

  profile::Cap<profile::Kobject> * ___self;

  ___self = cppbind::c::struct_cast<profile::Cap<profile::Kobject>>(__self);

  auto __out = ___self->cap();

  uint_64_t __ret;

  __ret = __out;

  return __ret;
}

} // extern "C"