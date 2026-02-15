## Shape wars
A game made in C and SDL3, themed around geometrical shapes.
<br>
The player is a triangle, enemies are squares.
<br>
The objective is to survive as many rounds as possible.
<br>

### Building from source
Requirements
- C compiler
- SDL3
- CMake

Build
```
cd <project root>
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```