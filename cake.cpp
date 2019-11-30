//September 25, 2018
//CompSci 40S - Huacheng Qin
/*cake - This program is based on hangman, except without the hanging... or the man.
		 In this program, the user will be asked to enter a word, then the user will 
		 be asked to guess the word that they just entered. If the user guessed wrong
		 'MAXg' amount of times, they lose (and they won't get cake!). If they guessed
		 every letter in the word before then, they get to keep what ever is left of
		 the cake (who doesn't want cake?).*/

//Developer Notes: It is suggested to play this game with at least 2 players. With 1 
//				   player writing the initial word, and the rest guessing.
		 
//"No man shall be hanged tonight, nor woman, not on my watch!" - Cakeperson, 2018

//*DISCLAIMER* - NO CAKES WERE WASTED DURING THE MAKING OF THIS PROGRAM.
//===============================================================================================

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "colours.h"
using namespace std;

//===============================================================================================

//Declare constants
const int MAXl = 10;			//Maximum number of letters in each word
const int MAXg = 10;			//Number of wrong guesses that are allowed before game over

//===============================================================================================

//Function Prototypes
int input(char word[MAXl]);		//Allows user to input the word
void clear();					//Clears the screen
void print(int, int, char[MAXg], char[MAXl], bool[MAXl]);	//Prints the cake

//===============================================================================================

//Main program
int main(void)
{
	bool ascii[95];			//What letters the user have guessed
	int win;				//Whether or not the user have won
	char word[MAXl];			//The word that the user guesses
	bool right[MAXl];			//Correct letters the user guessed
	char guess[MAXg];			//What the user guesses
	int numguess;				//How many times the user guessed
	int numlet;					//Number of letters in the word
	int count;					//Loop counter
	char choice;				//User choice
	bool found;					//Whether or not a match is found with the guess
	
	//Loop until user quits
	do
	{	//Initialize
		for (int x = 0; x < MAXl; x++)
			right[x] = false;
		for (int x = 0; x < 95; x++)
			ascii[x] = false;
		count = 0;
		numguess = 0;
		clear();
		win = 0;
		
		//Allow user to enter the word
		text_colour(f_cyan, b_black);
		cout << "Enter the word: ";
		numlet = input(word);

		//Loop until win or lose
		while (numguess < MAXg && win < numlet)
		{
			//Initialize
			found = false;
			win = 0;

			//Print cake
			clear();
			print(numlet, numguess, guess, word, right);

			//Ask user for their guess
			text_colour(f_cyan, b_black);
			cout << "Guess? ";
			text_colour(f_yellow, b_black);
			guess[count] = toupper(_getch());
			if ((int)guess[count] < 32)
				guess[count] = toupper(_getch());
			cout << guess[count] << endl;
			//Validate
			while (ascii[(int)guess[count] - 32])
			{
				text_colour(f_red, b_black);
				cout << "Already guessed! Guess? ";
				text_colour(f_yellow, b_black);
				guess[count] = toupper(_getch());
				cout << guess[count] << endl;
			}//Validate

			//Check if user guess is correct
			for (int x = 0; x < numlet; x++)
				if (word[x] == guess[count])
				{
					right[x] = true;
					found = true;
				}//if

			//Set letter to already guessed and increase counters
			ascii[(int)guess[count] - 32] = true;
			numguess++;
			count++;

			//Reduce guess number if the user guessed right
			if (found)
			{
				numguess--;
				count--;
			}//if

			//Check if user has won
			for (int x = 0; x < MAXl; x++)
				if (right[x])
					win++;
		}//while
		
		//Print text for win/loss
		if (win == numlet)
		{
			clear();
			print(numlet, numguess, guess, word, right);
			text_colour(f_green, b_black);
			cout << "Congratulations! You get a piece of cake!" << endl;
		}//win
		else
		{
			clear();
			//Set all to visible
			for (int x = 0; x < MAXl; x++)
			{
				right[x] = true;
			}//for
			print(numlet, numguess, guess, word, right);
			text_colour(f_red, b_black);
			cout << "You lost! No cake for you!" << endl;
		}//loss
		
		//Ask user if they want to play again
		text_colour(f_cyan, b_black);
		cout << "Do you want to play again? [Y/N] ";
		text_colour(f_yellow, b_black);
		choice = toupper(_getch());
		cout << choice << endl;
		//Validate
		while (choice != 'Y' && choice != 'N')
		{
			text_colour(f_cyan, b_black);
			cout << "Invalid choice! Do you want to play again? [Y/N] ";
			text_colour(f_yellow, b_black);
			choice = toupper(_getch());
			cout << choice << endl;
		}//Validate
	} while (choice == 'Y');

	//reset text colour
	text_colour(f_gray, b_black);
	return 0;
}//main

