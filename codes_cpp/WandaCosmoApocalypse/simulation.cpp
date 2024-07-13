#include "simulation.hpp"
#include <iostream>
#include "include/raylib.h"


void Simulation::Draw() {
    grid.Draw();
}

void Simulation::setFairy(int row, int col, int fairy) {
    grid.setState(row, col, fairy);
}

int Simulation::countWandas(int row, int col) {
    int Wandas = 0;
    /* for (int i = row-1; i <= row+1; i++) {
        for (int j = col-1; j <= col+1; j++) { */ //asi estaba antes e igual funcionaba 
    int iRow = row-1, fRow = row+1, iCol = col-1, fCol = col+1;
    if (iRow == -1) {iRow++;} 
    if (fRow == WIN_HEIGHT/FAIRY) {fRow--;} 
    if (iCol == -1) {iCol++;} 
    if (fCol == WIN_HEIGHT/FAIRY) {fCol--;} 
    for (int i = iRow; i <= fRow; i++) {
        for (int j = iCol; j <= fCol; j++) {
            if (grid.getState(i, j) == 1) {
                Wandas++;
            }
        }
    }
    return Wandas;
}

int Simulation::countCosmos(int row, int col) {
    int Cosmos = 0;
    int iRow = row-1, fRow = row+1, iCol = col-1, fCol = col+1;
    if (iRow == -1) {iRow++;} 
    if (fRow == WIN_HEIGHT/FAIRY) {fRow--;} 
    if (iCol == -1) {iCol++;} 
    if (fCol == WIN_WIDTH/FAIRY) {fCol--;} 
    for (int i = iRow; i <= fRow; i++) {
        for (int j = iCol; j <= fCol; j++) {
            if (grid.getState(i, j) == 2) {
                Cosmos++;
            }
        }
    }
    return Cosmos;
}

int Simulation::countDead(int row, int col) {
    int Dead = 0;
    int iRow = row-1, fRow = row+1, iCol = col-1, fCol = col+1;
    if (iRow == -1) {iRow++;} 
    if (fRow == WIN_HEIGHT/FAIRY) {fRow--;} 
    if (iCol == -1) {iCol++;} 
    if (fCol == WIN_WIDTH/FAIRY) {fCol--;} 
    for (int i = iRow; i <= fRow; i++) {
        for (int j = iCol; j <= fCol; j++) {
            if (grid.getState(i, j) == 0) {
                Dead++;
            }
        }
    }
    return Dead;
}

bool Simulation::Infection(int row, int col) {
    //este no funciona sin esto, funny funny
    int iRow = row-1, fRow = row+1, iCol = col-1, fCol = col+1;
    if (iRow == -1) {iRow++;} 
    if (fRow == WIN_HEIGHT/FAIRY) {fRow--;} 
    if (iCol == -1) {iCol++;} 
    if (fCol == WIN_WIDTH/FAIRY) {fCol--;} 
    for (int i = iRow; i <= fRow; i++) {
        for (int j = iCol; j <= fCol; j++) {
            if (grid.getState(i, j) == 3) {
                return 1;
            }
        }
    }
    return 0;
}

bool Simulation::moreWandas(int row, int col) {
    return countWandas(row,col) > countCosmos(row,col) + countDead(row,col);
}

bool Simulation::moreCosmos(int row, int col) {
    return countCosmos(row,col) > countWandas(row,col) + countDead(row,col);
}

bool Simulation::moreDead(int row, int col) {
    return countDead(row,col) > countWandas(row,col) + countCosmos(row,col);
}

bool Simulation::isEmpty() {
    for (int i = 0; i < grid.getRows(); i++) {
        for (int j = 0; j < grid.getCols(); j++) {
            if (grid.getState(i,j) != 0) {return 0;}
        }
    }
    return 1;
}

bool Simulation::isFull() {
    for (int i = 0; i < grid.getRows(); i++) {
        for (int j = 0; j < grid.getCols(); j++) {
            if (grid.getState(i,j) == 0) {return 0;}
        }
    }
    return 1;
}

void Simulation::Outbreak() {
    int GZ_amount = GetRandomValue(1,5);
    for (int i = 0; i < GZ_amount; i++) {
        temp.setState(GetRandomValue(0,39), GetRandomValue(0,39),3);
    }
    apocalypse = 1;
}

void Simulation::Safe() {
    apocalypse = 0;
}

bool Simulation::Apocalypse() {
    return apocalypse;
}


void Simulation::fillRandomSpaces(int spaces) {
    if (spaces < 1 || spaces > 4096) {
        spaces = GetRandomValue(1,4096);
    }
    int filled = 0;
    int row, col;
    while (filled < spaces) {
        row = GetRandomValue(0,63);
        col = GetRandomValue(0,63);
        if (grid.getState(row,col) == 0) {
            temp.setState(row,col,GetRandomValue(1,2));
            filled++;
        }
    }
}

void Simulation::FillFromFile(std::string fileName) {
    std::ifstream file(fileName); 
    std::string line;

    int row = 0;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string val;
        int col = 0;
        while (std::getline(ss, val, ',')) {
            int num = std::stoi(val);
            setFairy(row, col, num);
            col++;
        }
        row++;
    }
    file.close();
}

void Simulation::updateState() {
    if (!Apocalypse()) {
        if (!isEmpty()) {
            for (int i = 0; i < grid.getRows(); i++) {
                for (int j = 0; j < grid.getCols(); j++) {
                    int fairyVal = grid.getState(i,j);
                    int Wandas = countWandas(i,j);
                    int Cosmos = countCosmos(i,j);
                    
                    if (fairyVal == 1) {
                        if (moreWandas(i,j)) {temp.setState(i,j,1);}
                        else if (moreCosmos(i,j)) {temp.setState(i,j,2);}
                        else if (Cosmos == Wandas) {temp.setState(i,j,0);}
                        else {temp.setState(i,j,1);}
                    }
                    else if (fairyVal == 2) {
                        if (moreWandas(i,j)) {temp.setState(i,j,1);}
                        else if (moreCosmos(i,j)) {temp.setState(i,j,2);}
                        else if (Cosmos == Wandas) {temp.setState(i,j,0);}
                        else {temp.setState(i,j,2);}
                    }
                    else {
                        if (moreWandas(i,j) || (!Cosmos && Wandas)) {temp.setState(i,j,1);}
                        else if (moreCosmos(i,j) || (!Wandas && Cosmos)) {temp.setState(i,j,2);}
                        else if (moreDead(i,j)) {temp.setState(i,j,0);}
                        else {temp.setState(i,j,GetRandomValue(1,2));}
                    }
                }
            }
        }
        else {
            fillRandomSpaces(GetRandomValue(3,10));
        }
        if (isFull()) {
            Outbreak();
        }
    }
    else {
        if (!isEmpty()) {
            for (int i = 0; i < grid.getRows(); i++) {
                for (int j = 0; j < grid.getCols(); j++) {
                    int fairyVal = grid.getState(i,j);
                    bool Virus = Infection(i,j);
                    
                    if (fairyVal == 1) {
                        if (Virus) {temp.setState(i,j,3);}
                        else {temp.setState(i,j,1);}
                    }
                    else if (fairyVal == 2) {
                        if (Virus) {temp.setState(i,j,3);}
                        else {temp.setState(i,j,2);}
                    }
                    else if (fairyVal == 3) {
                        temp.setState(i,j,0);
                    }
                    else {
                        temp.setState(i,j,0);
                    }
                }
            }
        }
        else {
            Safe();
        }
    }
    grid = temp;
}