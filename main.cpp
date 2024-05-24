#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

//class + constructors
class Node {

public:
  
  int data;
  char color;

  Node* left;
  Node* right;
  Node* parent;

  
  Node(int newData){
    data = newData;
    color = 'R';
    left = NULL;
    right = NULL;
    parent = NULL;
  }

  Node(){
    color = 'R';
    left = NULL;
    right = NULL;
    parent = NULL;
  }
  
};

//function prototypes
void printTree(Node* tree, int depth, int fromwhere);

Node* rotateLeft(Node* node);
Node* rotateRight(Node* node);

//void rotateLeft(Node* &root, Node* &node);
//void rotateRight(Node* &root, Node* &node);
Node* add(Node* &root, int data, bool &LL, bool &RR, bool &LR, bool &RL, Node* &actualRoot);
//void checkTree(Node* &root, Node* &nnode);
int searchhh(Node* root, int searchNum);
Node* findNode(Node* root, int data);
Node* nextValue(Node* root);
Node* deleet(Node* &realRoot, Node* startNode, int deleteNum);
void checkDelete(Node* &root, Node* &node);
void deleteHelper(Node* &node, int deleteNum);

int main(){
  Node* root = NULL;

  bool LL = false;
  bool RR = false;
  bool LR = false;
  bool RL = false;

  
  bool justKeepGoing = true;
  char inputt[15];

  //asking for user input loop with add by file, console, printing tree, and quit
  while(justKeepGoing){
    cout << "enter a command: ADD(A), PRINT(P), SEARCH(S), DELETE(D), or QUIT(Q) - ";
    cout << "Add by console and file are both in ADD" << endl;
    cin >> inputt;

    if(strcmp(inputt, "A") == 0){
      cout << "input type? (FILE or CONSOLE)" << endl;
      cin >> inputt;
      if(strcmp(inputt, "FILE")==0){

	char* fileName = new char[80];
      
	cout << "what's the name of the file you want to add (include the .txt)" << endl;
	cin >> fileName;
	cin.ignore();
	fstream file;
	file.open(fileName);
	int inpit = 0;
	while(file >> inpit){
	  add(root, inpit, LL, RR, LR, RL, root);
	}
	file.close();
      
      } else if (strcmp(inputt, "CONSOLE")==0){
	bool justKeepGoingtwo = true;
	char input[10];
      
	while(justKeepGoingtwo){
	  cout << "enter numbers from 1-999, or \"DONE\" when done" << endl;
	  
	  cin >> input;
	  if(strcmp(input, "DONE")==0){
	    justKeepGoingtwo = false;
	  } else {
	    int num = atoi(input);
	    add(root, num, LL, RR, LR, RL, root);
	  }
	}
      }
      
    } else if (strcmp(inputt, "S")==0){ //if the user wants to search, ask for the number and call search function. 
      cout << "what number do you want to find?" << endl;
      int searchNum;
      cin >> searchNum;
      int found = searchhh(root, searchNum);
      if(found == searchNum){
	cout << searchNum << " exists in the tree" << endl;
      } else {
	cout << searchNum << " does not exist in the tree" << endl;
      }
    } else if (strcmp(inputt, "D")==0){ //if the user wants to delete, ask for number and cal delete function
      cout << "num to delete?" << endl;
      int deleteNum;
      cin >> deleteNum;
      int found = searchhh(root, deleteNum);
      if(found == deleteNum){
	root = deleet(root, root, deleteNum);
      } else {
	cout << deleteNum << " does not exist in the tree!" << endl;
      }
    } else if (strcmp(inputt, "P")==0){
      printTree(root, 0, 0);
    } else if (strcmp(inputt, "Q")==0){
      justKeepGoing = false;
    } else if(strcmp(inputt, "PPP")==0){
      rotateRight(root);
    } else if (strcmp(inputt, "ABC")==0){
      
      add(root, 100, LL, RR, LR, RL, root);
      add(root, 90, LL, RR, LR, RL, root);
      add(root, 110, LL, RR, LR, RL, root);
      add(root, 105, LL, RR, LR, RL, root);
      add(root, 80, LL, RR, LR, RL, root);
      add(root, 95, LL, RR, LR, RL, root);
      add(root, 130, LL, RR, LR, RL, root);
      add(root, 140, LL, RR, LR, RL, root);
      add(root, 70, LL, RR, LR, RL, root);
      add(root, 85, LL, RR, LR, RL, root);
      add(root, 87, LL, RR, LR, RL, root);

      printTree(root, 0, 0);
      cout << "-------------------------------" << endl;
      root = deleet(root, root, 90);
      printTree(root, 0, 0);
      cout << "-------------------------------" << endl;
      root = deleet(root, root, 87);
      printTree(root, 0, 0);
      cout << "-------------------------------" << endl;
      
      add(root, 84, LL, RR, LR, RL, root);
      add(root, 83, LL, RR, LR, RL, root);

      printTree(root, 0, 0);
      cout << "-------------------------------" << endl;

      cout << root->right->right->right->parent->left << endl;
      root = deleet(root, root, 140);

      printTree(root, 0, 0);

      cout << root->right->data << " " << root->left->data << endl;
      cout << "aoeugbaoeugbaoeubgaouegbeg" << endl;
      cout << root->right->right->right << endl;
      cout << root->right->right->left << endl;
      cout << root->right->right->parent->left->data << endl;
      cout << (root->right->right->right==NULL) << endl;
      cout << (root->right->right->left == NULL) << endl;
      
      cout << "-------------------------------" << endl;
      root = deleet(root, root, 130);
      
      printTree(root, 0, 0);
      cout << "-------------------------------" << endl;

      //add(root, inpit, LL, RR, LR, RL, root);


    }
  }


  
  
}


