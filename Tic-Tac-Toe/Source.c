#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>

typedef enum {
	false = 0,
	true = 1,
}bool;

//functions prototype
void displayBoard(char* boardPtr, int* size);
void insert(char* boardPtr, int* size, char* turn);
void switchTurn(char* turn);
void checkWinStatus(char* boardPtr, int* size, int* winStatus, char* turn);
void keyBoardBuffer();
void checkDrawStatus(char* boardPtr, int* size, int* drawStatus);

int main() {

	//An empty board array
	char board[] = { '-','-', '-', '-', '-', '-', '-', '-', '-', };

	//Users turn defaultly set to X, meaning X always starts first
	char turn = 'X';

	//pointer to the board
	char *boardPtr;

	//size of array
	int size;

	//checking the winning status
	int winStatus = 0;

	//checking the draw status
	int drawStatus = 0;

	//checking when the program should end
	int programEnd = false;

	//getting the size of the board array
	size = sizeof(board)/ sizeof(board[0]);

	//using a pointer to point at the board array
	boardPtr = board;

	//funtion call to display the board
	displayBoard(boardPtr, &size);

	do {

		//function call to get players choice
		insert(boardPtr, &size, &turn);

		//function call to check winning status
		checkWinStatus(boardPtr, &size, &winStatus, &turn);

		//function call to check draw status
		checkDrawStatus(boardPtr, &size, &drawStatus);

		//checking win or draw status
		if (winStatus == 1) {
			printf("\nCongratulations '%c'!!!, You just won the game.", turn);
			programEnd = true;	
		}
		else if (drawStatus == 1) {
			printf("\nThis game is a tie. Better luck next time!.");
			programEnd = true;
		}
		else {
			//function call for switching players turn
			switchTurn(&turn);
		}

	} while (programEnd == false);

	getchar();

	return 0;
}

void displayBoard(char *boardPtr, int *size) {
	for (int i = 0; i <= *size - 1; i++) {
		printf("|%c       ", boardPtr[i]);

		//breaks line after 3 characters from the board array is printed out
		if (((i + 1) % 3) == 0) {
			printf("\n");
		}
	}
}

void insert(char* boardPtr, int *size, char* turn) {
	//index on the board
	int index;

	//Getting index from player
	printf("%c turn, Enter your index on the board(1 - 9): ", *turn);

	//verifying players chosen index
	while (scanf("%d", &index) != 1 || index < 1 || index > 9 || boardPtr[index - 1] == 'X' || boardPtr[index - 1] == 'O') {

		printf("Wrong input, try again: ");

		//removing keyBoard Buffer
		keyBoardBuffer();
	}

	keyBoardBuffer();

	//replacing the index on the board given by the user with either X or O
	boardPtr[index - 1] = *turn;

	//Displaying the edited board to the console
	displayBoard(boardPtr, size);
}

void switchTurn(char* turn) {
	//switches the value of turn
	if (*turn == 'X') {
		*turn = 'O';
	}
	else if (*turn == 'O') {
		*turn = 'X';
	}
}

void checkWinStatus(char* boardPtr, int* size, int* winStatus, char* turn) {
	//checking how the player won (not really necessary)
    int horizontalWin = 0;
	int verticalWin = 0;
	int diagonalWin = 0;

	//checking for every possible horizontal win
	if (boardPtr[0] == *turn && boardPtr[1] == *turn && boardPtr[2] == *turn) {
		horizontalWin = 1;
		*winStatus = 1;
	}
	else if(boardPtr[3] == *turn && boardPtr[4] == *turn && boardPtr[5] == *turn) {
		horizontalWin = 1;
		*winStatus = 1;
	}
	else if (boardPtr[6] == *turn && boardPtr[7] == *turn && boardPtr[8] == *turn) {
		horizontalWin = 1;
		*winStatus = 1;
	}

	//checking for every possible vertical win
	if (boardPtr[0] == *turn && boardPtr[3] == *turn && boardPtr[6] == *turn) {
		verticalWin = 1;
		*winStatus = 1;
	}
	else if (boardPtr[1] == *turn && boardPtr[4] == *turn && boardPtr[7] == *turn) {
		verticalWin = 1;
		*winStatus = 1;
	}
	else if (boardPtr[2] == *turn && boardPtr[5] == *turn && boardPtr[8] == *turn) {
		verticalWin = 1;
		*winStatus = 1;
	}

	//checking for every possible diagonal win
	if (boardPtr[0] == *turn && boardPtr[4] == *turn && boardPtr[8] == *turn) {
		verticalWin = 1;
		*winStatus = 1;
	}
	else if (boardPtr[2] == *turn && boardPtr[4] == *turn && boardPtr[6] == *turn) {
		verticalWin = 1;
		*winStatus = 1;
	}
}

void checkDrawStatus(char* boardPtr, int* size, int* drawStatus) {
	//checking if every X or O is found in every position in the array
	for (int i = 0; i <= *size - 1; i++) {
		if (boardPtr[i] == 'X' || boardPtr[i] == 'O') {
			*drawStatus = 1;
		}
		else if (boardPtr[i] == '-') {
			*drawStatus = 0;
		}
	}
}

void keyBoardBuffer() {
	while (getchar() != '\n')
		continue;
}

