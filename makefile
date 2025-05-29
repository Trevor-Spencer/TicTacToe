TicTacToeWindow: src/windowGame.cpp src/gl.c
	g++ src/windowGame.cpp src/gl.c -o TicTacToeWindow -Iinclude -Llib -lglfw3 -lopengl32 -lgdi32 -DGLFW_STATIC
cleanWindow:
	del /Q TicTacToeWindow.exe
TicTacToeTerminal: src/terminalGame.cpp
	g++ src/terminalGame.cpp -o TicTacToeTerminal
cleanTerminal:
	del /Q TicTacToeTerminal.exe
