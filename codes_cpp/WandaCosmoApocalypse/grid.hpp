#pragma once
const int WIN_WIDTH = 960;
const int WIN_HEIGHT = 960;
const int FAIRY = 15;

class Grid {
    private:
        int rows;
        int cols;
        int fairySize;
        int fairies[WIN_HEIGHT/FAIRY][WIN_WIDTH/FAIRY] = {0};

        bool Bounded(int row, int col);

    public:
        Grid(int width, int height, int fairySize) {
            this->rows = height/fairySize;
            this->cols = width/fairySize;
            this->fairySize = fairySize;
        }

        void Draw();
        int getCols();
        int getRows();
        void setState(int row, int col, int state);
        int getState(int row, int col);
};