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
    Board SlidingBoard;
    CreateRandomBoard(&SlidingBoard, 15);
    if (CalculateInversions(&SlidingBoard)) {
        printf("\nGame Board:\n");
        PrintGameBoard(&SlidingBoard);
        AStarSearch(&SlidingBoard);
    }
    CreateRandomBoard(&SlidingBoard, 21);
    if (CalculateInversions(&SlidingBoard)) {
        printf("\nGame Board:\n");
        PrintGameBoard(&SlidingBoard);
        AStarSearch(&SlidingBoard);
    }
    CreateRandomBoard(&SlidingBoard, 12);
    if (CalculateInversions(&SlidingBoard)) {
        printf("\nGame Board:\n");
        PrintGameBoard(&SlidingBoard);
        AStarSearch(&SlidingBoard);
    }
    return 0;
}

