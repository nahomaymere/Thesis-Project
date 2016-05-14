//
//  abelianSquareAvoidance.h
//  Thesis project
//
//  Created by Nahom Hailu on 09/02/16.
//  Copyright (c) 2016 Nahom. All rights reserved.
//

#ifndef __Thesis_project__abelianSquareAvoidance__
#define __Thesis_project__abelianSquareAvoidance__

#include <stdio.h>
#include <stdbool.h>

void setWordSize(char *prompt);
void read_baseWord(char *prompt);
void read_vectorsToAvoid(char* prompt);
void set_Number_of_vectors();
char * extend_base_word(char *baseWord, int size);
int convert_letterToParikValue(char letter);
bool is_abelian_square();
void extendWord();

#endif /* defined(__Thesis_project__abelianSquareAvoidance__) */
