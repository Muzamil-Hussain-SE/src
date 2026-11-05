# Ping Pong (raylib)

A small two-paddle Pong game written in C++ with [raylib](https://www.raylib.com/). Play against a CPU-controlled paddle and try to keep the ball in play.

## Features

- 800 × 600 game window running at 60 FPS
- Player-controlled paddle and a simple CPU opponent
- Ball and paddle collisions, wall bounces, and score tracking
- A green court with a center line and circle

## Controls

| Key | Action |
| --- | --- |
| **Up Arrow** | Move the player paddle up |
| **Down Arrow** | Move the player paddle down |
| **Esc** | Close the game window |

## Requirements

- A C++ compiler with C++ support
- raylib installed and available to your compiler and linker

## Build and run

The main Pong implementation is in `PingPong.cpp`. With raylib installed, a MinGW-w64/GCC build on Windows can be made with:

```sh
g++ PingPong.cpp -o PingPong.exe -lraylib -lopengl32 -lgdi32 -lwinmm
```

If raylib is installed in a nonstandard location, add its include and library directories with `-I` and `-L` options. On other platforms, use the appropriate raylib linker dependencies for your compiler and operating system.

Then launch `PingPong.exe` (or the executable produced by your platform's build command).

## Project files

- `PingPong.cpp` — Pong game, including the ball, paddles, CPU behavior, and scoring.
- `main.cpp`, `ball.cpp`, and `ball.h` — additional/simple ball-game source files in the repository; they are separate from the self-contained Pong implementation above.

## How to play

Move the right-side paddle with the Up and Down Arrow keys. The CPU controls the left-side paddle. Each time the ball passes a paddle and exits the screen, the opposing side's score increases and the ball returns to the center.