//printtree function (prints the color of the node after the number
void printTree(Node* tree, int depth, int fromwhere){
  if(tree == NULL){
    cout << "tree is empty" << endl;
    return;
  }
  if(tree->right != NULL){
    printTree(tree->right, depth+1, 1);
  }

  for(int i = 0;i<depth-1;i++){
    cout << "\t";
  }
  if(fromwhere==2){
    cout << "\\____";
  } else if(fromwhere == 1){
    cout << "/▔▔▔▔▔";
  }
  cout << tree->data << " " << tree->color << endl;

  if(tree->left != NULL){
    printTree(tree->left, depth+1, 2);
  }
    
}


Node* rotateLeft(Node* node) {
  Node* x = node->right;
  Node* y = x->left;
  x->left = node;
  node->right = y;
  node->parent = x;
  if (y != NULL)
    y->parent = node;
  return x;
}

Node* rotateRight(Node* node){
  Node* x = node->left;
  Node* y = x->right;
  x->right = node;
  node->left = y;
  node->parent = x;
  if(y != NULL){
    y->parent = node;
  }
  return x;
}


//add function that checks the tree inside the add function
Node* add(Node* &root, int data, bool &LL, bool &RR, bool &LR, bool &RL, Node* &actualRoot){

  
  bool f = false;
  
  if(root == NULL){
    Node* newNode = new Node(data);
    root = newNode;
    
    return newNode;
  } else if (data < root->data){//for checkTree, just start with this else if stsatement (as an if statement) and change it so it just checks if theres an RR, then set f to true, then move past to if LL... (maybe change that if it doesnt work, we'll see)
    //NOTE: ^This comment is just for me in the future
    root->left = add(root->left, data, LL, RR, LR, RL, actualRoot);
    root->left->parent = root;
    if(root != actualRoot){
      if(root->color == 'R' && root->left->color == 'R'){
	f = true;
      }
    }
  } else {
    root->right = add(root->right, data, LL, RR, LR, RL, actualRoot);
    root->right->parent = root;
    if(root != actualRoot){
      if(root->color == 'R' && root->right->color == 'R'){
	f = true;
      }
    }
  }

  if(LL){
    root = rotateLeft(root);
    root->color = 'B';
    root->left->color = 'R';
    LL = false;
  } else if (RR){
    root = rotateRight(root);
    root->color = 'B';
    root->right->color = 'R';
    RR = false;
  } else if (RL){
    root->right = rotateRight(root->right);
    root->right->parent = root;
    root = rotateLeft(root);
    root->color = 'B';
    root->left->color = 'R';
    RL = false;
  } else if (LR){
    root->left = rotateLeft(root->left);
    root->left->parent = root;
    root = rotateRight(root);
    root->color = 'B';
    root->right->color = 'R';
    LR = false;
  }

  if(f == true){
    if(root->parent->right == root){
      if(root->parent->left == NULL || root->parent->left->color == 'B'){
	if(root->left != NULL && root->left->color == 'R'){
	  RL = true;
	} else if (root->right != NULL && root->right->color == 'R'){
	  LL = true;
	}
      } else {
	root->parent->left->color = 'B';
	root->color = 'B';
	if(root->parent != actualRoot) {
	  root->parent->color = 'R';
	}
      }
    } else {
      if(root->parent->right == NULL || root->parent->right->color == 'B'){
	if(root->left != NULL && root->left->color == 'R'){
	  RR = true;
	} else if (root->right != NULL && root->right->color == 'R'){
	  LR = true;
	}
      } else {
	root->parent->right->color = 'B';
	root->color = 'B';
	if(root->parent != actualRoot){
	  root->parent->color = 'R';
	}
      }
    }
    f = false;
  }

  if(actualRoot != NULL){
    actualRoot->color = 'B';
  }
  return root;

  
}



