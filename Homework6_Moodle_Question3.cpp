
#include "Homework5.hpp"
#include <iostream>
#include <sstream>

using namespace std;

//called by the destructor
void deleteHelper(MovieNode *delNode){
	//post-order traversal
	if (delNode != NULL){
		deleteHelper(delNode->leftChild);
		deleteHelper(delNode->rightChild);
		delete delNode;
		//delNode = NULL;
	}
}

//constructor 
MovieTree::MovieTree(){
	root = NULL;
}

//destructor
MovieTree::~MovieTree(){
	deleteHelper(root);
	root = NULL;
}

//finds minimum value in right subtree
MovieNode* getMinValue (MovieNode* root){
	if (root != nullptr){
		//left most value will be the min 
		while (root->leftChild != nullptr){
			root = root->leftChild;
		}
		return root;
	}
	else {
	    return NULL;
	}
}

//finds max value in left subtree
MovieNode* getMaxValue(MovieNode* root){
	if (root != nullptr){
		while (root->rightChild != nullptr){
			root = root->rightChild;
		}
		return root;
	}
	else {
	    return NULL;
	}
} 

//helper function to search tree --> returns node pointer
MovieNode* MovieTree::search(MovieNode *node, std::string title){

	MovieNode* mySearchNode = node;
	//check if tree is empty
	if(mySearchNode != NULL){

		//If root is the node you are looking for
	    if (mySearchNode->title == title){
		    	return mySearchNode;
		}
		//easier to search the tree this way instead of recursion
		else {
		    while (mySearchNode != NULL){
		    	//not going to lie, the comparison stuff is still confusing
		        if (mySearchNode->title > title){
		            mySearchNode = mySearchNode->leftChild;    
		        }
		        else if (mySearchNode->title < title){
		            mySearchNode = mySearchNode->rightChild;
		        }
				//if the movie node is found, this will return it
		        else if (mySearchNode->title == title){
		            return mySearchNode;
		        }
		    }
		}
	}

	else {
		cout << "Movie not found." << endl;
		return NULL;
	}
	return mySearchNode;
}

//in-order traversal of tree and prints left-parent-right
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


//helper function to add node
MovieNode* addMovieHelper(MovieNode* node, int ranking, std::string title, int year, int quantity){

	if (node == NULL){
	    MovieNode* newMovieNode = new MovieNode(ranking, title, year, quantity);
		//newMovieNode->parent = node->parent;
		//error is most likely coming from needing to set the parent of the node to something
		//root = newMovieNode;
		return newMovieNode;
	}
	//the movie should go to the left/lesser node
	else if (title < node->title){
		node->leftChild = addMovieHelper(node->leftChild, ranking, title, year, quantity);
		return node;
	}
	else {
	    node->rightChild = addMovieHelper(node->rightChild, ranking, title, year, quantity);
	    return node;
	}
}

//create a new struct node for each movie and add it to the tree
void MovieTree::addMovieNode(int ranking, std::string title, int releaseYear, int quantity){
	root = addMovieHelper(root, ranking, title, releaseYear, quantity);
}

//print tree InOrder = left->root->right
void MovieTree::printMovieInventory(){
		//helper recursion function
		printHelper(root);
}

//function that uses search() to get the data for a node
void MovieTree::findMovie(std::string title){
	MovieNode* tempMovieNode = root;
	//helper function to search tree for the movie
	tempMovieNode = search(tempMovieNode, title);
	 cout << "Movie Info:" << endl;
	 cout << "===========" << endl;
	 cout << "Ranking:" << tempMovieNode->ranking << endl;
	 cout << "Title:" << tempMovieNode->title << endl;
	 cout << "Year:" << tempMovieNode->year << endl;
	 cout << "Quantity:" << tempMovieNode->quantity << endl;
}

//user will give movie title --> find it in tree (if possible) and decrement inventory count
void MovieTree::rentMovie(std::string title){
	MovieNode* tempMovieNode;
	//find the movie node and retrieve all the struct info
	tempMovieNode = search(root, title);
	//movie wasn't found
	if (tempMovieNode == NULL){
	    cout << "Movie not found." << endl;
	}
	//movie was found and it is in stock
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
	//movie was found but it is out of stock
	else if (tempMovieNode->quantity == 0){
		cout << "Movie out of stock." << endl;
	}
}
	
