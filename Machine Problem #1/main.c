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
    Board SlidingBoard_1;
    CreateRandomBoard(&SlidingBoard_1, 10);
    if (CalculateInversions(&SlidingBoard_1)) {
        printf("\nGame Board:\n");
        PrintGameBoard(&SlidingBoard_1);
        AStarSearch(&SlidingBoard_1);
    }
    Board SlidingBoard_2;
    CreateRandomBoard(&SlidingBoard_2, 11);
    if (CalculateInversions(&SlidingBoard_2)) {
        printf("\nGame Board:\n");
        PrintGameBoard(&SlidingBoard_2);
        AStarSearch(&SlidingBoard_2);
    }
    Board SlidingBoard_3;
    CreateRandomBoard(&SlidingBoard_3, 12);
    if (CalculateInversions(&SlidingBoard_3)) {
        printf("\nGame Board:\n");
        PrintGameBoard(&SlidingBoard_3);
        AStarSearch(&SlidingBoard_3);
    }
    return 0;
}

