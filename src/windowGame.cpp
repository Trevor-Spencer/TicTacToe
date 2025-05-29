#include <iostream>
#include <vector>
#include <gl/gl.h>
#include <GLFW/glfw3.h>
#include <math.h>

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

//GLOBAL VARIABLES
int** board;
bool endGame;
int player = 1;
int turns = 0;
int boardSize = 0;
vector<node>P1List;
vector<node>P2List;
bool shouldRedraw = true;

/*
Function Information
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
Function Information
*/
void placeBoard(int** (&board),int boardSize, vector<node>& PList, int xBoard, int yBoard)
{
    if(PList.size() == boardSize)
    {
        node remNode = PList.back();
        node tempNode;
        PList.pop_back();
        board[remNode.getXCord()][remNode.getYCord()] = -1;
        tempNode.setXCord(xBoard);
        tempNode.setYCord(yBoard);
        PList.insert(PList.begin(), tempNode);
        board[xBoard][yBoard] = player;
    }
    else if(PList.size() == 0)
    {
        node tempNode;
        tempNode.setXCord(xBoard);
        tempNode.setYCord(yBoard);
        PList.push_back(tempNode);
        board[xBoard][yBoard] = player;
    }
    else
    {
        node tempNode;
        tempNode.setXCord(xBoard);
        tempNode.setYCord(yBoard);
        PList.insert(PList.begin(), tempNode);
        board[xBoard][yBoard] = player;
    }
    player = player ^ 1;
    turns++;
}

bool checkBoard(int** board, int boardSize)
{
    //Check if the board is full
    for(int i = 0; i < boardSize; i++)
    {
        for(int j = 0; j < boardSize; j++)
        {
            if(board[i][j] == -1)
            {
                return false;
            }
        }
    }
    return true;
}

