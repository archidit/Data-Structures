// You may add helper functions between this comment and the deleteMovie
// definition if you like

MovieNode* getMinValue (MovieNode* root){
	if (root != nullptr){
		//left most value will be the min 
		while (root->leftChild != nullptr){
			root = root->leftChild;
		}
		return root;
	}
}


void MovieTree::deleteMovie(std::string title){
   MovieNode* target = search(root, title);
   
		if (target != nullptr){
		
		    //target for deletion has no children
			if (target->rightChild == NULL && target->leftChild == NULL){
			    if (target->parent == NULL){
			        delete target;
			        target = NULL;
			        root = NULL;
			    }
			    else if (target->parent->leftChild == target){
			        target->parent->leftChild = NULL;
			        delete target;
			    }
			    else if (target->parent->rightChild == target){
			        target->parent->rightChild = NULL;
			        delete target;
			    }
			}
			
			//if target has one child
			else if (target->leftChild == NULL){
			    if (target == root){
			        root = target->rightChild;
			        delete target;
			    }
			    else {
			        if (target->parent->rightChild == target){
			            target->parent->rightChild = target->rightChild;
			            target->rightChild->parent= target->parent;
			            delete target;
			        }
			        else {
			            target->parent->leftChild = target->rightChild;
			            target->rightChild->parent = target->parent;
			            delete target;
			        }
			    }
			}
			
			else if (target->rightChild == NULL){
			    if (target == root){
			        root = target->leftChild;
			        delete target;
			    }
			    else {
			        if (target->parent->rightChild == target){
			            target->parent->rightChild = target->leftChild;
			            target->leftChild->parent= target->parent;
			            delete target;
			        }
			        else {
			            target->parent->leftChild = target->leftChild;
			            target->leftChild->parent = target->parent;
			            delete target;
			        }
				}
			}
			
			//target has two children
			else if (target->rightChild != nullptr && target->leftChild != nullptr){
				
			
			    MovieNode* minRightNode = getMinValue(target->rightChild);
				std::string minRight = minRightNode->title;
				int minRightQuantity = minRightNode->quantity;
				//MovieNode* minRightNode = search(target->rightChild, minRight);
				
				//minRightNode has a child --> assign the target's child to the parent's right
				
			    if (minRightNode->rightChild != nullptr){
					
					minRightNode->rightChild->parent = minRightNode->parent;
					if (minRightNode->parent->rightChild == minRightNode){
						minRightNode->parent->rightChild = minRightNode->rightChild;
					}
					else if (minRightNode->parent->leftChild == minRightNode) {
						minRightNode->parent->leftChild = minRightNode->rightChild;
					}
				}
				
				//minRightNode has no children
				else {
					if (minRightNode->parent->rightChild == minRightNode){
						minRightNode->parent->rightChild = NULL;
					}
					else if (minRightNode->parent->leftChild == minRightNode) {
						minRightNode->parent->leftChild = NULL;
					}
				}
				
				delete minRightNode;
                minRightNode = NULL;
				target->title = minRight;
				target->quantity = minRightQuantity;
			}
			
			
		}
		else {
			cout << "Movie not found." << endl;
		}
}
