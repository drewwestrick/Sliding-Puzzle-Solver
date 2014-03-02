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

typedef struct Board{
    int ID;
    Tile Tiles[9];
    int Inversions;
    int TotalDistance;
    int TotalMoves;
    int isSolvable;
    int SpacePosition;
    struct Board *PrevBoard;
} Board;

typedef struct List{
    Board This;
    struct List *Prev;
    struct List *Next;
} List;

Board NextSlidingBoard;
Board PrevSlidingBoard;

List OpenSet;
List ClosedSet;
List *ClosedSetTail;

int OpenSetCount;
int ClosedSetCount;

void CreateRandomBoard(Board *SlidingBoard, int Seed);
void PrintGameBoard(Board *SlidingBoard);
void CreateGoalBoard(Board *SlidingBoard);
void PrintBoardDistance(Board *SlidingBoard);
int CalculateInversions(Board *SlidingBoard);
Board AStarSearch(Board *SlidingBoard);
void CalculateDistance(Board *SlidingBoardNew);
void ShiftPuzzle(Board *SlidingBoardOld, Board *SlidingBoardNew, int Amount);
void CheckMinDistance(Board *NextState, Board *SlidingBoardNew, int *MinDistance);
int CheckDifference(Board *SlidingBoardNew, Board *SlidingBoardOld);
void AddToOpen(Board *SlidingBoard);
List FindLowest(List *Set, int ListNum);
void ExploreNeighbors(Board *SlidingBoard);
void AddToClosed(List *NewList);
int CheckOpenList(Board *SlidingBoardNew);
int CheckClosedList(Board *SlidingBoardNew);
int PrintBoardProgession(Board *SlidingBoard);
int FreeList(List *NewList);
#endif
