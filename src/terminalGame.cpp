#include <iostream>
#include <vector>
using namespace std;


class node
{
    private:
        int xCord;
        int yCord;
    public:
        node()
        {
            xCord = -1;
            yCord = -1;
        }
        node(int x, int y)
        {
            xCord = x;
            yCord = y;
        }
        void setXCord(int val) {xCord = val;}
        void setYCord(int val) {yCord = val;}
        int getXCord() {return xCord;}
        int getYCord() {return yCord;}
};

/*
Function: initializeBoard
Function Description:
    Initializes the game board to a default state where all cells are empty (-1).

Parameters:
    board: Reference to a 2D array representing the game board.
    boardSize: Size of the board (number of rows/columns).

Returns:
    void: Function does not return a value.
*/
void initializeBoard(int** (&board), int boardSize)
{
    for(int i = 0; i < boardSize; i++)
    {
        for(int j = 0; j < boardSize; j++)
        {
           board[i][j] = -1; 
        }
    }
}

/*
Function: displayBoard
Function Description:
    Displays the current state of the game board in the console.

Parameters:
    board: Reference to a 2D array representing the game board.
    boardSize: Size of the board (number of rows/columns).

Returns:
    void: Function does not return a value.
*/
void displayBoard(int** board, int boardSize)
{
    //Go through Display board
    cout << "+";
    for(int i = 0; i < boardSize; i++)
    {
        cout << "-";
    
    }
    cout << "+\n";
    for(int row = 0; row < boardSize; row++)
    {
        cout << "|";
        for(int column = 0; column < boardSize; column++)
        {
            if(board[row][column] == -1)
            {
                cout << " ";
            }
            else if(board[row][column] == 1)
            {
                cout << "X";
            }
            else if(board[row][column] == 0)
            {
                cout << "O";
            }
            else
            {
                cout << "E";
            }
        }
        cout << "|\n";
    }
     cout << "+";
    for(int i = 0; i < boardSize; i++)
    {
        cout << "-";
    
    }
    cout << "+\n";

}

/*
Function: placeBoard
Function Description:
    Places a piece on the game board at the specified coordinates (x, y) for the current player.
    If the board is full, it removes the oldest piece from the player's list and places the new piece.
    This function loops until a valid placement is made, ensuring the coordinates are within bounds and not already occupied.
    The function updates the board and the player's piece list accordingly.

Parameters:
    board: Reference to a 2D array representing the game board.
    boardSize: Size of the board (number of rows/columns).
    player: The current player (1 or 0).
    PList: Reference to the player's piece list (vector of nodes).

Returns:
    void: Function does not return a value.
*/
void placeBoard(int** (&board),int boardSize, int player, vector<node>& PList)
{
    //Declare variables
    int x;
    int y;
    bool invalidPlace;
    node tempNode;
    do
    {
        cout << "Where to place piece(x y): ";
        cin >> x;
        cin >> y;
        if(x < 0 || x >= boardSize || y < 0 || y >= boardSize)
        {
            cout << "Invalid Place. Bounds are [0," << boardSize << ") for x and y." << endl;
            invalidPlace = true;
            continue;
        }
        if(board[x][y] != -1)
        {
            cout << "Invalid place. Can not place on another piece." << endl;
            invalidPlace = true;
            continue;
        }
        if(PList.size() == boardSize)
        {
            node remNode = PList.back();
            PList.pop_back();
            board[remNode.getXCord()][remNode.getYCord()] = -1;
            tempNode.setXCord(x);
            tempNode.setYCord(y);
            PList.insert(PList.begin(), tempNode);
            invalidPlace = false;
            board[x][y] = player;
        }
        else if(PList.size() == 0)
        {
            tempNode.setXCord(x);
            tempNode.setYCord(y);
            PList.push_back(tempNode);
            invalidPlace = false;
            board[x][y] = player;
        }
        else
        {
            tempNode.setXCord(x);
            tempNode.setYCord(y);
            PList.insert(PList.begin(), tempNode);
            invalidPlace = false;
            board[x][y] = player;
        }
    } while (invalidPlace);
}

