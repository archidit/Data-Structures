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
