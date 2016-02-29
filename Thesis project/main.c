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
    
    int wordSize = getWordSize("Enter the number of letters of your base word");
    char word[wordSize + 1 ];
    
    read_baseWord("Enter the base word", word,wordSize);
    is_abelian_square();
    /*if (!is_abelian_square()) {
        extendWord();
    }*/
    return 0;
}
