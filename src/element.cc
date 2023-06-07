#include <rf/element.hh>
#include <stdexcept>

// std::map<Element*, double> gravities

rf::Element::Element(Color color) {
    this->color = color;
}

rf::Element::Element(Color color, std::map<rf::Element*, double> gravities) {
    this->color = color;
    for (auto gravityEntry : gravities) {
        setGravity(gravityEntry.first, gravityEntry.second);
    }
}

double rf::Element::getGravity(rf::Element* other) {
    if (other == nullptr)
        throw std::runtime_error("NullPointerException");
    auto item = gravities.find(other);
    if (item == gravities.end()) {
        float r = static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX);
        setGravity(other, r);
        return r;
    }
    return item->second;
}

void rf::Element::setGravity(rf::Element* other, double gravity) {
    if (other == nullptr)
        throw std::runtime_error("NullPointerException");
    gravities[other] = gravity;
}

Color rf::Element::getColor() {
    return color;
}
