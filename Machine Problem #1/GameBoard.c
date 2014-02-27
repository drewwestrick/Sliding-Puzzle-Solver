//
//  GameBoard.c
//  Machine Problem #1
//
//  Created by Andrew Westrick on 2/26/14.
//  Copyright (c) 2014 Andrew Westrick. All rights reserved.
//

#include "GameBoard.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

/* Create a random puzzle */
void CreateRandomBoard(Board *SlidingBoard) {
    Tile *Tiles = SlidingBoard->Tiles;
    SlidingBoard->TotalDistance = 0;
    SlidingBoard->Inversions = 0;
    int rnum;
    int i,j;
    int Row = 0;
    int Col = 0;
    for (i=0;i<9;i++) {
        Tiles[i].Value = -1;
    }
    //srand((unsigned int)time(0));
    srand(10);
    for (Row=0;Row<3;Row++) {
        for (Col=0;Col<3;Col++) {
            rnum = rand()%9;
            j=0;
            while(j<(Row*3+Col)) {
                if (Tiles[j].Value==rnum) {
                    rnum = rand()%9;
                    j=0;
                }
                else {
                    j++;
                }
            }
            Tiles[Row*3+Col].Value = rnum;
            Tiles[Row*3+Col].Xposition = Col;
            Tiles[Row*3+Col].Yposition = Row;
            if (rnum>0) {
                Tiles[Row*3+Col].GoalDistance = abs(Tiles[Row*3+Col].Xposition-((rnum-1)%3))+abs(Tiles[Row*3+Col].Yposition-floor(((float)rnum-1)/(float)3));
            }
            else {
                Tiles[Row*3+Col].GoalDistance = abs((2-Tiles[Row*3+Col].Xposition)+(2-Tiles[Row*3+Col].Yposition));
                SlidingBoard->SpacePosition = Row*3+Col;
            }
            SlidingBoard->TotalDistance += Tiles[Row*3+Col].GoalDistance;
        }
    }
}

/* Display the puzzle board */
void PrintGameBoard(Board *SlidingBoard) {
    Tile *Tiles = SlidingBoard->Tiles;
    printf("\n%d %d %d\n%d %d %d\n%d %d %d\n\n",Tiles[0].Value,Tiles[1].Value,Tiles[2].Value,Tiles[3].Value,Tiles[4].Value,Tiles[5].Value,Tiles[6].Value,Tiles[7].Value,Tiles[8].Value);
}

/* Display the distance of each tile from the goal position */
void PrintBoardDistance(Board *SlidingBoardLocal) {
    Tile *Tiles = SlidingBoardLocal->Tiles;
    printf("\n%d %d %d\n%d %d %d\n%d %d %d\n\n",Tiles[0].GoalDistance,Tiles[1].GoalDistance,Tiles[2].GoalDistance,Tiles[3].GoalDistance,Tiles[4].GoalDistance,Tiles[5].GoalDistance,Tiles[6].GoalDistance,Tiles[7].GoalDistance,Tiles[8].GoalDistance);
    printf("Total Distance: %d\n", SlidingBoardLocal->TotalDistance);
    printf("Total Inversions: %d\n", SlidingBoardLocal->Inversions);
    printf("Solveable?: %d\n\n", SlidingBoardLocal->isSolvable);
}

/* Create a goal board for reference */
void CreateGoalBoard(Board *SlidingBoard) {
    Tile *Tiles = SlidingBoard->Tiles;
    int Row=0;
    int Col=0;
    int rnum;
    for (Row=0;Row<3;Row++) {
        for (Col=0;Col<3;Col++) {
            rnum = Row*3+Col+1;
            if (rnum<9) {
                Tiles[Row*3+Col].Value = rnum;
            }
            else {
                Tiles[Row*3+Col].Value = 0;
            }
            Tiles[Row*3+Col].Xposition = Col;
            Tiles[Row*3+Col].Yposition = Row;
            /* Calculate the distance to goal state */
            CalculateDistance(Tiles, Row, Col, rnum);
        }
    }
}

