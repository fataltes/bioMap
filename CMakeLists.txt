cmake_minimum_required(VERSION 3.21)
project(goMap)

set(CMAKE_CXX_STANDARD 17)

set(GM_CPP_FLAGS "-W;-Wall;-Wextra;-Wpointer-arith;-Wunused;-Wwrite-strings;-Wno-unknown-pragmas;-Wno-unused-function")


set(OPT_FLAGS "-DHAVE_SIMDE;-D__STDC_FORMAT_MACROS;-DSTX_NO_STD_STRING_VIEW;-O3;-fPIC;-DNDEBUG;-funroll-loops;-ftree-vectorize;-fno-strict-aliasing")
set(DEBUG_FLAGS "-DHAVE_SIMDE;-D__STDC_FORMAT_MACROS;-DSTX_NO_STD_STRING_VIEW;-pg;-g;-gstabs")


set(GOMAP_RELEASE_FLAGS "${DEFINE_FLAGS};${GM_CPP_FLAGS};${OPT_FLAGS}")
set(GOMAP_DEBUG_FLAGS "${DEFINE_FLAGS};${GM_CPP_FLAGS};${DEBUG_FLAGS}")


include_directories(include)
link_directories(lib)
add_subdirectory(src)
