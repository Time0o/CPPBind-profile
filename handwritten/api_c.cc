#include <memory>

#include "api.h"
#include "api_c.h"

using namespace profile;

extern "C" {

size_t profile_ko_sz = sizeof(Kobject);

profile_ko_t profile_kobject_new(char *mem, int64_t a)
{ return reinterpret_cast<profile_ko_t>(new (mem) Kobject(a)); }

void profile_kobject_delete(profile_ko_t ko)
{ reinterpret_cast<Kobject *>(ko)->~Kobject(); }

int64_t profile_kobject_call(profile_ko_t ko, int64_t b, int64_t c, int64_t *res)
{
  Cap<Kobject> x(reinterpret_cast<Kobject *>(ko));
  return x->call(b, c, res);
}

} // extern "C"
