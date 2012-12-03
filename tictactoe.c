//-----------------------------------
// Ryan Endacott
// Test tic tac toe program
//-----------------------------------

#include <stdio.h>

#define NUMROWS 4
#define NUMCOLS 5
#define WINCOND 3

// The preprocessor will not multiply these two, HOWEVER, 
// The compiler will optimise so that the calculation should only occur once
// (probably/hopefully)
#define GRIDSPACES (NUMROWS * NUMCOLS)

#define TRUE 1
#define FALSE 0

// Function to see if someone has won after moving at position
int win(char board[NUMROWS][NUMCOLS], int position);

// Function to see if someone won horizontally
// Row and col are latest move space, curVal is value to check against
int horiz(char board[NUMROWS][NUMCOLS], int row, int col, char curVal);


// Function to see if someone won vertically
// Row and col are latest move space, curVal is value to check against
int vert(char board[NUMROWS][NUMCOLS], int row, int col, char curVal);


// Function to see if someone won positive diagonally
// Row and col are latest move space, curVal is value to check against
int posDiag(char board[NUMROWS][NUMCOLS], int row, int col, char curVal);


// Function to see if someone won negative diagonally
// Row and col are latest move space, curVal is value to check against
int negDiag(char board[NUMROWS][NUMCOLS], int row, int col, char curVal);


// Prints the board
void printBoard(char board[NUMROWS][NUMCOLS]);


// Resets the tic tac toe array to be all
// '-' characters
void reset(char board[NUMROWS][NUMCOLS]);


// Lets the current player have a turn
// Returns position of latest turn
int playerTurn(char board[NUMROWS][NUMCOLS], int player);


// Method to get a valid space to move to
int getValidSpace(char board[NUMROWS][NUMCOLS]);


// Returns min
int min (int x, int y);

// Returns max
int max (int x, int y);



int main(void)
{

    // Init the board
    char board[NUMROWS][NUMCOLS];



    // Reset it
    reset(board);

    printBoard(board);

    // Holds the winner
    int winner = 0;

    // Active player
    int player = 1;

    while(!winner)
    {

        // Player has a turn
        int position = playerTurn(board, player);


        if (win(board, position)) 
        {
            winner = player;
        }

        player = (player == 1) ? 2 : 1;


        printf("\n\n");

        printBoard(board);
    }

    printf("Congrats!  Player %d has won!\n", winner);

    return 0; 
}

// Prints the board
void printBoard(char board[NUMROWS][NUMCOLS])
{

    int row, col;

    for (row = 0; row < NUMROWS; row++)
    {

        for (col = 0; col < NUMCOLS; col++)
        {
            printf("%c ", board[row][col] );
        } 

        printf("\n");
    }
}

// Resets the tic tac toe array to be all
// '-' characters
void reset(char board[NUMROWS][NUMCOLS])
{
    int row;
    int col;


    for (row = 0; row < NUMROWS; row++)
    {
        for (col = 0; col < NUMCOLS; col++)
        {
            board[row][col] = '-';
        } 
    }
}

// Function to see if someone has won after moving at position
int win(char board[NUMROWS][NUMCOLS], int position)
{

    // Zero-indexed
    position--;

    // board[row][col] = row * NUMCOLS + col
    int row = position / NUMCOLS;
    int col = position % NUMCOLS;


    // Value to check against to see if won
    char curVal = board[row][col];


    return horiz(board, row, col, curVal) ||
        vert(board, row, col, curVal) || 
        posDiag(board, row, col, curVal) ||
        negDiag(board, row, col, curVal);
}

// Function to see if someone won horizontally
// Row and col are latest move space, curVal is value to check against
int horiz(char board[NUMROWS][NUMCOLS], int row, int col, char curVal)
{

    // Only need to check within range of a possible win,
    // Also must be in bounds
    int endCol = min(col + WINCOND - 1, NUMCOLS - 1);
    col = max(col - WINCOND + 1, 0);


    int count = 0;
    for (;col <= endCol; col++)
    {
        if (board[row][col] == curVal)
            count++;
        else
            count = 0;

        if (count == WINCOND)
            return 1;

    }

    return 0;

}

