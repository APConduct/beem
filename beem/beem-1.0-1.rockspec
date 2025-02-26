package = "beem"
version = "1.0-1"
source = {
   url = "git+https://github.com/APConduct/beem.git",
   tag = "v1.0"
}
description = {
   summary = "C++ binding library for Lua using Sol2",
   detailed = [[
      A binding library providing Point class with distance calculations.
      Built with Sol2 for Lua/LuaJIT integration.
   ]],
   homepage = "https://github.com/APConduct/beem",
   license = "Apache-2.0"
}
build = {
   type = "cmake",
   variables = {
      CMAKE_INSTALL_PREFIX = "$(PREFIX)",
      BUILD_SHARED_LIBS = "ON",
      CMAKE_BUILD_TYPE = "Release",
      CMAKE_GENERATOR = "Ninja"

   },
   platforms = {
      unix = {
         variables = {
            CMAKE_GENERATOR = "Ninja"

         }
      },
      macosx = {
         variables = {
            CMAKE_GENERATOR = "Ninja",
            CMAKE_CXX_COMPILER = "/opt/homebrew/opt/llvm/bin/clang++",
            CMAKE_C_COMPILER = "/opt/homebrew/opt/llvm/bin/clang"

         }
      }
   }
}