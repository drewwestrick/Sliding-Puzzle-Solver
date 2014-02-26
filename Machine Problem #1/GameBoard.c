//
//  GameBoard.c
//  Machine Problem #1
//
//  Created by Andrew Westrick on 2/26/14.
//  Copyright (c) 2014 Andrew Westrick. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "GameBoard.h"

void CreateRandomBoard(Tile *PuzzleBoard) {
    int rnum;
    int i,j,row,col;
    int NumArray[9] = {-1,-1,-1,-1,-1,-1,-1,-1};
    int size = 1;
    NumArray[0] = rand()%9;
    for (row=0;row<3;row++) {
        for (col=0;col<3;col++) {
            for (i=1;i<9;i++) {
                rnum = rand()%9;
                for (j=0;j<size;j++) {
                    if (NumArray[j]==rnum) {
                        rnum = rand()%9;
                        j=0;
                    }
                }
                PuzzleBoard[row*2+col].GoalDistance = 0;
                PuzzleBoard[row*2+col].Xposition = 0;
                PuzzleBoard[row*2+col].Yposition = 0;
                PuzzleBoard[row*2+col].Value = rnum;
                size++;
                i++;
            }
            col++;
        }
        row++;
    }
    printf("%d %d %d\n%d %d %d\n%d %d %d\n",PuzzleBoard[0].Value,PuzzleBoard[1].Value,PuzzleBoard[2].Value,PuzzleBoard[3].Value,PuzzleBoard[4].Value,PuzzleBoard[5].Value,PuzzleBoard[6].Value,PuzzleBoard[7].Value,PuzzleBoard[8].Value);
}