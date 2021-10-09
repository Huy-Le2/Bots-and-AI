
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//The program will be split into multiple functions which all help create or maximize the game

#define Computer 1 
#define Player 2 

#define SIDE 3 //board's sides. Defining it like this means that I don't have to constantly type in 3 3 for the matrix. Which saves time.

// Computer will move with 'O' and the player moves with 'X' 
#define ComputerMOVE 'O' 
#define PlayerMOVE 'X' 

//A funciton used to update the board everytime a move is made
void displayBoard(char board[][SIDE]) 
{ 
	
	printf("\t\t\t %c | %c | %c \n", board[0][0], board[0][1], board[0][2]); 
	printf("\t\t\t-----------\n"); 
	printf("\t\t\t %c | %c | %c \n", board[1][0], board[1][1], board[1][2]); 
	printf("\t\t\t-----------\n"); 
	printf("\t\t\t %c | %c | %c \n\n", board[2][0], board[2][1], board[2][2]);  
} 

// A function to show the instructions 
void manual() 
{ 
	printf("\nChoose a cell numbered from 1 to 9 as below and play\n\n"); 
	
	printf("\t\t\t 1 | 2 | 3 \n"); 
	printf("\t\t\t-----------\n"); 
	printf("\t\t\t 4 | 5 | 6 \n"); 
	printf("\t\t\t-----------\n"); 
	printf("\t\t\t 7 | 8 | 9 \n\n"); 
} 


// A function to start the game 
void makeGame(char board[][SIDE]) 
{	
	//Empty board
	for (int i=0; i<SIDE; i++) 
	{ 
		for (int j=0; j<SIDE; j++) 
			board[i][j] = ' '; 
	} 
} 

// A function to declare the winner of the game 
void declareWinner(int currTurn) 
{ 
	if (currTurn == Computer) 
		printf("Computer has won\n"); 
	else
		printf("Player has won\n"); 
} 

// A function that returns true if any of the row is crossed with the same player's puck 
bool rowchecker(char board[][SIDE]) 
{ 
	for (int i=0; i<SIDE; i++) 
	{ 
		if (board[i][0] == board[i][1] && 
			board[i][1] == board[i][2] && 
			board[i][0] != ' ') 
			return (true); 
	} 
	return(false); 
} 

// A function that returns true if any of the column is crossed with the same player's puck 
bool columnchecker(char board[][SIDE]) 
{ 
	for (int i=0; i<SIDE; i++) 
	{ 
		if (board[0][i] == board[1][i] && 
			board[1][i] == board[2][i] && 
			board[0][i] != ' ') 
			return (true); 
	} 
	return(false); 
} 

// A function that returns true if any of the diagonal is crossed with the same player's puck 
bool crosschecker(char board[][SIDE]) 
{ 
	if (board[0][0] == board[1][1] && 
		board[1][1] == board[2][2] && 
		board[0][0] != ' ') 
		return(true); 
		
	if (board[0][2] == board[1][1] && 
		board[1][1] == board[2][0] && 
		board[0][2] != ' ') 
		return(true); 

	return(false); 
} 

// A function that returns true if the game is over else it returns a false 
bool stopGame(char board[][SIDE]) 
{ 
	return(rowchecker(board) || columnchecker(board) || crosschecker(board) ); 
}

//We will split the board into numbers so that the AI can pick which move can have the highest number
//With this in mind we can give each move a value of either 1 or -1 indicating that the bot should move in there or not. Min maxing the chances of winning for the Bot
// Minimax will simply look at the board and calculate the specific score for the entire board at the moment. Asigning a score to potential moves
int minimax(char board[][SIDE], int bestmove, bool AIgo)
{
	int score = 0;
	int bestScore = 0;
	if (stopGame(board) == true)
	{
		if (AIgo == true)
			return -1;
		if (AIgo == false)
			return +1;
	}
	else
	{
		if(bestmove < 9)
		{
			if(AIgo == true)
			{
				bestScore = -999;
				for(int i=0; i<SIDE; i++)
				{
					for(int j=0; j<SIDE; j++)
					{
						if (board[i][j] == ' ')
						{
							board[i][j] = ComputerMOVE;
							score = minimax(board, bestmove + 1, false);
							board[i][j] = ' ';
							if(score > bestScore)
							{
								bestScore = score;
							}
						}
					}
				}
				return bestScore;
			}
			else
			{
				bestScore = 999;
				for (int i = 0; i < SIDE; i++)
				{
					for (int j = 0; j < SIDE; j++)
					{
						if (board[i][j] == ' ')
						{
							board[i][j] = PlayerMOVE;
							score = minimax(board, bestmove + 1, true);
							board[i][j] = ' ';
							if (score < bestScore)
							{
								bestScore = score;
							}
						}
					}
				}
				return bestScore;
			}
		}
		else
		{
			return 0;
		}
	}
}

