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
- GLAD API gl (Version 3.3)
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
    ```bash
    make TicTacToeTerminal
    ```
3. Run the game:
    - For Windowed mode:
    ```bash
    ./TicTacToeWindow
    ```
    Enter the size of the board you want to play on in the terminal.
    - For Terminal mode:
    ```bash
    ./TicTacToeTerminal
    ```
    Enter the size of the board you want to play on in the terminal.
    Follow the prompts to play the game.
4. OPTIONAL: If you dont have a c++ compiler installed, you can download the precompiled binaries from the /bin folder

## Usage
- Compile the code using the provided makefile.
- Run the game in terminal or windowed mode as per your preference.
