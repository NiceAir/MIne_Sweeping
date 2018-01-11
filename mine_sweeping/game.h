#ifndef __GAME_H__
#define __GAME_H__
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include <math.h>
#include<Windows.h>
#define MROW 32
#define  MCOL 32

enum level{
	EAZY = 8,
	ORDINARY = 16,
	DIFFICUTE = 24,
};

void PutMine(char mine[MROW][MCOL], const int row, const int col, int Fx, int Fy, int *count);
void Init_Board(char mine[MROW][MCOL], char show[MROW][MCOL], int *row, int *col);
void Show_Board( const char board[MROW][MCOL], const int row, const int col);
int Check_Legal(const int row, const int col, const int x, const int y);
int expand(const char mine[MROW][MCOL], char show[MROW][MCOL], const int row, const int col, const int x, const int y);
int  Player_Do(char mine[MROW][MCOL], char show[MROW][MCOL], const int row, const int col, int dead[2], int *Fx, int *Fy);
int Check_Win(static char show[MROW][MCOL], static int row, static int col, int count);

/*
void Init_Board(char mine[MROW][MCOL], char show[MROW][MCOL], int *row, int *col);
void PutMine(char mine[MROW][MCOL], int row, int col, int Fx, int Fy, int *count);
void Show_Board(char board[MROW][MCOL], int row, int col);
int Check_Legal(int row, int col, int x, int y);
int  Player_Do(char mine[MROW][MCOL], char show[MROW][MCOL], int row, int col, int dead[2], int *Fx, int *Fy);*/

#endif
