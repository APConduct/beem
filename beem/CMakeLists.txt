cmake_minimum_required(VERSION 3.28)
project(beem)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE__CXX_STANDARD_REQUIRED ON)

if(APPLE)
    set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++")
    set(CMAKE_C_COMPILER "/opt/homebrew/opt/llvm/bin/clang")
endif ()

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-fexperimental-library)
    add_compile_options(-fmodules)
    set(CMAKE_CXX_SCAN_FOR_MODULES ON)
endif ()

find_package(PkgConfig REQUIRED)
pkg_check_modules(LUAJIT REQUIRED luajit)

include_directories(${LUAJIT_INCLUDE_DIRS})
link_directories(${LUAJIT_LIBRARY_DIRS})

set(sol2_VERSION 3.2.1)
set(RAYLIB_VERSION 5.5)

if (APPLE)
    set(LUAJIT_LOCAL_INCLUDE_DIR "/opt/homebrew/opt/luajit/include/luajit-2.1")
endif ()

include(FetchContent)
FetchContent_Declare(
        sol2
        GIT_REPOSITORY https://github.com/ThePhD/sol2.git
        GIT_TAG develop
)
FetchContent_MakeAvailable(sol2)

FetchContent_Declare(
        tinyfd
        GIT_REPOSITORY https://git.code.sf.net/p/tinyfiledialogs/code tinyfiledialogs-code
        GIT_TAG master
)
FetchContent_MakeAvailable(tinyfd)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)


FetchContent_Declare(
        raylib
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
        URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
)
FetchContent_MakeAvailable(raylib)

# Place this before add_library(beem ...)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

if (CMAKE_COMPILER_ID MATCHES "Clang")
        add_compile_options(-fmodules)
endif ()

add_library(beem SHARED include/beem.hpp)
target_sources(beem
        PUBLIC
        FILE_SET CXX_MODULES
        FILES
        src/modules/raylib.ixx
        src/modules/beem.ixx
        src/modules/euclid.ixx


)
if(APPLE)
    set(CMAKE_SHARED_LIBRARY_SUFFIX ".dylib")
    set_target_properties(beem PROPERTIES
            PREFIX ""
            SUFFIX ".dylib"
            MACHO_COMPATIBILITY_VERSION "1.0.0"
            MACHO_CURRENT_VERSION "1.0.0"
    )
    target_link_options(beem PRIVATE "-undefined" "dynamic_lookup")
endif()
target_include_directories(beem PRIVATE
        ${LUAJIT_INCLUDE_DIRS}
        ${LUAJIT_LOCAL_INCLUDE_DIR}
)
target_link_directories(beem PRIVATE
        ${LUAJIT_LIBRARY_DIRS}
)
target_link_libraries(beem PRIVATE
        sol2 raylib ${LUAJIT_LIBRARIES}
)



set_target_properties(beem PROPERTIES PREFIX "")
set_target_properties(beem PROPERTIES OUTPUT_NAME "beem")

# In CMakeLists.txt
install(TARGETS beem
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/lua/5.1
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(FILES beem/init.lua
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/lua/5.1/beem
)

if(APPLE)
    install(FILES ${CMAKE_BINARY_DIR}/_deps/raylib-build/raylib/libraylib.dylib
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/lua/5.1)
endif()