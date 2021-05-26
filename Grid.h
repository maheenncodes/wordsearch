#include <iostream>
#include <ctime>
#include<cstdlib>
#include<fstream>
#include<string>
using  namespace std;

//----------------------------------------------Grid Generator------------------------------------------------------


//this function deallocates array and saves memory space
void Deallocation(char** array, int rows)     
{
	if (array != 0)
	{
		for (int i = 0; i < rows; i++)
		{
			delete[]array[i];

		}
		delete[] array;
	}
}

//this function counts the number of words in input.txt file
int RowCounter(string filename)   
{
	ifstream file(filename);
	int lineNumber = 1; //As it will not count last line so initial value is 1
	char ch;
	while (file)
	{
		file.get(ch);

		if (ch == '\n')
		{
			lineNumber++;
		}

	}
	file.close();
	return lineNumber;
}

//function to calculate stringlenght of a word without
//counting spaces in between it like WORD SEARCH has one space in between
int StringLenght(char* str)   
{
	int stringLen = 0;
	int i = 0;

	while (str[i] != '\0')
	{
		if (str[i] != ' ')
		{
			stringLen++;
		}

		i++;
	}

	return stringLen;
}

//function to calculate stringlenght of a word with spaces
int StringLenghtWithoutSpaces(char* str)   //function to calculate stringlenght of a word without counting spaces in between it like WORD SEARCH has one space in between
{
	int stringLen = 0;
	int i = 0;

	while (str[i] != '\0')
	{
		stringLen++;
		i++;
	}

	return stringLen;
}

//This function checks if the user entered dimensions is greater than or equal to the longestword length and returns true
bool CheckGrid(char** list, int TR, int TC, int numberOfWords)     //this function finds the dimension of the wordSearch Grid
{
	int max = 0;

	int cols;
	for (int i = 0; i < numberOfWords; i++)    //maxlength word find
	{
		cols = StringLenght(list[i]);
		if (cols > max)
		{
			max = cols;
		}
	}

	int longWords = 0;

	for (int i = 0; i < numberOfWords; i++)   //number of words that have maxklength
	{
		cols = StringLenght(list[i]);
		if (cols == max)
		{
			longWords++;
		}
	}

	if (max > TR || max > TC || numberOfWords > TR + 1 || numberOfWords > TC + 1 || (longWords==3 && (max==TR || max == TC)))    //if the number of words in the grid are more than the length of the largest word in the list then it takes the number of words as dimmensions
	{
		return false;
	}
	return true;
}

//reads the file containg words in a 2d array
char** ReadListFromFile(string filename)     
{

	ifstream file(filename);
	const int rows = RowCounter(filename);

	char** List = new char* [rows];

	if (file)
	{

		char abc[80];

		int i = 0;

		while (i < rows)
		{

			file.getline(abc, 80);
			int cols = 0;
			cols = StringLenght(abc);

			List[i] = new char[cols + 1];

			int length = StringLenghtWithoutSpaces(abc);
			int j = 0;
			int k = 0;
			for (j = 0; j < length && k < cols; j++)     //deep copying
			{
				if (abc[j] != ' ')
				{
					List[i][k] = abc[j];
					k++;
				}
				else
				{
					j++;
					List[i][k] = abc[j];
					k++;
				}
			}
			List[i][k] = '\0';
			i++;
			k++;
		}
	}
	file.close();


	return List;

}

//to intialize word Search grid with special character
char** GridIntialization(int TR, int TC)          
{
	char** grid = new char* [TR];

	for (int i = 0; i < TR; i++)
	{
		grid[i] = new char[TC + 1];

	}

	for (int i = 0; i < TR; i++)
	{
		int j = 0;
		for (j = 0; j < TC; j++)
		{

			grid[i][j] = '*';

		}
		grid[i][j] = '\0';
	}

	return grid;

}

