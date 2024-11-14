#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h> //included for the sleep/cls/console screen functions

#define MAXLENGTH 15

void intro();
void resetBoard();
void printSuperBoard();
void printCurrBoard(int, int);
int  playerMove(int*);
int  computerMove(int*);
void checkWinner(char*, char*, int, int);
void printWinner(char);
void playAgain(int*);

char BOARD[9][3][3];

char validMove[10][MAXLENGTH] = {
	"top left", "top middle", "top right",
	"middle left", "middle middle", "middle right",
	"bottom left", "bottom middle", "bottom right", "N/A"
};

int previousBoard;

int currBoard;
int* pCurrBoard = &currBoard;

int Game = 1;
int* pGame = &Game;

/*
TODO:

Implement visual board showing what square has been won by who
Computer difficulty settings
Two player mode
Add game counter if more than 1 game is played
Abstract functions into seperate header files for readability?

*/

int main(void)
{	
	HWND consoleWindow = GetConsoleWindow();
	ShowWindow(consoleWindow, SW_MAXIMIZE);

	do
	{
		char winner = ' ';

		previousBoard = 9;
		int gamesWonPlayer = 0;
		int gamesWonComputer = 0;

		char* Pwinner = &winner;

		//this keep tracks of the state of which boards have been won
		char boardStatus[9] = {
			' ', ' ', ' ',
			' ', ' ', ' ',
			' ', ' ', ' '
		};
		
		resetBoard();
		currBoard = 4;

		intro();
		system("cls");;

		while (1)
		{
			printSuperBoard();
			printCurrBoard(previousBoard, currBoard);
			playerMove(pCurrBoard);
			checkWinner(Pwinner, boardStatus, gamesWonPlayer, gamesWonComputer);
			if (winner != ' ')
			{
				break;
			}
				
			system("cls");
			printSuperBoard();
			printCurrBoard(previousBoard, currBoard);
			computerMove(pCurrBoard);
			checkWinner(Pwinner, boardStatus, gamesWonPlayer, gamesWonComputer);
			if (winner != ' ')
			{
				break;
			}

			system("cls");

		}

		system("cls");
		printSuperBoard();
		printWinner(winner);
		playAgain(pGame);

	} while (Game == 1);
	
	return 0;
}







void intro()
{
	printf("                                            Welcome to SUPER-TIC-TAC-TOE\n\n");
	printf("This game consists of 9 seperate regular tic-tac-toe games being played at the same time on a single board called the SUPER BOARD.\n\n");
	printf("              The player (X), starts play in the centre game of the super board. Valid player inputs are as follow...\n\n");
	printf("-Top Left\n-Middle Middle\n-Bottom Right\n\n                    Case insensitive, as long as it follows [ROW] [COLUMN] the input will be accepted.\n\n");
	printf("      Whatever square the player chooses, will determine where on the superboard the opponent will be forced to play next move.\n\n");
	printf("                  If the player chooses top right, the opponent has to play in the TOP RIGHT tic-tac-toe game.\n\n");
	printf("               If your opponent chooses BOTTOM MIDDLE, you play in the BOTTOM MIDDLE game next and so on so forth.\n\n");
	printf("To win you must win three games in a row ont the super board OR have the most amount of games won if a move is played forcing a draw.\n\n");

	printf("                                           Are you ready to play????? [Yes]\n");

	while (1)
	{
		char response[5];

		fgets(response, (5), stdin);
		response[strcspn(response, "\n")] = 0;
		if (strlen(response) >= (4))
		{
			int x;
			while ((x = getchar()) != '\n' && x != EOF) {}
		}

		for (int i = 0; i < 4; i++)
		{
			response[i] = tolower(response[i]);
		}

		if (strcmp(response, "yes") == 0)
		{
			return;
		}
	}
}

