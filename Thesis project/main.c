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
    is_abelian_square();
    extendWord();
    /*if (!is_abelian_square()) {
        extendWord();
    }*/
    return 0;
}
