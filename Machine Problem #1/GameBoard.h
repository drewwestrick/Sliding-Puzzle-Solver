//
//  GameBoard.h
//  Machine Problem #1
//
//  Created by Andrew Westrick on 2/26/14.
//  Copyright (c) 2014 Andrew Westrick. All rights reserved.
//

#ifndef Machine_Problem__1_GameBoard_h
#define Machine_Problem__1_GameBoard_h

#define COL 3
#define ROW 3

typedef struct {
    int Value;
    int Xposition;
    int Yposition;
    int GoalDistance;
} Tile;

typedef struct {
    Tile Tiles[9];
    int Inversions;
    int TotalDistance;
} Board;

Board SlidingBoard;

void CreateRandomBoard(Board *SlidingBoard);
void PrintGameBoard(Board *SlidingBoard);
void CreateGoalBoard(Board *SlidingBoard);
void PrintBoardDistance(Board *SlidingBoard);


#endif
