#ifndef GUARD_API_C_H
#define GUARD_API_C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "cppbind/c/c_bind_error_c.h"

typedef long int_64_t;
typedef unsigned long uint_64_t;

struct profile_cap_kobject;
struct profile_cap_base;
struct profile_kobject;

struct profile_cap_kobject
{
  union {
    char mem[8];
    void *ptr;
  } obj;

  char is_const;
  char is_owning;
};

struct profile_cap_base
{
  union {
    char mem[8];
    void *ptr;
  } obj;

  char is_const;
  char is_owning;
};

struct profile_kobject
{
  union {
    char mem[8];
    void *ptr;
  } obj;

  char is_const;
  char is_owning;
};

struct profile_kobject profile_kobject_new(int_64_t state);

void profile_kobject_delete(const struct profile_kobject * __self);

int_64_t profile_kobject_call(struct profile_kobject * __self, int_64_t a, int_64_t b, int_64_t * res);

struct profile_cap_base profile_cap_base_new(uint_64_t c);

uint_64_t profile_cap_base_cap(struct profile_cap_base * __self);

struct profile_cap_base profile_cap_base_copy(const struct profile_cap_base * _1);

struct profile_cap_base profile_cap_base_move(struct profile_cap_base * _1);

void profile_cap_base_delete(const struct profile_cap_base * __self);

struct profile_cap_kobject profile_cap_kobject_new_1(uint_64_t c);

struct profile_cap_kobject profile_cap_kobject_new_2(const struct profile_kobject * p);

struct profile_kobject profile_cap_kobject_access(const struct profile_cap_kobject * __self);

void profile_cap_kobject_delete(const struct profile_cap_kobject * __self);

uint_64_t profile_cap_kobject_cap(struct profile_cap_kobject * __self);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // GUARD_API_C_H