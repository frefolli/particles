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
    elements[name] = element;
}

rf::Element* rf::Matter::randomElement() {
    auto it = elements.begin();
    std::advance(it, std::rand() % elements.size());
    return &it->second;
}
