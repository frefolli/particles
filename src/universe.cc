#include <rf/universe.hh>
#include <cmath>
#include <raylib.h>

// Matter matter
// std::map<Element*, vector<Particle>> particles

rf::Universe::Universe(size_t width, size_t height, size_t radius, float speed) {
    this->width = width;
    this->height = height;
    this->radius = radius;
    this->speed = speed;
}

void rf::Universe::step() {
    for (auto groupA = particles.begin(); groupA != particles.end(); ++groupA) {
        for (auto groupB = particles.begin(); groupB != particles.end(); ++groupB) {
            double gravity = groupA->first->getGravity(groupB->first);
            for (auto particleA = groupA->second.begin(); particleA != groupA->second.end(); ++particleA) {
                for (auto particleB = groupB->second.begin(); particleB != groupB->second.end(); ++particleB) {
                    double dx = (particleA->pos.x - particleB->pos.x);
                    double dy = (particleA->pos.y - particleB->pos.y);
                    // double d = std::sqrt((dx*dx) + (dy*dy));
                    double d = (dx*dx) + (dy*dy);
                    if (d > 0 && d < radius) {
                        double F = (gravity) / d;
                        particleA->acc.x += F * dx;
                        particleA->acc.y += F * dy;
                    }
                }
                particleA->vel.x += speed * particleA->acc.x;
                particleA->vel.y += speed * particleA->acc.y;

                particleA->pos.x += particleA->vel.x;
                particleA->pos.y += particleA->vel.y;
                
                if (particleA->pos.x <= 0) {
                    particleA->vel.x *= -1;
                    particleA->pos.x = 1;
                } else if (particleA->pos.x >= width) {
                    particleA->vel.x *= -1;
                    particleA->pos.x = width - 1;
                }
                
                if (particleA->pos.y <= 0) {
                    particleA->vel.y *= -1;
                    particleA->pos.y = 1;
                } else if (particleA->pos.y >= height) {
                    particleA->vel.y *= -1;
                    particleA->pos.y = height - 1;
                }

                particleA->acc = {0, 0};
            }
        }
    }
}

void rf::Universe::draw() {
    for (auto group = particles.begin(); group != particles.end(); ++group) {
        for (auto particle = group->second.begin(); particle != group->second.end(); ++particle) {
            particle->draw();
        }
    }
}

void rf::Universe::addElement(std::string name, rf::Element element) {
    matter.setElement(name, element);
}

rf::Element* rf::Universe::getElement(std::string name) {
    return matter.getElement(name);
}

void rf::Universe::addParticle() {
    Element* element = matter.randomElement();
    float x = std::rand() % width;
    float y = std::rand() % height;
    particles[element].push_back(
            Particle({x, y}, element));
}

void rf::Universe::addParticles(size_t numberOfParticles) {
    for (size_t i = 0; i < numberOfParticles; i++) {
        addParticle();
    }
}

void rf::Universe::loadMatterFromString(std::string* text) {
    matter.loadFromString(text);
}

void rf::Universe::loadMatterFromFile(std::string path) {
    matter.loadFromFile(path);
}


void rf::Universe::randomMatter() {
    matter.setElement("Green", Element(GREEN));
    matter.setElement("Red", Element(RED));
    matter.setElement("Black", Element(BLACK));
    matter.setElement("Blue", Element(BLUE));
};

std::string* rf::Universe::dumpMatterToString() {
    return matter.dumpToString();
}

void rf::Universe::dumpMatterToFile(std::string path) {
    matter.dumpToFile(path);
}
