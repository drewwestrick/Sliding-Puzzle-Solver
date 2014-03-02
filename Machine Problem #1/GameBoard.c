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
void CreateRandomBoard(Board *SlidingBoard, int Seed) {
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
    srand(Seed);
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
        }
    }
    CalculateDistance(SlidingBoard);
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
            CalculateDistance(SlidingBoard);
        }
    }
}

/* Calculate the next state of the board and select optimal state */
Board AStarSearch(Board *SlidingBoard) {
    OpenSetCount = 0;
    ClosedSetCount = 0;
    List Lowest;
    if (!(OpenSet.Next)&&!(OpenSet.Prev)) {
        memcpy(&OpenSet.This, SlidingBoard, sizeof(*SlidingBoard));
        OpenSetCount++;
    }
    CalculateDistance(SlidingBoard);
    while (OpenSetCount>0) {
        Lowest = FindLowest(&OpenSet, OpenSetCount);
        if (Lowest.This.TotalDistance==0) {
            printf("Moves: %d\n", Lowest.This.TotalMoves);
            printf("Found Goal!\n");
            PrintGameBoard(&Lowest.This);
            PrintBoardProgession(&Lowest.This);
            printf("Step: %d\n", Lowest.This.TotalMoves);
            PrintGameBoard(&Lowest.This);
            FreeList(&OpenSet);
            FreeList(&ClosedSet);
            OpenSet.Next = NULL;
            OpenSet.Prev = NULL;
            ClosedSet.Next = NULL;
            ClosedSet.Prev = NULL;
            ClosedSetTail = NULL;
            OpenSetCount = 0;
            ClosedSetCount = 0;
            break;
        }
        else {
            OpenSetCount--;
            if (OpenSetCount>0) {
                if (!(Lowest.Prev)) {
                    OpenSet = *Lowest.Next;
                    OpenSet.Prev = NULL;
                    AddToClosed(&Lowest);
                }
                else if (!(Lowest.Next)) {
                    Lowest.Prev->Next = NULL;
                }
                else {
                    Lowest.Prev->Next = Lowest.Next;
                }
            }
        }
        ExploreNeighbors(&Lowest.This);
    }
    return Lowest.This;
}

/* Calculate the number of inversion to see if the puzzle is solveable */
int CalculateInversions(Board *SlidingBoard) {
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
        return 1;
    }
    else {
        printf("Board is NOT solvable...\n");
        return 0;
    }
}

/* Calculate heuristic variable distance */
void CalculateDistance(Board *SlidingBoardNew) {
    SlidingBoardNew->TotalDistance = 0;
    Tile *Tiles = SlidingBoardNew->Tiles;
    int i;
    for (i=0;i<9;i++) {
        if (Tiles[i].Value>0) {
            Tiles[i].GoalDistance = abs(Tiles[i].Xposition-((Tiles[i].Value-1)%3))+abs(Tiles[i].Yposition-floor(((float)Tiles[i].Value-1)/(float)3));
        }
        else {
            Tiles[i].GoalDistance = abs((2-Tiles[i].Xposition)+(2-Tiles[i].Yposition));
            SlidingBoardNew->SpacePosition = i;
        }
        SlidingBoardNew->TotalDistance += Tiles[i].GoalDistance;
    }
    //printf("Total Distance: %d\n", SlidingBoardNew->TotalDistance);
}

/* Shift Puzzle Board to new position, update x,y values */
void ShiftPuzzle(Board *SlidingBoardOld, Board *SlidingBoardNew, int Amount) {
    Tile *TilesNew;
    Tile temp;
    int temppos;
    memcpy(SlidingBoardNew, SlidingBoardOld, sizeof(*SlidingBoardNew));
    TilesNew = SlidingBoardNew->Tiles;
    temp = TilesNew[SlidingBoardOld->SpacePosition];
    TilesNew[SlidingBoardOld->SpacePosition] = TilesNew[(SlidingBoardOld->SpacePosition)+Amount];
    TilesNew[(SlidingBoardOld->SpacePosition)+Amount] = temp;
    temppos = TilesNew[SlidingBoardOld->SpacePosition].Xposition;
    TilesNew[SlidingBoardOld->SpacePosition].Xposition = TilesNew[(SlidingBoardOld->SpacePosition)+Amount].Xposition;
    TilesNew[(SlidingBoardOld->SpacePosition)+Amount].Xposition = temppos;
    temppos = TilesNew[SlidingBoardOld->SpacePosition].Yposition;
    TilesNew[SlidingBoardOld->SpacePosition].Yposition = TilesNew[(SlidingBoardOld->SpacePosition)+Amount].Yposition;
    TilesNew[(SlidingBoardOld->SpacePosition)+Amount].Yposition = temppos;
    SlidingBoardNew->SpacePosition = SlidingBoardOld->SpacePosition+Amount;
    SlidingBoardNew->TotalMoves++;
    SlidingBoardNew->ID = rand();
    SlidingBoardNew->PrevBoard = malloc(sizeof(Board));
    memcpy(SlidingBoardNew->PrevBoard, SlidingBoardOld, sizeof(*SlidingBoardOld));
}

int CheckDifference(Board *SlidingBoardNew, Board *SlidingBoardOld) {
    int i;
    for(i=0;i<9;i++) {
        if (SlidingBoardNew->Tiles[i].Value!=SlidingBoardOld->Tiles[i].Value) {
            return 0;
        }
    }
    return 1;
}

int CheckClosedList(Board *SlidingBoardNew) {
    int i;
    List *TempList = &ClosedSet;
    for (i=0;i<ClosedSetCount;i++) {
        if (CheckDifference(&TempList->This, SlidingBoardNew)) {
            return 0;
        }
        TempList = TempList->Next;
    }
    return 1;
}

