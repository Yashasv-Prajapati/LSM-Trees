// *******************NOTE**********************
/*

2)Assuming that index.db has atleast 1 sstable
3) SIZE is of the size of contents of sstable
*/
//*************GLOBAL VARIABLE FOR COMPACTION INDEX******************
int currentcompacindex=0;//this represents till which compaction made ....+1 it to make new
#define SIZE 100
#include <stdlib.h>
#include<iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <string>
using namespace std;

// Function to compare 2 words
bool isAlphabeticallySmaller(string str1, string str2)
{
	transform(str1.begin(), str1.end(), str1.begin(),
			::toupper);
	transform(str2.begin(), str2.end(), str2.begin(),
			::toupper);
	if (str1 < str2) {
		return true;
	}
	return false;
}

int ParseCharToInt(char c){
    return int(c)-97;

}

void merge(string Arr3[],string Arr1[],
					string Arr2[],int numArr1[],int numArr2[],int numArr3[],int mergingsize,int bloom[])
{
    cout<<"merging started!!"<<endl;
	int m =mergingsize ;
	int n = mergingsize;
	//string Arr3[m+n];
	int idx = 0;

	int i = 0;
	int j = 0;
	while (i < m && j < n) {
		if (isAlphabeticallySmaller(Arr1[i], Arr2[j])) {
			//Arr3=(string*) realloc(Arr3,sizeof(string)*(idx+1));
			Arr3[idx]=Arr1[i];
			numArr3[idx]=numArr1[i];

			int firstCharOfArray = ParseCharToInt(Arr1[i][0]);
			if(bloom[firstCharOfArray]==-1){
                bloom[firstCharOfArray]=idx;
			}

			i++;
			idx++;
		}
		else {
            //Arr3=(string*) realloc(Arr3,sizeof(string)*(idx+1));
			Arr3[idx]=Arr2[j];
			numArr3[idx]=numArr2[j];

			int firstCharOfArray = ParseCharToInt(Arr2[j][0]);
			if(bloom[firstCharOfArray]==-1){
                bloom[firstCharOfArray]=idx;
			}

			j++;
			idx++;
		}
	}
	while (i < m) {
       // Arr3=(string*) realloc(Arr3,sizeof(string)*(idx+1));
		Arr3[idx]=Arr1[i];
		numArr3[idx]=numArr1[i];

		int firstCharOfArray = ParseCharToInt(Arr1[i][0]);
        if(bloom[firstCharOfArray]==-1){
            bloom[firstCharOfArray]=idx;
        }

		i++;
		idx++;
	}
	while (j < n) {
        //Arr3=(string*) realloc(Arr3,sizeof(string)*(idx+1));
		Arr3[idx]=Arr2[j];
		numArr3[idx]=numArr2[j];

		int firstCharOfArray = ParseCharToInt(Arr2[i][0]);
        if(bloom[firstCharOfArray]==-1){
            bloom[firstCharOfArray]=idx;
        }

		j++;
		idx++;
		cout<<"merging ended"<<endl;
	}
//	return Arr3;
}

