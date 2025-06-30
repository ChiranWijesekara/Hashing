#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Initial values
int TABLE_SIZE = 7;
float load_factor = 0;


 typedef struct block{
    int value;
    bool full;
 }Block;


void rehashing(Block** hashTable){
    TABLE_SIZE *= 2;
    printf("Rehashing...\n");
    *hashTable = (Block*)realloc(*hashTable, TABLE_SIZE * sizeof(Block));
    for (int i = TABLE_SIZE / 2; i < TABLE_SIZE; i++) {
        (*hashTable)[i].full = false;
    }
    load_factor = (load_factor*(TABLE_SIZE/2))/TABLE_SIZE;
    // printf("New table size: %d\n", TABLE_SIZE);
}

int hashFunction(int val){
    return val % TABLE_SIZE;
}

void insert(Block *hashTable){
    int value;
    printf("Enter value: ");
    scanf("%d", &value);
    int key = hashFunction(value);
    int j = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (!hashTable[key].full) {
            hashTable[key].value = value;
            hashTable[key].full = true;
            load_factor = (load_factor * TABLE_SIZE + 1) / TABLE_SIZE;
            break;
        } else {
            key = (key + (++j) * (++j)) % TABLE_SIZE;
        }
    }

    if (load_factor >= 0.7) {
        rehashing(&hashTable);
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