//search for a number and return -1 if it isn't found (same as from binary search tree)
int searchhh(Node* root, int searchNum){
  if(root == NULL){
    return -1;
  } else if (root->data == searchNum){
    return root->data;
  }

  if(root->data < searchNum){
    return searchhh(root->right, searchNum);
  } else if (root->data > searchNum){
    return searchhh(root->left, searchNum);
  }

  return -1;
}



//function that returns the node pointer that has the data being looked for. 
Node* findNode(Node* root, int data){
  Node* node = root;
  while (node != NULL) {
    if (node->data > data) { //go left
      node = node->left;
    } else if (node->data < data) { //go right
      node = node->right;
    } else if (node->data == data) {
      return node;
    }
  }
  return NULL;
}

//returns the next value 
Node* nextValue(Node* root){
  Node* current = root;
  while(current != NULL && current->left != NULL){
    current = current->left;
  }

  return current;
}



Node* deleet(Node* &realRoot, Node* startNode, int deleteNum){

  bool dB;

  if(realRoot == NULL){ //if there is not root, or root has no children, just return null.
    return realRoot;
  } else if (realRoot->left == NULL && realRoot->right == NULL){
    return NULL;
  } else {//otherwise:
    //find the node with findNode function (and for the rest of this function "root" is the node that we're on, and "realRoot" is the actual root of the RB tree
    Node* root = findNode(startNode, deleteNum);

    //if root has no children, set the color of root to B and its data to 0, then call checkDelete function of realRoot, and root
    if(root->left == NULL && root->right == NULL){
      if(root->color == 'B' && root->parent->color == 'R'){
	root->parent->color = 'B';
	checkDelete(realRoot, root);
      } else if(root->color == 'B' && root->parent->color == 'B'){
	checkDelete(realRoot, root->parent);
      }
	/* else if (root->color == 'B' && root->parent->color == 'B' && root->left != NULL && root->right != NULL){
	rotateRight(root);
      }
      /*if(root->color == 'B'){
	root->data = 0;
		checkDelete(realRoot, root);
		}*/
      if(root->parent->left == root){//using this if and else statement, remove the parent's pointer to root
	root->parent->left = NULL;
      } else {
	root->parent->right = NULL;
      }
      //then delete root and return realRoot
      delete root;
      return realRoot;
    } else if(root->left == NULL){ //if root has no left child

      Node* temp = root->right;//temporary node
      
      if(root->color == 'R' || root->right->color == 'R'){//if root and roots right is a double red, set root->right (temp) to black
	temp->color = 'B';
      } else if(root->right == NULL || root->right->color == 'B'){ //otherwise, set doubleBlack boolean to true
	dB = true;
      }

      if(root->parent != NULL){//if root has a parent (isnt the real root)
	if(root->parent->right == root){//if root is a right node, set root's parents right pointer to temp
	  root->parent->right = temp;
	} else {
	  root->parent->left = temp;//otherwise, set root's parent's left pointer to temp
	}
	//set temps parent to roots parent
	temp->parent = root->parent;
      }
      else {
	//otherwise, set realRoot to temp
	realRoot = temp;
      }
      //finally, delete root
      delete root;

      if(dB){//if double black, call check delete function
	checkDelete(realRoot, temp);
      }
    } else if (root->right == NULL){//if root has no right node, do everything the same as above, but using roots left node
      Node* temp = root->left;
      if(root->color == 'R' || root->left->color == 'R'){
	temp->color = 'B';
      } else if(root->left == NULL || root->left->color == 'B'){
	dB = true;
      }
      
      if(root->parent != NULL){
	if(root->parent->right == root){
	  root->parent->right = temp;
	} else {
	  root->parent->left = temp;
	}
	temp->parent = root->parent;
      }
      else{
	realRoot = temp;
      }
      delete root;

      if(dB){
	checkDelete(realRoot, temp);
      }

      
      

      
    }
    else{ //else create temp node with data of nextValue of root->right. then call deleet function again and return realRoot
      //cout << "here" << endl;
      Node* temp = nextValue(root->right);

      /*
      if(root->right->left == NULL && root->right->right != NULL){

	if(root != realRoot){
	  root->parent->right = root->right;
	  root->right->parent = root->parent;
	} else {
	  realRoot = root->right;
	  realRoot->left = root->left;
	  realRoot->right->parent = realRoot;
	  realRoot->left->parent = realRoot;
	}
	  //root->data = root->right->data;
	//root->right = temp;
	//	root->right->parent = root;
	}*/
      
      int temptwo = temp->data;

      root->data = temptwo;//temptwo;

      Node* tempthree = root->right;
      if(tempthree->left != NULL){
	while(tempthree->left != NULL){
	  tempthree = tempthree->left;
	}
	//Node* tempfour = tempthree;
	tempthree->parent->left = NULL;
	checkDelete(realRoot, root);
	
	if(root->right == NULL || root->right->color == 'R'){
	  checkDelete(realRoot, root->right);
	}
	//checkDelete(realRoot, root->right);
      } else {
	root->right = NULL;
      }

      root = rotateRight(root);
      //delete tempthree;
      

      return realRoot;
    }
  }

  return realRoot;
  
}


