/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include "console.h"
#include <cmath>
using namespace std;

/* Constants */


const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

const int NCubeSides = 6;
const int DELAY = 250;
const int BOGGLE_N_ROWS = 4;
const int BOGGLE_N_COLS = 4;
/* Function prototypes */

void welcome();
void giveInstructions();
void drawBoggle();
void playGame();
void play();
string chooseSetUp();
Grid<char> rollDiceSimulation(string);
Grid<char> simulateAutomatically();
Grid<char> simulateManually();
void generateCubeAndInstructions(string);
void startGameInstructions();
void generateCubeLabels(string);
void generateMoves(Grid<char> );
Set<string> generateUsersMove(Lexicon,Grid<char> charsGrid);
bool IsPossibleOnBoard(string);
bool checkForRequirments(string, Lexicon, Set<string>, Grid<char> );
string getRandomSequence();
string getSequence(Vector<string>&);
void generateRandomCube(Vector<string>&);
void swapWords(Vector<string>&, int);
void copyCubeWords(Vector<string>&, int);
bool IsPossibleOnBoard(string, Grid <char>);
void generateComputersMove(Lexicon, Grid<char>,Set<string>);
void generateWords(Lexicon, Grid<char>&, Set<string>&, Set<string>&, string, int, int, int , int, Grid<int>&);
Grid<char> strToGrid(string);
bool legalNumFormat(int, int, Grid<char>);
bool checkPossibility(string , Grid<char> , int , int , int, int , int, Grid<int>&);
void highlightCube(Grid<int>&, bool);
/* Main program */

int main() {
    GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    initGBoggle(gw);
    welcome();
    giveInstructions();
	playGame();
    return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}

// [TODO: Fill in the rest of the code]

//This function manages game process to continue until the player wants to play additional round.
void playGame(){
	drawBoggle();
	play();
	while(true){
		string answer;
		while(true){
			answer = getLine("would you like to play again? ");
			answer = toLowerCase(answer);
			if(answer=="yes" || answer=="no"){
				break;
			}else{
				cout<<"please answer yes or no"<<endl;
			}
		}
		if(answer == "no") break;
		drawBoggle();
		play();
	}
}

//this function draws boggle on the window
void drawBoggle(){
	drawBoard(BOGGLE_N_ROWS,BOGGLE_N_COLS);
}

//this function provides playing process
void play(){
	string answer = chooseSetUp();
	Grid<char> charsGrid = rollDiceSimulation(answer);
	generateMoves(charsGrid);
}

//this function lets the player to choose whether he wants to set up the board to his specification.
string chooseSetUp(){
	string answer;
	while(true){
		cout<< "I'll give you a chance to set up the board to your specification, ";
		cout<< "which makes it easier to confirm that your boggle program is working. ";
		cout<< "Do you want to force the board configuration? ";
		answer = getLine();
		answer = toLowerCase(answer);
		if(answer=="yes" || answer=="no"){
			break;
		}else{
			cout<<"please answer yes or no"<<endl;
		}
	}
	return answer;
}

//pre-condition: the player chooses whether he wants to set up the board up to his specification
//post-condition: the program responds accordingly - lets the player set up the board or 
//sets it up itself
Grid<char> rollDiceSimulation(string answer){
	Grid<char> charsGrid;
	if(answer == "no"){
		charsGrid = simulateAutomatically();
	}else{
		charsGrid = simulateManually();
	}
	return charsGrid;
}

//pre-condition: the player refuses to set up the board up to his specification
//post-condition: the program has set up the board with random sequence of random chars 
Grid<char> simulateAutomatically(){
	string str = getRandomSequence(); 
	generateCubeAndInstructions(str);
	return strToGrid(str);
}

//this function writes each character of string in chars' grid in corresponding order
Grid<char> strToGrid(string str){
	int nrows = BOGGLE_N_ROWS;
	int ncols = BOGGLE_N_COLS;
	Grid<char> charsGrid(nrows,ncols);
	int curIndex = 0;
	for(int r=0; r<nrows; r++){
		for(int c=0; c<ncols; c++){
			charsGrid[r][c] = str[curIndex];
			curIndex++;
		}
	}
	return charsGrid;
}

