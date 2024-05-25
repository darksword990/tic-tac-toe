cmake_minimum_required(VERSION 3.10)
project(OOPProject)

add_compile_options(-std=c++11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)

include_directories("C:/Users/user/Documents/oop-project/include" "C:/Users/user/Documents/Emscripten/emsdk/upstream/emscripten/cache/sysroot/include" "C:/Users/user/Downloads/json/json/include")
file(GLOB_RECURSE SOURCES "index.cpp" "src/*.cpp")
add_executable(OOPProject ${SOURCES})

# Adjusted target_link_options for standalone module
target_link_options(OOPProject PRIVATE
    "-Os"
    "--bind"
    # "-s SIDE_MODULE=1"
    # "-s WASM=1"
    "--preload-file db.json"
    # "-sFORCE_FILESYSTEM"
    # "-s BINARYEN_ASYNC_COMPILATION=0"
    "-sEXPORTED_FUNCTIONS=_malloc,_free,setValue,getValue"
    "-sEXPORTED_RUNTIME_METHODS=ccall,cwrap"
)