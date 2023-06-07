#include <rf/universe.hh>
#include <raylib.h>
#include <ctime>
#include <random>
#include <stdexcept>

size_t WIDTH = 600;
size_t HEIGHT = 400;
size_t NUMBER_OF_PARTICLES = 50;

rf::Universe* UNIVERSE = nullptr;

void InitUniverse() {
    UNIVERSE = new rf::Universe(WIDTH, HEIGHT);
    if (UNIVERSE == nullptr)
        throw std::runtime_error("NullPointerException");
}

void FillUniverse() {
    UNIVERSE->addElement("Carbon", rf::Element(BLACK));
    UNIVERSE->addElement("Oxygen", rf::Element(RED));
    UNIVERSE->addElement("Hydrogen", rf::Element(BLUE));
    auto Carbon = UNIVERSE->getElement("Carbon");
    auto Oxygen = UNIVERSE->getElement("Oxygen");
    auto Hydrogen = UNIVERSE->getElement("Hydrogen");

    Carbon->setGravity(Carbon, 1.0F);
    Carbon->setGravity(Oxygen, -1.0F);
    Carbon->setGravity(Hydrogen, -1.0F);
    
    Oxygen->setGravity(Oxygen, 1.0F);

    Hydrogen->setGravity(Hydrogen, 1.0F);
    Hydrogen->setGravity(Oxygen, -1.0F);
    Hydrogen->setGravity(Carbon, 1.0F);

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
