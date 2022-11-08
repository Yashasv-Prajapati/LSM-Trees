#include<iostream>
#include<bits/stdc++.h>
#include <cmath>
#include <cstdlib>
#include<thread>
#include <fstream> 
#include <string.h>
#include "rbtree.h"

using namespace std;

#define block_size 100

struct node {
    string key;
    int value;
    int color;
    struct node* parent;
    struct node* right;
    struct node* left;
};

struct llnode {
	string key[block_size];
	int value[block_size];
	struct llnode* next;
} *llist, *ltemp, *lroot;
 
// global root for the entire tree
struct node* root = NULL;
 
// function to perform BST insertion of a node
struct node* bst(struct node* trav,
                      struct node* temp)
{
    // If the tree is empty,
    // return a new node
    if (trav == NULL)
        return temp;
 
    // Otherwise recur down the tree
    if (temp->key < trav->key)
    {
        trav->left = bst(trav->left, temp);
        trav->left->parent = trav;
    }
    else if (temp->key > trav->key)
    {
        trav->right = bst(trav->right, temp);
        trav->right->parent = trav;
    }
 
    // Return the (unchanged) node pointer
    return trav;
}
 
// Function performing right rotation
// of the passed node
void rightrotate(struct node* temp)
{
    struct node* left = temp->left;
    temp->left = left->right;
    if (temp->left)
        temp->left->parent = temp;
    left->parent = temp->parent;
    if (!temp->parent)
        root = left;
    else if (temp == temp->parent->left)
        temp->parent->left = left;
    else
        temp->parent->right = left;
    left->right = temp;
    temp->parent = left;
}
 
// Function performing left rotation
// of the passed node
void leftrotate(struct node* temp)
{
    struct node* right = temp->right;
    temp->right = right->left;
    if (temp->right)
        temp->right->parent = temp;
    right->parent = temp->parent;
    if (!temp->parent)
        root = right;
    else if (temp == temp->parent->left)
        temp->parent->left = right;
    else
        temp->parent->right = right;
    right->left = temp;
    temp->parent = right;
}
 
