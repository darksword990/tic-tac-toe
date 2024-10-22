<h1 align="center">Welcome to tic-tac-toe 👋</h1>

> This project uses the Emscripten toolchain to compile this C++ project to WebAssembly. I have also used concepts of Minimax Algorithm to make AI game mode. We can choose custom difficulty levels (Easy, Medium, Hard). The project uses macros such as `EM_JS` and `EM_ASM` from Emscripten library and other Emscripten functions. More info can be found on their documentation.

## Installation

You must have [CMake](https://cmake.org/download/), [Git](https://git-scm.com), and [Emscripten](https://emscripten.org/docs/getting_started/downloads.html) properly installed first.

## Build

You first have to make build directory inside the project

Run:

```sh
cd build
```

Then run the following commands on terminal:

```sh
emcmake cmake -G "MinGW Makefiles" ..

emmake make
```

## Usage

```sh
emrun --no_browser --port <port number> .
```

## Example

```sh
emrun --no_browser --port 8080 .
```

`--no_browser` (optional) This argument opens up the browser

`--port` The port number must be specified after this argument

## Author

👤 **Khuzaima Sharif**

* Github: [@darksword990](https://github.com/darksword990)

## Contributors

👤 **Muhammad Ali Khan**

* Github: [@MAKhan9909](https://github.com/MAKhan9909)

👤 **Cr07ch37**

* Github: [@Cr07ch37](https://github.com/Cr07ch37)

## Show your support

Give a ⭐️ if you liked this project!