//after placing words fills the reamaining spaces with  random alphabets
void FinalFill(char**& grid, int TR, int TC)     
{
	for (int i = 0; i < TR; i++)
	{

		for (int j = 0; j < TC; j++)
		{


			if (grid[i][j] == '*')
			{

				int r = rand() % 26;
				grid[i][j] = 'A' + r;   //random alphabets

			}


		}

	}
}

//this function sorts the list of words in an acending order
char** sortArray(char** list, int rows)
{

	string s[100];
	for (int i = 0; i < rows; i++)
		s[i] = list[i];
	
	for (int i = 1; i < rows; i++)
	{
		string temp = s[i];

		
		int j = i - 1;                                       //sorting
		while (j >= 0 && temp.length() < s[j].length())
		{
			s[j + 1] = s[j];
			j--;
		}
		s[j + 1] = temp;
	}

	char** sortedArray = new char* [rows];
	for (int i = 0; i < rows; i++)
	{
		
		int length = s[i].length();
		
		sortedArray[i] = new char[length + 1];
		int k = 0;
		int j = 0;

		for (j = 0; j < length && k < length + 1; j++)
		{
			if (s[i][k] != ' ')
			{
				*(*(sortedArray + i) + j) = s[i][k];   //final sorted array without spaces
				k++;
			}
			else
			{
				k++;
				*(*(sortedArray + i) + j) = s[i][k];
				k++;

			}
		}
		sortedArray[i][j] = '\0';
	}
	return sortedArray;
}

