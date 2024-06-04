#include <iostream>
using namespace std;

/*
Function Information
*/
void initializeBoard(int (&board)[3][3])
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
           board[i][j] = -1; 
        }
    }
}

/*
Function Information
*/
void displayBoard(int board[3][3])
{
    //Declare variables
    int i = 0;
    int j = 0;
    //Go through Display board 3x+2 database board size
    for(int row = 0; row < 3; row++)
    {
        for(int column = 0; column < 3; column++)
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
        cout << endl;
    }
}

void placeBoard(int (&board)[3][3], int player)
{
    //Declare variables
    int x;
    int y;
    bool invalidPlace;
    do
    {
        cout << "Where to place piece(x y): ";
        cin >> x;
        cin >> y;
        if(x < 0 || x > 2 || y < 0 || y > 2)
        {
            cout << "Invalid Place. Bounds are [0,2] for x and y." << endl;
            invalidPlace = true;
            continue;
        }
        if(board[x][y] != -1)
        {
            cout << "Invalid place. Can not place on another piece." << endl;
            invalidPlace = true;
            continue;
        }
        if(player == 1)
        {
            board[x][y] = 1;
            return;
        }
        else if(player == 0)
        {
            board[x][y] = 0;
            return;
        }
        else
        {
            exit(1);
        }
    } while (invalidPlace);
}

/*
Function Information
*/
bool checkWinner(int board[3][3])
{
    //Declare variables
    bool winner = false;
    //Horizontal Win
    for(int i = 0; i < 3; i++)
    {
        winner = false;
        for(int j = 1; j < 3; j++)
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
    for(int j = 0; j < 3; j++)
    {
        winner = false;
        for(int i = 1; i < 3; i++)
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
    if((board[1][1] == board[0][0] && board[1][1] == board[2][2]) && (board[1][1] == 1 || board[1][1] == 0))
    {
        winner = true;
    }
    else
    {
        winner = false;
    }
    if(winner)
    {
        return winner;
    }
    if((board[1][1] == board[2][0] && board[1][1] == board[0][2]) && (board[1][1] == 1 || board[1][1] == 0))
    {
        winner = true;
    }
    else
    {
        winner = false;
    }
    if(winner)
    {
        return winner;
    }
    return winner;
}

/*
Function Information
*/
int main()
{
    //Declare variables
    int board[3][3];
    bool endGame;
    int player = 1;
    int turns = 0;
    //Initialize board
    initializeBoard(board);
    //Control the game based on if a player has won.
    do
    {
        if(turns > 8)
        {
            break;
        }
        cout << "Current Board" << endl;
        displayBoard(board);
        if(player == 1)
        {
            placeBoard(board, player);
            turns++;
        }
        else if(player == 0)
        {
            placeBoard(board,player);
            turns++;
        }
        else
        {
            exit(1);
        }
        if(player == 1)
        {
            player = 0;
        }
        else if(player == 0)
        {
            player = 1;
        }
        else
        {
            exit(1);
        }
        endGame = checkWinner(board);
    } while (!endGame);
    if(endGame)
    {
        cout << "Winner Found" << endl;
    }
    else
    {
        cout << "No Winner Found" << endl;
    }
    cout << "Displaying final board:" << endl;
    displayBoard(board);
    return 0;
}