void resetBoard()
{

	int board = 0;

	do
	{
		for (int row = 0; row < 3; row++) //iterates throughout the board to intialize each space to empty
		{
			for (int column = 0; column < 3; column++)
			{
				BOARD[board][row][column] = ' ';

			}
		}

		board++;

	} while (board < 9);
}

void printSuperBoard()
{
	for (int i = 0; i < 3; i++)
	{
		printf(" %c | %c | %c II %c | %c | %c II %c | %c | %c", BOARD[0][i][0], BOARD[0][i][1], BOARD[0][i][2], BOARD[1][i][0], BOARD[1][i][1], BOARD[1][i][2], BOARD[2][i][0], BOARD[2][i][1], BOARD[2][i][2]);
		if (i < 2)
		{
			printf("\n-----------II-----------II------------\n");
		}
		else
		{
			printf("\n=====================================\n");
		}
	}

	for (int i = 0; i < 3; i++)
	{
		printf(" %c | %c | %c II %c | %c | %c II %c | %c | %c", BOARD[3][i][0], BOARD[3][i][1], BOARD[3][i][2], BOARD[4][i][0], BOARD[4][i][1], BOARD[4][i][2], BOARD[5][i][0], BOARD[5][i][1], BOARD[5][i][2]);
		if (i < 2)
		{
			printf("\n-----------II-----------II------------\n");
		}
		else
		{
			printf("\n=====================================\n");
		}
	}

	for (int i = 0; i < 3; i++)
	{
		printf(" %c | %c | %c II %c | %c | %c II %c | %c | %c", BOARD[6][i][0], BOARD[6][i][1], BOARD[6][i][2], BOARD[7][i][0], BOARD[7][i][1], BOARD[7][i][2], BOARD[8][i][0], BOARD[8][i][1], BOARD[8][i][2]);
		if (i < 2)
		{
			printf("\n-----------II-----------II------------\n");
		}
	}
	printf("\n");
}

void printCurrBoard(int previousBoard, int currBoard)
{
	printf("\nThe previous playboard is: %s\n", validMove[previousBoard]);
	printf("The current playboard is: %s\n", validMove[currBoard]);
	printf("\n            %c | %c | %c \n", BOARD[currBoard][0][0], BOARD[currBoard][0][1], BOARD[currBoard][0][2]);
	printf("            ---------\n");
	printf("            %c | %c | %c \n", BOARD[currBoard][1][0], BOARD[currBoard][1][1], BOARD[currBoard][1][2]);
	printf("            ---------\n");
	printf("            %c | %c | %c \n\n", BOARD[currBoard][2][0], BOARD[currBoard][2][1], BOARD[currBoard][2][2]);
}

int playerMove(int* pCurrBoard)
{
	printf("YOUR MOVE!\n\n");

	char move[MAXLENGTH];
	
	while (1)
	{
		fgets(move, MAXLENGTH, stdin);
		move[strcspn(move, "\n")] = 0; //removes \n character from input string

		//flush input buffer if input is greater than max input and lower than min input
		if (strlen(move) >= (MAXLENGTH - 1))
		{
			int x;
			while ((x = getchar()) != '\n' && x != EOF) {}
		}

		//converting all characters to lower case for strcmp
		for (int i = 0; i < MAXLENGTH; i++)
		{
			move[i] = tolower(move[i]);
		}

		for (int i = 0; i < 9; i++)
		{
			//checking to see if the the chosen square is occupied and if the input matches a valid move
			if (BOARD[currBoard][i / 3][i % 3] == ' ' && strcmp(move, validMove[i]) == 0)
			{
				printf("\n");
				BOARD[currBoard][i / 3][i % 3] = 'X';
				previousBoard = currBoard; //saves what the board the current board is for check winner functions
				*pCurrBoard = i; //update the current board
				return previousBoard;
			}
		}
		printf("\nInvalid input!\n");
	}
}

