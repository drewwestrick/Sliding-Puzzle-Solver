//
//  GameBoard.h
//  Machine Problem #1
//
//  Created by Andrew Westrick on 2/26/14.
//  Copyright (c) 2014 Andrew Westrick. All rights reserved.
//

#ifndef Machine_Problem__1_GameBoard_h
#define Machine_Problem__1_GameBoard_h

typedef struct {
    int Value;
    int Xposition;
    int Yposition;
    int GoalDistance;
} Tile;

int COL = 3;
int ROW = 3;
Tile PuzzleBoard[9];

void CreateRandomBoard(Tile *PuzzleBoard);

#endif
