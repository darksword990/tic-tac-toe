# Tic-tac-toe Project

This project uses the Emscripten toolchain to compile this C++ project to WebAssembly. I have also used concepts of Minimax Algorithm to make AI game mode. You can also choose custom difficulty levels (Easy, Medium, Hard).

## Installation

You must have [CMake](https://cmake.org/download/), [git](https://git-scm.com), and [Emscripten](https://emscripten.org/docs/getting_started/downloads.html) toolchain compiler installed properly.

Make sure to edit the include paths in `CMakeLists.txt` file to avoid any errors.

## Build

To build this project, you must have the necessary tools installed above. Then open up command prompt and run the following commands:

Changing directory:
```bash
cd <current-project-directory-path>
```
Make folder:
```bash
mkdir build
```
Changing directory to build directory:
```bash
cd build
```
Building MinGW Makefiles:
```bash
emcmake cmake -G "MinGW Makefiles" ..
```
Build the project:
```bash
emmake make
```

## Running the project
Run the following command in your shell:

```bash
emrun --no_browser --port <port number> .
```

`--no_browser` is optional, it simply opens up the browser

`--port` is necessary to host the project to the specified port