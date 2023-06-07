#include <rf/universe.hh>
#include <cmath>

// Matter matter
// std::map<Element*, vector<Particle>> particles

rf::Universe::Universe(size_t width, size_t height) {
    this->width = width;
    this->height = height;
}

void rf::Universe::step() {
    for (auto groupA = particles.begin(); groupA != particles.end(); ++groupA) {
        for (auto groupB = particles.begin(); groupB != particles.end(); ++groupB) {
            double gravity = groupA->first->getGravity(groupB->first);
            for (auto particleA = groupA->second.begin(); particleA != groupA->second.end(); ++particleA) {
                for (auto particleB = groupB->second.begin(); particleB != groupB->second.end(); ++particleB) {
                    double
                        dx = (particleA->pos.x - particleB->pos.x),
                        dy = (particleA->pos.y - particleB->pos.y);
                    double d = std::sqrt((dx*dx) + (dy*dy));
                    double F = (d > 0) ? (gravity / d) : 1.0F;
                    particleA->acc.x += F * dx;
                    particleA->acc.y += F * dy;
                }
            }
        }
    }
    for (auto group = particles.begin(); group != particles.end(); ++group) {
        for (auto particle = group->second.begin(); particle != group->second.end(); ++particle) {
            particle->vel.x += particle->acc.x;
            particle->vel.y += particle->acc.y;
            
            if (particle->pos.x < 0 || particle->pos.x >= width) {
                particle->pos.x = std::min(std::max(particle->pos.x, 0.0F), (float) width);
                particle->vel.x *= -0.1;
            }
            
            if (particle->pos.y < 0 || particle->pos.y >= height) {
                particle->pos.y = std::min(std::max(particle->pos.y, 0.0F), (float) height);
                particle->vel.y *= -0.1;
            }

            particle->pos.x += particle->vel.x;
            particle->pos.y += particle->vel.y;
            particle->acc = {0, 0};
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
