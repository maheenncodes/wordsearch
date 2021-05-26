#include <iostream>
#include <ctime>
#include<cstdlib>
#include<fstream>
#include<string>
using  namespace std;

//----------------------------------------------WORD SEARCHER---------------------------------------------------

//calculates length of string
int StringLength(char* str)   //function to calculate stringlenght
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

//reads the list of words fom file
char** ListOfWords(string filename, int& rows, int& cols, int& testcases)
{
	ifstream file(filename);
	file >> rows >> cols >> testcases;   //by reference passed 
	if (file)
	{
		string dummy;                //to remove dummy line from file
		getline(file, dummy);


		char** wordList = new char* [testcases];

		int i = 0;

		while (i < testcases)
		{
			char abc[80];

			file.getline(abc, 80);

			int cols = 0;
			cols = StringLength(abc);

			wordList[i] = new char[cols + 1];

			int j = 0;
			for (j = 0; j < cols; j++) //deep copying
			{
				wordList[i][j] = abc[j];
			}
			wordList[i][j] = '\0';
			i++;
		}

		return wordList;
	}

}

//reads the grid from file
char** ReadWordSearchGrid(int rows, int cols, string filename)
{
	ifstream file(filename);
	if (file)
	{
		int i = 0;
		char** Grid = new char* [rows];
		while (i < rows)
		{
			char abc[80];

			file.getline(abc, 80);   //takes the word from a line 

			Grid[i] = new char[cols + 1];

			int j = 0;
			int k = 0;
			for (j = 0; j < cols && k < (cols + cols - 1); j++) //deep copying
			{

				Grid[i][j] = abc[k];
				k += 2;

			}
			Grid[i][j] = '\0';
			i++;
		}

		return Grid;
	}

}


