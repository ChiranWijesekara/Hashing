 #include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Initial values
int TABLE_SIZE = 7;

 typedef struct block{
    int value;
    bool full;
 }Block;

int hashFunction(int val,int i){
    return ((val % 7) + i*(5 - (val % 5)))%TABLE_SIZE;
}

void insert(Block *hashTable){
    int value;
    printf("Enter value: ");
    scanf("%d", &value);
    int key = hashFunction(value,0);
    int j = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (!hashTable[key].full) {
            hashTable[key].value = value;
            hashTable[key].full = true;
            break;
        } else {
            key = hashFunction(value,i+1);
        }
    }
}

void displayTable(Block* hashTable){
    printf("---------------------------\n");
    printf("HASHTABLE : \n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i].full) {
            printf("\t[%d] \t: %d\n", i, hashTable[i].value);
        } else {
            printf("\t[%d] \t: empty\n", i);
        }
    }
    printf("---------------------------\n");
}

int main(){
    Block *hashTable = (Block *)malloc(TABLE_SIZE * sizeof(Block));
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i].full = false;
    }
    int nVal = 0;
    printf("Enter number of values: ");
    scanf("%d",&nVal);
    for(int i=0;i<nVal;i++){
        insert(hashTable);
    }
    displayTable(hashTable);
    free(hashTable);
    return 0;
}