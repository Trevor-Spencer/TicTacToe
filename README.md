# TicTacToe Game
This ia a TicTacToe game with a twist that allows for players to be more strategic with their gameplay.

## Table of Contents
- [TicTacToe Game](#tictactoe-game)
  - [Table of Contents](#table-of-contents)
  - [Overview](#overview)
  - [Features](#features)
  - [Requirements](#requirements)
  - [Installation](#installation)

## Overview
This TicTacToe game introduces a twist where players can only have a limited number of pieces on the board at once.
The oldest piece is removed when a new piece is placed - allowing for strategy and foresight. Board can be played
on any square sized grid in a terminal or graphical window. The game continues until a player wins.

## Features
- Playable in terminal or game window popup.
- 3x3, 5x5, and 7x7 boards.
- Players can only have a limited number of pieces on the board at a time.
- Visual indication of the piece that will be removed next in the game window.
- Strategy and preemptive thinking required for piece placements.
- Game continues until a winner is found.
- Simple and intuitive interface.

## Requirements
- Windows 64-bit OS
- C++ compiler (g++, minGW, etc.)
- OpenGL
- GLFW (or use the library provided in the repository)
- GDI (part of Windows)

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/Trevor-Spencer/TicTacToe.git
   cd TicTacToe
    ```
    or download the ZIP file and extract it to your desired location.
2. Make 
    For Windowed mode:
    ```bash
    make TicTacToeWindow
    ```
    For Terminal mode:
    ````bash
    make TicTacToeTerminal
    ```
3. Run the game:
    - For Windowed mode:
    ```bash
    ./TicTacToeWindow
    ```
    - For Terminal mode:
    ```bash
    ./TicTacToeTerminal
    ```
4. OPTIONAL: If you dont have a c++ compiler installed, you can download the precompiled binaries from the /bin folder

## Usage
- Open source code of app type in any text editor to change the board size.
    For Terminal mode, you can change the board size in the `TicTacTowTerminal.cpp` file on line 235.
    For Windowed mode, you can change the board size in the `TicTacToeWindow.cpp` file on line 37.
- Compile the code using the provided makefile.
- Run the game in terminal or windowed mode as per your preference.
