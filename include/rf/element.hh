#ifndef RF_ELEMENT
#define RF_ELEMENT

#include <map>
#include <string>
#include <raylib.h>

namespace rf {
    class Element {
        private:
            Color color;
            std::map<Element*, double> gravities;
        public:
            Element(Color color = BLACK);
            Element(Color color, std::map<Element*, double> gravities);

            double getGravity(Element* other);
            void setGravity(Element* other, double gravity);
            Color getColor();
    };
}

#endif