void GotoNextState(Board *SlidingBoard) {
    Tile *Tiles = SlidingBoard->Tiles;
    Tile temp;
    Board SlidingBoardRight;
    Board SlidingBoardLeft;
    Board SlidingBoardTop;
    Board SlidingBoardBtm;
    Tile *TilesRight;
    Tile *TilesLeft;
    Tile *TilesTop;
    Tile *TilesBtm;
    switch (Tiles[SlidingBoard->SpacePosition].Xposition) {
        case 0:
            memcpy(&SlidingBoardLeft, SlidingBoard, sizeof(SlidingBoardLeft));
            TilesLeft = SlidingBoardLeft.Tiles;
            temp = TilesLeft[SlidingBoard->SpacePosition];
            TilesLeft[SlidingBoard->SpacePosition] = TilesLeft[(SlidingBoard->SpacePosition)-1];
            TilesLeft[(SlidingBoard->SpacePosition)-1] = temp;
            PrintGameBoard(&SlidingBoardLeft);
            break;
        case 1:
            memcpy(&SlidingBoardRight, SlidingBoard, sizeof(SlidingBoardRight));
            memcpy(&SlidingBoardLeft, SlidingBoard, sizeof(SlidingBoardLeft));
            TilesRight = SlidingBoardRight.Tiles;
            TilesLeft = SlidingBoardLeft.Tiles;
            /* Move Space Right */
            temp = TilesRight[SlidingBoard->SpacePosition];
            TilesRight[SlidingBoard->SpacePosition] = TilesRight[(SlidingBoard->SpacePosition)+1];
            TilesRight[(SlidingBoard->SpacePosition)+1] = temp;
            PrintGameBoard(&SlidingBoardRight);
            /* Move Space Left */
            temp = TilesLeft[SlidingBoard->SpacePosition];
            TilesLeft[SlidingBoard->SpacePosition] = TilesLeft[(SlidingBoard->SpacePosition)-1];
            TilesLeft[(SlidingBoard->SpacePosition)-1] = temp;
            PrintGameBoard(&SlidingBoardLeft);
            break;
        case 2:
            memcpy(&SlidingBoardRight, SlidingBoard, sizeof(SlidingBoardRight));
            TilesRight = SlidingBoardRight.Tiles;
            /* Move Space Right */
            temp = TilesRight[SlidingBoard->SpacePosition];
            TilesRight[SlidingBoard->SpacePosition] = TilesRight[(SlidingBoard->SpacePosition)+1];
            TilesRight[(SlidingBoard->SpacePosition)+1] = temp;
            PrintGameBoard(&SlidingBoardRight);
            break;
    }
    switch (Tiles[SlidingBoard->SpacePosition].Yposition) {
        case 0:
            memcpy(&SlidingBoardTop, SlidingBoard, sizeof(SlidingBoardTop));
            TilesTop = SlidingBoardTop.Tiles;
            temp = TilesTop[SlidingBoard->SpacePosition];
            TilesTop[SlidingBoard->SpacePosition] = TilesTop[(SlidingBoard->SpacePosition)+3];
            TilesTop[(SlidingBoard->SpacePosition)+3] = temp;
            PrintGameBoard(&SlidingBoardTop);
            break;
        case 1:
            memcpy(&SlidingBoardTop, SlidingBoard, sizeof(SlidingBoardTop));
            memcpy(&SlidingBoardBtm, SlidingBoard, sizeof(SlidingBoardBtm));
            TilesTop = SlidingBoardTop.Tiles;
            TilesBtm = SlidingBoardBtm.Tiles;
            /* Move Space Right */
            temp = TilesTop[SlidingBoard->SpacePosition];
            TilesTop[SlidingBoard->SpacePosition] = TilesTop[(SlidingBoard->SpacePosition)+3];
            TilesTop[(SlidingBoard->SpacePosition)+3] = temp;
            PrintGameBoard(&SlidingBoardTop);
            /* Move Space Left */
            temp = TilesBtm[SlidingBoard->SpacePosition];
            TilesBtm[SlidingBoard->SpacePosition] = TilesBtm[(SlidingBoard->SpacePosition)-3];
            TilesBtm[(SlidingBoard->SpacePosition)-3] = temp;
            PrintGameBoard(&SlidingBoardBtm);
            break;
        case 2:
            memcpy(&SlidingBoardBtm, SlidingBoard, sizeof(SlidingBoardBtm));
            TilesBtm = SlidingBoardBtm.Tiles;
            temp = TilesBtm[SlidingBoard->SpacePosition];
            TilesBtm[SlidingBoard->SpacePosition] = TilesBtm[(SlidingBoard->SpacePosition)-3];
            TilesBtm[(SlidingBoard->SpacePosition)-3] = temp;
            PrintGameBoard(&SlidingBoardBtm);
            break;
    }
}

/* Calculate the number of inversion to see if the puzzle is solveable */
void CalculateInversions(Board *SlidingBoard) {
    Tile *Tiles = SlidingBoard->Tiles;
    int i;
    int Row = 0;
    int Col = 0;
    for (Row=0;Row<3;Row++) {
        for (Col=0;Col<3;Col++) {
            for(i=Row*3+Col;i<9;i++) {
                if ((Tiles[Row*3+Col].Value>Tiles[i].Value) && (Tiles[i].Value!=0) && (Tiles[Row*3+Col].Value!=0)) {
                    SlidingBoard->Inversions++;
                }
            }
        }
    }
    SlidingBoard->isSolvable = !(SlidingBoard->Inversions % 2);
    if(SlidingBoard->isSolvable) {
        printf("Board is solvable...\n");
    }
    else {
        printf("Board is NOT solvable...\n");
    }
}

void CalculateDistance(Tile *Tiles, int Row, int Col, int Value) {
    if (Value>0) {
        Tiles[Row*3+Col].GoalDistance = (((Value-1)%3)-Tiles[Row*3+Col].Xposition);
    }
    else {
        Tiles[Row*3+Col].GoalDistance = (2-Tiles[Row*3+Col].Xposition)+(2-Tiles[Row*3+Col].Yposition);
    }
}

