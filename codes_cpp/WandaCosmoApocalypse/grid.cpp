#include "grid.hpp"
#include "include/raylib.h"

Color Wanda = {222, 95, 165, 255};
Color Cosmo = {123, 183, 81, 255};
Color Dead = {170, 170, 170, 255};
Color Virus = {163, 136, 80, 255};

void Grid::Draw() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Color fairyColor;
            if (fairies[i][j] == 1) {fairyColor = Wanda;}
            else if (fairies[i][j] == 2) {fairyColor = Cosmo;}
            else if (fairies[i][j] == 3) {fairyColor = Virus;}
            else {fairyColor = Dead;}
            DrawRectangle(j*fairySize, i*fairySize, fairySize-1, fairySize-1, fairyColor);
        }
    }
}

int Grid::getCols() {
    return cols;
}

int Grid::getRows() {
    return rows;
}

bool Grid::Bounded(int row, int col) {
    return (row >= 0 && row <= rows && col >= 0 && col <= cols);
}

void Grid::setState(int row, int col, int state) {
    if (Bounded(row,col)) {
        fairies[row][col] = state;
    }
}

int Grid::getState(int row, int col) {
    if (Bounded(row,col)) {
        return fairies[row][col];
    }
    return -1;
}
