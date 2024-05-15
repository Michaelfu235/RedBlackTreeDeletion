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
    cout << "enter a command: ADD(A), PRINT(P), or QUIT(Q)" << endl;
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
    } else if (strcmp(inputt, "S")==0){
      cout << "what number do you want to find?" << endl;
      int searchNum;
      cin >> searchNum;
      int found = searchhh(root, searchNum);
      if(found == searchNum){
	cout << searchNum << " exists in the tree" << endl;
      } else {
	cout << searchNum << " does not exist in the tree" << endl;
      }
    } else if (strcmp(inputt, "P")==0){
      printTree(root, 0, 0);
    } else if (strcmp(inputt, "Q")==0){
      justKeepGoing = false;
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