//the following functions return 1 if the word can be placed and also the number of placement
int* SearchWordLeftToRight(char** grid, int TR, int TC, int row, int col, int length, char* word)
{
	int* arr = new int[2];
	int j = 0;
	for (j = 0; j < length; j++)             // LeftToRight
	{
		if (row > TR - 1 || row < 0 || (col + j) > TC - 1 || (col + j) < 0)
		{
			break;
		}
		if (grid[row][col + j] != '*' && grid[row][col + j] != word[j])
		{
			break;
		}

	}
	if (j == length)
	{
		arr[0] = 1;
		arr[1] = 2;
		return arr;
	}
	arr[0] = 0;
	arr[1] = 0;

	return arr;
}
int* SearchWordRightToLeft(char** grid, int TR, int TC, int row, int col, int length, char* word)
{
	int* arr = new int[2];
	int j = 0;
	for (j = 0; j < length; j++)             // RightToLeft
	{
		if (row > TR - 1 || row < 0 || (col - j) > TC - 1 || (col - j) < 0)
		{
			break;
		}
		if (grid[row][col - j] != '*' && grid[row][col - j] != word[j])
		{
			break;
		}
	}
	if (j == length)
	{
		arr[0] = 1;
		arr[1] = 3;

		return arr;
	}
	arr[0] = 0;
	arr[1] = 0;
	return arr;
}
int* SearchWordTopToBottom(char** grid, int TR, int TC, int row, int col, int length, char* word)
{
	int* arr = new int[2];
	int j = 0;
	for (j = 0; j < length; j++)             // TopToBottom
	{
		if ((row + j) > TR - 1 || (row + j) < 0 || col > TC - 1 || col < 0)
		{
			break;
		}
		if (grid[row + j][col] != '*' && grid[row + j][col] != word[j])
		{
			break;
		}

	}
	if (j == length)
	{
		arr[0] = 1;
		arr[1] = 4;   

		return arr;
	}
	arr[0] = 0;
	arr[1] = 0;

	return arr;
}
int* SearchWordBottomToTop(char** grid, int TR, int TC, int row, int col, int length, char* word)
{

	int* arr = new int[2];
	int j = 0;
	for (j = 0; j < length; j++)             // BottomToTop
	{
		if ((row - j) > TR - 1 || (row - j) < 0 || col > TC - 1 || col < 0)
		{
			break;
		}
		if (grid[row - j][col] != '*' && grid[row - j][col] != word[j])
		{
			break;
		}

	}
	if (j == length)
	{
		arr[0] = 1;
		arr[1] = 5;

		return arr;
	}
	arr[0] = 0;
	arr[1] = 0;

	return arr;
}
int* SearchWordTopLeftToBottomRight(char** grid, int TR, int TC, int row, int col, int length, char* word)
{

	int* arr = new int[2];
	int j = 0;
	for (j = 0; j < length; j++)             // TopLeftToBottomRight
	{
		if ((row + j) > TR - 1 || (row + j) < 0 || (col + j) > TC - 1 || (col + j) < 0)
		{
			break;
		}
		if (grid[row + j][col + j] != '*' && grid[row + j][col + j] != word[j])
		{
			break;
		}
	}
	if (j == length)
	{
		arr[0] = 1;
		arr[1] = 6;

		return arr;
	}
	arr[0] = 0;
	arr[1] = 0;

	return arr;
}
int* SearchWordTopRightToBottomLeft(char** grid, int TR, int TC, int row, int col, int length, char* word)
{

	int* arr = new int[2];
	int j = 0;
	for (j = 0; j < length; j++)             // TopRightToBottomLeft
	{
		if ((row + j) > TR - 1 || (row + j) < 0 || (col - j) > TC - 1 || (col - j) < 0)
		{
			break;
		}
		if (grid[row + j][col - j] != '*' && grid[row + j][col - j] != word[j])
		{
			break;
		}
	}
	if (j == length)
	{
		arr[0] = 1;
		arr[1] = 7;

		return arr;
	}
	arr[0] = 0;
	arr[1] = 0;

	return arr;
}
int* SearchWordBottomLeftToTopRight(char** grid, int TR, int TC, int row, int col, int length, char* word)
{

	int* arr = new int[2];
	int j = 0;
	for (j = 0; j < length; j++)             // BottomLeftToTopRight
	{
		if ((row - j) > TR - 1 || (row - j) < 0 || (col + j) > TC - 1 || (col + j) < 0)
		{
			break;
		}
		if (grid[row - j][col + j] != '*' && grid[row - j][col + j] != word[j])
		{
			break;
		}
	}
	if (j == length)
	{
		arr[0] = 1;
		arr[1] = 8;
		return arr;
	}
	arr[0] = 0;
	arr[1] = 0;

	return arr;
}
int* SearchWordBottomRightToTopLeft(char** grid, int TR, int TC, int row, int col, int length, char* word)
{

	int* arr = new int[2];
	int j = 0;
	for (j = 0; j < length; j++)             // BottomRightToTopLeft
	{
		if ((row - j) > TR - 1 || (row - j) < 0 || (col - j) > TC - 1 || (col - j) < 0)
		{
			break;
		}
		if (grid[row - j][col - j] != '*' && grid[row - j][col - j] != word[j])
		{
			break;
		}
	}
	if (j == length)
	{
		arr[0] = 1;
		arr[1] = 9;

		return arr;
	}
	arr[0] = 0;
	arr[1] = 0;

	return arr;
}

