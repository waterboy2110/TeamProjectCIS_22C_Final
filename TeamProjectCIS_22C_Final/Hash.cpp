//
//  Hash.cpp
//  Project
//
//  Created by Christina Sok on 3/9/14.
//  Copyright (c) 2014 Christina Sok. All rights reserved.
//

#include "Hash.h"
#include <stdio.h>
#include <stdlib.h>

//**************************************************************************************************
// Definition of hashFunction
//
//**************************************************************************************************
int hashTable::hashFunction(int tNum)
{
    int sum = 0;
    
    // Convert street number to a string
    //char *intStr = itoa(tNum);
    string str = to_string(tNum);
    
    // Convert street number string to a c-string
    char cstr[str.length()+1];
    strcpy(cstr, str.c_str());
    
    // Add each integer in street number
    for (int i = 0; i <= str.length(); i++)
    {
        sum += cstr[i];
    }
    
    // Divide the sum of each integer by the number of integers
    // in the string.
    return sum/str.length();
}