/*
Function: checkWinner
Function Description:
    Checks if there is a winner on the game board by checking rows, columns, and diagonals.
Parameters:
    board: Reference to a 2D array representing the game board.
    boardSize: Size of the board (number of rows/columns).
Returns:
    bool: Returns true if a winner is found, false otherwise.
*/
bool checkWinner(int** board,int boardSize)
{
    //Declare variables
    bool winner = false;
    //Horizontal Win
    for(int i = 0; i < boardSize; i++)
    {
        winner = false;
        for(int j = 1; j < boardSize; j++)
        {
            if((board[i][0] == board[i][j]) && (board[i][0] == 1 || board[i][0] == 0))
            {
                winner = true;
            }
            else
            {
                winner = false;
                break;
            }
        }
        if(winner)
        {
            return winner;
        }
    }
    
    //Vertical Win
    winner = false;
    for(int j = 0; j < boardSize; j++)
    {
        winner = false;
        for(int i = 1; i < boardSize; i++)
        {
            if((board[0][j] == board[i][j]) && (board[0][j] == 1 || board[0][j] == 0))
            {
                winner = true;
            }
            else
            {
                winner = false;
                break;
            }
        }
        if(winner)
        {
            return winner;
        }
    }
    
    //Diagonal Win
    winner = false;
    for(int i = 1; i < boardSize; i++)
    {
        if(board[0][0] == board[i][i] && (board[i][i] == 1 || board[i][i] == 0))
        {
            winner = true;
        }
        else
        {
            winner = false;
            break;
        }
    }
    if(winner)
    {
        return winner;
    }
    
    //Anti-Diagonal Win
    winner = false;
    for(int i = 1; i < boardSize; i++)
    {
        if((board[boardSize - 1][0] == board[boardSize - i - 1][i]) && (board[boardSize - i - 1][i] == 1 || board[boardSize - i - 1][i] == 0))
        {
            winner = true;
        }
        else
        {
            winner = false;
            break;
        }
    }
    if(winner)
    {
        return winner;
    }
    return winner;
}

int main()
{
    //Declare variables
    int** board;
    bool endGame;
    int player = 1;
    int turns = 0;
    int boardSize = 0;
    vector<node>P1List;
    vector<node>P2List;

    cout << "Welcome to the Terminal Tic Tac Toe Game!" << endl;
    cout << "Enter the size of the board (3 for 3x3, 4 for 4x4, etc.): ";
    cin >> boardSize;
    if (boardSize < 3) {
        cout << "Board size must be at least 3." << endl;
        return 1;
    }

    board = (int**)malloc(boardSize * sizeof(int*));
    if (board == NULL) {
        perror("Failed to allocate row pointers");
        return 1;
    }
    for (int i = 0; i < boardSize; i++) {
        board[i] = (int*)malloc(boardSize * sizeof(int));
        if (board[i] == NULL) {
            perror("Failed to allocate row");
            return 1;
        }
    }

    
    //Initialize board
    initializeBoard(board, boardSize);
    //Control the game based on if a player has won.
    do
    {
        cout << "Current Board" << endl;
        displayBoard(board, boardSize);
        if(player == 1)
        {
            placeBoard(board, boardSize, player, P1List);
            turns++;
            player = 0;
        }
        else if(player == 0)
        {
            placeBoard(board,boardSize, player, P2List);
            turns++;
            player = 1;
        }
        else
        {
            exit(1);
        }
        //Check if a player has won
        endGame = checkWinner(board, boardSize);
    } while (!endGame);

    //Display the winner
    cout << "Game Over" << endl;
    cout << "Turns Taken: " << turns << endl;
    if(endGame)
    {
        cout << "Winner Found" << endl;
    }
    else
    {
        cout << "No Winner Found" << endl;
    }
    cout << "Displaying final board:" << endl;
    displayBoard(board, boardSize);

    //Free the allocated memory
    for (int i = 0; i < boardSize; i++) {
        free(board[i]);
    }
    free(board);
    return 0;
}