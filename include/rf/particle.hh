#ifndef RF_PARTICLE
#define RF_PARTICLE

#include <rf/element.hh>
#include <raylib.h>

namespace rf {
    class Particle {
        public:
            Vector2 pos;
            Vector2 vel;
            Vector2 acc;
            Element* element;
            Particle(Vector2 pos, Element* element);
            Vector2& getPos();
            Vector2& getVel();
            Vector2& getAcc();
            void draw();
    };
}

#endif
