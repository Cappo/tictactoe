//-----------------------------------
// Ryan Endacott
// Test tic tac toe program
//-----------------------------------

#include <stdio.h>

#define NUMROWS 3
#define NUMCOLS 3
#define WINCOND 3

// The preprocessor will not multiply these two, HOWEVER, 
// The compiler will optimise so that the calculation should only occur once
// (probably/hopefully)
#define GRIDSPACES (NUMROWS * NUMCOLS)

#define TRUE 1
#define FALSE 0


// Function to see if someone has won
int win(char board[NUMROWS][NUMCOLS]);

// Function to see if someone won horizontally
// same return conditions as win
int horiz(char board[NUMROWS][NUMCOLS]);


// Function to see if someone won vertically
// same return conditions as win
int vert(char board[NUMROWS][NUMCOLS]);


// Function to see if someone won diagonally
// same return conditions as win
int diag(char board[NUMROWS][NUMCOLS]);


// Prints the board
void printBoard(char board[NUMROWS][NUMCOLS]);


// Resets the tic tac toe array to be all
// '-' characters
void reset(char board[NUMROWS][NUMCOLS]);


// Lets the current player have a turn
void playerTurn(char board[NUMROWS][NUMCOLS], int player);


// Method to get a valid space to move to
int getValidSpace();


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
        playerTurn(board, player);


        if (win(board)) 
        {
            winner = player;
        }
        printf("player: %d\n", player);

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

int win(char board[NUMROWS][NUMCOLS])
{
    return 0;    
}

int horiz(char board[NUMROWS][NUMCOLS])
{
    return 0;
}



// Lets the current player have a turn
void playerTurn(char board[NUMROWS][NUMCOLS], int player)
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

    input = getValidSpace();


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
}

// Method to get a valid space to move to
int getValidSpace()
{
    int input;
    int valid = 0;

    while(!valid)
    {
        scanf("%d", &input);

        if (input > 0 && input <= GRIDSPACES)
        {
            valid = 1;
        }
        else 
        {
            printf("Input must be between 1 and %d.\n\n", GRIDSPACES);
        }
    }

    return input;
}