// This function fixes violations
// caused by BST insertion
void fixup(struct node* root, struct node* pt)
{
    struct node* parent_pt = NULL;
    struct node* grand_parent_pt = NULL;
 
    while ((pt != root) && (pt->color != 0)
           && (pt->parent->color == 1))
    {
        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;
 
        /*  Case : A
             Parent of pt is left child
             of Grand-parent of
           pt */
        if (parent_pt == grand_parent_pt->left)
        {
 
            struct node* uncle_pt = grand_parent_pt->right;
 
            /* Case : 1
                The uncle of pt is also red
                Only Recoloring required */
            if (uncle_pt != NULL && uncle_pt->color == 1)
            {
                grand_parent_pt->color = 1;
                parent_pt->color = 0;
                uncle_pt->color = 0;
                pt = grand_parent_pt;
            }
 
            else {
 
                /* Case : 2
                     pt is right child of its parent
                     Left-rotation required */
                if (pt == parent_pt->right) {
                    leftrotate(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }
 
                /* Case : 3
                     pt is left child of its parent
                     Right-rotation required */
                rightrotate(grand_parent_pt);
                int t = parent_pt->color;
                parent_pt->color = grand_parent_pt->color;
                grand_parent_pt->color = t;
                pt = parent_pt;
            }
        }
 
        /* Case : B
             Parent of pt is right
             child of Grand-parent of
           pt */
        else {
            struct node* uncle_pt = grand_parent_pt->left;
 
            /*  Case : 1
                The uncle of pt is also red
                Only Recoloring required */
            if ((uncle_pt != NULL) && (uncle_pt->color == 1))
            {
                grand_parent_pt->color = 1;
                parent_pt->color = 0;
                uncle_pt->color = 0;
                pt = grand_parent_pt;
            }
            else {
                /* Case : 2
                   pt is left child of its parent
                   Right-rotation required */
                if (pt == parent_pt->left) {
                    rightrotate(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }
 
                /* Case : 3
                     pt is right child of its parent
                     Left-rotation required */
                leftrotate(grand_parent_pt);
                int t = parent_pt->color;
                parent_pt->color = grand_parent_pt->color;
                grand_parent_pt->color = t;
                pt = parent_pt;
            }
        }
    }
 
    root->color = 0;
}
int counter = 0;
string arr_key[block_size];
int arr_val[block_size];

void inorder(struct node* trav)
{
    if (trav == NULL)
        return;
    inorder(trav->left);
    arr_key[counter] = trav->key;
    arr_val[counter] = trav->value;
    counter++;
    //cout << trav->key << " " << trav->value << endl;
    inorder(trav->right);
}
void free_inorder(struct node* trav)
{
    if (trav == NULL)
        return;
    //cout<<"HEllo\n"<<endl;
    inorder(trav->left);
    //free(trav->left);
    //cout << trav->key << " " << trav->value << endl;
    inorder(trav->right);
    free(trav);
    //free(trav->right);
}
 
void insert_into_rbtree(string name, int val)
{
	struct node* temp = (struct node*)malloc(sizeof(struct node));
        temp->right = NULL;
        temp->left = NULL;
        temp->parent = NULL;
        temp->key = name;
        temp->value = val;
        temp->color = 1;
 
        // calling function that performs bst insertion of
        // this newly created node
        root = bst(root, temp);
 
        // calling function to preserve properties of rb
        // tree
        fixup(root, temp);
}
 
int file_counter = 0;

bool flag = true;

//ofstream MyFileIndex("index.db");


int ParseCharToIntRB(const char c){
    return int(c)-97;
}

void ssflush()
{
	//cout << "g" << endl;
	ofstream MyFileIndex("index.db");
	while(1)
	{
		if(lroot->next != NULL)
		{
            int bloom[26];
            for (int i = 0; i < 26; i++)
            {
                bloom[i]=-1;
            }
            
			string fileName = "table/ss_";
			string fileNameIndex = "ss_";
			fileName += to_string(file_counter);
			fileName+= ".db";
			fileNameIndex += to_string(file_counter);
			


			MyFileIndex << fileNameIndex << " " << block_size << endl;
				
			//cout << fileName << endl;
			file_counter++;
			ofstream MyFile(fileName);
            
			// Bloom filter
            for (int idx = 0; idx < block_size; idx++)
            {
                if(bloom[ParseCharToIntRB(lroot->key[idx][0])] == -1){
                    bloom[ParseCharToIntRB(lroot->key[idx][0])] = idx;
                }
                
            }

            for (int i = 0; i < 26; i++)
            {
                MyFile<<bloom[i]<<" ";
            }
            MyFile<<"\n";

            // Bloom filter ends
            
            for(int i=0;i<block_size;i++)
			{

				MyFile << lroot->key[i] << " " << lroot->value[i] << " 0" << endl;
			}
			
			MyFile.close();
			lroot = lroot->next;
			flag = true;
		}
		else
		{
			flag = false;
		}
		//cout << "abc" << endl;
	}
	
	MyFileIndex.close();
	/*
	string fileName = "SS/ss_10_"+file_counter;
	file_counter++;
	ofstream MyFile(fileName);
	
	for(int i=0;i<block_size;i++)
	{
		MyFile << arr_key[i] << " " << arr_val[i] << endl;
	}
	
	MyFile.close();
	*/
} 
 
int mainInsert()
{

	time_t start, end;
	time(&start);
	//thread t1;
    	 // detach t1 from main thread
// Create a text string, which is used to output the text file
string myText;
    ifstream MyReadFile("TestCase.txt");
    
    int ct = 0;
    
    //Initialize linked list
    llist = ltemp = lroot = NULL;
    
    
    while (getline (MyReadFile, myText)) {
    	//cout << "e f" << endl;
        // Output the text from the file
        //cout << myText << endl;
        string word = "";
        string name = "";
	    for (auto x : myText)
	    {
		if (x == ' ')
		{
		    //cout << word << endl;
		    name = word;
		    word = "";
		}
		else {
		    word = word + x;
		}
	    }
        insert_into_rbtree(name,stoi(word));
        ct++;
        if(ct == block_size)
        {
        	inorder(root);
        	if(llist == NULL)
        	{
        		ltemp = (struct llnode*)malloc(sizeof(struct llnode));
        		//memcpy(ltemp->key, , block_size);
        		for(int i=0;i<block_size;i++)
        		{
        			ltemp->key[i] = arr_key[i];
				//cout<<arr_key[i]<<endl;
				ltemp->value[i] = arr_val[i];
        		}
        		ltemp->next = NULL;
        		llist = ltemp;
        		lroot = ltemp;
        		//cout << "d" << endl;
        		//free_inorder(root);
        		//delete root;
        		
        		counter = 0;
        		
        		root = NULL;
        		ct = 0;
        		
        		//async(launch::async, ssflush);
        		thread t1(ssflush);
			t1.detach();
        	}
        	else
        	{
        		ltemp = (struct llnode*)malloc(sizeof(struct llnode));
        		for(int i=0;i<block_size;i++)
        		{
        			
				//ltemp->key[i] = arr_key[i];
				ltemp->key[i] = arr_key[i];
				//cout<<arr_key[i]<<endl;
				ltemp->value[i] = arr_val[i];
        		}
        		ltemp->next = NULL;
        		llist->next = ltemp;
        		llist = ltemp;
        		//cout << "c" << endl;
        		//delete root;
        		//free_inorder(root);
        		root = NULL;
        		ct = 0;
        		counter = 0;
        		//cout << lroot << " " << lroot -> next << endl;
        	}
        	
    	}
    }
    time(&end);
    double time_taken = double(end - start);
    cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(5);
    cout << " sec " << endl;	
    while(flag);

ofstream MyFileIndex("index.db", ios::out | ios::app);

    
string fileName = "table/ss_";
string fileNameIndex = "ss_";
fileName += to_string(file_counter);
fileName+= ".db";
fileNameIndex += to_string(file_counter);

MyFileIndex << fileNameIndex << " " << block_size << endl;
	
//cout << fileName << endl;
file_counter++;
ofstream MyFile(fileName);

// Bloom filter
int bloom[26];
for (int i = 0; i < 26; i++)
{
    bloom[i]=-1;
}

int idx = 0;
for (int i = 0; i < block_size; i++)
{
    if(bloom[ParseCharToIntRB(lroot->key[i][0])] == -1){
        bloom[ParseCharToIntRB(lroot->key[i][0])] = i;
    }
    
    // MyFile<< bloom[idx] <<" ";
}

for (int i = 0; i < 26; i++)
{
    MyFile<<bloom[i]<<" ";
}
MyFile<<"\n";

// Bloom filter ends


for(int i=0;i<block_size;i++)
{
	MyFile << lroot->key[i] << " " << lroot->value[i] << " 0" << endl;
}

MyFile.close();
	//lroot = lroot->next;
    
    //Write last ss table
    
    // Close the file
MyReadFile.close(); 


    /*
    printf("Inorder Traversal of Created Tree\n");
    inorder(root);
    
    for(int i=0;i<block_size;i++)
    {
    	cout << arr_key[i] << " " << arr_val[i] << endl;
    }
    */
    MyFileIndex.close();
    return 0;
    
}
