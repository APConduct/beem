cmake_minimum_required(VERSION 3.28)
project(beem)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE__CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-fexperimental-library)
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
        raylib
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
        URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
)
FetchContent_MakeAvailable(raylib)

# Place this before add_library(beem ...)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

add_library(beem SHARED src/beem.cpp include/beem.hpp)
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