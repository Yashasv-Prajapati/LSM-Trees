# LSM Trees 
This is the readme file of CS201 project of year 2022.
The team members are - 
1. Arnav Kharbanda (2021CSB1072)
2. Gopal Bansal (2021CSB1089)
3. Yashasav Prajapati (2021CSB1143)

##### This project is under the mentorship of Ms. Akansha_

LSM trees are used in several NoSQL databases. LSM-tree has a higher storage space usage efficiency than B-Trees. The main reason why LSM provides high write throughput is that every write request is actually performed only “in-memory” in contrast to traditional B-Tree based implementation where the updates are done to disk which can trigger an update to an index making it very expensive.

# Instructions to run the program


Before running the final program, you need to make a testcase file, and for that, you need to run `testcase.py` 
To run that, use the command
``` sh
python3 testcase.py
```

This will create a file named `TestCase.txt`

-----------------------------------------------
There are several files, the file to run is `main.cpp`. 
The file can be run using the command 
``` sh
g++ main.cpp rbtree.cpp compaction.cpp read.cpp -lm -pthread
```
This will create a file `a.out`, and it can executed using the command
``` sh
./a.out
```

After execution of this file, you will see three options
1. Insert(predefined input)
2. Search
3. Delete

These are the 3 operations available. You first have to insert the data, so for that select `Insert` which will automatically start inserting the data from the testcase file generated using the python code.

Now the insertion will take time as it is writing, flushing and merging data in the background while the program is running. 
After insertion is done, the folder `table` will contain several compaction files, which have been formed after merging several SSTables.

Now the search and delete operation can be performed easily. 


