package.cpath = package.cpath .. ';out/api_handwritten.so'

local api = require 'api_handwritten'

local Kobject = api.profile.Kobject

function ipc_call(state, a, b)
  local ko = Kobject.new(state)

  _, res = ko:call(a, b)

  return res
end