//this function searches in all 8 directions at a particular cordinate
int* SearchAllDirections(char** grid, int TR, int TC, int row, int col, char* word, int numberOfword)
{
	int* arr = new int[2];    //this array will keep have 1 at 0 position if word is found and record of the end cordinates of the word
	arr[0] = 0;
	arr[1] = 0;

	if (grid[row][col] != '*' && grid[row][col] != word[0])
	{
		arr[0] = -1;
		arr[1] = 0;
		return  arr;
	}
	int length = StringLenght(word);

	if (numberOfword == 0)    //first word is placed
	{
		arr = SearchWordTopLeftToBottomRight(grid, TR, TC, row, col, length, word);
		if (arr[0] != 0)
		{
			return arr;
		}
	}
	
	if (numberOfword % 2 == 0)               //dividing words half words to placed in top to bottom or left to right positions
	{
		arr = SearchWordTopToBottom(grid, TR, TC, row, col, length, word);
		if (arr[0] != 0)
		{
			return arr;
		}

		arr = SearchWordLeftToRight(grid, TR, TC, row, col, length, word);
		if (arr[0] != 0)
		{
			return arr;
		}
		arr = SearchWordTopRightToBottomLeft(grid, TR, TC, row, col, length, word);
		if (arr[0] != 0)
		{
			return arr;
		}
	}
	else                             //half words placed in opposite directions   downwards to upwards and right to left etc
	{
		arr = SearchWordRightToLeft(grid, TR, TC, row, col, length, word);
		if (arr[0] != 0)
		{
			return arr;
		}

		arr = SearchWordBottomLeftToTopRight(grid, TR, TC, row, col, length, word);
		if (arr[0] != 0)
		{
			return arr;
		}

		arr = SearchWordBottomToTop(grid, TR, TC, row, col, length, word);
		if (arr[0] != 0)
		{
			return arr;
		}

		arr = SearchWordBottomRightToTopLeft(grid, TR, TC, row, col, length, word);
		if (arr[0] != 0)
		{
			return arr;
		}

		
	}


	arr[0] = -1;
	arr[1] = 0;

	return  arr;
}

//the following functions place a word in a particular direction
void PlaceWordLeftToRight(char**& Grid, char** list, int length, int wordNumber, int row, int col)
{
	for (int j = 0; j < length; j++)             // left to right
	{
		Grid[row][col + j] = list[wordNumber][j];
	}
}
void PlaceWordRightToLeft(char**& Grid, char** list, int length, int wordNumber, int row, int col)
{
	for (int j = 0; j < length; j++)         //right to left
	{
		Grid[row][col - j] = list[wordNumber][j];
	}
}
void PlaceWordTopToBottom(char**& Grid, char** list, int length, int wordNumber, int row, int col)
{
	for (int j = 0; j < length; j++)       //top to bottom
	{
		Grid[row + j][col] = list[wordNumber][j];
	}
}
void PlaceWordBottomToTop(char**& Grid, char** list, int length, int wordNumber, int row, int col)
{
	for (int j = 0; j < length; j++)   //bottom to top
	{
		Grid[row - j][col] = list[wordNumber][j];
	}
}
void PlaceWordTopLeftToBottomRight(char**& Grid, char** list, int length, int wordNumber, int row, int col)
{
	for (int j = 0; j < length; j++) //top left to bottom right
	{
		Grid[row + j][col + j] = list[wordNumber][j];
	}
}
void PlaceWordTopRightToBottomLeft(char**& Grid, char** list, int length, int wordNumber, int row, int col)
{
	for (int j = 0; j < length; j++)   //top right to bottom left
	{
		Grid[row + j][col - j] = list[wordNumber][j];
	}
}
void PlaceWordBottomLeftToTopRight(char**& Grid, char** list, int length, int wordNumber, int row, int col)
{
	for (int j = 0; j < length; j++)   //bottom left to top right
	{
		Grid[row - j][col + j] = list[wordNumber][j];
	}
}
void PlaceWordBottomRightToTopLeft(char**& Grid, char** list, int length, int wordNumber, int row, int col)
{
	for (int j = 0; j < length; j++)  //bottom right to top left
	{
		Grid[row - j][col - j] = list[wordNumber][j];
	}
}

