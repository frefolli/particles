#include <rf/universe.hh>
#include <raylib.h>
#include <ctime>
#include <random>
#include <stdexcept>

size_t WIDTH = 1366;
size_t HEIGHT = 768;
size_t RADIUS = 80;
size_t NUMBER_OF_PARTICLES = 2000;

rf::Universe* UNIVERSE = nullptr;

void InitUniverse() {
    UNIVERSE = new rf::Universe(WIDTH, HEIGHT, RADIUS);
    if (UNIVERSE == nullptr)
        throw std::runtime_error("NullPointerException");
    UNIVERSE->loadMatterFromFile("assets/first.mat");
}

void FillUniverse() {
    UNIVERSE->addParticles(NUMBER_OF_PARTICLES);
}

void StepUniverse() {
    UNIVERSE->step();
}

void DrawUniverse() {
    UNIVERSE->draw();
}

void CloseUniverse() {
    delete UNIVERSE;
    UNIVERSE = nullptr;
}

int main() {
    InitWindow(WIDTH, HEIGHT, "deez nuts");
    SetTargetFPS(60);
    std::srand(time(NULL));
    // --------------------------------------------------------------------
    // INIT
    InitUniverse();
    FillUniverse();
    // --------------------------------------------------------------------
    // REL
    while (!WindowShouldClose()) {
        if(IsKeyDown(KEY_SPACE))
            StepUniverse();
        BeginDrawing();
        ClearBackground(WHITE);
        DrawUniverse();
        EndDrawing();
    }
    // --------------------------------------------------------------------
    // DELETE
    CloseUniverse();
    // --------------------------------------------------------------------
    CloseWindow();
}
