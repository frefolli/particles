#include <rf/particle.hh>
#include <stdexcept>
#define RADIUS 10

// Vector2 pos
// Vector2 vel
// Vector2 acc
// Element* element

rf::Particle::Particle(Vector2 pos, rf::Element* element) {
    this->pos = pos;
    acc = {0, 0};
    vel = {0, 0};
    if (element == nullptr)
        throw std::runtime_error("NullPointerException");
    this->element = element;
}

Vector2& rf::Particle::getPos() {
    return pos;
}

Vector2& rf::Particle::getVel() {
    return vel;
}

Vector2& rf::Particle::getAcc() {
    return acc;
}

void rf::Particle::draw() {
    DrawCircle(pos.x, pos.y, RADIUS, element->getColor());
}

void rf::Particle::tick() {
    /*TODO*/
}
