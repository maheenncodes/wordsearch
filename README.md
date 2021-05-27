# wordsearch
Word Search Puzzle Project that generates a grid by user entered dimensions and search words in a grid. Console based .Coded in cpp.
So I was assigned a project to make a word Search puzzle 

## Functionality :
This code has two functionalities mainly :

#### Grid Generator
* To generate a grid by user entered dimensions and to read woords from a file and place them in the grid randomly
#### Word Searcher
* To select a file that has words to be seacrched  in it and a file that has a grid in it. The program will then seacrch words in the grid and display the coordinates(start and end) of the word on console and also save them in a file.

## Algorithm :
### Grid.h
This header file has all the functions needed to generate a grid and place words in it.
>* First the **RowCounter()** function reads the total rows (number of words) of the word file 
>* Then the **ReadListFromFile()** function reads the list of words fom the file entered by the user into a 2d array
>* The **sortArray()** functions sorts the list of words in an acesending order according to length of words and also deletes the space beteen a word like *Word Search* is a single word and has a space in it
>* Then the function **CheckGrid()** checks whether the user entered dimensions aren't a threat to the longest word in the word file and eturns true or false.
>* **GridIntialization()** function initialize the Grid with "__*__" (asterisk: Ascii code: 42) character 
>* The **PlaceWord()** function starts placing the words starting from the longest. It first checks for available space in the grid.Half of the words are searched for available space from top to down or right to left positions from the start of the grid and Half are searched from opposite direction starting from the end of the grid.The words are divided by even and odd number of word.All this is done in **GridSpaceSearch()** function. this further calls the **SearchAllDirections()** function.
>* The **SearchAllDirections()** function seacrhes in all 8 direcections 
>Each have a separate function i.e.
>1. SearchWordLeftToRight()
>2. SearchWordRightToLeft()
>3. SearchWordTopToBottom()
>4. SearchWordBottomToTop()
>5. SearchWordTopLeftToBottomRight()
>6. SearchWordTopRightToBottomLeft()
>7. SearchWordBottomLeftToTopRight()
>8. SearchWordBottomRightToTopLeft()
>* The **GridSpaceSearch()** Function returns an array which has the direction in which the word can be placed.
>The place word function is divided into 8 functions these functions are called in the **PlaceWord()** function to place the word:
>1. PlaceWordLeftToRight()
>2. PlaceWordRightToLeft()
>3. PlaceWordTopToBottom()
>4. PlaceWordBottomToTop()
>5. PlaceWordTopLeftToBottomRight()
>6. PlaceWordTopRightToBottomLeft()
>7. PlaceWordBottomLeftToTopRight()
>8. PlaceWordBottomRightToTopLeft()
>* After all the words are place the **FinalFill()** is called that replaces the character __*__ with  a random alphabet.
>* Last but not the least the **SaveGrid()** function creates a file and  saves the grid in the user entered filename. Aso this function capitalizes all the letters in the grid.
 ### Search.h
 This header file has functions to search words in a grid and display their coordinates
 >* First the **ListOfWords()** reads the words  , the dimensions of the grid and the testcases from the user entered file.
 >* The **ReadWordSearchGrid()** reads the grid file enetered by the user.
 >* The **GridSearch()** starts the word search from the start of the grid by calling the **SearchInAllDirections()** function which returns the end coordinates of the word if it is found. The latter function is further divided into 8 parts.
>1. SearchLeftToRight()
>2. SearchRightToLeft()
>3. SearchTopToBottom()
>4. SearchBottomToTop()
>5. SearchTopLeftToBottomRight()
>6. SearchTopRightToBottomLeft()
>7. SearchBottomLeftToTopRight()
>8. SearchBottomRightToTopLeft()
>* **ShowCordinatesOnConsole()** function  shows the coordinates of the word on the console and **ShowCordinates()** saves these coordinates in the file entered by user.

### SectionA_20L-1259_A5.cpp
This file is the driver file.
>The main is divided into two parts as for now _as more functionalities can be easily added_.\
>It has two functions for the two functionalties to take user input and call the functions from the two files i.e. Grid.h and Search.h\
>In the main the user is asked to select an option on the console from the menu
>1. If the User selects "C" or "c" the **CreateGrid()**function is called and takes user input to create and grid and then generates a grid and again displays the main menu
>2. If the User selects "S" or "s" the **WordSearch()**function is called and takes user input i.e name of files etc and srches the words and displays coordinates and the main menu
>3. If the User selects "Q" or "q" the program ends.