//BestnextMove will determine the highest posssible score on the board and maximize making that move
int bestnextMove(char board[][SIDE], int moveNum)
{
	int x = -1, y = -1;
	int score = 0, bestScore = -999;
	for (int i = 0; i < SIDE; i++)
	{
		for (int j = 0; j < SIDE; j++)
		{
			if (board[i][j] == ' ')
			{
				board[i][j] = ComputerMOVE;
				score = minimax(board, moveNum+1, false);
				board[i][j] = ' ';
				if(score > bestScore)
				{
					bestScore = score;
					x = i;
					y = j;
				}
			}
		}
	}
	return x*3+y;
}

// A function to play Tic-Tac-Toe 
void Tictactoegaming(int currTurn) 
{ 
	char board[SIDE][SIDE]; 
	int moveNum = 0, x = 0, y = 0;

	makeGame(board);
	manual(); 
	
	// The game won't stop until a draw is reached or either side wins
	while (stopGame(board) == false && moveNum != SIDE*SIDE) 
	{ 
		int n;
		if (currTurn == Computer) 
		{
			n = bestnextMove(board, moveNum);
			x = n / SIDE;
			y = n % SIDE;
			board[x][y] = ComputerMOVE; 
			printf("Computer has put a %c in cell %d\n\n", ComputerMOVE, n+1);
			displayBoard(board);
			moveNum ++; 
			currTurn = Player;
		} 
		
		else if (currTurn == Player) 
		{
			printf("You can insert in the following positions: ");
			for(int i=0; i<SIDE; i++)
				for (int j = 0; j < SIDE; j++)
					if (board[i][j] == ' ')
						printf("%d ", (i * 3 + j) + 1);
			printf("\n\nEnter the position: ");
			scanf("%d",&n);
			n--;
			x = n / SIDE;
			y = n % SIDE; 
			if(board[x][y] == ' ' && n<9 && n>=0)
			{
				board[x][y] = PlayerMOVE; 
				printf ("\nPlayer has put a %c in cell %d\n\n", PlayerMOVE, n+1); 
				displayBoard(board); 
				moveNum++; 
				currTurn = Computer;
			}
			else if(board[x][y] != ' ' && n<9 && n>=0)
			{
				printf("\nPosition's not valid, select any one place from the available spaces\n\n");
			}
			else if(n<0 || n>8)
			{
				printf("Invalid placement\n");
			}
		} 
	} 

	// If the game has drawn 
	if (stopGame(board) == false && moveNum == SIDE * SIDE) 
		printf("It's a draw\n"); 
	else
	{ 
		// Toggling the user to declare the actual winner 
		if (currTurn == Computer) 
			currTurn = Player; 
		else if (currTurn == Player) 
			currTurn = Computer; 
		
		declareWinner(currTurn); 
	} 
} 
//Int main will handle the displaying and inputs
int main() 
{ 
	printf("\n-------------------------------------------------------------------\n\n");
	printf("\t\t\t A game of tic-Tac-Toe\n"); 
	printf("\n-------------------------------------------------------------------\n\n");
	char cont='y';
	do {
		char choice;
	 	printf("Do you want to start first?(y/n): ");
	 	scanf(" %c", &choice);

		if(choice=='n')
			Tictactoegaming(Computer);
		else if(choice=='y')
			Tictactoegaming(Player);
		else
			printf("Invalid choice\n"); 
        
		printf("\nDo you want to quit(y/n): ");
       		scanf(" %c", &cont);
	} while(cont=='n');
	return (0); 
} 