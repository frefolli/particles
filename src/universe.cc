#include <rf/universe.hh>

// Matter matter
// std::map<Element*, vector<Particle>> particles

rf::Universe::Universe(size_t width, size_t height) {
    this->width = width;
    this->height = height;
}

void rf::Universe::step() {
    /*TODO*/
}

void rf::Universe::draw() {
    for (auto group : particles) {
        for (auto particle : group->second) {
            particle.draw();
        }
    }
}

void rf::Universe::addElement(rf::Element element) {
    matter.setElement();
}

void rf::Universe::addParticle() {
    Element* element = (particles.begin() + (std::rand() % particles.size())).first;
    particles[element].push_back(
            Particle({std::rand() % 600,
                      std::rand() % 400}, element));
}

void rf::Universe::addParticles(size_t numberOfParticles) {
    for (size_t i = 0; i < numberOfParticles; i++) {
        addParticle();
    }
}
