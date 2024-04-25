#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

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

void printTree(Node* tree, int depth, int fromwhere);
void rotateLeft(Node* &root, Node* &node);
void rotateRight(Node* &root, Node* &node);
Node* add(Node* &root, int data, bool &LL, bool &RR, bool &LR, bool &RL);
void checkTree(Node* &root, Node* &nnode);


int main(){
  Node* root = NULL;

  bool LL = false;
  bool RR = false;
  bool LR = false;
  bool RL = false;

  add(root, 4, LL, RR, LR, RL);
  checkTree(root, root);
  printTree(root, 0, 0);
  cout << "----------------------------------" << endl;

  add(root, 5, LL, RR, LR, RL);
  checkTree(root, root);
  printTree(root, 0, 0);
  cout << "----------------------------------" << endl;

  add(root, 7, LL, RR, LR, RL);
  checkTree(root, root);
  printTree(root, 0, 0);
  cout << "----------------------------------" << endl;

  add(root, 8, LL, RR, LR, RL);
  checkTree(root, root);
  printTree(root, 0, 0);
  cout << "----------------------------------" << endl;

  add(root, 9, LL, RR, LR, RL);
  checkTree(root, root);
  printTree(root, 0, 0);
  cout << "----------------------------------" << endl;

  add(root, 3, LL, RR, LR, RL);
  checkTree(root, root);
  printTree(root, 0, 0);
  cout << "----------------------------------" << endl;

  add(root, 1, LL, RR, LR, RL);
  checkTree(root, root);
  printTree(root, 0, 0);
  cout << "----------------------------------" << endl;


  printTree(root, 0, 0);
  
}


void printTree(Node* tree, int depth, int fromwhere){
  if(tree->data == -1){
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


void rotateLeft(Node* &root, Node* &node){
  Node* y = node->right;
  node->right = y->left;
  if(node->right != NULL){
    node->right->parent = node;
  }
  y->parent = node->parent;

  if(node->parent == NULL){
    root = y;
  } else if (node == node->parent->left){
    node->parent->left = y;
  } else {
    node->parent->right = y;
  }
  y->left = node;
  node->parent = y;
}

void rotateRight(Node* &root, Node* &node){
  Node* y = node->left;
  node->left = y->right;
  if(node->left != NULL){
    node->left->parent = node;
    
  }
  y->parent = node->parent;
  if(node->parent == NULL){
    root = y;
  } else if (node == node->parent->left){
    node->parent->left = y;
  } else {
    node->parent->right = y;
  }
  y->right = node;
  node->parent = y;
}


Node* add(Node* &root, int data, bool &LL, bool &RR, bool &LR, bool &RL){
  
  if(root == NULL){
    Node* newNode = new Node(data);
    root = newNode;
    return root;
  } else {
    bool isRedRed = false;
    if(data < root->data && root->left != NULL){
      Node* temp = root->left;
      return add (temp, data, LL, RR, LR, RL);
    } else if (data < root->data && root->left == NULL){
      Node* newNode = new Node(data);
      root->left = newNode;
      newNode->parent = root;
      return newNode;
    }

    if(data > root->data && root->right != NULL){
      Node* temp = root->right;
      return add(temp, data, LL, RR, LR, RL);
    } else if (data > root->data && root->right == NULL){
      Node* newNode = new Node(data);
      root->right = newNode;
      newNode->parent = root;
      return newNode;
    }
    /*if (data < root->data && root->left == NULL){
    Node* newNode = new Node(data);
    root->left = newNode;
    newNode->parent = root;
    return newNode;*/
  }
  return NULL;
}


void checkTree(Node* &root, Node* &nnode){
  Node* parent = NULL;
  Node* grandpa = NULL;
  Node* uncle = NULL;

  while((nnode != root) && (nnode->color == 'R') && (nnode->parent->color=='R')){
    parent = nnode->parent;
    grandpa = parent->parent;
    if(parent == grandpa->left){
      uncle = grandpa->right;
      if(uncle != NULL && uncle->color == 'R'){
	grandpa->color = 'R';
	parent->color = 'B';
	uncle->color = 'B';
	nnode = grandpa;
      } else {
	if(nnode == parent->right){
	  rotateLeft(root, parent);
	  nnode = parent;
	  parent = nnode->parent;
	}
	rotateRight(root, grandpa);
	parent->color = 'B';
	grandpa->color = 'R';
	nnode = parent;
      }
      
    }
    else {
      uncle = grandpa->left;
      if(uncle != NULL && uncle->color == 'R'){
	grandpa->color = 'R';
	parent->color = 'B';
	uncle->color = 'B';
	nnode = grandpa;
      }
      else {
	if(nnode == parent->left){
	  rotateRight(root, parent);
	  nnode = parent;
	  parent = nnode->parent;
	}
	rotateLeft(root, grandpa);
	parent->color = 'B';
	grandpa->color = 'R';
	nnode = parent;
      }
    }
  }
  root->color = 'B';
}
