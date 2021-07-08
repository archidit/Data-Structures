/*
HW7
command line: g++ -std=c++11 -g filename.cpp -o filename -lm
*/

/*

*/
#include "HashTable.hpp"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;


HashTable::HashTable(int _hashTableSize){
	//declare hashTableArray and initialize all buckets to NULL
	//wordItem* hashTable[_hashTableSize];
	hashTable = new wordItem*[_hashTableSize];
	for (int ind = 0; ind < _hashTableSize; ind++){
		hashTable[ind] = NULL;
	}
	numUniqueWords = 0;
	numCollisions = 0;
	hashTableSize = _hashTableSize;
}

HashTable::~HashTable(){
	
}

//add up the ASCII values of each character in the string and return the hash value
//don't need to pass in hashTableSize because it is in your class
int HashTable::getHash(std::string word){
	int hashValue = 5381;
	for (int ind = 0; ind < word.length(); ind++){
		hashValue = hashValue*33 + word[ind];
	}
	hashValue = (hashValue % hashTableSize);
	if (hashValue < 0){
		hashValue += hashTableSize;
	}
	//cout << "hashValue: " << hashValue << endl;
	return hashValue;
}
//searches the hashtable for a specific word
wordItem* HashTable::searchTable(string word){
	//cout << "searchTable check 1" << endl;
	int hashValue = getHash(word);
	//hashValue = hashValue % hashTableSize;
	//cout << "hashValue: " << hashValue << " - hashTableSize: " << hashTableSize << endl;
	//cout << "searchTable check 2" << endl;
	wordItem* temp = hashTable[hashValue];
	//cout << "searchTable check 3" << endl;
	//cout << "temp: " << temp << endl;
 	while (temp != NULL && temp->word != word){
		temp = temp->next;
		//cout << "searchTable check 4" << endl;
	}
	return hashTable[hashValue];
}

void HashTable::getStopWords(char *ignoreWordFileName){
	 
	//open file with ifstream
	ifstream myFile;
	myFile.open(ignoreWordFileName);
	if (myFile.is_open()){
	
		string myLine;
		int vectorIndex = 0;
		while (myFile >> myLine){
			//DON'T USE PUSH_BACK(); ASSIGN WORD TO EACH POSITION IN VECTOR
			vecIgnoreWords[vectorIndex] = myLine;
			vectorIndex++;
		}
	}
	//error message if file doesn't open correctly
	else {
		cout << "Error opening stopWords file" << endl;
		myFile.close();
	}
	
/* 	int counter = 0;
	//check vector by printing out contents with for each loop
 	for (auto vectorContent: vecIgnoreWords){
			cout << "counter: " << counter << endl;
			counter++;
			cout << "stop word: " << vectorContent << endl;
		}  */
		
	//close file
	myFile.close();
	return;	
}

//searches the vector of stop words to see if parameter is a stop word 
bool HashTable::isStopWord(std::string word){
	bool wordFound = false;
	//searches through list of most common words and only returns true if the word is found
	for (int vectorInt = 0; vectorInt < vecIgnoreWords.size(); vectorInt++){
		//cout << word << " : " << vecIgnoreWords[vectorInt] << endl;
		if (word == vecIgnoreWords[vectorInt]){
			//true = 1
			//cout << vectorInt << endl; --> print out index position in vector that you found 'word'
			wordFound = true;
			return wordFound;
		}
	}
		//wait until outside the for loop to return false if the word isn't in the list
	if (wordFound == false){
		//returns false if wordFound hasn't been assigned 'true'; false = 0
		return wordFound;
	}
}

//this doesn't actually search the table, it just is a bool evaluation to give a yes/no answer
bool HashTable::isInTable(std::string word){
	//cout << "isInTable check : " << word << endl;
	bool wordFound = false;
	//call search helper funciton that will return the node if found in the hashtable 
	wordItem* temp = searchTable(word);
	if (temp == NULL){
		return wordFound;
	}
	else {
		wordFound = true;
		return wordFound;
	}
}

//setter function that should search the hashtable for a word and increment its count
void HashTable::incrementCount(std::string word){
	//temp struct pointer to increment count
	wordItem* tempCounter = searchTable(word);
	
	//the word wasn't in the hashtable
	if (tempCounter == NULL){
		//since it wasn't in the hashtable, don't increment the count
	}
	//the word is in the hashtable
	else {
		tempCounter->count++;
	}
}

//check for collisions 
//Good on Moodle --> don't change!!
void HashTable::addWord(std::string word){
	//newWord is the pointer to that new struct
	wordItem* newWord = new wordItem;
	//wordItem* newWord;
	newWord->word = word;
	newWord->count = 0;
	newWord->next = NULL;

	//search the hashtable first to see if it is in there
	//bool wordFound = isInTable(word);
	//hash the word to get hash value
	int newHashValue = getHash(word);
	//newWord = searchTable(word);
	//if the word wasn't found then you need to add it to the hashtable
	//cout << "wordFound: " << wordFound << endl;---> prints 0 = false
	//if (!wordFound){
		//check if the bucket is empty
		if (hashTable[newHashValue] == NULL){
			//hash the word and add it to the hashtable then assign the head pointer to that node?
			hashTable[newHashValue] = newWord;
			newWord->count++;
			
		}
		//if the bucket isn't empty
		else {
			cout << "collisions check: " << endl;
			newWord->next = hashTable[newHashValue];
			hashTable[newHashValue] = newWord;
			numCollisions++;
		}
		numUniqueWords++;
	//check to see if it was added succesfully
	//cout << "end of add word: " << endl;
	bool success = false;
	if (hashTable[newHashValue]->word == word){
		success = true;
		cout << "Added to the HashTable: " << word << endl;
	}
}

int HashTable::getTotalNumberNonStopWords(){
	int totalCount = 0;
	//loop through entire array 
	for (int index = 0; index < hashTableSize; index++){
		//access the struct to get actual word count for each word
		wordItem* tempCounter = hashTable[index];
		while (tempCounter != NULL){
			totalCount += tempCounter->count;
		    tempCounter = tempCounter->next;
		}
		//totalCount += hashTable[index]->count;
	}
return totalCount;
}

void HashTable::printTopN(int n){
	//declare an array of pointers
	wordItem* tempWordArray[n];
	
	for (int ind = 0; ind <= n - 1; ind++){
        cout << tempWordArray[ind]->count << " - " << tempWordArray[ind]->word <<endl;
    }
}

int HashTable::getNumUniqueWords(){
	//
	return numUniqueWords;
}

int HashTable::getNumCollisions(){
	//
	return numCollisions;
}

/*
//search array structs of unique words to see if it is already in there
//change to notInUniqueWordArray
bool notInUniqueWordArray(string singleWord, wordItem uniqueWordArray[], int arraySize){
	//cout << singleWord << endl;
	bool wordNotInArray = true;
	//loop through array of structs to see if the word is in the array 
	for (int structArrayIndex = 0; structArrayIndex < arraySize; structArrayIndex++){
		//if it is in array	then change bool to false
		if (singleWord == uniqueWordArray[structArrayIndex].word){
			uniqueWordArray[structArrayIndex].count++;
			wordNotInArray = false;
		}
	}
	return wordNotInArray;
}*/
