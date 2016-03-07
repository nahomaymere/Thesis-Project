//
//  abelianSquareAvoidance.c
//  Thesis project
//
//  Created by Nahom Hailu on 09/02/16.
//  Copyright (c) 2016 Nahom. All rights reserved.
//

#include "abelianSquareAvoidance.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
//nodes
typedef struct node{
    char letter;
    int key;
    struct node *nextptr;
    struct node *prev;
}word_node;
typedef word_node *word_nodePtr;

//array
typedef struct dynamicArray {
    char* word;
    int wordSize;
}String;
word_nodePtr head = NULL;
word_nodePtr last = NULL;
int the_word_size = 0;

//prototypes
void printWord();
void copyWordFromList(word_nodePtr *headptr, String *stringPtr);
void freeString(String *myString);
int isEmpty();
void insertLastNode(char letter);
void deleteLastNode();
int deltaVector_isNull(int *vectorU, int *vectorV);
void backtrack();

void read_baseWord(char *prompt){
    
    enum boo{ yes, no};
    enum boo allowlooping = yes;
    String wordFromList;
    char base_word[the_word_size + 1];
    
    while (allowlooping == yes) {
        char inp;
        printf("%s\n",prompt);
        fgets(base_word, the_word_size + 1, stdin);
        for (int i = 0; *(base_word + i) != '\0'; i++) {
            
            if(*(base_word + i) != 'a' && *(base_word + i) != 'b' && *(base_word + i) != 'c' && *(base_word +i)!= EOF && *(base_word + i) != '\n' ){
                
                allowlooping = yes;
                break;
            }
            else
                allowlooping = no;
        }
        //cleaning the input
        while ((inp = getchar()) != '\n' && inp != EOF);
    }
    
    for (int i = 0; base_word[i] != '\0';i++) {
        insertLastNode(base_word[i]);
    }
    printf("This is your string: ");
    printWord();
    if(is_abelian_square())
        printf("the word in the list has an abelian square not accepted for extending\n");
    else{
        printf("No abelian square detected this word can be extended\n");
        
    }
}
void setWordSize(char *prompt){
    
    int wordSize = 0;
    char input[3];
    char inp;
    while (1) {
        printf("%s\n", prompt);
        fgets(input, 3, stdin);
        wordSize = atoi(input);
        while ((inp = getchar()) != '\n' && inp != EOF );
        if (wordSize > 0 && wordSize < 100) {
            break;
        }
        
    }
    the_word_size = wordSize;
}

void extendWord(){
    
    char letter[] = "abc" ;
    int letterIndex = 0;
    int parik_vectorU[3];
    int parik_vectorV[3];
    int counter = 0;
    word_nodePtr tempPtr = last;
    int prevKey = 0;
    char prevLetter = ' ';
    while (tempPtr->prev->prev != NULL ) {
        prevLetter = last->letter;
        prevKey = last->key;
        insertLastNode('a');
        //printWord();

        //it should delete the last letter if it creates an abelian square in the word but if the last letter has already been deleted it will not delete the same letter again it should backtrack to more than one word
        // i need to know when
        if (last->key == prevKey && last->letter == prevLetter) {
        }
        if (is_abelian_square()) {
            backtrack();
           // printWord();
        }
        if (prevLetter == last->letter && prevKey == last->key && last->key >the_word_size){
            deleteLastNode();
            /*printf("If the word is the same ");
            printWord();*/
            switch (last->letter) {
                case 'a':
                    insertLastNode('b');
                    break;
                    
                case 'b':
                    insertLastNode('c');
                    break;
                case 'c':
                    deleteLastNode();
                    break;
            }
            /*printf("changing word ");
            printWord();*/
        }
        if (prevKey <= last->key ) {
            printf("%d and %d\n",prevKey,last->key);
            printWord();
            counter = 0;
        }
        

    }
}

int convert_letterToParikValue(char letter){
    if(letter == 'a')
        return 0;
    else if (letter == 'b') {
        return 1;
    }
    else if(letter == 'c')
        return 2;
    return -1;
}