//this function provides generating random sequence of chars recorded in string
string getRandomSequence(){
	Vector<string> wordsVec;
	generateRandomCube(wordsVec);
	string finalSequence = getSequence(wordsVec);
	return finalSequence;
}

//this function 
string getSequence(Vector<string>& wordsVec){
	string res = "";
	for(int i=0; i<wordsVec.size(); i++){
		int randIndex = randomInteger(0, NCubeSides-1);
		string curStr = wordsVec[i];
		res += curStr[randIndex];
	}
	return res;
}

//this function gets empty vector as an argument and fills it with strings which are 
//copied from const STANDARD_CUBES in random sequence
void generateRandomCube(Vector<string>& wordsVec){
	int cubeSize = BOGGLE_N_ROWS*BOGGLE_N_COLS;
	copyCubeWords(wordsVec, cubeSize);
	swapWords(wordsVec, cubeSize);
}

//this function provides to randomely distribute strings in Vector.
void swapWords(Vector<string>& wordsVec, int cubeSize){
	for(int i=0; i<wordsVec.size(); i++){
		int x = randomInteger(i,cubeSize-1);
		string temp = wordsVec[i];
		wordsVec[i] = wordsVec[x];
		wordsVec[x] = temp;
	}
}

//this function provides to copy words from const STANDARD_CUBES into a Vector
void copyCubeWords(Vector<string>& wordsVec, int cubeSize){
	for(int i=0; i<cubeSize; i++){
		wordsVec.add(STANDARD_CUBES[i]);
	}
}

//this function gets string from player, which is the sequence of chars 
//that will be used to fill Cube
Grid<char> simulateManually(){
	cout<<"Enter a 16-character string to identify which letters you want on the cubes. "<<endl;
	cout<<"The first 4 letters are the cubes on the top row from left to right, ";
	cout<<"the next 4 letters are the second row, and so on. ";
	string str = getLine("Enter the string: ");
	int strLen = BOGGLE_N_ROWS*BOGGLE_N_COLS;
	while(str.length()!=strLen){
		str = getLine("String must include 16 characters! Try again: ");
 	}
	str = toUpperCase(str);
	generateCubeAndInstructions(str);
	return strToGrid(str);
}

//pre-condition: the player has chosen the way to set up the board configuration
//this function provides to see the board configuration on the screen and gives
//afterwards instructions to player
void generateCubeAndInstructions(string str){
	startGameInstructions();
	generateCubeLabels(str);
}

//this function gives instructions to player about playing the game and then cutting the game process.
void startGameInstructions(){
	cout<<"Ok, take all the time you want and find all the words you can! ";
	cout<<"Signal that you're finished by entering an empty line."<<endl;
}

//this function sets up the board with the chars of string that is given to function as an argument
void generateCubeLabels(string str){
	int NRows = BOGGLE_N_ROWS;
	int NCols = BOGGLE_N_COLS;
	int curIndex = 0;
	for(int r=0; r<NRows; r++){
		for(int c=0; c<NCols; c++){
			char ch = str[curIndex];
			labelCube(r,c,ch);
			curIndex++;
		}
	}
}

//pre-condition: the board configuration is already set up. 
//this function lets the player and computer to take turns
void generateMoves(Grid<char> charsGrid){
	Lexicon lex("EnglishWords.dat");
	Set<string> usersWords = generateUsersMove(lex, charsGrid);
	generateComputersMove(lex,charsGrid,usersWords);
}

//this function lets the player to make moves and find all words he can. 
//found words are saved in set named usersWords.
Set<string> generateUsersMove(Lexicon lex, Grid<char> charsGrid){
	Set <string> usersWords;
	while(true){
		string curWord = getLine("Enter a word: ");
		if(curWord == "") break;
		curWord = toLowerCase(curWord);
		bool isPossible = checkForRequirments(curWord, lex, usersWords,charsGrid);
		if(isPossible){
			curWord = toUpperCase(curWord);
			usersWords.add(curWord);
			recordWordForPlayer(curWord, HUMAN);
		}
	}
	return usersWords;
}