int* SearchLeftToRight(char** grid, int TR, int TC, int row, int col, int length, char* word)
{
	int* arr = new int[3];
	int j = 0;
	for (j = 0; j < length; j++)             // LeftToRight
	{
		if (row > TR - 1 || row < 0 || (col + j) > TC - 1 || (col + j) < 0)
		{
			break;
		}
		if (grid[row][col + j] != word[j])
		{
			break;
		}

	}
	if (j == length)
	{
		arr[0] = 1;
		arr[1] = row;
		arr[2] = col + j - 1;
		return arr;
	}
	arr[0] = -1;
	arr[1] = 0;
	arr[2] = 0;
	return arr;
}
int* SearchRightToLeft(char** grid, int TR, int TC, int row, int col, int length, char* word)
{
	int* arr = new int[3];
	int j = 0;
	for (j = 0; j < length; j++)             // RightToLeft
	{
		if (row > TR - 1 || row < 0 || (col - j) > TC - 1 || (col - j) < 0)
		{
			break;
		}
		if (grid[row][col - j] != word[j])
		{
			break;
		}
	}
	if (j == length)
	{
		arr[0] = 1;
		arr[1] = row;
		arr[2] = col - j + 1;
		return arr;
	}
	arr[0] = -1;
	arr[1] = 0;
	arr[2] = 0;
	return arr;
}
int* SearchTopToBottom(char** grid, int TR, int TC, int row, int col, int length, char* word)
{
	int* arr = new int[3];
	int j = 0;
	for (j = 0; j < length; j++)             // TopToBottom
	{
		if ((row + j) > TR - 1 || (row + j) < 0 || col > TC - 1 || col < 0)
		{
			break;
		}
		if (grid[row +j][col] != word[j])
		{
			break;
		}

	}
	if (j == length)
	{
		arr[0] = 1;
		arr[1] = row + j - 1;
		arr[2] = col;

		return arr;
	}
	arr[0] = -1;
	arr[1] = 0;
	arr[2] = 0;
	return arr;
}
int* SearchBottomToTop(char** grid, int TR, int TC, int row, int col, int length, char* word)
{

	int* arr = new int[3];
	int j = 0;
	for (j = 0; j < length; j++)             // BottomToTop
	{
		if ((row - j) > TR - 1 || (row - j) < 0 || col > TC - 1 || col < 0)
		{
			break;
		}
		if (grid[row-j][col] != word[j])
		{
			break;
		}

	}
	if (j == length)
	{
		arr[0] = 1;
		arr[1] = row - j + 1;
		arr[2] = col;

		return arr;
	}
	arr[0] = -1;
	arr[1] = 0;
	arr[2] = 0;
	return arr;
}
int* SearchTopLeftToBottomRight(char** grid, int TR, int TC, int row, int col, int length, char* word)
{

	int* arr = new int[3];
	int j = 0;
	for (j = 0; j < length; j++)             // TopLeftToBottomRight
	{
		if ((row + j) > TR - 1 || (row + j) < 0 || (col + j) > TC - 1 || (col + j) < 0)
		{
			break;
		}
		if (grid[row+j][col + j] != word[j])
		{
			break;
		}
	}
	if (j == length)
	{
		arr[0] = 1;
		arr[1] = row + j-1;
		arr[2] = col + j - 1;

		return arr;
	}
	arr[0] = -1;
	arr[1] = 0;
	arr[2] = 0;

	return arr;
}
int* SearchTopRightToBottomLeft(char** grid, int TR, int TC, int row, int col, int length, char* word)
{

	int* arr = new int[3];
	int j = 0;
	for (j = 0; j < length; j++)             // TopRightToBottomLeft
	{
		if ((row + j) > TR - 1 || (row + j) < 0 || (col - j) > TC - 1 || (col - j) < 0)
		{
			break;
		}
		if (grid[row+j][col - j] != word[j])
		{
			break;
		}
	}
	if (j == length)
	{
		arr[0] = 1;
		arr[1] = row+j-1;
		arr[2] = col - j + 1;


		return arr;
	}
	arr[0] = -1;
	arr[1] = 0;
	arr[2] = 0;
	return arr;
}
int* SearchBottomLeftToTopRight(char** grid, int TR, int TC, int row, int col, int length, char* word)
{

	int* arr = new int[3];
	int j = 0;
	for (j = 0; j < length; j++)             // BottomLeftToTopRight
	{
		if ((row - j) > TR - 1 || (row - j) < 0 || (col + j) > TC - 1 || (col + j) < 0)
		{
			break;
		}
		if (grid[row-j][col + j] != word[j])
		{
			break;
		}
	}
	if (j == length)
	{
		arr[0] = 1;
		arr[1] = row - j + 1;
		arr[2] = col + j - 1;

		return arr;
	}
	arr[0] = -1;
	arr[1] = 0;
	arr[2] = 0;

	return arr;
}
int* SearchBottomRightToTopLeft(char** grid, int TR, int TC, int row, int col, int length, char* word)
{

	int* arr = new int[3];
	int j = 0;
	for (j = 0; j < length; j++)             // BottomRightToTopLeft
	{
		if ((row - j) > TR - 1 || (row - j) < 0 || (col - j) > TC - 1 || (col - j) < 0)
		{
			break;
		}
		if (grid[row-j][col - j] != word[j])
		{
			break;
		}
	}
	if (j == length)
	{
		arr[0] = 1;
		arr[1] = row - j + 1;
		arr[2] = col - j + 1;

		return arr;
	}
	arr[0] = -1;
	arr[1] = 0;
	arr[2] = 0;
	return arr;
}
//searches the word in all directions
int* SearchInAllDirections(char** grid, int gridRow, int gridCol, int row, int col, char* word)
{    //  search in 8 directions  in the order (right to left),(left to right),(top to bottom),(bottom to top),(top left to bottom right),(top right to bottom left),(bottom left to top right),(bottom right to top left)
	

	int* arr = new int[3];    //this array will keep have 1 at 0 position if word is found and record of the end cordinates of the word
							 //if word not found then the array wil will have -1 at 0 position

	if (grid[row][col] != word[0])   //checks if the cordinate have the first letter of word 
	{
		arr[0] = -1;
		arr[1] = 0;
		arr[2] = 0;
		return  arr;
	}


	int length = StringLength(word);

	arr = SearchLeftToRight(grid, gridRow, gridCol, row, col, length, word);
	if (arr[0] == 1)
	{
		return arr;
	}

	arr=SearchRightToLeft(grid, gridRow, gridCol, row, col, length, word);
	if (arr[0] == 1)
	{
		return arr;
	}
			
	arr = SearchTopToBottom(grid, gridRow, gridCol, row, col, length, word);
	if (arr[0] == 1)
	{
		return arr;
	}

	arr = SearchBottomToTop(grid, gridRow, gridCol, row, col, length, word);
	if (arr[0] == 1)
	{
		return arr;
	}
	arr = SearchTopLeftToBottomRight(grid, gridRow, gridCol, row, col, length, word);
	if (arr[0] == 1)
	{
		return arr;
	}

	arr = SearchTopRightToBottomLeft(grid, gridRow, gridCol, row, col, length, word);
	if (arr[0] == 1)
	{
		return arr;
	}

	arr = SearchBottomLeftToTopRight(grid, gridRow, gridCol, row, col, length, word);
	if (arr[0] == 1)
	{
		return arr;
	}

	arr = SearchBottomRightToTopLeft(grid, gridRow, gridCol, row, col, length, word);
	if (arr[0] == 1)
	{
		return arr;
	}

	
	arr[0] = -1;
	arr[1] = 0;
	arr[2] = 0;
	return  arr;
}

