#include "Piece.h"
#include <stdlib.h>

//1 - Piesa I
//2 - Piesa O
//3 - Piesa S
//4: //Piesa Z
//5 - Piesa L
//6 - Piesa J
//7 - Piesa T


uint8_t** getPiece(char type)
{

	uint8_t** piece = (uint8_t**)malloc(4 * 4 * sizeof(uint8_t*));
	for (int i = 0; i < 4; i++)
	{
		piece[i] = (uint8_t*)malloc(4 * sizeof(uint8_t));
		for (int j = 0; j < 4; ++j)
		{
			piece[i][j] = 0;
		}
	}
	switch (type)
	{
	case 'I':
		piece[0][1] = 1;
		piece[1][1] = 1;
		piece[2][1] = 1;
		piece[3][1] = 1;
		return piece;
	case 'O':
		piece[0][1] = 2;
		piece[1][1] = 2;
		piece[0][2] = 2;
		piece[1][2] = 2;
		return piece;
	case 'S':
		piece[0][2] = 3;
		piece[1][1] = 3;
		piece[0][3] = 3;
		piece[1][2] = 3;
		return piece;
	case 'Z':
		piece[0][0] = 4;
		piece[1][1] = 4;
		piece[0][1] = 4;
		piece[1][2] = 4;
		return piece;
	case 'L':
		piece[0][1] = 5;
		piece[1][1] = 5;
		piece[2][1] = 5;
		piece[2][2] = 5;
		return piece;
	case 'J':
		piece[0][1] = 6;
		piece[1][1] = 6;
		piece[2][1] = 6;
		piece[2][0] = 6;
		return piece;
	case 'T':
		piece[0][1] = 7;
		piece[0][2] = 7;
		piece[0][3] = 7;
		piece[1][2] = 7;
		return piece;
	default:
		break;
	}
	return piece;

}


int isEmptyRow(uint8_t** piece, int rowIndex)
{
	int i = 0;
	for (i = 0; i < 4; ++i)
		if (piece[rowIndex][i] != 0)
			return 0;
	return 1;
}
int isEmptyCol(uint8_t** piece, int colIndex)
{
	int i = 0;
	for (i = 0; i < 4; ++i)
		if (piece[i][colIndex] != 0)
			return 0;
	return 1;
}

int findTop(uint8_t** piece, int rows)
{
	for (int i = 0; i < rows; ++i)
	{
		if (isEmptyRow(piece, i) == 0)
		{
			return i;
		}
	}
	return -1;
}
int findBottom(uint8_t** piece, int rows)
{
	for (int i = rows - 1; i >= 0; --i)
		if (isEmptyRow(piece, i) == 0)
		{
			return i;

		}
	return -1;
}

int findLeft(uint8_t** piece, int cols)
{
	for (int i = 0; i < cols; ++i)
	{
		if (isEmptyCol(piece, i) == 0)
		{
			return i;

		}
	}
	return -1;
}
int findRight(uint8_t** piece, int cols)
{

	for (int i = cols - 1; i > 0; --i)
		if (isEmptyCol(piece, i) == 0)
		{
			return i;
		}
	return -1;
}

uint8_t** getPaddedPiece(uint8_t** piece, int* resultRows, int* resultCols)
{
	int rows = 4;
	int cols = 4;
	int top = 0; int bottom = rows - 1; int left = 0; int right = cols - 1;
	int i, j;

	top = findTop(piece, rows);
	bottom = findBottom(piece, rows);
	left = findLeft(piece, cols);
	right = findRight(piece, cols);
	*resultRows = bottom - top + 4;
	*resultCols = right - left + 4;
	int r = bottom - top + 1;
	int c = right - left + 1;
	*resultRows = r;
	*resultCols = c;
	uint8_t** paddedPiece = (uint8_t**)malloc(r*c*sizeof(uint8_t*));
	for (i = 0; i < r; i++)
	{
		paddedPiece[i] = (uint8_t*)malloc(c*sizeof(uint8_t));
		for (j = 0; j < c; j++)
		{
			paddedPiece[i][j] = 0;
		}
	}
	int x = 0;
	int y = 0;
	for (i = top; i <= bottom; ++i)
	{
		for (j = left; j <= right; ++j)
		{
			if (piece[i][j] > 0)
				paddedPiece[y][x] = piece[i][j];
			x++;
		}
		y++;
		x = 0;
	}
	return paddedPiece;


}

void rotateMatrix(uint8_t** piece)
{
	int i, j;
	for (i = 0; i < 4 / 2; i++)
	{
		for (j = i; j < 4 - i - 1; j++)
		{
			uint8_t tmp = piece[i][j];
			piece[i][j] = piece[j][4 - 1 - i];
			piece[j][4 - 1 - i] = piece[4 - 1 - i][4 - 1 - j];

			piece[4 - 1 - i][4 - 1 - j] = piece[4 - 1 - j][i];

			piece[4 - 1 - j][i] = tmp;
		}
	}
}
void rotatePiece(uint8_t** piece, int angle)
{
	angle = 360-angle;
	int count = angle/90;
	int i = 0;
	for (i = 0; i < count; ++i)
	{
		rotateMatrix(piece);
	}
}