//moves in the whole grid and seacrhes ina ll 8 directions if a word can be placed
int* GridSpaceSearch(char** grid, int TR, int TC, char* word, int wordNumber)  //this function searches all words
{
	int* returnArray = new int[4];
	int* arr = new int[2];  //arr returned by SearchAllDirections

	for (int row = 0; row < TR; row++)   //half words places from the start of grid
	{
		for (int col = 0; col < TC; col++)
		{
			if (wordNumber % 2 == 0)
			{
				arr = SearchAllDirections(grid, TR, TC, row, col, word, wordNumber);
				if (arr[0] == 1)
				{
					returnArray[0] = arr[0];  //for true
					returnArray[1] = arr[1];  //number of placement

					returnArray[2] = row;  //start cordinates of word
					returnArray[3] = col;
					return returnArray;
				}
			}
			

		}

	}
	for (int row = TR - 1; row >= 0; row--)     //half words places from the end of grid
	{
		for (int col = TC - 1; col >= 0; col--)
		{
			if (wordNumber % 2 == 1)
			{
				arr = SearchAllDirections(grid, TR, TC, row, col, word, wordNumber);
				if (arr[0] == 1)
				{
					returnArray[0] = arr[0];  //for true
					returnArray[1] = arr[1];  //number of placement

					returnArray[2] = row;  //start cordinates of word
					returnArray[3] = col;
					return returnArray;
				}
			}


		}

	}
	delete[]arr;
	returnArray[0] = -1;
	returnArray[1] = 0;
	returnArray[2] = 0;
	returnArray[3] = 0;
	return returnArray;

}

//this function places the word
void PlaceWord(char**& Grid, char** list, int numberOfWords, int TR, int TC)
{
	int numberOfword = 0;
	for (int wordNumber = numberOfWords - 1; wordNumber >= 0; wordNumber--)  ///reads the file in desecnding order so largest word comes first
	{
		
		int* arr = 0;
		int length = StringLenght(list[wordNumber]);

		arr = GridSpaceSearch(Grid, TR, TC, list[wordNumber], numberOfword);
		numberOfword++;

		if (arr[0] == 1)  //true that word can be placed
		{
			int row = arr[2];   //returned by GridSpaceSearch
			int col = arr[3];

			if (arr[1] == 2)   //left to right
			{
				length = StringLenght(list[wordNumber]);
				PlaceWordLeftToRight(Grid, list, length, wordNumber, row, col);

			}
			if (arr[1] == 3)   //right to left
			{
				length = StringLenght(list[wordNumber]);
				PlaceWordRightToLeft(Grid, list, length, wordNumber, row, col);
			}
			if (arr[1] == 4)  //top to bottom
			{
				length = StringLenght(list[wordNumber]);
				PlaceWordTopToBottom(Grid, list, length, wordNumber, row, col);
			}
			if (arr[1] == 5)    //bottom to top
			{
				length = StringLenght(list[wordNumber]);
				PlaceWordBottomToTop(Grid, list, length, wordNumber, row, col);

			}
			if (arr[1] == 6)   //top left to bottom right
			{
				length = StringLenght(list[wordNumber]);
				PlaceWordTopLeftToBottomRight(Grid, list, length, wordNumber, row, col);
			}
			if (arr[1] == 7)       //top right to bottom left
			{
				length = StringLenght(list[wordNumber]);
				PlaceWordTopRightToBottomLeft(Grid, list, length, wordNumber, row, col);

			}
			if (arr[1] == 8)      //bottom left to top right
			{
				length = StringLenght(list[wordNumber]);
				PlaceWordBottomLeftToTopRight(Grid, list, length, wordNumber, row, col);
			}
			if (arr[1] == 9)       //bottom right to top left
			{
				length = StringLenght(list[wordNumber]);
				PlaceWordBottomRightToTopLeft(Grid, list, length, wordNumber, row, col);

			}
			delete[] arr;
			arr = 0;
		}

	}


}

//function to save grid in file
void SaveGrid(char** list, int TR, int TC, string savename)
{
	ofstream file(savename);
	if (file)
	{
		file << endl << endl;

		for (int i = 0; i < TR; i++)
		{

			for (int j = 0; j < TC; j++)
			{
				if (list[i][j] != ' ')
				{
					if ((list[i][j] > 97 || list[i][j] == 97) && (list[i][j] < 122 || list[i][j] == 122))         //if the words placed in grid are lower case convert to upper
					{

						list[i][j] -= 32;   //capitalizes all the letters in the grid
					}

					file << list[i][j] << " ";
				}

			}
			file << endl;
		}
	}
	file.close();

}
