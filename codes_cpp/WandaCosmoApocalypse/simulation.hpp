#pragma once
#include "grid.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

/* const int W4C = 4;
const int C4W = 4; */

class Simulation {
    private:
    Grid grid;
    Grid temp;
    bool apocalypse = 0;

    public:
    Simulation(int width, int height, int fairySize): grid(width, height, fairySize), temp(width, height, fairySize) {};
    void Draw();
    void setFairy(int row, int col, int fairy);
    int countWandas(int row, int col);
    int countCosmos(int row, int col);
    int countDead(int row, int col);
    bool Infection(int row, int col);
    bool moreWandas(int row, int col);
    bool moreCosmos(int row, int col);
    bool moreDead(int row, int col);
    bool isEmpty();
    bool isFull();
    void Outbreak();
    void Safe();
    bool Apocalypse();
    void fillRandomSpaces(int spaces);
    void FillFromFile(const std::string fileName);
    void updateState();

};