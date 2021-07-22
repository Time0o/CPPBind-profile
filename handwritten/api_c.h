#ifndef GUARD_API_C_H
#define GUARD_API_C_H

#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint64_t profile_ko_t;
extern size_t profile_ko_sz;

profile_ko_t profile_kobject_new(char *mem, int64_t state);

void profile_kobject_delete(profile_ko_t ko);

int64_t profile_kobject_call(profile_ko_t ko, int64_t a, int64_t b, int64_t *res);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // GUARD_API_C_H
