#include<iostream>
#include<string>
#include<cstring>
#include<fstream>

using namespace std;

int calc_size()
{
    fstream file1;
    file1.open("index.db",ios::in);

    //vector<string> sstable_names;
    //int sstablecount=0;
    //int * sstable_sizes = (int *) malloc(sizeof(int));

    //vector<int> sstable_sizes;
    //define krdiye dono arrays
    //Assuming that index.db has atleast 1 sstable
    
    int counter = 0;
    
    while(!file1.eof()){
        string temp;
        file1>>temp;
        //sstable_names.push_back(temp);
        int a;
        file1>>a;
        //sstable_sizes.push_back(a);
	counter++;
    }

    file1.close();
    return counter-1;
}



int ParseCharToIntRD(const char c){
    return int(c)-97;
}

int SearchInDisk(const string key){
    
    int IndexFileNumber = calc_size();
    
    ifstream ReadIndex;
    ReadIndex.open("index.db");
    int in=0;
    string *FileNames = new string[IndexFileNumber];
    int *FileSizes = new int[IndexFileNumber];

    for (int i = 0; i < IndexFileNumber; i++)
    {
        ReadIndex>>FileNames[i];
        ReadIndex>>FileSizes[i];
    }

    for (int i = 0; i < IndexFileNumber; i++)
    {
        ifstream ReadFile;
        const string filePath = "table/"+FileNames[i]+".db";
        ReadFile.open(filePath);
        int bloom[26];

        for (int  j = 0; j < 26; j++)
        {
            ReadFile>>bloom[j];
        }

        // index from where we will start looking
        int IndexToStart = bloom[ParseCharToIntRD(key[0])];

        if(IndexToStart==-1){
            continue;
        }

        // index till where we will look

        for (int j = 0; j < IndexToStart; j++)
        {
            // Redundant Reading to reach the index we want to start from
            string s;
            ReadFile>>s;
            int k;
            ReadFile>>k;
            int tomb;
            ReadFile>>tomb;
        }

        for (int j = IndexToStart; j < FileSizes[i]; j++)
        {
            string FileKey; 
            int FileValue;
            int TombStone;
            ReadFile>>FileKey;
            ReadFile>>FileValue;
            ReadFile>>TombStone;

            // if the key you're looking for doesn't start from the letter of first letter of FileKey, then break
            if(ParseCharToIntRD(FileKey[0])!=ParseCharToIntRD(key[0])){
                break;
            }

            if(key==FileKey){ // key matches 
                if(TombStone==0){ // tombstone is absent
                    return FileValue;
                }else{ // tombstone is present
                    return -1;
                }
            }
        }

    }
    return -1;
    
    
}

int DeleteKey(const string key){
    
    int IndexFileNumber = calc_size();	
    
    ifstream ReadIndex;
    ReadIndex.open("index.db");

    string *FileNames = new string[IndexFileNumber];
    int *FileSizes = new int[IndexFileNumber];

    for (int i = 0; i < IndexFileNumber; i++)
    {
        ReadIndex>>FileNames[i];
        ReadIndex>>FileSizes[i];
    }

    for (int i = 0; i < IndexFileNumber; i++)
    {
        ifstream ReadFile;
        const string filePath = "table/"+FileNames[i]+".db";
        ReadFile.open(filePath);
        int bloom[26];

        for (int  j = 0; j < 26; j++)
        {
            ReadFile>>bloom[j];
        }

        

        // index from where we will start looking
        int IndexToStart = bloom[ParseCharToIntRD(key[0])];

        if(IndexToStart==-1){
            continue;
        }

        // index till where we will look

        for (int j = 0; j < IndexToStart; j++)
        {
            // Redundant Reading to reach the index we want to start from
            string s;
            ReadFile>>s;
            int k;
            ReadFile>>k;
            int tombstone;
            ReadFile>>tombstone;
        }

        for (int j = IndexToStart; j < FileSizes[i]; j++)
        {
            string FileKey; 
            int FileValue;
            int TombStone;
            ReadFile>>FileKey;
            ReadFile>>FileValue;
            ReadFile>>TombStone;

            // if the key you're looking for doesn't start from the letter of first letter of FileKey, then break
            if(ParseCharToIntRD(FileKey[0])!=ParseCharToIntRD(key[0])){
                break;
            }

            if(key==FileKey && TombStone==0){ // key found and tombstone is not present, so it's not deleted
                // found the key-value pair, now deleting it and pushing changes

                ifstream DeletionKeyFile;
                DeletionKeyFile.open(filePath);
                string *keys = new string[FileSizes[i]];
                int *values = new int[FileSizes[i]];
                int *TombStone = new int[FileSizes[i]];
                int *BLOOM = new int[26];

                for (int  k = 0; k < 26; k++)
                {
                    DeletionKeyFile>>BLOOM[k];
                }

                for (int k = 0; k < FileSizes[i]; k++)
                {
                    DeletionKeyFile>>keys[k];
                    DeletionKeyFile>>values[k];
                    DeletionKeyFile>>TombStone[k];
                }
                
                TombStone[j]=1; // now file is deleted

                ofstream Push;
                Push.open(filePath);
                for (int k = 0; k < 26; k++)
                {
                    Push<<BLOOM[k]<<' ';
                }
                Push<<"\n";
                
                for (int k = 0; k < FileSizes[i]; k++)
                {
                    Push<<keys[k]<<" "<<values[k]<<" "<<TombStone[k]<<"\n";
                }
                return 1;
                

            }
        }

    }
    return -1;
    
    
}

/*
int main(){

    int k = DeleteKey("anmdlxwcd");
    cout<<k<<endl;
    
}
*/
