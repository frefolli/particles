#ifndef RF_UNIVERSE
#define RF_UNIVERSE

#include <rf/element.hh>
#include <rf/matter.hh>
#include <rf/particle.hh>

namespace rf {
    class Universe {
        private:
            size_t width, height;
            Matter matter;
            std::map<Element*, vector<Particle>> particles;
        public:
            Universe(size_t width, size_t height);
            void step();
            void draw();
            void addElement(Element element);
            void addParticle();
            void addParticles(size_t numberOfParticles);
    };
};

#endif
