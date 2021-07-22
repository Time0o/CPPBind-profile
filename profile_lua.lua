package.cpath = package.cpath .. ';out/api.so'

local api = require 'api'

local Kobject = api.profile.Kobject
local CapKobject = api.profile.CapKobject

function ipc_call(state, a, b)
  local ko = Kobject.new(state)

  local cap = CapKobject.new_2(ko)

  _, res = cap:access():call(a, b, 0)

  return res
end
