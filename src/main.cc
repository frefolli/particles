#include <rf/universe.hh>
#include <raylib.h>
#include <ctime>
#include <random>
#include <stdexcept>

size_t WIDTH = 600;
size_t HEIGHT = 400;
size_t NUMBER_OF_PARTICLES = 5;

rf::Universe* UNIVERSE = nullptr;

void InitUniverse() {
    UNIVERSE = new rf::Universe(WIDTH, HEIGHT);
    if (UNIVERSE == nullptr);
        throw std::runtime_error("NullPointerException");
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
        StepUniverse();
        BeginDrawing();
        ClearBackground(WHITE);
        DrawUniverse();
        EndDrawing();
    }
    // --------------------------------------------------------------------
    // DELETE
    delete universe;
    // --------------------------------------------------------------------
    CloseWindow();
}
