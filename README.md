# 🎮 Ping Pong Game

<div align="center">

<img src="https://img.shields.io/badge/C%2B%2B-17-00599C?style=for-the-badge&logo=c%2B%2B" alt="C++" />
<img src="https://img.shields.io/badge/raylib-3.7-6B8E23?style=for-the-badge" alt="raylib" />
<img src="https://img.shields.io/badge/Status-Playable-4CAF50?style=for-the-badge" alt="Playable" />

A colorful, fast-paced Pong arcade game built with C++ and raylib.

</div>

## ✨ Overview

This project is a small but polished arcade-style ping pong game where a player faces a CPU-controlled opponent in a two-paddle match. The game includes score tracking, collision detection, velocity-based ball movement, and a clean retro-styled UI.

## 🕹️ Gameplay

- Move your paddle up and down using the keyboard
- Compete against a simple AI opponent
- Score points by getting the ball past the opponent
- Keep the rally going and win the match

## 🎯 Features

- Smooth 60 FPS gameplay
- Player vs CPU mode
- Real-time collision handling
- Score system
- Center court and visual divider
- Simple, responsive controls
- Built using raylib for lightweight graphics

## 🕹️ Controls

| Key | Action |
| --- | --- |
| ↑ / W | Move paddle up |
| ↓ / S | Move paddle down |
| Esc | Exit the game |

## 🧰 Requirements

Before building the game, make sure you have:

- C++ compiler
- raylib installed
- OpenGL support on your system

## 🚀 Build Instructions

### Windows (MinGW / g++)

```bash
g++ PingPong.cpp -o PingPong.exe -lraylib -lopengl32 -lgdi32 -lwinmm
```

Then run:

```bash
./PingPong.exe
```

### Linux

```bash
g++ PingPong.cpp -o PingPong -lraylib -lm -ldl -lpthread
./PingPong
```

### macOS

```bash
g++ PingPong.cpp -o PingPong -framework OpenGL -framework Cocoa -framework IOKit -lraylib
./PingPong
```

> If raylib is not installed globally, add the correct include and library paths for your environment.

## 📁 Project Structure

```text
src/
├── PingPong.cpp     # Main game implementation
├── main.cpp         # Extra raylib test/demo file
├── ball.h           # Ball class declaration
├── ball.cpp         # Ball class implementation
├── README.md        # Project documentation
├── game.exe         # Built Windows executable
├── main.exe         # Extra built executable
└── output/          # Output folder
```

## 🏗️ Notes

The main playable game logic is implemented in `PingPong.cpp`. The other files in the project are supporting or experimental examples related to raylib and ball movement.

## 📌 Goal

The objective is simple: beat the CPU and keep the ball out of your goal as long as possible.

---

Made with ❤️ and raylib.
