#include <rf/matter.hh>
#include <stdexcept>

// std::map<std::string, Element> elements

rf::Matter::Matter() {
    /*TODO*/
}

rf::Matter::Matter(std::map<std::string, rf::Element> elements) {
    this->elements = elements;
}

rf::Element* rf::Matter::getElement(std::string name) {
    auto item = elements.find(name);
    if (item == elements.end())
        throw std::runtime_error("ItemNotFoundException");
    return &item->second;
}

void rf::Matter::setElement(std::string name, rf::Element element) {
    gravities[name] = element;
}
