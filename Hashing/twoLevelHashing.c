#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define PRIMARY_SIZE 10

typedef struct {
    int *table;
    int size;
    int a, b;
} SecondryHashTable;

typedef struct {
    SecondryHashTable slots[PRIMARY_SIZE];
} TwoLevelHashTable;

int firstHash(int key){
    return key % PRIMARY_SIZE;
}

int secondHash(int key, int a, int b, int size){
    return ((a * key + b) % size);
}

int getRandom(int min, int max){
    return min + rand() % (max - min + 1);
}

void initializeTable(TwoLevelHashTable *hashTable){
    for (int i = 0; i < PRIMARY_SIZE; i++){
        hashTable->slots[i].table = NULL;
        hashTable->slots[i].size = 0;
        hashTable->slots[i].a = 0;
        hashTable->slots[i].b = 0;
    }
}

void buildHashTable(TwoLevelHashTable *hashTable, int keys[], int n){
    int collisions[PRIMARY_SIZE] = {0};

    for (int i = 0; i < n; i++){
        int index = firstHash(keys[i]);
        collisions[index]++;
    }

    for (int i = 0; i < PRIMARY_SIZE; i++){
        if (collisions[i] > 0){
            hashTable->slots[i].size = collisions[i] * collisions[i];
            hashTable->slots[i].table = (int*)malloc(hashTable->slots[i].size * sizeof(int));
            for (int j = 0; j < hashTable->slots[i].size; j++){
                hashTable->slots[i].table[j] = -1;
            }

            bool valid = false;
            while(!valid){
                hashTable->slots[i].a = getRandom(1, 100);
                hashTable->slots[i].b = getRandom(0, 100);

                int usedIndicates[hashTable->slots[i].size];
                for (int j=0;j<hashTable->slots[i].size;j++){
                    usedIndicates[j] = -1;
                }
                valid = true;

                for (int j=0;j<n;j++){
                    if (firstHash(keys[j]) == i){
                        int subIndex = secondHash(keys[j],hashTable->slots[i].a,hashTable->slots[i].b,hashTable->slots[i].size);

                        if (usedIndicates[subIndex] != -1){
                            valid = false;
                            break;
                        }
                        usedIndicates[subIndex] = keys[j];
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++){
        int index = firstHash(keys[i]);

        int subSize = hashTable->slots[index].size;
        int subIndex = secondHash(keys[i], hashTable->slots[index].a, hashTable->slots[index].b, subSize);
        hashTable->slots[index].table[subIndex] = keys[i];
    }
}

void displayTable(TwoLevelHashTable *hashTable){
    printf("HASHTABLE:\n");
    for (int i = 0; i < PRIMARY_SIZE; i++){
        printf("\t[%d]: ", i);
        if (hashTable->slots[i].size > 0){
            printf("{");
            for (int j = 0; j < hashTable->slots[i].size; j++){
                if (hashTable->slots[i].table[j] != -1) {
                    printf("%d", hashTable->slots[i].table[j]);
                } else {
                    printf("empty");
                }
                if (j < hashTable->slots[i].size - 1) {
                    printf(", ");
                }
            }
            printf("}");
        }
        printf("\n");
    }
}

int main(){
    srand(time(NULL));
    int keys[] = {12, 44, 13, 88, 23, 94, 11, 39, 20, 16};
    int n = sizeof(keys) / sizeof(keys[0]);
    TwoLevelHashTable hashtable;
    initializeTable(&hashtable);
    buildHashTable(&hashtable, keys, n);
    displayTable(&hashtable);
    return 0;
}