//delete a node from a tree  
void MovieTree::deleteMovie(std::string title){
   MovieNode* target = search(root, title);
   /*cout << "root: " << root->title << endl;
   cout << "root leftChild: " << root->leftChild->title << endl;
   cout << "root rightChild: " << root->rightChild << endl;
   cout << "root parent: " << root->parent << endl;*/
		//target is the movie node we want to delete
		//checks if the target movie node has data in it
		if (target != nullptr){
		
		    //target for deletion has no children
			if (target->rightChild == NULL && target->leftChild == NULL){
				//target is the only node in the tree
			    if (target->parent == NULL){
			        delete target;
			        target = NULL;
			        //root = target;
					}
				//if target is the left child of the root node
				else if (target->parent->leftChild == target){
					target->parent->leftChild = NULL;
					delete target;
				}
				//if target is the right child of the root node
				else if (target->parent->rightChild == target){
					target->parent->rightChild = NULL;
					delete target;
				}
			}
			
			//if target has one child and it is the rightChild
			else if (target->leftChild == NULL){
				//target is the root node
			    if (target == root){
			        root = target->rightChild;
			        delete target;
			    }
				//target is NOT root node
			    else {
					//if target is rightChild of parent node
			        if (target->parent->rightChild == target){
			            target->parent->rightChild = target->rightChild;
			            target->rightChild->parent= target->parent;
			            delete target;
			        }
					//if target is the leftChild of parent node
			        else {
			            target->parent->leftChild = target->rightChild;
			            target->rightChild->parent = target->parent;
			            delete target;
			        }
			    }
			}
			//if target has one child and it is the leftChild
			else if (target->rightChild == NULL){
				//target is the root node
			    if (target == root){
			        root = target->leftChild;
			        delete target;
			    }
				//target is NOT root node
			    else {
					//if target is rightChild of parent node
			        if (target->parent->rightChild == target){
			            target->parent->rightChild = target->leftChild;
			            target->leftChild->parent= target->parent;
			            delete target;
			        }
					//if target is leftChild of parent node
			        else {
			            target->parent->leftChild = target->leftChild;
			            target->leftChild->parent = target->parent;
			            delete target;
			        }
				}
			}
			
			//target has TWO children
			else if (target->rightChild != nullptr && target->leftChild != nullptr){
				
				//cout << "ooooo " << endl;
				//get the minimum value of the right subtree underneath target
			    MovieNode* minRightNode = getMinValue(target->rightChild);
				//assign the min value's data to temp variables
				std::string minRight = minRightNode->title;
				int minRightQuantity = minRightNode->quantity;
				
				//minRightNode has a child --> assign minRightNode's parent to the target's parent and the target's parent rightChild to target's rightChild
				//this closes the links around target and allows you delete target
				//the minimum value node underneath the target node has a right child ~~~ this means it is bigger than minRightNode
			    if (minRightNode->rightChild != nullptr){
					//cout << "ppppp " << endl;
					cout << "minRightNode->title: " << minRightNode->title << endl; //--->prints out Waking Ned Devine
					cout << "minRightNode->rightChild->title: " << minRightNode->rightChild->title << endl; //--->prints out X-Men
					cout << "minRightNode->parent: " << minRightNode->parent << endl;
					cout << "minRightNode->parent->title: " << minRightNode->parent->title << endl;
//------------------------------------CAN'T ACCESS minRightNode->Parent->DATA----------------------------------------------------------------					
					cout << "minRightNode->parent->rightChild->title: " << minRightNode->parent->rightChild->title << endl;
					cout << "parent->rightChild->title: " << minRightNode->parent->rightChild->title << endl;
					cout << "parent->leftChild->title: " << minRightNode->parent->leftChild->title << endl;
					
					minRightNode->rightChild->parent = minRightNode->parent;
//------------------------------------------THIS EVALUATION GETS SEG FAULT ERRORS-----------------------------------------------------------
					if (minRightNode->parent->rightChild == minRightNode){
						minRightNode->parent->rightChild = minRightNode->rightChild;
					}
					else if (minRightNode->parent->leftChild == minRightNode) {
						minRightNode->parent->leftChild = minRightNode->rightChild;
					}
				}
				
				//minRightNode has no children ----> just assign it's parent's leftChild/rightChild to null
				else {
					if (minRightNode->parent->rightChild == minRightNode){
						minRightNode->parent->rightChild = NULL;
					}
					else if (minRightNode->parent->leftChild == minRightNode) {
						minRightNode->parent->leftChild = NULL;
					}
				}
				//delete the minRightNode because you've already reconnected everything in the tree
				delete minRightNode;
                minRightNode = NULL;
				//assign all the data from the minRightNode to the target
				target->title = minRight;
				target->quantity = minRightQuantity;
			}		
		}
		else {
			cout << "Movie not found." << endl;
		}
}
//in order tree traversal that visits each movie node and counts the overall number of nodes/movies in the tree
int countMovieHelper(MovieNode* root){
	MovieNode* counterNode = root;
	int counterInt = 0;
	//check if tree is empty
	if(counterNode != NULL){ 
	    //goes through all the nodes on the left
		if (counterNode->leftChild != NULL){
			counterInt += countMovieHelper(counterNode->leftChild);
		}
		//increment counter
		counterInt++;
		//goes through all the nodes on the right 
		if (counterNode->rightChild != NULL){
			counterInt += countMovieHelper(counterNode->rightChild);
		}
		return counterInt;
	}
	else {
		return counterInt;
	}
}

//will call helper function
void MovieTree::countMovies(){
	//traverse the tree in any order and count the total of all the movies in tree
	int totalMovies = 0;
	totalMovies = countMovieHelper(root);
	cout << "Count = " << totalMovies << endl;
}