bool is_abelian_square(){
    int parik_vectorU[3];
    int parik_vectorV[3];
    int counter = 0;
    word_nodePtr tempPtrV = last;
    word_nodePtr tempPtrU = tempPtrV->prev->prev;
    

    parik_vectorV[0] = parik_vectorV[1] = parik_vectorV [2] = 0;
    parik_vectorU[0] = parik_vectorU [1] = parik_vectorU [2] = 0;
    //loop
   while (tempPtrU != NULL && last->key > 1) {
       
        parik_vectorV[convert_letterToParikValue(tempPtrV->letter)]++;
        counter++;
        if (counter > 1) {
            tempPtrU = tempPtrV->prev;
            //seting value back to 0 befor the new loop
            parik_vectorU[0] = parik_vectorU [1] = parik_vectorU [2] = 0;
            for (int j = 0; j < counter && tempPtrU!= NULL; j++) {
                //increment an element of paric vectorU
                parik_vectorU[convert_letterToParikValue(tempPtrU->letter)]++;
                tempPtrU = tempPtrU->prev;
            }
            
           //ready for compare
           if(deltaVector_isNull(parik_vectorU, parik_vectorV))
               return true; // abelian square detected
           }
       
       //Go to next node
      // testing the values of the parik vectors
        
     /*  printf("Vector U     \t  Vector V\n");
       for (int i = 0; i < 3; i++){
           printf("%d",parik_vectorU[i]);
           printf("              \t %d",parik_vectorV[i]);
           printf("\n");
       }*/
       tempPtrV = tempPtrV->prev;
    }
    
    return false;
}

int deltaVector_isNull(int *vectorU, int *vectorV){
    
    int delta_vector[3];
    
    for (int i = 0; i < 3; i ++) {
         delta_vector[i]= vectorU[i] - vectorV[i];
        if (delta_vector[i]!= 0) {
            return 0; //vector is not null
        }
    }
    
    return 1;
}

void printWord(){
    
    word_nodePtr temPtr = head;
    while (temPtr!= NULL) {
        printf("%c",temPtr->letter);
        temPtr = temPtr->nextptr;
    }
    printf("\n");

}
void copyWordFromList(word_nodePtr *headptr, String *stringPtr){
    int counter = 0;
    stringPtr->word = (char*)malloc(sizeof(char) * (counter +1));
    word_nodePtr temptr = *headptr;
    
    do{
        stringPtr->word = (char*)realloc(stringPtr->word, sizeof(char) * (counter + 1));
        stringPtr->word[counter] = temptr->letter;
        temptr = temptr->nextptr;
        counter ++;
    }while(temptr->nextptr != NULL);
    
    stringPtr->word[counter] = '\0';
    stringPtr->wordSize = counter + 1;
}
void freeString(String *myString){
    if (myString != NULL) {
        free(myString->word);
        myString->word = NULL;
        myString->wordSize = 0;
    }
    
}
int isEmpty(){
    if (head == NULL) {
        return 1;
    }
    return 0;
}
void insertLastNode(char letter){
    word_nodePtr newPtr = malloc(sizeof(word_node));
    if (newPtr!=NULL) {
        
        newPtr->letter = letter;
        if (isEmpty()) {
            head = newPtr;
            newPtr->key = 0;
            newPtr->prev = NULL;
        }
        else{
            last->nextptr = newPtr;//connect the last node to the new node just created
            newPtr->prev = last;//connect from the new node to the last node in the list
            newPtr->key = newPtr->prev->key+ 1;
        }
        last = newPtr;
        newPtr->nextptr = NULL;

    }
    else
        printf("Memory is full");
}
void deleteLastNode(){
    word_nodePtr tempPtr = last;
    //if only one link
    if(head->nextptr == NULL)
        head = NULL;// delete the node
    else{
        //set
        last->prev->nextptr = NULL;//cuting the connection from the current last node to the previous node
    }
    last = last->prev; //setting the previous element as the last element
    free(tempPtr);//free space
}
void backtrack(){
    while(last->key > the_word_size && is_abelian_square()) {
        printf("In backtrack ");
        printWord();
        switch (last->letter) {
            case 'a':
                deleteLastNode();
                insertLastNode('b');
                break;
                
            case 'b':
                deleteLastNode();
                insertLastNode('c');
                break;
            case 'c':
                deleteLastNode();
                break;
        }
        
    }
}
