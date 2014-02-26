//
//  main.c
//  Machine Problem #1
//
//  Created by Andrew Westrick on 2/26/14.
//  Copyright (c) 2014 Andrew Westrick. All rights reserved.
//

#include <stdio.h>
#include "GameBoard.h"

int main(int argc, const char * argv[])
{
    CreateRandomBoard(&SlidingBoard);
    PrintGameBoard(&SlidingBoard);
    PrintBoardDistance(&SlidingBoard);
    
    CreateGoalBoard(&SlidingBoard);
    PrintGameBoard(&SlidingBoard);
    return 0;
}

