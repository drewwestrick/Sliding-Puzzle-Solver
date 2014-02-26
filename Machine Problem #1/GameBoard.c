//
//  GameBoard.c
//  Machine Problem #1
//
//  Created by Andrew Westrick on 2/26/14.
//  Copyright (c) 2014 Andrew Westrick. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "GameBoard.h"

void CreateRandomBoard(Board *SlidingBoard) {
    Tile *Tiles = SlidingBoard->Tiles;
    SlidingBoard->TotalDistance = 0;
    SlidingBoard->Inversions = 0;
    int rnum;
    int i,j;
    int row = 0;
    int col = 0;
    for (i=0;i<9;i++) {
        Tiles[i].Value = -1;
    }
    srand(time(0));
    for (row=0;row<3;row++) {
        for (col=0;col<3;col++) {
            rnum = rand()%9;
            j=0;
            while(j<(row*3+col)) {
                if (Tiles[j].Value==rnum) {
                    rnum = rand()%9;
                    j=0;
                }
                else {
                    j++;
                }
            }
            Tiles[row*3+col].Value = rnum;
            Tiles[row*3+col].Xposition = col;
            Tiles[row*3+col].Yposition = row;
            if (rnum>0) {
                Tiles[row*3+col].GoalDistance = abs(Tiles[row*3+col].Xposition-((rnum-1)%3))+abs(Tiles[row*3+col].Yposition-floor(((float)rnum-1)/(float)3));
            }
            else {
                Tiles[row*3+col].GoalDistance = abs((2-Tiles[row*3+col].Xposition)+(2-Tiles[row*3+col].Yposition));
            }
            SlidingBoard->TotalDistance += Tiles[row*3+col].GoalDistance;
        }
    }
}

void PrintGameBoard(Board *SlidingBoard) {
    Tile *Tiles = SlidingBoard->Tiles;
    printf("%d %d %d\n%d %d %d\n%d %d %d\n\n",Tiles[0].Value,Tiles[1].Value,Tiles[2].Value,Tiles[3].Value,Tiles[4].Value,Tiles[5].Value,Tiles[6].Value,Tiles[7].Value,Tiles[8].Value);
}

void PrintBoardDistance(Board *SlidingBoard) {
    Tile *Tiles = SlidingBoard->Tiles;
    printf("%d %d %d\n%d %d %d\n%d %d %d\n\n",Tiles[0].GoalDistance,Tiles[1].GoalDistance,Tiles[2].GoalDistance,Tiles[3].GoalDistance,Tiles[4].GoalDistance,Tiles[5].GoalDistance,Tiles[6].GoalDistance,Tiles[7].GoalDistance,Tiles[8].GoalDistance);
    printf("Total Distance: %d\n\n", SlidingBoard->TotalDistance);
}

void CreateGoalBoard(Board *SlidingBoard) {
    Tile *Tiles = SlidingBoard->Tiles;
    int row=0;
    int col=0;
    int rnum;
    for (row=0;row<3;row++) {
        for (col=0;col<3;col++) {
            rnum = row*3+col+1;
            if (rnum<9) {
                Tiles[row*3+col].Value = rnum;
            }
            else {
                Tiles[row*3+col].Value = 0;
            }
            Tiles[row*3+col].Xposition = col;
            Tiles[row*3+col].Yposition = row;
            if (rnum>0) {
                Tiles[row*3+col].GoalDistance = (((rnum-1)%3)-Tiles[row*3+col].Xposition);
            }
            else {
                Tiles[row*3+col].GoalDistance = (2-Tiles[row*3+col].Xposition)+(2-Tiles[row*3+col].Yposition);
            }
        }
    }
}