int computerMove(int* PcurrBoard) //void computerMove(int difficulty) (PROTOTYPE FOR DIFFICULTY SELECTION)
{
	printf("OPPONENTS MOVE!\n\n");
	Sleep(3000);
	srand(time(0));

	while (1)
	{
		int computerMoveRow = (rand() % 3);
		int computerMoveColumn = ((rand() + 2) % 3);
		if (BOARD[currBoard][computerMoveRow][computerMoveColumn] == ' ')
		{
			BOARD[currBoard][computerMoveRow][computerMoveColumn] = 'O';
			previousBoard = currBoard;
			*PcurrBoard = ((computerMoveRow * 3) + computerMoveColumn);
			return previousBoard;
		}
	}
}

void checkWinner(char* pWinner, char* boardStatus, int gamesWonPlayer, int gamesWonComputer)
{
	//checking for valid moves
	int board = 0;
	int spaces = 9;
	int totalSpaces = 81;
	do
	{
		for (int row = 0; row < 3; row++)
		{
			for (int column = 0; column < 3; column++)
			{
				if (BOARD[board][row][column] != ' ')
				{
					spaces--;
					totalSpaces--;
				}
			}
		}
		//rare occasions a move will result in playing a board that is already filled out soft-locking the game.
		if (spaces == 0)
		{
			for (int i = 0; i < 9; i++)
			{
				if (boardStatus[i] == 'X')
				{
					gamesWonPlayer += 1;

				}
				if (boardStatus[i] == 'O')
				{
					gamesWonComputer += 1;
				}
			}
			if (gamesWonPlayer > gamesWonComputer)
			{
				*pWinner = 'X';
			}
			else if (gamesWonPlayer < gamesWonComputer)
			{
				*pWinner = 'O';
			}
			else
			{
				*pWinner = 'T';
			}
		}

		spaces = 9;
		board++;

	} while (board < 9);

	//calculating who has most games won once no more valid moves are left on the Super Board
	if (totalSpaces == 0)
	{
		{
			for (int i = 0; i < 9; i++)
			{
				if (boardStatus[i] == 'X')
				{
					gamesWonPlayer += 1;

				}
				if (boardStatus[i] == 'O')
				{
					gamesWonComputer += 1;
				}
			}
			if (gamesWonPlayer > gamesWonComputer)
			{
				*pWinner = 'X';
			}
			else if (gamesWonPlayer < gamesWonComputer)
			{
				*pWinner = 'O';
			}
			else
			{
				*pWinner = 'T';
			}
		}
		return;
	}

	/*
		start checking the LAST board played to see someone has won that board
	*/

	//check horizontal win conditions for last board played 
	for (int i = 0; i < 3; i++)
	{
		if (boardStatus[previousBoard] = ' ' && BOARD[previousBoard][i][0] == 'X' && BOARD[previousBoard][i][1] == 'X' && BOARD[previousBoard][i][2] == 'X')
		{
			boardStatus[previousBoard] = 'X';
			return;
		}
		else if (boardStatus[previousBoard] = ' ' && BOARD[previousBoard][i][0] == 'O' && BOARD[previousBoard][i][1] == 'O' && BOARD[previousBoard][i][2] == 'O')
		{
			boardStatus[previousBoard] = 'O';
			return;
		}
	}
	
	//check vertical win conditions for last board played
	for (int i = 0; i < 3; i++)
	{
		if (boardStatus[previousBoard] = ' ' && BOARD[previousBoard][0][i] == 'X' && BOARD[previousBoard][1][i] == 'X' && BOARD[previousBoard][2][i] == 'X')
		{
			boardStatus[previousBoard] = 'X';
			return;
		}
		else if (boardStatus[previousBoard] = ' ' && BOARD[previousBoard][i][0] == 'O' && BOARD[previousBoard][i][1] == 'O' && BOARD[previousBoard][i][2] == 'O')
		{
			boardStatus[previousBoard] = 'O';
			return;
		}
	}

	//check diagonal win conditions for last board played
	if (boardStatus[previousBoard] = ' ' && BOARD[previousBoard][0][0] == 'X' && BOARD[previousBoard][1][1] == 'X' && BOARD[previousBoard][2][2] == 'X' || BOARD[previousBoard][2][0] == 'X' && BOARD[previousBoard][1][1] == 'X' && BOARD[previousBoard][0][2] == 'X')
	{
		boardStatus[previousBoard] = 'X';
		return;
	}
	else if (boardStatus[previousBoard] = ' ' && BOARD[previousBoard][0][0] == 'O' && BOARD[previousBoard][1][1] == 'O' && BOARD[previousBoard][2][2] == 'O' || BOARD[previousBoard][2][0] == 'O' && BOARD[previousBoard][1][1] == 'O' && BOARD[previousBoard][0][2] == 'O')
	{
		boardStatus[previousBoard] = 'O';
		return;
	}

	/*
		start checking the SUPER Board to see if someone has gotten three in a row
	*/

	//check horizontal win conditions on Super Board 
	for (int i = 0; i < 9; (i += 3))
	{
		if (boardStatus[i] == 'X' && boardStatus[i + 1] == 'X' && boardStatus[i + 2] == 'X')
		{
			*pWinner = 'X';
			return;
		}
		else if (boardStatus[i] == 'O' && boardStatus[i + 1] == 'O' && boardStatus[i + 2] == 'O')
		{
			*pWinner = 'O';
			return;
		}
	}
	
	//check vertical win conditions on Super Board
	for (int i = 0; i < 3; i++)
	{
		if (boardStatus[i] == 'X' && boardStatus[i + 3] == 'X' && boardStatus[i + 6] == 'X')
		{
			*pWinner = 'X';
			return;
		}
		else if (boardStatus[i] == 'O' && boardStatus[i + 3] == 'O' && boardStatus[i + 6] == 'O')
		{
			*pWinner = 'O';
			return;
		}
	}
	
	//check diagonal win conditions on Super Board
	if (boardStatus[0] == 'X' && boardStatus[4] == 'X' && boardStatus[8] == 'X' || boardStatus[2] == 'X' && boardStatus[4] == 'X' && boardStatus[6] == 'X')
	{
		*pWinner = 'X';
		return;
	}
	else if (boardStatus[0] == 'O' && boardStatus[4] == 'O' && boardStatus[8] == 'O' || boardStatus[2] == 'O' && boardStatus[4] == 'O' && boardStatus[6] == 'O')
	{
		*pWinner = 'O';
		return;
	}
}

