#pragma once
#include <stdint.h>


uint8_t** getPiece(char type);

int isEmptyRow(uint8_t** piece, int rowIndex);
int isEmptyCol(uint8_t** piece, int colIndex);
int findTop(uint8_t** piece, int rows);
int findBottom(uint8_t** piece, int rows);
int findLeft(uint8_t** piece, int cols);
int findRight(uint8_t** piece, int cols);

uint8_t** getPaddedPiece(uint8_t** piece, int* resultRows, int* resultCols);
void rotateMatrix(uint8_t** piece);
void rotatePiece(uint8_t** piece, int angle);