int CheckOpenList(Board *SlidingBoardNew) {
    int i;
    List *TempList = &OpenSet;
    for (i=0;i<OpenSetCount;i++) {
        if (CheckDifference(&TempList->This, SlidingBoardNew)) {
            return 0;
        }
        TempList = TempList->Next;
    }
    return 1;
}

void ExploreNeighbors(Board *SlidingBoard) {
    Tile *Tiles = SlidingBoard->Tiles;
    Board SlidingBoardRight;
    Board SlidingBoardLeft;
    Board SlidingBoardTop;
    Board SlidingBoardBtm;
    switch (Tiles[SlidingBoard->SpacePosition].Xposition) {
        case 0:
            ShiftPuzzle(SlidingBoard, &SlidingBoardRight, 1);
            CalculateDistance(&SlidingBoardRight);
            AddToOpen(&SlidingBoardRight);
            break;
        case 1:
            ShiftPuzzle(SlidingBoard, &SlidingBoardRight, 1);
            CalculateDistance(&SlidingBoardRight);
            AddToOpen(&SlidingBoardRight);
            ShiftPuzzle(SlidingBoard, &SlidingBoardLeft, -1);
            CalculateDistance(&SlidingBoardLeft);
            AddToOpen(&SlidingBoardLeft);
            break;
        case 2:
            ShiftPuzzle(SlidingBoard, &SlidingBoardLeft, -1);
            CalculateDistance(&SlidingBoardLeft);
            AddToOpen(&SlidingBoardLeft);
            break;
    }
    switch (Tiles[SlidingBoard->SpacePosition].Yposition) {
        case 0:
            ShiftPuzzle(SlidingBoard, &SlidingBoardTop, 3);
            CalculateDistance(&SlidingBoardTop);
            AddToOpen(&SlidingBoardTop);
            break;
        case 1:
            ShiftPuzzle(SlidingBoard, &SlidingBoardTop, 3);
            CalculateDistance(&SlidingBoardTop);
            AddToOpen(&SlidingBoardTop);
            ShiftPuzzle(SlidingBoard, &SlidingBoardBtm, -3);
            CalculateDistance(&SlidingBoardBtm);
            AddToOpen(&SlidingBoardBtm);
            break;
        case 2:
            ShiftPuzzle(SlidingBoard, &SlidingBoardBtm, -3);
            CalculateDistance(&SlidingBoardBtm);
            AddToOpen(&SlidingBoardBtm);
            break;
    }

}

List FindLowest(List *Set, int ListNum) {
    int Min = 10000;
    List *temp;
    while (ListNum>0) {
        if (Set->This.TotalDistance<Min) {
            Min = Set->This.TotalDistance;
            temp = Set;
            Set = Set = Set->Next;
        }
        else {
            Set = Set->Next;
        }
        ListNum--;
    }
    return *temp;
}

void AddToOpen(Board *SlidingBoard) {
    int tmpcnt = OpenSetCount;
    List *OpenSetTemp = &OpenSet;
    List *temp;
    if ((CheckClosedList(SlidingBoard)&&(CheckOpenList(SlidingBoard)))) {
        if (OpenSetCount==0) {
            memcpy(&OpenSetTemp->This, SlidingBoard, sizeof(*SlidingBoard));
            OpenSetCount++;
        }
        else {
            while(tmpcnt>0) {
                if (SlidingBoard->TotalDistance<OpenSetTemp->This.TotalDistance) {
                    temp = malloc(sizeof(List));
                    memcpy(&temp->This, &OpenSetTemp->This, sizeof(OpenSetTemp->This));
                    memcpy(&OpenSetTemp->This, SlidingBoard, sizeof(*SlidingBoard));
                    temp->Next = OpenSetTemp->Next;
                    OpenSetTemp->Next = temp;
                    temp->Prev = OpenSetTemp;
                    OpenSetCount++;
                    break;
                }
                else if (tmpcnt==1) {
                    OpenSetTemp->Next = malloc(sizeof(List));
                    memcpy(&OpenSetTemp->Next->This, SlidingBoard, sizeof(*SlidingBoard));
                    OpenSetTemp->Next->Prev = OpenSetTemp;
                    OpenSetCount++;
                }
                else {
                    OpenSetTemp = OpenSetTemp->Next;
                }
                tmpcnt--;
            }
        }
    }
}
void AddToClosed(List *NewList) {
    if (!(ClosedSetTail)) {
        ClosedSetTail = &ClosedSet;
        memcpy(&ClosedSet, NewList, sizeof(*NewList));
        ClosedSet.Prev = NULL;
        ClosedSet.Next = NULL;
        ClosedSetCount++;
    }
    else {
        ClosedSetTail->Next = malloc(sizeof(List));
        memcpy(ClosedSetTail->Next, NewList, sizeof(*NewList));
        ClosedSetTail->Next->Prev = ClosedSetTail;
        ClosedSetTail->Next->Next = NULL;
        ClosedSetTail = ClosedSetTail->Next;
        ClosedSetCount++;
    }
}

int PrintBoardProgession(Board *SlidingBoard) {
    if (SlidingBoard->PrevBoard) {
        SlidingBoard = SlidingBoard->PrevBoard;
        PrintBoardProgession(SlidingBoard);
        printf("Step: %d\n", SlidingBoard->TotalMoves);
        PrintGameBoard(SlidingBoard);
    }
    else {
        return 0;
    }
    return 0;
}

int FreeList(List *NewList) {
    if (NewList->Next) {
        NewList = NewList->Next;
        FreeList(NewList);
        free(NewList);
        return 0;
    }
    else {
        return 0;
    }
}
