#pragma once

#define BLANK		0
#define	MISSING		-1
#define P			'P'
#define Y			'Y'
#define B			'B'
#define G			'G'

#include <malloc.h>
#include <math.h>
#include <stdio.h>
// #include <gdiplus.h>

struct Point
{
	size_t x;
	size_t y;

	Point()
	{

	}
	Point(size_t ny, size_t nx)
	{
		x = nx;
		y = ny;
	}
};

struct Board
{
	size_t nRows;
	size_t nCols;
	char **matrix;
};

class TrominoPuzzle
{
private:
	Board _board;
	Point _blank;

	// create starting board with a missing tile
	void createBoard(size_t size);
	// assign color for tiles
	void assignColor(size_t xlo, size_t ylo);
	// run the algorithm to solve TP
	void TP(size_t xlo, size_t ylo, size_t size, Point blank);

public:
	TrominoPuzzle(size_t size, size_t blankX, size_t blankY);
	~TrominoPuzzle();
	// wraper function to run TP()
	void solve();
	// print result to console
	void print();
};

