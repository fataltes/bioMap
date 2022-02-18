
set(goMap_lib_srcs
        goMap.cpp)

add_library(goMapLib STATIC ${goMap_lib_srcs})
add_executable(goMap main.cpp)
target_compile_options(goMap PUBLIC "$<$<CONFIG:DEBUG>:${PUFF_DEBUG_FLAGS}>")
target_compile_options(goMap PUBLIC "$<$<CONFIG:RELEASE>:${PUFF_RELEASE_FLAGS}>")
target_link_libraries(goMap goMapLib)