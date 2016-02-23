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
//nodes
typedef struct node{
    char letter;
    struct node *nextptr;
}word_node;
typedef word_node *word_nodePtr;

//array
typedef struct dynamicArray {
    char* word;
    int wordSize;
}String;

//prototypes
void extendWord(word_nodePtr *headptr);
void push(word_nodePtr *headptr,char data);
void pop(word_nodePtr *headptr);
void printWord(String *wordFromList, word_nodePtr *headptr);
void copyWordFromList(word_nodePtr *headptr, String *stringPtr);
void freeString(String *myString);

void read_baseWord(char *prompt, char *base_word, int word_size){
    
    enum boo{ yes, no};
    enum boo allowlooping = yes;
    String wordFromList;
    word_nodePtr startptr = NULL;
    
    push(&startptr, ' ');

    while (allowlooping == yes) {
        
        printf("%s\n",prompt);
        fgets(base_word, word_size + 1, stdin);
        for (int i = 0; *(base_word + i) != '\0'; i++) {
            if(*(base_word + i) != 'a' && *(base_word + i) != 'b' && *(base_word + i) != 'c' && *(base_word +i)!= EOF && *(base_word + i) != '\n' ){
                
                allowlooping = yes;
                printf("because of %c is not\n", *(base_word + i));
                break;
            }
            else
                allowlooping = no;
        }
        
        for (int i = 0; base_word[i] != '\0';i++) {
            push(&startptr, base_word[i]);
        }
       
    }
    
    printf("This is your string: %s\n", base_word);
    extendWord(&startptr);
   
    
}
int getWordSize(char *prompt){
    
    int wordSize = 0;
    char input[3];
    char inp;
    while (1) {
        printf("%s\n", prompt);
        fgets(input, 3, stdin);
        wordSize = atoi(input);
        while ((inp = getchar()) != '\n' && inp != EOF );
        if (wordSize > 0 && wordSize < 10) {
            break;
        }
        
    }
    return wordSize;
}

void extendWord(word_nodePtr *headptr){
    
    char letter[] = "abc" ;
    int letterIndex = 0;
    String aWord;
    word_nodePtr tempPtr = *headptr;
   /* while (tempPtr->nextptr!=NULL) {
        //take the list content and put it in to string
        copyWordFromList(&tempPtr, &aWord);
        if (is_abelian_square(aWord.word, aWord.wordSize)){
            *headptr = tempPtr;
            pop(&tempPtr);
            if (letterIndex < 2) {
                letterIndex++;
                copyWordFromList(headptr, &aWord);
            }
            else{
                *headptr = tempPtr;
                pop(&tempPtr);
                letterIndex = 0;
            // here it should pop one letter and then continue to search for the other possiblities
            }
        }
        //if it has no abelian square
        
        printWord(&aWord, headptr);
        //add letter a to the word
        *headptr = tempPtr;
        push(&tempPtr, letter[letterIndex]);
        tempPtr = tempPtr->nextptr;
        
    }*/
    copyWordFromList(&tempPtr, &aWord);
    while (tempPtr->nextptr!=NULL) {
        if (is_abelian_square(aWord.word, aWord.wordSize)) {
            *headptr = tempPtr;
            pop(&tempPtr);
            copyWordFromList(&tempPtr, &aWord);
        }
        printWord(&aWord, &tempPtr);
        *headptr = tempPtr;
        push(&tempPtr, letter[letterIndex]);
        copyWordFromList(&tempPtr, &aWord);
    }
    
    
}

 char * extend_base_word(char *baseWord, int size){
     
    char *alphabet = "abc";
    word_nodePtr topPtr;
    int indexofnewletters = 0;
    char newletter;
    baseWord = (char*)malloc(size *(sizeof(char)));
 
    while (is_abelian_square(baseWord,size) == 0) {
        push(&topPtr,newletter);
        if (indexofnewletters > 2 ) {
            indexofnewletters = 0;
        }
    }
    char myString[size];
    for (int i = 0; i <  size; i++) {
         myString[i] = *(baseWord + i); // copying data from one array to the second one
    }
    
    free(baseWord);
    baseWord = NULL;
     
    return myString;
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

int is_abelian_square(char *word,int word_size){
    int parik_vectorU[3];
    int parik_vectorV[3];
    for (int i = 0; i < 3; i++) {
        parik_vectorU[i] = 0;
        parik_vectorV[i] = 0;
    }
    
    //loop
    for (int i = 1; i <= word_size / 2 ; i++) {
        
        parik_vectorV[convert_letterToParikValue(word[word_size -i])]++;
        for (int j = 2; j < i + 1; j++) {
            parik_vectorU[convert_letterToParikValue(word[word_size - i - j])]++;

        }
        //ready for compare
        if(deltaVector_isNull(parik_vectorU, parik_vectorV))
            return 1; // abelian square detected
    }
   
    for (int i = 0; i < 3; i++){
        printf("%d",parik_vectorU[i]);
        printf("              \t %d",parik_vectorV[i]);
        printf("\n");
    }
    
    return 0;
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

void push(word_nodePtr *headptr,char data){
    //we create a new pointer to allocate a memory space for creating a new node
    word_nodePtr newPtr = malloc(sizeof(word_node));
    if (newPtr != NULL) {
        //we put our data in
        newPtr->letter = data;
        //then we link the node down to the previous node
        newPtr->nextptr = *headptr;
        //now we put headptr to point to the new node
        *headptr = newPtr;
    }
    else
        printf("Error not enough memory available");
}

void pop(word_nodePtr *headptr){
    //we create tempPtr because we don t want to delete headptr
    word_nodePtr tempPtr;
    //we make temPtr to point to the last node
    tempPtr = *headptr;
    *headptr = (*headptr)->nextptr;
    free(tempPtr);
}


void printWord(String *wordFromList, word_nodePtr *headptr){
    
    printf("This is your list content\n");
    for (int i = wordFromList->wordSize - 1 ; i > -1 ; i--) {
        printf("%c",wordFromList->word[i]);
    }
    printf("\n");
    //once used the memory is freed
    freeString(wordFromList);
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

