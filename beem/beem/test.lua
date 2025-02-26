#!/usr/bin/env luajit

package.cpath = package.cpath .. ";../lib/?.dylib"
local beem = require('beem')

local p1 = beem.Point.new(0,0)
local p2 = beem.Point.new(3,4)
print(p1:distance_to(p2))