void printWinner(char winner)
{
	if (winner == 'T')
	{
		printf("\n\n!!! DRAW !!!\n");
	}

	else if (winner == 'X' || winner == 'O')
	{
		char border[34] = "\n             ===================\n";
		for (int i = 0; i < (34); i++)
		{
			Sleep(10);
			printf("%c", border[i]);
		}

		printf("\n!!! %c IS YOUR SUPER - TICTACTOE CHAMPION !!! \n", winner);

		for (int i = 0; i < (34); i++)
		{
			Sleep(10);
			printf("%c", border[i]);
		}
		printf("\n");
	}
}

void playAgain(int* pGame)
{
	printf("Would you like to play again? [Yes]/[No]\n");

	while (1)
	{
		char response[5];

		fgets(response, (5), stdin);
		response[strcspn(response, "\n")] = 0;
		if (strlen(response) >= (4))
		{
			int x;
			while ((x = getchar()) != '\n' && x != EOF) {}
		}

		for (int i = 0; i < 4; i++)
		{
			response[i] = tolower(response[i]);
		}

		if (strcmp(response, "yes") == 0)
		{
			printf("\n");
			return;
		}

		else if (strcmp(response, "no") == 0) //say good bye and close the game
		{
			printf("Thanks for playing! Closing in...\n");
			for (int i = 3; i > 0; i--)
			{
				printf("%i\n", i);
				Sleep(1000);
			}
			*pGame = 0;
			return;
		}

		printf("\nInvalid answer. Type Yes or No.\n");

	}
}
