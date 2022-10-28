// which data type to use in making the SSTables, here instead of Sorted Strings, we are considering sorted integers
typedef int keyType; 
typedef int valType;

typedef struct TableElement{
    keyType key;
    valType val;
} TableElement;

typedef struct LSMTree{
    int flushLimit;

} LSMTree;