//===============================================================================================

//input - This function allows the user to enter the word
//word - The word that the user enters
int input(char word[MAXl])
{
	bool loop;						//Switch used for loops
	char temp;						//Temporary placeholder
	int numlet = -1;				//Number of letters in the word

	//initialize
	loop = false;
	temp = '\0';
	//Loop for input
	for (int x = 0; x <= MAXl; x++)
	{
		//User input
		if (!loop) //if the user has not pressed enter
		{
			text_colour(f_yellow, b_black);
			if (x < MAXl)
				word[x] = toupper(_getch());
			else //allow the user to backspace on the 11th character
				temp = _getch();
		}//if (before enter)
		//Print results based on input
		if (loop && x < MAXl) //if the user already pressed enter, assign null to the rest of the characters
			word[x] = '\0';
		else
			if (x < MAXl)
			{
				if (word[x] == '\b') //if the user pressed backspace
				{
					if (x != 0)
					{
						cout << "\b \b";
						x--;
					}//if backspace and not at 0 characters
					x--;
				}//if backspace
				else
					if (word[x] == '\r') //if the user pressed enter
					{
						if (x != 0)
							loop = true;
						else
							x--;
					}//if
					else
						cout << "*";
			}//if x < NUMp
			else
				if (temp == '\b') //this allows the user to press backspace on the 11th character
				{
					cout << "\b \b";
					x -= 2;
					temp = '\0';
				}//if backspace
				else
					if (temp != '\r' && temp != '\0') //this prevents the user from entering characters beyond the 10th
						x--;
	}//for (input)
	cout << endl;

	//Check how many letters there are
	for (int x = MAXl; x > 0; x--)
		if (word[x] == '\r')
			numlet = x;
	if (numlet == -1)
		numlet = 10;

	return numlet;
}//input

//===============================================================================================

//clear - This function prints a bunch of new lines to clear the screen
void clear()
{
	//Loops 60 times to fill the screen
	for (int x = 1; x < 60; x++)
		cout << endl;

	return;
}//clear

//===============================================================================================

