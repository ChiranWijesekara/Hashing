#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Initial values
int TABLE_SIZE = 7;

typedef struct block{
    int value;
    struct block *next;
} Block;

Block** hashTable = NULL;

int hashFunction(int val){
    return val % TABLE_SIZE;
}

Block* createNode(int val){
    Block* newBlock = (Block*)malloc(sizeof(Block));
    newBlock->value = val;
    newBlock->next = NULL;
    return newBlock;
}

void insert(){
    int value;
    printf("Enter value: ");
    scanf("%d", &value);
    int key = hashFunction(value);
    if (hashTable[key] == NULL){
        hashTable[key] = createNode(value);
        return;
    }
    if (hashTable[key] != NULL){
        Block* current = NULL;
        for(current = hashTable[key]; current->next != NULL; current = current->next);
        current->next = createNode(value);
    }
}

void delete(){
    int value;
    printf("Enter value to be deleted: ");
    scanf("%d", &value);
    int key = hashFunction(value);
    if (hashTable[key] == NULL){
        printf("SLOT IS EMPTY!\n");
        return;
    }
    Block *current = hashTable[key];
    Block *prev = NULL;
    while (current != NULL && current->value != value) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Value not found!\n");
        return;
    }
    if (prev == NULL) {
        hashTable[key] = current->next;
    } else {
        prev->next = current->next;
    }
    free(current);
}

void search(){
    int value;
    printf("Enter value to be searched: ");
    scanf("%d", &value);
    int key = hashFunction(value);
    if (hashTable[key] == NULL){
        printf("SLOT IS EMPTY!\n");
        return;
    }
    Block *current = hashTable[key];
    while (current != NULL && current->value != value) {
        current = current->next;
    }
    if (current != NULL) {
        printf("Value found!\n");
    } else {
        printf("Value not found!\n");
    }
}

void displayTable(){
    printf("HASHTABLE:\n");
    for(int i = 0; i < TABLE_SIZE; i++){
        printf("\t[%d]: ", i);
        for (Block* current = hashTable[i]; current != NULL; current = current->next){
            printf("%d -> ", current->value);
        }
        printf("NULL\n");
    }
}

int main(){
    printf("Enter table size: ");
    scanf("%d", &TABLE_SIZE);
    hashTable = (Block**)malloc(TABLE_SIZE * sizeof(Block*));

    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }

    int choice = 0;
    while(1){
        printf("MAIN MENU\n");
        printf("\t1-> Insert\n");
        printf("\t2-> Delete\n");
        printf("\t3-> Search\n");
        printf("\t4-> Display\n");
        printf("\t5-> Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice){
            case 1: insert(); break;
            case 2: delete(); break;
            case 3: search(); break;
            case 4: displayTable(); break;
            case 5: goto out;
            default: printf("Invalid choice!\n");
        }
    }
out:
    // displayTable();
    for (int i = 0; i < TABLE_SIZE; i++) {
        Block* current = hashTable[i];
        while (current != NULL) {
            Block* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(hashTable);
    return 0;
}