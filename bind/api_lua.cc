#define LUA_LIB

extern "C" {
#ifdef JIT
#include "luajit-2.0/lua.h"
#include "luajit-2.0/lauxlib.h"
#else
#include "lua.h"
#include "lauxlib.h"
#endif
}

struct lua_longjmp {
  struct lua_longjmp *previous;
  int b;
  volatile int status;
};

#include "cppbind/lua/lua_util.h"
#include "cppbind/type_info.h"

#include "/home/timo/github/projects/CPPBind-profile/api.h"
#include "/home/timo/github/projects/CPPBind-profile/api.h"

namespace cppbind::type_info {
  type_instance<profile::Kobject> _ZTSN7profile7KobjectE;
  type_instance<profile::Cap_base> _ZTSN7profile8Cap_baseE;
  type_instance<profile::Cap<profile::Kobject>, profile::Cap_base> _ZTSN7profile3CapINS_7KobjectEEE;
}

namespace
{

int profile_kobject_new(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "function expects 1 arguments");

  using namespace profile;

  int64_t _state;

  luaL_checktype(L, 1, LUA_TNUMBER);
  _state = cppbind::lua::tointegral<int64_t>(L, 1);

  auto __out = new profile::Kobject(_state);

  cppbind::type_info::make_typed(__out, lua_newuserdata(L, sizeof(cppbind::type_info::typed_ptr)), true);
  cppbind::lua::setmetatable(L, "METATABLE__ZTSN7profile7KobjectE");

  return 1;
}

int profile_kobject_call(lua_State *L)
{
  try {
    if (lua_gettop(L) != 4)
      return luaL_error(L, "function expects 4 arguments");

    using namespace profile;

    profile::Kobject * ___self;
    int64_t _a;
    int64_t _b;
    int64_t * _res;

    luaL_checktype(L, 1, LUA_TUSERDATA);
    ___self = cppbind::type_info::typed_pointer_cast<profile::Kobject>(lua_touserdata(L, 1));

    luaL_checktype(L, 2, LUA_TNUMBER);
    _a = cppbind::lua::tointegral<int64_t>(L, 2);

    luaL_checktype(L, 3, LUA_TNUMBER);
    _b = cppbind::lua::tointegral<int64_t>(L, 3);

    if (lua_isuserdata(L, 4)) {
      _res = cppbind::type_info::typed_pointer_cast<int64_t>(lua_touserdata(L, 4));
    } else {
      luaL_checktype(L, 4, LUA_TNUMBER);
      static int64_t __tmp = cppbind::lua::tointegral<int64_t>(L, 4);
      _res = &__tmp;
    }

    auto __out = ___self->call(_a, _b, _res);

    cppbind::lua::pushintegral(L, __out);

    int __top = lua_gettop(L);

    if (!lua_isuserdata(L, 4) && _res)
       cppbind::lua::pushintegral(L, *_res);

    return 1 + (lua_gettop(L) - __top);
  } catch (std::exception const &__e) {
    lua_pushstring(L, __e.what());
  } catch (lua_longjmp *) {
    throw;
  } catch (...) {
    lua_pushstring(L, "exception");
  }

  return lua_error(L);
}

int profile_cap_base_new(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "function expects 1 arguments");

  using namespace profile;

  uint64_t _c;

  luaL_checktype(L, 1, LUA_TNUMBER);
  _c = cppbind::lua::tointegral<uint64_t>(L, 1);

  auto __out = new profile::Cap_base(_c);

  cppbind::type_info::make_typed(__out, lua_newuserdata(L, sizeof(cppbind::type_info::typed_ptr)), true);
  cppbind::lua::setmetatable(L, "METATABLE__ZTSN7profile8Cap_baseE");

  return 1;
}

int profile_cap_base_cap(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "function expects 1 arguments");

  using namespace profile;

  profile::Cap_base * ___self;

  luaL_checktype(L, 1, LUA_TUSERDATA);
  ___self = cppbind::type_info::typed_pointer_cast<profile::Cap_base>(lua_touserdata(L, 1));

  auto __out = ___self->cap();

  cppbind::lua::pushintegral(L, __out);

  return 1;
}

int profile_cap_base_copy(lua_State *L)
{
  try {
    if (lua_gettop(L) != 1)
      return luaL_error(L, "function expects 1 arguments");

    using namespace profile;

    const profile::Cap_base * __1;

    luaL_checktype(L, 1, LUA_TUSERDATA);
    __1 = cppbind::type_info::typed_pointer_cast<const profile::Cap_base>(lua_touserdata(L, 1));

    auto __out = new profile::Cap_base(*__1);

    cppbind::type_info::make_typed(__out, lua_newuserdata(L, sizeof(cppbind::type_info::typed_ptr)), true);
    cppbind::lua::setmetatable(L, "METATABLE__ZTSN7profile8Cap_baseE");

    return 1;
  } catch (std::exception const &__e) {
    lua_pushstring(L, __e.what());
  } catch (lua_longjmp *) {
    throw;
  } catch (...) {
    lua_pushstring(L, "exception");
  }

  return lua_error(L);
}