// Function to see if someone won vertically
// Row and col are latest move space, curVal is value to check against
int vert(char board[NUMROWS][NUMCOLS], int row, int col, char curVal)
{


    // Only need to check within range of a possible win,
    // Also must be in bounds
    int endRow = min(row + WINCOND - 1, NUMROWS - 1);
    row = max(row - WINCOND + 1, 0);


    int count = 0;
    for (;row <= endRow; row++)
    {
        if (board[row][col] == curVal)
            count++;
        else
            count = 0;

        if (count == WINCOND)
            return 1;

    }

    return 0;

}

// Function to see if someone won positive diagonally
// Row and col are latest move space, curVal is value to check against
int posDiag(char board[NUMROWS][NUMCOLS], int row, int col, char curVal)
{

    // Set up endRow and endCol by setting to both to max possible
    int endRow = min(row + WINCOND - 1, NUMROWS - 1);
    int endCol = min(col + WINCOND - 1, NUMCOLS - 1);

    // Then equalizing them to the max in bounds and on diag
    int diff = min(endRow - row, endCol - col); 
    endRow = row + diff;
    endCol = col + diff;

    // Set up row and col the same way, both to min possible
    row = max(row - WINCOND + 1, 0);
    col = max(col - WINCOND + 1, 0);

    // Then equalize to min in bounds and on diag
    diff = min(endRow - row, endCol - col);
    row = endRow - diff;
    col = endCol - diff;



    int count = 0;

    // Because all are equalized, only one counter (row to endRow) should be needed
    while (row <= endRow)
    {
        if (board[row][col] == curVal)
            count++;
        else
            count = 0;

        if (count == WINCOND)
            return 1;

        row++;
        col++;
    }

    return 0;
}


// Function to see if someone won negative diagonally
// Row and col are latest move space, curVal is value to check against
int negDiag(char board[NUMROWS][NUMCOLS], int row, int col, char curVal)
{
   // Set up endRow and endCol by setting one to max, other to min
    int endRow = min(row + WINCOND - 1, NUMROWS - 1);
    int endCol = max(col - WINCOND + 1, 0);

    // Then equalizing them to the values such that they will both be in bounds and on the diag
    int diff = min(endRow - row, col - endCol);
    endRow = row + diff;
    endCol = col - diff;

    // Set up row and col the same way, both to best possible
    row = max(row - WINCOND + 1, 0);
    col = min(col + WINCOND - 1, NUMCOLS - 1);

    // Then equalize to best in bounds and on diag
    diff = min(endRow - row, col - endCol);
    row = endRow - diff;
    col = endCol + diff;



    int count = 0;

    // Because all are equalized, only one counter (row to endRow) should be needed
    while (row <= endRow)
    {
        if (board[row][col] == curVal)
            count++;
        else
            count = 0;

        if (count == WINCOND)
            return 1;

        row++;
        col--;
    }

    return 0;



    return 0;
}


// Lets the current player have a turn
// Returns position of latest turn
int playerTurn(char board[NUMROWS][NUMCOLS], int player)
{

    int input;
    static int count = 1;


    if (count <= 2) // Give instructions on first call for each player
    {
        printf("\n\n"
            "In order to place a piece, press the number that corresponds to the desired place.\n"
            "Ex:  The numbers will be laid out as follows:\n"
            "");

        int i, j;  

        int count2 = 1;


        for (i = 0; i < NUMROWS; i++)
        {
            for(j = 0; j < NUMCOLS; j++)
            {
                printf("%-3d", count2);
                count2++;
            }
            printf("\n");
        }

    }

    printf("\n\nPlayer %d's turn to move.\nPlease enter a move: ", player);

    input = getValidSpace(board);


    // Set char using pointer arithmetic to find the place
    if (player == 1)
    {
        *(*board + input - 1) = 'X';
    }
    else
    {
        *(*board + input - 1) = 'O';
    }

    count++;  

    return input;
}

// Method to get a valid space to move to
int getValidSpace(char board[NUMROWS][NUMCOLS])
{
    int input;
    int valid = 0;

    while(!valid)
    {
        scanf("%d", &input);

        char currentVal = *(*board + input - 1);


        if (input > 0 && input <= GRIDSPACES && currentVal == '-')
        {
            valid = 1;
        }
        else 
        {
            printf("Input must be between 1 and %d.\n", GRIDSPACES);
            printf("It must also be unoccupied.\n\n");
        }
    }

    return input;
}


// Returns min
int min (int x, int y)
{
    return (x > y) ? y : x;
}

// Returns max
int max (int x, int y)
{
    return (x > y) ? x: y;
}