// Function to mergeSort 2 arrays
/*char** mergeSort(Char** Arr, int lo, int hi)
{
	if (lo == hi) {
		vector<string> A = { Arr[lo] };
		return A;
	}
	int mid = lo + (hi - lo) / 2;
	char** arr1 = mergeSort(Arr, lo, mid);
	char** arr2 = mergeSort(Arr, mid + 1, hi);

	char** arr3 = merge(arr1, arr2);
	return arr3;
}*/
void Compaction(){
    //step 1 is to read index.db file into an sstable_namesay and then we will do bakchodi on it
    //step 1a opening index.db
    fstream file1;
    file1.open("index.db",ios::in);
    //saving whole data into an dynamic array of strings
    //How would i know that how many ss table names i have to take input in input arrays
    //const char* sstable_names[SIZE];
    //const int ss_sizes[SIZES];
    vector<string> sstable_names;
    //int sstablecount=0;
    //int * sstable_sizes = (int *) malloc(sizeof(int));

    vector<int> sstable_sizes;
    //define krdiye dono arrays
    //Assuming that index.db has atleast 1 sstable
    while(!file1.eof()){
        string temp;
        file1>>temp;
        sstable_names.push_back(temp);
        int a;
        file1>>a;
        sstable_sizes.push_back(a);
        //file1>>sstable_sizes[sstablecount];

        //sstable_names= (string*) realloc(sstable_names, (sstablecount + 1) * sizeof(string));
        //sstable_sizes= (int*) realloc(sstable_sizes, (sstablecount + 1) * sizeof(int));
        //sstablecount++;
    }
    //cout<<"sstablesize in starting="<<sstable_names.size()<<endl;
    file1.close();
    int sstablecount=sstable_names.size()-1;
     //cout<<sstable_names[0];
    //cout<<sstablecount<<endl;
    /*cout<<"Current index table is:"<<endl;
          for(int j=0;j<sstablecount;j++){
            cout<<sstable_names[j]<<" "<<sstable_sizes[j]<<endl;}*/
    //closing the file :))))
    //i have taken input from index.db in an dynamic array of strings for names and dynamic array of integers for keys
    //remember that index.db will be automatically sorted
    //now i will traverse over the whole array of integers and find same size wale and merge them recursively untill their is no matching isme bhi time legega i think
    //ab main traverse krna tab hi rukunga jab  i last tak pahunch jaayega
    //should i try making the index.db sorted usme time kaafi lgega par kya muje usse fayda ho rha hai??.......
    //agar wo naa sorted rha to muje pura traverse krna pdega but agar sorted rha to jaise hi different aata h i will stop hehe
    // so i think sorted is best!!!!!
    int currentmergingsize;//this  merging size we are currently trying to match so that we can merge that

    //next question is that is there any need to open index.db again  and again  what i think is that first i can make full changes in array of strings and array of integers then i will push it in the index.db file which is a ggod thing
    int i=0;
    /*cout<<"Current index table is:"<<endl;
          for(int j=0;j<sstablecount;j++){
            cout<<sstable_names[j]<<" "<<sstable_sizes[j]<<endl;
          }*/
    while(i<sstablecount-1){// i have taken counter as sstablecount-1 because im checking on next one agar wo last wala hi hai to to fir bhi stop hona hai
       //abhi mera ith index wala jo hai naa wo mera current merging size wala h ......now we will start another counter that will go from ith index and find matching one
       //or we can just if next is matching that if next is not matching that any other wont match.
       /*cout<<"Current index table is:"<<endl;
          for(int j=0;j<sstablecount;j++){
            cout<<sstable_names[j]<<" "<<sstable_sizes[j]<<endl;
          }*/
       if(sstable_sizes[i]==sstable_sizes[i+1]){
            //cout<<"YES1"<<endl;
        //tab asli kaam shuru hota h
        //bas ab hum-ne kya kya krna h  wo btata hun.....
        //sbse pehle agar match hogya h to basically unhe hume merge krna by merge sort
        //aur ek compaction file bnaani hai nayi usme daalte jaana h
        //we have to maintain the compaction index file also
        //we have to delete the sstable files also
        //then we will update the index.db file
        //now we will  update sstablesize value also
        //now we will update i also.
        //*********************************************************************************************
        //first lets access the sstable_name[i] string and match with it and store the data  and apply merge sort and create new compaction file
        //first create the compaction index file
        //but me and yashasav thought there is no need to make any compaction index file but store the compaction index in RAM and make a global file for that
        //ok created a compaction index file....now lets read both the ss tables:)))).
         //now we habe to read both the ss tables and merge them
         // we can note that string and char* are interchangable
         //merge krne se pehle hum ek baar read to krle
         // but changes krne se acha vector bna deta hun ss table ke contents ka
         //ok we are almost done
         //what name can we give to it
          string s1=sstable_names[i];
          string s2=sstable_names[i+1];
          string s3=".db";
          s1=s1+s3;
          s2=s2+s3;
          string s9="table/";
          s1=s9+s1;
          s2=s9+s2;
       //cout<<"s1 and s2="<<s1<<" "<<s2<<endl;
          //now s1 and s2 contains names of ss table file names
          // now we have to read these 2 files
          // now i have to see how to read the files from ss tables s1 and s2 and we have to merge them then
          //lets read these files first
          fstream file2;
          file2.open(s1,ios::in);
          //string sstablekey1[sstable_sizes[i]];
          vector <string>sstablekey1;
          vector<int> TombStone1;
          //string sstablekey2[sstable_sizes[i+1]];
          vector <string> sstablekey2;
          //cout<<"YES:)"<<endl;;
          vector <int> TombStone2;
          vector<int> sstablevalue1;
          vector <int> sstablevalue2;
          int c;
          for(int j=0;j<26;j++){
            file2>>c;
          }
          //cout<<"YES3"<<endl;
          //bloom filters ko dekh liya read mei
          for(int j=0;j<sstable_sizes[i];j++){
                string temp;
          file2>>temp;
            sstablekey1.push_back(temp);
            int b;
            file2>>b;
            sstablevalue1.push_back(b);
            int e;
            file2>>e;
            TombStone1.push_back(e);
            //sstablekey1=(string*) realloc(sstablekey1,sizeof(string)*(j+1));
            //sstablevalue1=(int*) realloc(sstablevalue1,sizeof(int)*(j+1));
          }
          //cout<<"YES4"<<endl;
          file2.close();
          fstream file3;
          file3.open(s2,ios::in);
          for(int j=0;j<26;j++){
                int d;
            file3>>d;
          }
          for(int j=0;j<sstable_sizes[i+1];j++){
                     string temp;
          file3>>temp;
          sstablekey2.push_back(temp);
          int b;
            file3>>b;
            sstablevalue2.push_back(b);
            int e;
            file3>>e;
            TombStone2.push_back(e);
            //file3>>sstablekey2[j];
           // file3>>sstablevalue2[j];
            //sstablekey2=(string*) realloc(sstablekey2,sizeof(string)*(j+1));
            //sstablevalue2=(int*) realloc(sstablevalue2,sizeof(int)*(j+1));
          }
          file3.close();
          //cout<<"YES5"<<endl;
          //read ho gya hai ab aagya time merge ka bhai
          vector<int> sstablemergedvalues;
          vector<int> mergedTombStone;
          //ek bloom filter bhi bnaate hain yaar jo khyaal rkhega sab cheezon ka
          int bloom[26];
          for(int j=0;j<26;j++){
            bloom[j]=-1;
          }
          //cout<<"YES6"<<endl;
          //string sstablemergedkeys[sstable_sizes[i]+sstable_sizes[i+1]];
          vector <string> sstablemergedkeys;
          //merge(sstablemergedkeys,sstablekey1,sstablekey2,sstablevalue1,sstablevalue2,sstablemergedvalues,sstable_sizes[i],bloom);
          //merge(string Arr3[],string Arr1[],
					//string Arr2[],int numArr1[],int numArr2[],int numArr3[],int mergingsize,int bloom[])
          //cout<<"merging started!!"<<endl;
          int mergingsize=sstable_sizes[i];
	int m1 =mergingsize ;
	int n = mergingsize;
	//string sstablemergedkeys[m+n];
	int idx = 0;

	int i1 = 0;
	int j1 = 0;
	while (i1 < m1 && j1 < n) {
		if (isAlphabeticallySmaller(sstablekey1[i1], sstablekey2[j1])) {
			//sstablemergedkeys=(string*) realloc(sstablemergedkeys,sizeof(string)*(idx+1));
			sstablemergedkeys.push_back(sstablekey1[i1]);
			sstablemergedvalues.push_back(sstablevalue1[i1]);
            mergedTombStone.push_back(TombStone1[i1]);
			int firstCharOfArray = ParseCharToInt(sstablekey1[i1][0]);
			if(bloom[firstCharOfArray]==-1){
                bloom[firstCharOfArray]=idx;
			}

			i1++;
			idx++;
		}
		else {
            //sstablemergedkeys=(string*) realloc(sstablemergedkeys,sizeof(string)*(idx+1));
			sstablemergedkeys.push_back(sstablekey2[j1]);
			sstablemergedvalues.push_back(sstablevalue2[j1]);
            mergedTombStone.push_back(TombStone2[j1]);
			int firstCharOfArray = ParseCharToInt(sstablekey2[j1][0]);
			if(bloom[firstCharOfArray]==-1){
                bloom[firstCharOfArray]=idx;
			}

			j1++;
			idx++;
		}
	}
	while (i1 < m1) {
       // sstablemergedkeys=(string*) realloc(sstablemergedkeys,sizeof(string)*(idx+1));
		sstablemergedkeys.push_back(sstablekey1[i1]);
		sstablemergedvalues.push_back(sstablevalue1[i1]);
        mergedTombStone.push_back(TombStone1[i]);
		int firstCharOfArray = ParseCharToInt(sstablekey1[i][0]);
        if(bloom[firstCharOfArray]==-1){
            bloom[firstCharOfArray]=idx;
        }

		i1++;
		idx++;
	}
	while (j1 < n) {
        //sstablemergedkeys=(string*) realloc(sstablemergedkeys,sizeof(string)*(idx+1));
		sstablemergedkeys.push_back(sstablekey2[j1]);
		sstablemergedvalues.push_back(sstablevalue2[j1]);
        mergedTombStone.push_back(TombStone2[j1]);
		int firstCharOfArray = ParseCharToInt(sstablekey2[j1][0]);
        if(bloom[firstCharOfArray]==-1){
            bloom[firstCharOfArray]=idx;
        }

		j1++;
		idx++;
		//cout<<"merging ended"<<endl;
	}

          //cout<<"YES7"<<endl;
          //merge ho gya
          //now we have to make a new compaction file
          //int sstablemergedvalues[sstable_sizes[i]+sstable_sizes[i+1]];
          //ab mujhe nayi compaction file bnaani hai
          //usme daalna hai ye
          //and then i will write that compaction file:))))
          //lets create the compaction file
          currentcompacindex++;
          fstream file4;
          string s6="Compaction_"+ to_string(currentcompacindex);
          string s5=s6+".db";
          s5="table/"+s5;
          file4.open(s5,ios::out);
          for(int j=0;j<26;j++){
            file4<<bloom[j]<<" ";
          }
          file4<<"\n";
          for(int j=0;j<(2*sstable_sizes[i]);j++){
            file4<<sstablemergedkeys[j]<<" "<<sstablemergedvalues[j]<<" "<<mergedTombStone[j]<<"\n";
          }
          //compaction file write ho chuki hai
          file4.close();
          //now its time update our index.db file hhehe
          // we have to delete previous also remember
          sstable_names[i]=s6;
          sstable_sizes[i]=sstable_sizes[i]*2;
          //now we will shift the array
          for(int j=i+1;j<sstablecount-1;j++){
            sstable_names[j]=sstable_names[j+1];
            sstable_sizes[j]=sstable_sizes[j+1];
          }
          sstablecount--;
          int status=remove(s1.c_str());
          status=remove(s2.c_str());
          i=0;
          //cout<<"sstablecount="<<sstablecount<<endl;
          /*cout<<"Current index table is:"<<endl;
          for(int j=0;j<sstablecount;j++){
            cout<<sstable_names[j]<<" "<<sstable_sizes[j]<<endl;}*/

       }
       else{
        //agar match ni ho rha  h to hum straightaway next index pe move kr jaate hain aur fir checking start krte hain
        i++;
        //cout<<"faaltu"<<endl;
       }
    }
    //cout<<"i="<<i<<endl;
    fstream file7;
    file7.open("index.db",ios::out);
    for(int j=0;j<sstablecount;j++){
        file7<<sstable_names[j]<<" "<<sstable_sizes[j]<<"\n";
    }
    file7.close();



//baad mei yaad rkhio for loop ke baad index.db ko write bhi krna h
}
/*
int main(){
 Compaction();
return 0;
}
*/
