#include "include/raylib.h"
#include "simulation.hpp"

const int FPS = 13;

Color Black = {0, 0, 0, 255};


int main() {
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "Wanda vs Cosmo - Sisyphus");
    SetTargetFPS(FPS);

    Simulation sim(WIN_WIDTH, WIN_HEIGHT, FAIRY);
    sim.FillFromFile("..\\tests\\64x64\\64x64_matrix_0.txt");


    while(!WindowShouldClose()) {
        sim.updateState();

        BeginDrawing();
        ClearBackground(Black);
        sim.Draw();
        EndDrawing();
        //std::cout<<"Hay apocalipsis?: "<<sim.Apocalypse()<<" y Esta vacio? "<<sim.isEmpty()<<std::endl;
    }

    CloseWindow();
}