//this function checks if the current word meets the requirments of the instructions
//if it does not, then the function prints the reason of it in console.
bool checkForRequirments(string curWord, Lexicon lex, Set<string> usersWords, Grid<char> charsGrid){
	if(curWord.length()>3){
		if(!usersWords.contains(curWord)){
			if(lex.contains(curWord)){
				if(IsPossibleOnBoard(curWord, charsGrid)){
					return true;
				}else{
					cout<<"You can't make that word!"<<endl;
				}
			}else{
				cout<<"That's not a word!"<<endl;
			}
		}else{
			cout<<"You've already guessed that!"<<endl;
		}
	}else{
		cout<<"I'm sorry, but we have our standards."<<endl;
		cout<<"That word doesn't meet the minimum word length."<<endl;
	}
	return false;
}

//this function checks whether its possible for a word to configurate on current board.
bool IsPossibleOnBoard(string curWord, Grid<char> charsGrid){
	int curIndex = 0;
	int r0 = 0;
	int r = charsGrid.numRows();
	int c0 = 0;
	int c = charsGrid.numCols();
	Grid<int> usedChars(r, c);
	curWord = toUpperCase(curWord);
	bool res = checkPossibility(curWord, charsGrid, curIndex,r0,r,c0,c, usedChars);
	return res;
}

//this is recursive function which returns the answer whether its possible for a word to configurate on current board.
bool checkPossibility(string word, Grid<char> charsGrid, int curIndex, int r0, int r, int c0, int c, Grid<int>& usedChars){
	if(curIndex == word.length()){
		highlightCube(usedChars,true);
		pause(DELAY);
		highlightCube(usedChars,false);
		return true;
	}
	bool res = false;
	for(int i=r0; i<r; i++){
		for(int j=c0; j<c; j++){
			if(legalNumFormat(i,j,charsGrid)){
				if(charsGrid[i][j]==word[curIndex] && usedChars[i][j]==0){
					usedChars[i][j] = 1;
					res = checkPossibility(word, charsGrid, curIndex+1, i-1, i+2, j-1, j+2, usedChars);
					if(res) return true;
				}
			}
		}
	}
	return res;
}

//pre-condition: the word meets the requirments of instructions
//post-condition: the program highlights chars of the word.
void highlightCube(Grid<int>& usedChars, bool curSituation){
	for(int r = 0; r<usedChars.numRows(); r++){
		for(int c=0; c<usedChars.numCols(); c++){
			if(usedChars[r][c]==1) highlightCube(r,c,curSituation);
		}
	}
}

//this function checks whether i or j coordinate is out of bounds of charsGrid
bool legalNumFormat(int i, int j, Grid<char> charsGrid){
	if(i>=0 && i<charsGrid.numRows()){
		if(j>=0 && j<charsGrid.numCols()){
			return true;
		}
	}
	return false;
}

//this function generates computer's move
void generateComputersMove(Lexicon lex, Grid<char> charsGrid, Set<string> usersWords){
	Set<string> emptySet;
	string emptyStr = "";
	int r0 = 0;
	int r = charsGrid.numRows();
	int c0 = 0;
	int c = charsGrid.numCols();
	Grid<int> usedChars(r,c); 
	generateWords(lex, charsGrid, usersWords, emptySet, emptyStr, r0, r, c0, c, usedChars);
}

//this function provides finding all words on board that meet the program requirments and 
//also has not been found by the player
void generateWords(Lexicon lex, Grid<char>& charsGrid, Set<string>& usersWords, Set<string>& wordsSet, string word, int r0, int r, int c0, int c, Grid<int>& usedChars){
	if(word.length()>3 && !usersWords.contains(word) && !wordsSet.contains(word) && lex.contains(word)){
		wordsSet.add(word);
		recordWordForPlayer(word, COMPUTER);
	}
	for(int i=r0; i<r; i++){
		for(int j=c0; j<c; j++){
			if(legalNumFormat(i,j, charsGrid) && usedChars[i][j]==0){
				word += charsGrid[i][j];
				if(lex.containsPrefix(word)){
					usedChars[i][j] = 1;
					generateWords(lex, charsGrid, usersWords, wordsSet, word, i-1, i+2, j-1, j+2, usedChars);	
				}
				usedChars[i][j] = 0;
				word = word.substr(0, word.length()-1);
			}
		}
	}
}
