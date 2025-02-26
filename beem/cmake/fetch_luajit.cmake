FetchContent_Declare(
        luaJIT
        GIT_REPOSITORY https://github.com/luaJit/LuaJIT.git
        GIT_TAG v2.1 # latest stable version
)

FetchContent_MakeAvailable(luaJIT)
add_library(luajit STATIC IMPORTED)
set_target_properties(luajit PROPERTIES
        IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/_deps/luajit-build/src/libluajit.a
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_BINARY_DIR}/_deps/luajit-src/src
)