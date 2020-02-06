#include<stdio.h>
#include<stdlib.h>
#include <fstream>          //fstream header file for ifstream class 
#include<string.h>
#include <algorithm>
#include<iostream>
#include<queue>
using namespace std;

struct Node{ 
    char key; 
    struct Node* left, *right; 
}; 
  
/* Helper function that allocates a new Node with the 
   given key and NULL left and right pointers. */
Node* newNode(char key){ 
    Node* temp = new Node; 
    temp->key = key; 
    temp->left = temp->right = NULL; 
    return (temp); 
}
struct Node* insertValue(struct Node* root, char value, queue<Node *>& q) 
{ 
    Node* node = newNode(value); 
    if (root == NULL) 
        root = node; 
  
    // The left child of the current Node is 
    // used if it is available. 
    else if (q.front()->left == NULL) 
        q.front()->left = node; 
  
    // The right child of the current Node is used 
    // if it is available. Since the left child of this 
    // node has already been used, the Node is popped 
    // from the queue after using its right child. 
    else { 
        q.front()->right = node; 
        q.pop(); 
    } 
  
    // Whenever a new Node is added to the tree, its 
    // address is pushed into the queue. 
    // So that its children Nodes can be used later. 
    q.push(node); 
    return root; 
} 
  
// This function mainly calls insertValue() for 
// all array elements. All calls use same queue. 
Node* createTree(char inputs[], int size) 
{ 
    Node* root = NULL; 
    queue<Node*> q; 
    for (int i = 0; i < size; i++) 
      root = insertValue(root, inputs[i], q); 
    return root; 
} 
void preOrder(struct Node* root){
    if(root == NULL){
        return;
    }
    cout<<root->key;
    preOrder(root->left);
    preOrder(root->right);
}
// This is used to verify the logic. 
void levelOrder(struct Node* root) 
{ 
    if (root == NULL) 
        return; 
    queue<Node*> n; 
    n.push(root); 
    cout<<endl<<"Level Order Traversal:"<<endl;
    while (!n.empty()) { 
        cout << n.front()->key; 
        if (n.front()->left != NULL) 
            n.push(n.front()->left); 
        if (n.front()->right != NULL) 
            n.push(n.front()->right); 
        n.pop(); 
    }
    cout<<endl<<"Preorder Traversal:"<<endl;
    preOrder(root);
}

void deSerialize(string path){
    ifstream fin;               // Creation of ifstream class object to read the file
    cout<<path<<endl;
	fin.open(path);      // by default open mode = ios::in mode 
    if(!fin){
        cout<<"File Can't Be Opened";
        return;
    }
    string line;                // variable declared to store each line read
 	int size=0;
     cout<<"Contents Of the File in the Form of tree as:"<<endl;
	while (fin) {                       // Execute a loop until EOF (End of File)
		 size=0;
		getline(fin, line);         // Read a Line from File
        
        int n = line.length();      //Store the length of the line in a variable
        char inputs[n];
        
        if(n==0){                   //Check if the line if empty and the skip a loop for it
            continue;
        }
        
        for(int k=0;k<n;k++){           //Loop to extract each character. ',' acts as a delimiter and characters stored in vector temp
            if(line[k] == ','){
                continue;
            }
            else{
                inputs[size++] = line[k];
            }
        }
        Node* root = createTree(inputs,size);
        levelOrder(root);
        cout<<endl;
	}
}

void serialize(string path,string storepath){
     ifstream fin;               // Creation of ifstream class object to read the file

	fin.open(path);      // by default open mode = ios::in mode 
    if(!fin){
        cout<<"File Can't Be Opened";
        return;
    }
    string line;                // variable declared to store each line read
 	 
	while (fin) {                       // Execute a loop until EOF (End of File)
		 
		getline(fin, line);         // Read a Line from File
        fstream fout; 
  
    // opens an existing csv file or creates a new file. 
    fout.open(storepath, ios::out | ios::app);
    fout<<line<<"\n";
    }
}

int main(int argc, char *argv[]){
    if(strcmp(argv[1],"load")==0){
        deSerialize(argv[2]);
    }
    else if(strcmp(argv[1],"create")==0){
        deSerialize(argv[2]);
        serialize(argv[2],argv[3]);
    }
    else{
       cout<<"Please Enter A Valid Command"<<endl;
    }
    return 0;
}