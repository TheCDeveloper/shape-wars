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
git clone https://github.com/thecdeveloper/shape-wars.git shape-wars
cd shape-wars
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```
To run, `res` folder must accessable at current directory
