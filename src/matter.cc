#include <rf/matter.hh>
#include <stdexcept>
#include <fstream>
#include <raylib.h>
#include <sstream>

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

void rf::Matter::processCommand(std::vector<std::string>* command) {
    if (command->at(0) == "el") {
        if (command->size() != 3) {
            throw std::runtime_error("syntax for `el`: el <ElementName> <ElementColor>");
        }
        std::string name = command->at(1);
        std::string color = command->at(2);
        if (color.at(0) == '#') {
            if (color.size() != 7)
                throw std::runtime_error("RGB color should be in format #ffffff");
            int R, G, B;
            std::istringstream(color.substr(1,2)) >> std::hex >> R;
            std::istringstream(color.substr(3,2)) >> std::hex >> G;
            std::istringstream(color.substr(5,2)) >> std::hex >> B;
            setElement(name, Color {R,G,B});
        } else {
            if (color == "white")
                setElement(name, WHITE);
            else if (color == "red")
                setElement(name, RED);
            else if (color == "blue")
                setElement(name, BLUE);
            else if (color == "green")
                setElement(name, GREEN);
            else if (color == "black")
                setElement(name, BLACK);
            else if (color == "yellow")
                setElement(name, YELLOW);
            else if (color == "purple")
                setElement(name, PURPLE);
            else if (color == "brown")
                setElement(name, BROWN);
            else
                throw std::runtime_error("invalid std color: " + color);
        }

    } else if (command->at(0) == "gr") {
        if (command->size() != 4) {
            throw std::runtime_error("syntax for `gr`: gr <ElementA> <ElementB> <Gravity>");
        }
        std::string nameA = command->at(1);
        std::string nameB = command->at(2);
        float gravity = std::stof(command->at(3));
        getElement(nameA)->setGravity(getElement(nameB), gravity);
        getElement(nameB)->setGravity(getElement(nameA), gravity);
    }
    *command = {};
}

void rf::Matter::readFromString(std::string* text) {
    std::string buffer = "";
    std::vector<std::string> vbuffer = {};
    auto it = text->begin();
    while(it != text->end()) {
        if (*it == '\n') {
            if (vbuffer.size() > 0) {
                processCommand(&vbuffer);
            }
        } else if (*it == ' ') {
            if (buffer.size() > 0) {
                vbuffer.push_back(buffer);
                buffer = "";
            }
        } else {
            buffer += *it;
        }
        ++it;
    }
    if (buffer.size() > 0) {
        vbuffer.push_back(buffer);
        buffer = "";
    }
    if (vbuffer.size() > 0) {
        processCommand(&vbuffer);
    }
}

void rf::Matter::readFromFile(std::string path) {
    ifstream file; file.open(path);
    std::string text = "";
    while(std::getline(file, text))
        text += "\n";
    file.close();
    readFromString(&text);
}
