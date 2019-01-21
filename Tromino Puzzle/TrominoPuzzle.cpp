#include "TrominoPuzzle.h"



TrominoPuzzle::TrominoPuzzle(size_t size, size_t blankX, size_t blankY)
{
	this->_blank.x = blankX;
	this->_blank.y = blankY;
	size = pow(2, size);
	this->createBoard(size);
}


TrominoPuzzle::~TrominoPuzzle()
{
	for (size_t i = 0; i < this->_board.nRows; i++)
		free(this->_board.matrix[i]);
	free(this->_board.matrix);
}

void TrominoPuzzle::createBoard(size_t size)
{
	this->_board.nRows = size;
	this->_board.nCols = size;
	this->_board.matrix = (char**)malloc(sizeof(char*) * size);

	for (size_t i = 0; i < size; i++)
	{
		this->_board.matrix[i] = (char*)malloc(sizeof(char) * size);
		for (size_t j = 0; j < size; j++)
			this->_board.matrix[i][j] = BLANK;
	}

	this->_board.matrix[this->_blank.y][this->_blank.x] = MISSING;
}

void TrominoPuzzle::assignColor(size_t xlo, size_t ylo)
{
	if (this->_board.matrix[ylo][xlo] == MISSING)		// if the first tile is the missing tile
	{
		this->_board.matrix[ylo][xlo + 1] = P;		// second tile
		this->_board.matrix[ylo + 1][xlo] = P;		// third tile
		this->_board.matrix[ylo + 1][xlo + 1] = P;	// fourth tile
	}

	else if (this->_board.matrix[ylo][xlo + 1] == MISSING)	// if the second tile is the missing tile
	{
		this->_board.matrix[ylo][xlo] = Y;			// first tile
		this->_board.matrix[ylo + 1][xlo] = Y;		// third tile
		this->_board.matrix[ylo + 1][xlo + 1] = Y;	// fourth tile
	}

	else if (this->_board.matrix[ylo + 1][xlo] == MISSING)	// if the third tile is the missing tile
	{
		this->_board.matrix[ylo][xlo] = B;			// first tile
		this->_board.matrix[ylo][xlo + 1] = B;		// second tile
		this->_board.matrix[ylo + 1][xlo + 1] = B;	// fourth tile
	}

	else
	{
		this->_board.matrix[ylo][xlo] = G;			// first tile
		this->_board.matrix[ylo][xlo + 1] = G;		// second tile
		this->_board.matrix[ylo + 1][xlo] = G;		// third tile
	}
}

void TrominoPuzzle::TP(size_t xlo, size_t ylo, size_t size, Point blank)
{
	if (size < 2)
		return;
	else if (size == 2)
	{
		this->assignColor(xlo, ylo);
		return;
	}

	Point mid;
	mid.x = xlo + size / 2;
	mid.y = ylo + size / 2;

	if (blank.y < mid.y && blank.x < mid.x)	// if the missing tile is within the first submatrix
	{
		this->_board.matrix[mid.y - 1][mid.x] = MISSING;
		this->_board.matrix[mid.y][mid.x - 1] = MISSING;
		this->_board.matrix[mid.y][mid.x] = MISSING;
		
		// divide the current matrix into 4 submatrices
		TP(xlo, ylo, size / 2, Point(blank.y, blank.x));
		TP(mid.x, ylo, size / 2, Point(mid.y - 1, mid.x));
		TP(xlo, mid.y, size / 2, Point(mid.y, mid.x - 1));
		TP(mid.x, mid.y, size / 2, Point(mid.y, mid.x));
		
		// color the preadded tiles
		this->_board.matrix[mid.y - 1][mid.x] = P;
		this->_board.matrix[mid.y][mid.x - 1] = P;
		this->_board.matrix[mid.y][mid.x] = P;
	}

	else if (blank.y < mid.y && blank.x >= mid.x)	// if the missing tile is withint the second submatrix
	{
		this->_board.matrix[mid.y - 1][mid.x - 1] = MISSING;
		this->_board.matrix[mid.y][mid.x - 1] = MISSING;
		this->_board.matrix[mid.y][mid.x] = MISSING;

		TP(xlo, ylo, size / 2, Point(mid.y - 1, mid.x - 1));
		TP(mid.x, ylo, size / 2, Point(blank.y, blank.x));
		TP(xlo, mid.y, size / 2, Point(mid.y, mid.x - 1));
		TP(mid.x, mid.y, size / 2, Point(mid.y, mid.x));

		this->_board.matrix[mid.y - 1][mid.x - 1] = Y;
		this->_board.matrix[mid.y][mid.x - 1] = Y;
		this->_board.matrix[mid.y][mid.x] = Y;
	}

	else if (blank.y >= mid.y && blank.x < mid.x)	// if the missing tile is within the third submatrix
	{
		this->_board.matrix[mid.y - 1][mid.x - 1] = MISSING;
		this->_board.matrix[mid.y - 1][mid.x] = MISSING;
		this->_board.matrix[mid.y][mid.x] = MISSING;

		TP(xlo, ylo, size / 2, Point(mid.y - 1, mid.x - 1));
		TP(mid.x, ylo, size / 2, Point(mid.y - 1, mid.x));
		TP(xlo, mid.y, size / 2, Point(blank.y, blank.x));
		TP(mid.x, mid.y, size / 2, Point(mid.y, mid.x));

		this->_board.matrix[mid.y - 1][mid.x - 1] = B;
		this->_board.matrix[mid.y - 1][mid.x] = B;
		this->_board.matrix[mid.y][mid.x] = B;

	}

	else
	{
		this->_board.matrix[mid.y - 1][mid.x - 1] = MISSING;
		this->_board.matrix[mid.y - 1][mid.x] = MISSING;
		this->_board.matrix[mid.y][mid.x - 1] = MISSING;

		TP(xlo, ylo, size / 2, Point(mid.y, mid.x));
		TP(mid.x, ylo, size / 2, Point(mid.y - 1, mid.x));
		TP(xlo, mid.y, size / 2, Point(mid.y, mid.x - 1));
		TP(mid.x, mid.y, size / 2, Point(blank.y, blank.x));

		this->_board.matrix[mid.y - 1][mid.x - 1] = G;
		this->_board.matrix[mid.y - 1][mid.x] = G;
		this->_board.matrix[mid.y][mid.x - 1] = G;
	}
}

void TrominoPuzzle::solve()
{
	TP(0, 0, this->_board.nRows, this->_blank);
}

void TrominoPuzzle::print()
{
	for (size_t i = 0; i < this->_board.nRows; i++)
	{
		for (size_t j = 0; j < this->_board.nCols; j++)
		{
			printf("%c |", this->_board.matrix[i][j]);
		}
		printf("\n");
		for (size_t j = 0; j < this->_board.nCols * 3; j++)
			printf("-");
		printf("\n");
	}
	printf("\n");
}