//at a particular row and col starts searching the word in all direction by the above function
int* GridSearch(char** grid, int gridRow, int gridCol, char* word)  //this function searches all words
{
	int* returnArray = new int[4];
	int* arr = new int[3];

	for (int row = 0; row < gridRow; row++)
	{
		for (int col = 0; col < gridCol; col++)
		{
			arr = SearchInAllDirections(grid, gridRow, gridCol, row, col, word);
			if (arr[0] == 1)
			{
				returnArray[0] = row;  //start cordinates of word
				returnArray[1] = col;

				returnArray[2] = arr[1];  //end codinates of the word
				returnArray[3] = arr[2];
				return returnArray;
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

//function to show cordinates of words on console
void ShowCordinatesOnConsole(char** list, int numberOfWords, char** grid, int rows, int cols)  //function to show start and cordinates  of a word
{

	for (int i = 0; i < numberOfWords; i++)
	{

		int* resultArr = new int[4];

		resultArr = GridSearch(grid, rows, cols, list[i]);  //this function returns the cordinates
		cout << list[i] << ":\t";
		if (resultArr[0] == -1)
		{

			cout << "NOT FOUND";

		}
		else
		{
			cout << "{" << resultArr[0] << "," << resultArr[1] << "}" << "{" << resultArr[2] << "," << resultArr[3] << "}";

		}
		cout << endl;

		delete[]resultArr;


	}
}

//function to save cordinates of words in file
void ShowCordinates(char** list, int numberOfWords, char** grid, int rows, int cols, string filename)  //function to show start and cordinates  of a word
{
	ofstream file(filename);
	if (file)
	{
		for (int i = 0; i < numberOfWords; i++)
		{

			int* resultArr = new int[4];

			resultArr = GridSearch(grid, rows, cols, list[i]);  //this function returns the cordinates
			file << list[i] << ":\t";

			if (resultArr[0] == -1)
			{
				file << "NOT FOUND";

			}
			else
			{
				file << "{" << resultArr[0] << "," << resultArr[1] << "}" << "{" << resultArr[2] << "," << resultArr[3] << "}";

			}
			file << endl;

			delete[]resultArr;


		}
	}
	file.close();


}
