#ifndef RF_UNIVERSE
#define RF_UNIVERSE

#include <rf/element.hh>
#include <rf/matter.hh>
#include <rf/particle.hh>
#include <vector>

namespace rf {
    class Universe {
        private:
            size_t width, height, radius;
            float speed;
            Matter matter;
            std::map<Element*, std::vector<Particle>> particles;
        public:
            Universe(size_t width, size_t height, size_t radius, float speed);
            void step();
            void draw();
            void addElement(std::string name, Element element);
            Element* getElement(std::string name);
            void addParticle();
            void addParticles(size_t numberOfParticles);

            void loadMatterFromString(std::string* text);
            void loadMatterFromFile(std::string path);
            void randomMatter();
            std::string* dumpMatterToString();
            void dumpMatterToFile(std::string path);
    };
};

#endif