void checkDelete(Node* &root, Node* &node){ //check delete function
  if(node == root){//if node is root, then just return
    return;
  }

  //create a parent and sibling node, and assign sibling to the correct node
  Node* parent = node->parent;
  Node* sibling = node;
  if(parent->right == node){
    sibling = parent->left;
  } else {
    sibling = parent->right;
  }

  if(sibling == NULL){//if sibling is not exist, then call checkDelete again of the parent node
    checkDelete(root, parent);
  } else {//otherwise, if the sibling is R, set the parent to R and the sibling to B
    if(sibling->color == 'R'){
      parent->color = 'R';
      sibling->color = 'B';
      if(parent->left == sibling){//if the sibling is the left of the parent, rotateright of parent, otherwise, the opposite
	rotateRight(parent);
      } else {
	rotateLeft(parent);
      }
      //then call checkDelete of node again
      checkDelete(root, node);
    }
    else {//sibling is black
      if((sibling->left != NULL && sibling->left->color == 'R') || (sibling->right != NULL && sibling->right->color == 'R')){//if siblings left is R or siblings right is R
	if(sibling->left != NULL && sibling->left->color == 'R'){//if siblings left is R, then if sibling is the left node, then set siblings left to siblings color, and siblings color to parents color, then rotateRight of parent. otherwise rotateright of sibling, then rotateleft of parent
	  if(parent->left == sibling){
	    sibling->left->color = sibling->color;
	    sibling->color = parent->color;
	    rotateRight(parent);
	  } else {
	    sibling->left->color = parent->color;
	    rotateRight(sibling);
	    rotateLeft(parent);
	  }
	} else {//otherwise, do the same thing but the other way around
	  if(parent->left == sibling){
	    sibling->right->color = parent->color;
	    rotateLeft(sibling);
	    rotateRight(parent);
	  } else {
	    sibling->right->color = sibling->color;
	    sibling->color = parent->color;
	    rotateLeft(parent);
	  }
	}
	parent->color = 'B';
	
      } else {
	sibling->color = 'R';
	if(parent->color == 'B'){
	  checkDelete(root, parent);
	} else {
	  parent->color = 'B';
	}
      }

      
    }
  }
}



void deleteHelper(Node* &node, int deleteNum){
  Node* temp = node->right;
  if(temp != NULL){
    while(temp->left != NULL){
      temp = temp->left;
    }
    temp->parent->left = NULL;
    return;
  }
  node->right = NULL;
  return;
}