int profile_cap_base_move(lua_State *L)
{
  try {
    if (lua_gettop(L) != 1)
      return luaL_error(L, "function expects 1 arguments");

    using namespace profile;

    profile::Cap_base * __1;

    luaL_checktype(L, 1, LUA_TUSERDATA);
    __1 = cppbind::type_info::typed_pointer_cast<profile::Cap_base>(lua_touserdata(L, 1));

    auto __out = new profile::Cap_base(std::move(*__1));

    cppbind::type_info::make_typed(__out, lua_newuserdata(L, sizeof(cppbind::type_info::typed_ptr)), true);
    cppbind::lua::setmetatable(L, "METATABLE__ZTSN7profile8Cap_baseE");

    return 1;
  } catch (std::exception const &__e) {
    lua_pushstring(L, __e.what());
  } catch (lua_longjmp *) {
    throw;
  } catch (...) {
    lua_pushstring(L, "exception");
  }

  return lua_error(L);
}

int profile_cap_kobject_new_1(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "function expects 1 arguments");

  using namespace profile;

  uint64_t _c;

  luaL_checktype(L, 1, LUA_TNUMBER);
  _c = cppbind::lua::tointegral<uint64_t>(L, 1);

  auto __out = new profile::Cap<profile::Kobject>(_c);

  cppbind::type_info::make_typed(__out, lua_newuserdata(L, sizeof(cppbind::type_info::typed_ptr)), true);
  cppbind::lua::setmetatable(L, "METATABLE__ZTSN7profile3CapINS_7KobjectEEE");

  return 1;
}

int profile_cap_kobject_new_2(lua_State *L)
{
  try {
    if (lua_gettop(L) != 1)
      return luaL_error(L, "function expects 1 arguments");

    using namespace profile;

    const profile::Kobject * _p;

    luaL_checktype(L, 1, LUA_TUSERDATA);
    _p = cppbind::type_info::typed_pointer_cast<const profile::Kobject>(lua_touserdata(L, 1));

    auto __out = new profile::Cap<profile::Kobject>(_p);

    cppbind::type_info::make_typed(__out, lua_newuserdata(L, sizeof(cppbind::type_info::typed_ptr)), true);
    cppbind::lua::setmetatable(L, "METATABLE__ZTSN7profile3CapINS_7KobjectEEE");

    return 1;
  } catch (std::exception const &__e) {
    lua_pushstring(L, __e.what());
  } catch (lua_longjmp *) {
    throw;
  } catch (...) {
    lua_pushstring(L, "exception");
  }

  return lua_error(L);
}

int profile_cap_kobject_access(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "function expects 1 arguments");

  using namespace profile;

  const profile::Cap<profile::Kobject> * ___self;

  luaL_checktype(L, 1, LUA_TUSERDATA);
  ___self = cppbind::type_info::typed_pointer_cast<const profile::Cap<profile::Kobject>>(lua_touserdata(L, 1));

  auto __out = ___self->operator->();

  cppbind::type_info::make_typed(__out, lua_newuserdata(L, sizeof(cppbind::type_info::typed_ptr)), false);
  cppbind::lua::setmetatable(L, "METATABLE__ZTSN7profile7KobjectE");

  return 1;
}

int profile_cap_kobject_cap(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "function expects 1 arguments");

  using namespace profile;

  profile::Cap<profile::Kobject> * ___self;

  luaL_checktype(L, 1, LUA_TUSERDATA);
  ___self = cppbind::type_info::typed_pointer_cast<profile::Cap<profile::Kobject>>(lua_touserdata(L, 1));

  auto __out = ___self->cap();

  cppbind::lua::pushintegral(L, __out);

  return 1;
}

void _register(lua_State *L)
{
  lua_getglobal(L, "_G");
  if (lua_isnil(L, -1)) {
    lua_pop(L, 1);
    lua_createtable(L, 0, 0);
  }

  lua_getfield(L, -1, "profile");
  if (lua_isnil(L, -1)) {
    lua_pop(L, 1);
    lua_createtable(L, 0, 0);
  }

  lua_createtable(L, 0, 1);

  {
    static luaL_Reg const _functions[] = {
      {"new", profile_kobject_new},
      {nullptr, nullptr}
    };

    luaL_register(L, nullptr, _functions);
  }

  lua_setfield(L, -2, "Kobject");

  lua_createtable(L, 0, 3);

  {
    static luaL_Reg const _functions[] = {
      {"new", profile_cap_base_new},
      {"copy", profile_cap_base_copy},
      {"move", profile_cap_base_move},
      {nullptr, nullptr}
    };

    luaL_register(L, nullptr, _functions);
  }

  lua_setfield(L, -2, "CapBase");

  lua_createtable(L, 0, 2);

  {
    static luaL_Reg const _functions[] = {
      {"new_1", profile_cap_kobject_new_1},
      {"new_2", profile_cap_kobject_new_2},
      {nullptr, nullptr}
    };

    luaL_register(L, nullptr, _functions);
  }

  lua_setfield(L, -2, "CapKobject");

  lua_setfield(L, -2, "profile");

  lua_setglobal(L, "_G");
}

void _createmetatables(lua_State *L)
{
  cppbind::lua::createmetatable(L, "METATABLE__ZTSN7profile7KobjectE",
    {
      {"call", profile_kobject_call}
    });

  cppbind::lua::createmetatable(L, "METATABLE__ZTSN7profile8Cap_baseE",
    {
      {"cap", profile_cap_base_cap},
      {"copy", cppbind::lua::bind_copy},
      {"move", cppbind::lua::bind_move}
    });

  cppbind::lua::createmetatable(L, "METATABLE__ZTSN7profile3CapINS_7KobjectEEE",
    {
      {"access", profile_cap_kobject_access},
      {"cap", profile_cap_kobject_cap}
    });
}

extern "C"
{

LUALIB_API int luaopen_api(lua_State *L)
{
  _register(L);
  _createmetatables(L);

  return 1;
}

} // extern "C"

} // namespace
