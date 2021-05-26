#include"Grid.h"
#include"Search.h"

//function to generate a grid
char CreateGrid(char& option)
{
	int TR = 0, TC = 0;   //grid rows and grid columns
	char** list = 0;
	int numberOfWords;
	char** finalListOfWords = 0;
	char** grid = 0;               //word search grid
	bool check;

	cout << "Enter the name of the Input File with extension\n";
	string filename;
	cin >> filename;

	
	int rows = RowCounter(filename);      //counts the number of words in file for list array rows
	list = ReadListFromFile(filename);     //reads the word file into a 2d array


	
	cout << "\nEnter the number Of words in the file\n";
	cin >> numberOfWords;

	if (rows < numberOfWords)  //if the numberof words are more than that in the file
	{
		cout << "\n\nGrid Cannot be formed\nNumber of words Entered are Incorrect\nPress Any Key To return to Homescreen\n";
		cin >> option;
		return option;
	}


	finalListOfWords = sortArray(list, numberOfWords);    //this function sorts the list of words of file in ascending order

	cout << "\nEnter the number Of ROWS in the grid\n";
	cin >> TR;

	cout << "\nEnter the number Of COLUMNS in the grid\n";
	cin >> TC;


	check = CheckGrid(finalListOfWords, TR, TC, numberOfWords);     //decides whther dimensions of grid are according the longest word or not

	if (check == true)
	{
		grid = GridIntialization(TR, TC); //initializing grid

		PlaceWord(grid, finalListOfWords, numberOfWords, TR, TC);    //places all words in grid

		FinalFill(grid, TR, TC);      //fills the remaining space in grid with random alphabets

		string savename;
		cout << "\nEnter the name of the Output File of Grid with extension\n";
		cin >> savename;

		SaveGrid(grid, TR, TC, savename);        //saves grid in file

		cout << "\nSUCCESS!!\nYour WordSearch is ready!!  Check your File :)\n";
		cout << "-----------------------------------------------------------------------------------------------------------------------";
		cout << "\n\nPress Any Key To return to Homescreen\n";
		cin >> option;

		return option;
	}
	else
	{
		cout << "\n\nGrid Cannot be formed Press Any Key To return to Homescreen\n";
		cin >> option;
		return option;
	}
}

//function for wordSearch
char WordSearch(char& option)
{

	int rows = 0;
	int cols = 0;
	int testcases = 0;
	char** list = 0;    //list of words
	char** grid = 0;


	string gridFile;
	cout << "\nEnter the name of the file that has a grid in it\n";
	cin >> gridFile;

	string wordFile;
	cout << "\nEnter the name of the file that has words in it\n";
	cin >> wordFile;

	string outputFile;
	cout << "\nEnter the name of the outputfile \n";
	cin >> outputFile;

	list = ListOfWords(wordFile, rows, cols, testcases);         //reads the list of words


	grid = ReadWordSearchGrid(rows, cols, gridFile);    //reads the grid from file


	cout << "\n\nCORDINATES OF WORDS:\n\n";

	ShowCordinatesOnConsole(list, testcases, grid, rows, cols);  
	ShowCordinates(list, testcases, grid, rows, cols, outputFile);

	cout << endl << "\n\nAll Words Have Been Searched!\nCheck Your File:)\n\n";
	cout << "-----------------------------------------------------------------------------------------------------------------------";
	cout << "\n\nPress Any Key To return to Homescreen\n";
	cin >> option;

	return option;
}

int main()
{
	cout << "-----------------------------------------------------------------------------------------------------------------------";
	cout << "\t\t\t\t\t\t\tWELCOME TO WORD SEARCH\t\t\t\t\t\t\t\n ";
	cout << "-----------------------------------------------------------------------------------------------------------------------\n\n\n";
	
	char option = 'A';

	while (option != 'Q' && option != 'q')
	{
		cout << "1) Create Grid                                   Press C\n";
		cout << "2) Search Words From Grid                        Press S\n";
		cout << "3) Quit                                          Press Q\n\n";

		cin >> option;

		if (option == 'C' || option == 'c')
		{
			cout << "-------------------------------------------------WORD SEARCH GENERATOR--------------------------------------------------\n\n\n";
			
			option = CreateGrid(option);   //generates a grid
			

		}
		if (option == 'S' || option == 's')
		{
			cout << "----------------------------------------------------WORD SEARCHER-------------------------------------------------------";

			option = WordSearch(option);   //searches word in a grid

		}
	}
	if (option == 'Q' || option == 'q')
	{
		cout << "\n\nQUITING\nTHANKYOU FOR PLAYING THIS WORD SEARCH!!!\n\n";
		return 0;
	}

}
