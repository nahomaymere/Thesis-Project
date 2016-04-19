//
//  main.c
//  Thesis project
//
//  Created by Nahom Hailu on 03/02/16.
//  Copyright (c) 2016 Nahom. All rights reserved.
//


#include "abelianSquareAvoidance.h"
#include <stdio.h>

int main(){

    setWordSize("Enter the number of letters of your base word");
    read_baseWord("Enter the base word");
    
    if(is_abelian_square())
        printf("the word in the list has an abelian square it is not accepted for extending\n");
    else{
        printf("No abelian square detected this word can be extended\n");
        extendWord();
    }
    return 0;
}