//Print - This function prints the cake as well as previous guesses
//numlet - Number of letters in the word
//numguess - Number of times the user guessed wrong
//guess - The user's previous guesses
//word - The word that needs to be guessed
//right - The letters that were correctly guessed
void print(int numlet, int numguess, char guess[MAXg], char word[MAXl], bool right[MAXl])
{
	//Print the cake
	text_colour(f_white, b_black);
	if ((float)numguess / ((float)MAXg / 5) == 0)
	{
		cout << "                         ,@@@@@@@@@@@@@@@@," << endl;
		cout << "                 ,@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@," << endl;
		cout << "             ,@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@," << endl;
		cout << "          ,@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@," << endl;
		cout << "         ;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@;" << endl;
		cout << "         ;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@;" << endl;
		cout << "         ;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@;" << endl;
		cout << "         ;@@@::@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:@@@;" << endl;
		cout << "         ;:@::::@@@@@@@@:@@@@@@@@@@@@@@@@@@@@@::@@@@@@::::@@;" << endl;
		cout << "         ;::::::@@@@:@@::@:@@@@@@@@@@@@@:::@::::@@:@@@::::::;" << endl;
		cout << "         @@::::::@@::::::::::::@@@@@@@@:::::::::::::@@:::::@@" << endl;
		cout << "         ;@@@::::::::::::::::::::@@@:::::::::::::::::::::@@@;" << endl;
		cout << "     ,%%%;::@@@::@@@@@:@@@::::::::@::::::@@@@@:::@@@@:@@@@@:;%%%," << endl;
		cout << "  .%%%% @;::::@@@@:::@@::@@@@@::::::::@@@@@:@@@@@@@;@@@:::::;@ %%%%," << endl;
		cout << " .%%    @;;:::::@@::::::::::@@@@@@:@@@@@::::::::::::@::::::;;@    %%," << endl;
		cout << " %%      @;;;;;::::::::::::::::::@@@:::::::::::::::::::;;;;;@      %%" << endl;
		cout << " %%       @@@@;;;;;;:::::::::::::::::::::::::::;;;;;;;;;@@@@       %%" << endl;
		cout << " `%%%        @@@@@@;;;;;;;;;;:::::::::;;;;;;;;;;@@@@@@@@         %%%'" << endl;
		cout << "   `%%%%%          @@@@@@@@@@@;;;;;;;;;@@@@@@@@@             %%%%%'" << endl;
		cout << "       `%%%%%%%%              @@@@@@@@@              %%%%%%%%%'" << endl;
		cout << "              `%%%%%%%%%%%%               %%%%%%%%%%%%'" << endl;
		cout << "                         `%%%%%%%%%%%%%%%%%'           " << endl;
	}
	else
		if ((float)numguess / ((float)MAXg / 5) < 1)
		{
			cout << "                         ,@@@@@@@@@@@@@@@@," << endl;
			cout << "                 ,@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@," << endl;
			cout << "             ,@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@," << endl;
			cout << "          ,@@@@@@@@@@@@@@@@@@@@@@.@@@@@@@@@@@@@@@@@@@@@@@@@," << endl;
			cout << "         ;@@@@@@@@@@@@@@@@@@@@@' | `@@@@@@@@@@@@@@@@@@@@@@@@;" << endl;
			cout << "         ;@@@@@@@@@@@@@@@@@@@'   |   `@@@@@@@@@@@@@@@@@@@@@@;" << endl;
			cout << "         ;@@@@@@@@@@@@@@@@@'     |     `@@@@@@@@@@@@@@@@@@@@;" << endl;
			cout << "         ;@@@::@@@@@@@@@@@  .    |       @@@@@@@@@@@@@@@:@@@;" << endl;
			cout << "         ;:@::::@@@@@@@@:@      #|# .    :@@@:::@@@@@@::::@@;" << endl;
			cout << "         ;::::::@@@@:@@::@    ## | ##    ::@::::@@:@@@::::::;" << endl;
			cout << "         @@::::::@@:::::::  ##   |   ##  :::::::::::@@:::::@@" << endl;
			cout << "         ;@@@:::::::::::::##     |     ##::::::::::::::::@@@;" << endl;
			cout << "     ,%%%;::@@@::@@@@@:@@@   .   |    .  @@@@@:::@@@@:@@@@@:;%%%," << endl;
			cout << "  .%%%% @;::::@@@@:::@@:::     ,;';,     :::@@@@@@@;@@@:::::;@ %%%%," << endl;
			cout << " .%%    @;;:::::@@:::::::: . ,;'   ';,   :::::::::::@::::::;;@    %%," << endl;
			cout << " %%      @;;;;;::::::::::: ,;'        ;, ::::::::::::::;;;;;@      %%" << endl;
			cout << " %%       @@@@;;;;;;::::::;'           ';::::::;;;;;;;;;@@@@       %%" << endl;
			cout << " `%%%        @@@@@@;;;;;;;               ;;;;;;;@@@@@@@@         %%%'" << endl;
			cout << "   `%%%%%          @@@@@@@               @@@@@@@             %%%%%'" << endl;
			cout << "       `%%%%%%%%                                     %%%%%%%%%'" << endl;
			cout << "              `%%%%%%%%%%%%               %%%%%%%%%%%%'" << endl;
			cout << "                         `%%%%%%%%%%%%%%%%%'           " << endl;
		}
		else
			if ((float)numguess / ((float)MAXg / 5) < 2)
			{
				cout << "                         ,@@@@@@@@@@@@@@@@," << endl;
				cout << "                 ,@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@," << endl;
				cout << "             ,@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@," << endl;
				cout << "          ,@@@@@@@@@@@@@@@@@@@@@@.@@@@@@@@@@@@@@@@@@@@@@@@@," << endl;
				cout << "         ;@@@@@@@@@@@@@@@@@@@@@' |      `@@@@@@@@@@@@@@@@@@@;" << endl;
				cout << "         ;@@@@@@@@@@@@@@@@@@@'   |  .         `@@@@@@@@@@@@@;" << endl;
				cout << "         ;@@@@@@@@@@@@@@@@@'     |          .       `@@@@@@@;" << endl;
				cout << "         ;@@@::@@@@@@@@@@@  .    |     .               @:@@@;" << endl;
				cout << "         ;:@::::@@@@@@@@:@      #|###      .    .      :::@@;" << endl;
				cout << "         ;::::::@@@@:@@::@    ## |   #####             :::::;" << endl;
				cout << "         @@::::::@@:::::::  ##   |        #######   .  ::::@@" << endl;
				cout << "         ;@@@:::::::::::::##     |               ##### ::@@@;" << endl;
				cout << "     ,%%%;::@@@::@@@@@:@@@   .   |    .     .         #@@@@:;%%%," << endl;
				cout << "  .%%%% @;::::@@@@:::@@:::     ,;';;;,                 :::::;@ %%%%," << endl;
				cout << " .%%    @;;:::::@@:::::::: . ,;'     ';;;;;;;,    .    ::::;;@    %%," << endl;
				cout << " %%      @;;;;;::::::::::: ,;'               ';;;;;,   ::;;;@      %%" << endl;
				cout << " %%       @@@@;;;;;;::::::;'                       ';;;:@@@@       %%" << endl;
				cout << " `%%%        @@@@@@;;;;;;;                            @@         %%%'" << endl;
				cout << "   `%%%%%          @@@@@@@                                   %%%%%'" << endl;
				cout << "       `%%%%%%%%                                     %%%%%%%%%'" << endl;
				cout << "              `%%%%%%%%%%%%               %%%%%%%%%%%%'" << endl;
				cout << "                         `%%%%%%%%%%%%%%%%%'           " << endl;
			}
			else
				if ((float)numguess / ((float)MAXg / 5) < 3)
				{
					cout << "                         ,@@@@@@@@@@@@@@@@," << endl;
					cout << "                 ,@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@," << endl;
					cout << "             ,@@@@@@@@@@@@@@@@@@@@@@@@@@@@         ;" << endl;
					cout << "          ,@@@@@@@@@@@@@@@@@@@@@@.                 ;" << endl;
					cout << "         ;@@@@@@@@@@@@@@@@@@@@@' |                 ;" << endl;
					cout << "         ;@@@@@@@@@@@@@@@@@@@'   |                 ;" << endl;
					cout << "         ;@@@@@@@@@@@@@@@@@'     |      ###########;" << endl;
					cout << "         ;@@@::@@@@@@@@@@@  .    |######           ;" << endl;
					cout << "         ;:@::::@@@@@@@@:@      #|                 ;" << endl;
					cout << "         ;::::::@@@@:@@::@    ## |                 ;" << endl;
					cout << "         @@::::::@@:::::::  ##   |                 ;%%," << endl;
					cout << "         ;@@@:::::::::::::##     |       ,;;;;;;;;;; %%%%%%," << endl;
					cout << "     ,%%%;::@@@::@@@@@:@@@   .   |,;;;;;;'                 %%%%%," << endl;
					cout << "  .%%%% @;::::@@@@:::@@:::     ,;''                            %%%%," << endl;
					cout << " .%%    @;;:::::@@:::::::: . ,;'                                  %%," << endl;
					cout << " %%      @;;;;;::::::::::: ,;'                                     %%" << endl;
					cout << " %%       @@@@;;;;;;::::::;'                                       %%" << endl;
					cout << " `%%%        @@@@@@;;;;;;;                                       %%%'" << endl;
					cout << "   `%%%%%          @@@@@@@                                   %%%%%'" << endl;
					cout << "       `%%%%%%%%                                     %%%%%%%%%'" << endl;
					cout << "              `%%%%%%%%%%%%               %%%%%%%%%%%%'" << endl;
					cout << "                         `%%%%%%%%%%%%%%%%%'           " << endl;
				}
				else
					if ((float)numguess / ((float)MAXg / 5) < 4)
					{
						cout << "                         ,@" << endl;
						cout << "                 ,@@@@@@@@@@@" << endl;
						cout << "             ,@@@@@@@@@@@@@@@@@@" << endl;
						cout << "          ,@@@@@@@@@@@@@@@@@@@@@@." << endl;
						cout << "         ;@@@@@@@@@@@@@@@@@@@@@' |" << endl;
						cout << "         ;@@@@@@@@@@@@@@@@@@@'   |" << endl;
						cout << "         ;@@@@@@@@@@@@@@@@@'     |" << endl;
						cout << "         ;@@@::@@@@@@@@@@@  .    |" << endl;
						cout << "         ;:@::::@@@@@@@@:@      #|" << endl;
						cout << "         ;::::::@@@@:@@::@    ## |%%%%%%%," << endl;
						cout << "         @@::::::@@:::::::  ##   |      %%%%%%%%%%%%," << endl;
						cout << "         ;@@@:::::::::::::##     |                 %%%%%%%%%," << endl;
						cout << "     ,%%%;::@@@::@@@@@:@@@   .   |                         %%%%%," << endl;
						cout << "  ,%%%% @;::::@@@@:::@@:::     ,;'                             %%%%," << endl;
						cout << " ,%%    @;;:::::@@:::::::: . ,;'                                  %%," << endl;
						cout << " %%      @;;;;;::::::::::: ,;'                                     %%" << endl;
						cout << " %%       @@@@;;;;;;::::::;'                                       %%" << endl;
						cout << " `%%%        @@@@@@;;;;;;;                                       %%%'" << endl;
						cout << "   `%%%%%          @@@@@@@                                   %%%%%'" << endl;
						cout << "       `%%%%%%%%                                     %%%%%%%%%'" << endl;
						cout << "              `%%%%%%%%%%%%               %%%%%%%%%%%%'" << endl;
						cout << "                         `%%%%%%%%%%%%%%%%%'           " << endl;
					}
					else
						if ((float)numguess / ((float)MAXg / 5) < 5)
						{
							cout << "                           @@@@@@." << endl;
							cout << "                 @@@@@@@@@@@@@@' |" << endl;
							cout << "         ;@@@@@@@@@@@@@@@@@@@'   |" << endl;
							cout << "         ;@@@@@@@@@@@@@@@@@'     |" << endl;
							cout << "         ;@@@::@@@@@@@@@@@  .    |" << endl;
							cout << "         ;:@::::@@@@@@@@:@      #|" << endl;
							cout << "         ;::::::@@@@:@@::@    ## |%%%%%%%," << endl;
							cout << "         @@::::::@@:::::::  ##   |      %%%%%%%%%%%%," << endl;
							cout << "         ;@@@:::::::::::::##     |                 %%%%%%%%%," << endl;
							cout << "     ,%%%;::@@@::@@@@@:@@@   .   |                         %%%%%," << endl;
							cout << "  ,%%%% @;::::@@@@:::@@:::     ,;'                             %%%%," << endl;
							cout << " ,%%    @;;:::::@@:::::::: . ,;'                                  %%," << endl;
							cout << " %%      @;;;;;::::::::::: ,;'                                     %%" << endl;
							cout << " %%       @@@@;;;;;;::::::;'                                       %%" << endl;
							cout << " `%%%        @@@@@@;;;;;;;                                       %%%'" << endl;
							cout << "   `%%%%%          @@@@@@@                                   %%%%%'" << endl;
							cout << "       `%%%%%%%%                                     %%%%%%%%%'" << endl;
							cout << "              `%%%%%%%%%%%%               %%%%%%%%%%%%'" << endl;
							cout << "                         `%%%%%%%%%%%%%%%%%'           " << endl;
						}
						else
						{
							cout << "                           ,%%%%%%%%%%%%%," << endl;
							cout << "                ,%%%%%%%%%%%%           %%%%%%%%%%%%," << endl;
							cout << "         ,%%%%%%%%                                 %%%%%%%%%," << endl;
							cout << "     ,%%%%%                                                %%%%%," << endl;
							cout << "  ,%%%%                                                        %%%%," << endl;
							cout << " ,%%                                                              %%," << endl;
							cout << " %%                                                                %%" << endl;
							cout << " %%                                                                %%" << endl;
							cout << " `%%%                                                            %%%'" << endl;
							cout << "   `%%%%%                                                    %%%%%'" << endl;
							cout << "       `%%%%%%%%                                     %%%%%%%%%'" << endl;
							cout << "              `%%%%%%%%%%%%               %%%%%%%%%%%%'" << endl;
							cout << "                         `%%%%%%%%%%%%%%%%%'           " << endl;
						}//if

	//Print the word
	for (int x = 0; x < numlet; x++)
	{
		if (right[x])
			cout << word[x];
		else
			cout << "_";
		cout << " ";
	}//for
	cout << endl;

	//Print wrong guesses
	cout << "Wrong guesses: ";
	for (int x = 0; x < numguess; x++)
		cout << guess[x] << " ";
	cout << endl;

	return;
}//print

//End of file