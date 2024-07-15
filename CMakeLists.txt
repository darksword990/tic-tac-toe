cmake_minimum_required(VERSION 3.10)
project(OOPProject)

add_compile_options(-std=c++17 -pthread)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)

include_directories("C:/Users/user/Documents/oop-project/include" "C:/Users/user/Documents/Emscripten/emsdk/upstream/emscripten/cache/sysroot/include" "C:/Users/user/Downloads/json/json/include")
file(GLOB_RECURSE SOURCES "index.cpp" "src/*.cpp")
add_executable(OOPProject ${SOURCES})

target_link_options(OOPProject PRIVATE
    "-Os"
    "-sASSERTIONS=1"
    "-pthread"
    "-sVERBOSE=1"
    "-sPTHREAD_POOL_SIZE=1"
    "-sEXPORTED_FUNCTIONS=_malloc,_free,setValue,getValue"
    "-sEXPORTED_RUNTIME_METHODS=ccall,cwrap"
    "-sENVIRONMENT=web,worker"
    "-sTOTAL_MEMORY=67108864"
)