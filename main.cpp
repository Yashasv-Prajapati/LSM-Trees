#include<iostream>
#include<string>
#include "rbtree.h"
#include "compaction.h"
#include "read.h"

using namespace std;

int main()
{
	while(1)
	{
		cout << "1. Insert(predefined file) \n2. Delete\n3. Search\n4. Exit" << endl;
		int num;
		cin >> num;
		if(num == 1)
		{
			mainInsert();
			Compaction();
			//mainCompaction();
		}
		else if(num == 2)
		{
			string del;
			cout << "Enter key to Delete: ";
			cin >> del;
			int k = DeleteKey(del);
    			if (k == 1)
    			{
    				cout << "Delete Successful" << endl;
    			}
    			else
    			{
    				cout << "Delete Unsuccessful" << endl;
    			}
			//mainDelete();
		}
		else if(num == 3)
		{
			string srch;
			cout << "Enter string to Search: ";
			cin >> srch;
			
			int k = SearchInDisk(srch);
    			//cout<<k<<endl;
    			if (k != -1)
    			{
    				cout << "Value: " << k << endl;
    			}
    			else
    			{
    				cout << "Not Found" << endl;
    			}
			//mainSearch();
		}
		else if(num == 4)
		{
			exit(0);
		}
		else
		{
			cout << "Invalid Input" << endl;
		}
	}

}
