#include <rf/particle.hh>
#include <stdexcept>
#define RADIUS 10.0F

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

void rf::Particle::draw() {
    DrawCircle((int) pos.x, (int) pos.y, RADIUS, element->getColor());
}