/*
Function Information
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
            glColor3f(0.0f, 1.0f, 0.0f);
            float xBoardCenter = (i) * (600 / boardSize) + (600/(boardSize*2));
            float linePlacement = 2.0f / (float)boardSize;
            glLineWidth(5.0f);
            glBegin(GL_LINES);
                // Horizontal lines
                glVertex2f(-1.0f, -1.0f + (linePlacement * (i)) + linePlacement / 2);
                glVertex2f(1.0f, -1.0f + (linePlacement * (i)) + linePlacement / 2);
            glEnd();
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
            glColor3f(0.0f, 1.0f, 0.0f);
            float xBoardCenter = (j) * (600 / boardSize) + (600/(boardSize*2));
            float linePlacement = 2.0f / (float)boardSize;
            glLineWidth(5.0f);
            glBegin(GL_LINES);
                // Vertical lines
                glVertex2f(-1.0f + (linePlacement * (j)) + linePlacement / 2, -1.0f);
                glVertex2f(-1.0f + (linePlacement * (j)) + linePlacement / 2, 1.0f);
            glEnd();
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
        glColor3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_LINES);
            glVertex2f(-1.0f, -1.0f);
            glVertex2f(1.0f, 1.0f );
        glEnd();
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
        glColor3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_LINES);
            glVertex2f(1.0f, -1.0f);
            glVertex2f(-1.0f, 1.0f );
        glEnd();
        return winner;
    }
    return winner;
}

void mouseClickCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        // Convert mouse coordinates to OpenGL coordinates
        float x = (xpos / 300.0f) - 1.0f; // Assuming window width is 600
        float y = 1.0f - (ypos / 300.0f); // Assuming window height is 600

        int xBoard = (int)ypos / (600 / boardSize);
        int yBoard = (int)xpos / (600 / boardSize);

        float xBoardCenter = ((int)xpos / (600 / boardSize)) * (600 / boardSize) + (600/(boardSize*2));
        float yBoardCenter = ((int)ypos / (600 / boardSize)) * (600 / boardSize) + (600/(boardSize*2));

        std::cout << "Mouse clicked at Board coordinates: (" << xBoard << ", " << yBoard << ")\n";

        if(board[xBoard][yBoard] != -1)
        {
            cout << "Invalid Place. Can not place on another piece." << endl;
            return;
        }
        else
        {
            placeBoard(board, boardSize, (player == 1 ? P1List : P2List), xBoard, yBoard);
            shouldRedraw = true;
        }
    }

    
}

void drawBoard()
{
    float linePlacement = 2.0f / (float)boardSize;
    // Set line color (white)
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(5.0f);

    // Draw the grid lines
    glBegin(GL_LINES);
        for(int i = 0; i < boardSize - 1; i++)
        {
            // Vertical lines
            glVertex2f(-1.0f + (linePlacement * (i + 1)), -1.0f);
            glVertex2f(-1.0f + (linePlacement * (i + 1)), 1.0f);
            // Horizontal lines
            glVertex2f(-1.0f, -1.0f + (linePlacement * (i + 1)));
            glVertex2f(1.0f, -1.0f + (linePlacement * (i + 1)));
        }
    glEnd();

    // Draw the pieces
    for(int i = 0; i < boardSize; i++)
    {
        for(int j = 0; j < boardSize; j++)
        {
            if(board[i][j] == 1)
            {
                if(P1List.back().getXCord() == i && P1List.back().getYCord() == j && P1List.size() == boardSize && player == 1 && endGame == false)
                {
                    glColor3f(1.0f, 0.0f, 0.0f);
                }
                else
                {
                    glColor3f(1.0f, 1.0f, 1.0f); 
                }
                glBegin(GL_LINES);
                    glVertex2f(-1.0f + (linePlacement * j) + (linePlacement / 4), -1.0f + (linePlacement * i) + (linePlacement / 4));
                    glVertex2f(-1.0f + (linePlacement * j) + (linePlacement / 4) * 3, -1.0f + (linePlacement * i) + (linePlacement / 4) * 3);

                    glVertex2f(-1.0f + (linePlacement * j) + (linePlacement / 4), -1.0f + (linePlacement * i) + (linePlacement / 4) * 3);
                    glVertex2f(-1.0f + (linePlacement * j) + (linePlacement / 4) * 3, -1.0f + (linePlacement * i) + (linePlacement / 4));
                glEnd();
            }
            else if(board[i][j] == 0)
            {
                if(P2List.back().getXCord() == i && P2List.back().getYCord() == j && P2List.size() == boardSize && player == 0 && endGame == false)
                {
                    glColor3f(1.0f, 0.0f, 0.0f); 
                }
                else
                {
                    glColor3f(1.0f, 1.0f, 1.0f); 
                }
                float centerX = -1.0f + (linePlacement * j) + (linePlacement / 2);
                float centerY = -1.0f + (linePlacement * i) + (linePlacement / 2);
                float radius = linePlacement / 4;
                int segments = 40; // More segments = smoother circle
                glBegin(GL_TRIANGLE_FAN);
                    glVertex2f(centerX, centerY); // Center of circle
                    for (int k = 0; k <= segments; ++k) {
                        float angle = 2.0f * 3.1415926f * k / segments;
                        float x = centerX + cosf(angle) * radius;
                        float y = centerY + sinf(angle) * radius;
                        glVertex2f(x, y);
                    }
                glEnd();
                
            }
        }
    }
}


/*
Function Information
*/
int main()
{
    cout << "Welcome to the Window Tic Tac Toe Game!" << endl;
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

    if (!glfwInit()) {
        std::cerr << "Failed to init GLFW\n";
        return -1;
    }
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow* window = glfwCreateWindow(600, 600, "OpenGL Tic Tac Toe", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Setup the coordinate system to go from -1 to 1 on both axes
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, 1, -1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Register callbacks
    glfwSetMouseButtonCallback(window, mouseClickCallback);

    
    //Initialize board
    initializeBoard(board, boardSize);

    //Background color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    drawBoard();

    glfwSwapBuffers(window);
    //Control the game based on if a player has won.
    while(!glfwWindowShouldClose(window) && !endGame)
    {
        if(shouldRedraw)
        {
            

            if(checkWinner(board, boardSize) || checkBoard(board, boardSize))
            {
                endGame = true;
                glfwSetMouseButtonCallback(window, nullptr); // Unregister the mouse button callback

            }
            else
            {
                endGame = false;
            }
            //Background color
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            drawBoard();

            glfwSwapBuffers(window);
            shouldRedraw = false;
        }
        
        glfwWaitEvents();
    }
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    drawBoard();

    if(endGame)
    {
        cout << "Game Over" << endl;
        cout << "Turns Taken: " << turns << endl;
        if(checkWinner(board, boardSize))
        {
            
            glfwSwapBuffers(window);
            cout << "Winner Found" << endl;
        }
        else
        {
            cout << "No Winner Found" << endl;
        }
    }
    if(checkBoard(board, boardSize))
    {
        cout << "Board is full. No winner." << endl;
    }

    while(!glfwWindowShouldClose(window))
    {
        // Wait for events
        glfwWaitEvents();
    }
    

    glfwDestroyWindow(window);
    glfwTerminate();
    //Free the allocated memory
    for (int i = 0; i < boardSize; i++) {
        free(board[i]);
    }
    free(board);
    return 0;
}