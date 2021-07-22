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

#include "api_c.h"

namespace
{

int _profile_kobject_new(lua_State *L);
int _profile_kobject_delete(lua_State *L);
int _profile_kobject_call(lua_State *L);

int add(lua_State *L)
{
  int64_t a = lua_tointeger(L, 1);
  int64_t b = lua_tointeger(L, 2);

  lua_pushinteger(L, a + b);

  return 1;
}

int _profile_kobject_new(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "function expects 1 argument");

  int64_t _state;

  luaL_checktype(L, 1, LUA_TNUMBER);
  int64_t state = lua_tointeger(L, 1);

  lua_newtable(L);

  char *mem = static_cast<char *>(lua_newuserdata(L, profile_ko_sz));
  lua_setfield(L, -2, "_mem");

  profile_ko_t ko = profile_kobject_new(mem, state);
  lua_pushinteger(L, ko);
  lua_setfield(L, -2, "_ko");

  lua_pushstring(L, "METATABLE_Kobject");
  lua_gettable(L, LUA_REGISTRYINDEX);

  lua_setmetatable(L, -2);

  return 1;
}

int _profile_kobject_delete(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "function expects 1 argument");

  luaL_checktype(L, 1, LUA_TTABLE);

  lua_getfield(L, 1, "_ko");
  profile_ko_t ko = lua_tointeger(L, -1);
  lua_pop(L, 1);

  profile_kobject_delete(ko);

  return 0;
}

int _profile_kobject_call(lua_State *L)
{
  if (lua_gettop(L) != 3)
    return luaL_error(L, "function expects 3 arguments");

  luaL_checktype(L, 1, LUA_TTABLE);

  lua_getfield(L, 1, "_ko");
  profile_ko_t ko = lua_tointeger(L, -1);
  lua_pop(L, 1);

  luaL_checktype(L, 2, LUA_TNUMBER);
  int64_t a = lua_tointeger(L, 2);

  luaL_checktype(L, 3, LUA_TNUMBER);
  int64_t b = lua_tointeger(L, 3);

  int64_t err, res;
  err = profile_kobject_call(ko, a, b, &res);

  lua_pushinteger(L, err);
  lua_pushinteger(L, res);

  return 2;
}

extern "C"
{

LUALIB_API int luaopen_api_handwritten(lua_State *L)
{
  lua_createtable(L, 0, 0);

  // Kobject table
  lua_createtable(L, 0, 0);

  lua_createtable(L, 0, 1);

  {
    static luaL_Reg functions[] = {
      {"new", _profile_kobject_new},
      {nullptr, nullptr}
    };

    luaL_register(L, nullptr, functions);
  }

  lua_setfield(L, -2, "Kobject");

  lua_setfield(L, -2, "profile");

  // Kobject metatable
  lua_pushstring(L, "METATABLE_Kobject");

  lua_createtable(L, 0, 2);

  {
    static luaL_Reg functions[] = {
      {"call", _profile_kobject_call},
      {"__gc", _profile_kobject_delete},
      {nullptr, nullptr}
    };

    luaL_register(L, nullptr, functions);
  }

  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");

  lua_settable(L, LUA_REGISTRYINDEX);

  return 1;
}

} // extern "C"

} // namespace
