<h1 align="center">Welcome to tic-tac-toe 👋</h1>
<p>
  <a href="https://www.npmjs.com/package/tic-tac-toe" target="_blank">
    <img alt="Version" src="https://img.shields.io/npm/v/tic-tac-toe.svg">
  </a>
</p>

> This project uses the Emscripten toolchain to compile this C++ project to WebAssembly. I have also used concepts of Minimax Algorithm to make AI game mode. We can choose custom difficulty levels (Easy, Medium, Hard). The project uses macros such as `EM_JS` and `EM_ASM` from Emscripten library. More info can be found on their documentation.

## Install

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

## Show your support

Give a ⭐️ if you liked this project!
