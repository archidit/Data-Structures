#include "Homework5.hpp"
#include <iostream>
#include <sstream>

using namespace std;

MovieNode* deleteHelper(MovieNode *delNode){
	//post-order traversal
	if (delNode != NULL){
		deleteHelper(delNode->leftChild);
		deleteHelper(delNode->rightChild);
		delete delNode;
	}
	else {
		return NULL;
	}
}

MovieTree::MovieTree(){
	root = NULL;
}

MovieTree::~MovieTree(){
	deleteHelper(root);
	//delete root;
}

//helper function to search tree
MovieNode* MovieTree::search(MovieNode *node, std::string title){
	//cout << "Test" << endl;
	MovieNode* mySearchNode = node;
	
	//check if tree is empty
	if(mySearchNode != NULL){ 
	
		if (mySearchNode->leftChild != NULL){
				//search the left subtree
				search(mySearchNode->leftChild, title);  
			}			
		//cout << mySearchNode->title << endl;
		if (mySearchNode->title == title){
			return mySearchNode;
		}
		
		if (mySearchNode->rightChild != NULL){
			//search the right subtree
			search(mySearchNode->rightChild, title);   
		}
	}
	else {
		cout << "Movie not found." << endl;
		return NULL;
	}
}

void printHelper(MovieNode* root){
	MovieNode* myNode = root;

	//check if tree is empty
	if(myNode != NULL){ 

		if (myNode->leftChild != NULL){

			printHelper(myNode->leftChild);       //Visit left subtree
		}
		cout << "Movie: " << myNode->title << " " << myNode->quantity << endl;

		if (myNode->rightChild != NULL){

			printHelper(myNode->rightChild);      // Visit right subtree
		}
	}
	else {
		//cout << "Empty Tree" << endl;
	}
}

//string compare
//helper function to add node
MovieNode* addMovieHelper(MovieNode* root, int ranking, std::string title, int year, int quantity){
	
	MovieNode* newMovieNode = new MovieNode(ranking, title, year, quantity);

	if (root == NULL){
		//root = newMovieNode;
		return newMovieNode;
	}
	//the movie should go to the left/lesser node
	else if (title.compare(root->title) < 0){
		root->leftChild = addMovieHelper(root->leftChild, ranking, title, year, quantity);
		return root;
	}
	else {
	    root->rightChild = addMovieHelper(root->rightChild, ranking, title, year, quantity);
	    return root;
	}

}

//print tree InOrder = left->root->right
void MovieTree::printMovieInventory(){
		//helper recursion function
		printHelper(root);
}



//create a new struct node for each movie and add it to the tree
void MovieTree::addMovieNode(int ranking, std::string title, int releaseYear, int quantity){
	root = addMovieHelper(root, ranking, title, releaseYear, quantity);
	
}

void MovieTree::findMovie(std::string title){
	MovieNode* tempMovieNode = root;
	//helper function to search tree for the movie
	tempMovieNode = search(tempMovieNode, title);
/* 	if (tempMovieNode == NULL){
		cout << "Movie not found." << endl;
	} */
}


void MovieTree::rentMovie(std::string title){
	MovieNode* tempMovieNode = new MovieNode();
	tempMovieNode = search(root, title);
	if (tempMovieNode == NULL){
	    cout << "Movie not found." << endl;
	}
	else if (tempMovieNode->quantity > 0){
	    tempMovieNode->quantity--;
	    cout << "Movie has been rented." << endl;
	    cout << "Movie Info:" << endl;
	    cout << "===========" << endl;
	    cout << "Ranking:" << tempMovieNode->ranking << endl;
	    cout << "Title:" << tempMovieNode->title << endl;
	    cout << "Year:" << tempMovieNode->year << endl;
	    cout << "Quantity:" << tempMovieNode->quantity << endl;
	}
	else if (tempMovieNode->quantity == 0){
		cout << "Movie out of stock." << endl;
	}

}

void MovieTree::deleteMovie(std::string title){
	
}

int countMovieHelper(MovieNode* root){
	MovieNode* counterNode = root;
	int counterInt = 0;
	//check if tree is empty
	if(counterNode != NULL){ 

		if (counterNode->leftChild != NULL){
			countMovieHelper(counterNode->leftChild);       //Visit left subtree
		}
		
		counterInt += counterNode->quantity;

		if (counterNode->rightChild != NULL){
			countMovieHelper(counterNode->rightChild);      // Visit right subtree
		}
		return counterInt;
	}
	else {
		//cout << "Empty Tree" << endl;
		return counterInt;
	}
}

void MovieTree::countMovies(){
	//traverse the tree in any order and count the total of all the movies in tree
	int totalMovies = 0;
	totalMovies = countMovieHelper(root);
	cout << "Total Movies in Tree: " << totalMovies << endl;
}
