#include <rf/matter.hh>
#include <stdexcept>
#include <fstream>
#include <raylib.h>
#include <sstream>
#include <filesystem>

const char* HEX_DIGITS = "0123456789abcdef";
std::string to_hex(size_t number) {
    std::string ss = "";
    while (number > 16) {
        ss += HEX_DIGITS[number % 16];
        number /= 16;
    }
    ss += HEX_DIGITS[number % 16];
    if (number < 256 && ss.size() < 2)
        ss = "0" + ss;
    return ss;
}

size_t hex_index(char c) {
    for (size_t i = 0; i < 16; i++)
        if (HEX_DIGITS[i] == c)
            return i;
    return 16;
}

size_t from_hex(std::string number) {
    size_t acc = 0;
    for (size_t i = 0; i < number.size(); ++i) {
        acc += hex_index(number[i]);
        if (i != number.size() - 1)
            acc *= 16;
    }
    return acc;
}

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
    if (elements.size() == 0)
        throw std::runtime_error("EmptyMatterException");
    auto it = elements.begin();
    std::advance(it, std::rand() % elements.size());
    return &it->second;
}

void rf::Matter::processCommand(std::vector<std::string>* command) {
    if (command->at(0) == "el") {
        if (command->size() != 3) {
            throw std::runtime_error("syntax for `el`: el <ElementName> <ElementColor>\ngiven " + std::to_string(command->size()) + " arguments, expected 3");
        }
        std::string name = command->at(1);
        std::string color = command->at(2);
        if (color.at(0) == '#') {
            if (color.size() != 9)
                throw std::runtime_error("RGB color should be in format #ffffffff");
            unsigned char R, G, B, a;
            R = from_hex(color.substr(1,2));
            G = from_hex(color.substr(3,2));
            B = from_hex(color.substr(5,2));
            a = from_hex(color.substr(7,2));
            setElement(name, Color {R, G, B, a});
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
    } else {
        throw std::runtime_error("invalid command: " + command->at(0));
    }
    *command = {};
}

void rf::Matter::loadFromString(std::string* text) {
    std::string buffer = "";
    std::vector<std::string> vbuffer = {};
    auto it = text->begin();
    while(it != text->end()) {
        if (*it == '\n') {
            if (buffer.size() > 0) {
                vbuffer.push_back(buffer);
                buffer = "";
            }
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

void rf::Matter::loadFromFile(std::string path) {
    if (!std::filesystem::exists(path))
        throw std::runtime_error("file not found: " + path);
    std::ifstream file; file.open(path);
    std::string text = "", line = "";
    while(std::getline(file, line)) {
        text += line;
        text += "\n";
    }
    file.close();
    loadFromString(&text);
}

std::string* rf::Matter::dumpToString() {
    std::string* string = new std::string();
    for (auto entry : elements) {
        std::string name = entry.first;
        Color color = entry.second.getColor();
        string->append("el " + name + " #" +
                to_hex(color.r) + to_hex(color.g) +
                to_hex(color.b) + to_hex(color.a));
        string->append("\n");
    }

    for (auto entryA : elements) {
        for (auto entryB : elements) {
            string->append("gr " + entryA.first + " " + entryB.first);
            string->append(" " + std::to_string(entryA.second.getGravity(&entryB.second)));
            string->append("\n");
        }
    }
    return string;
}

void rf::Matter::dumpToFile(std::string path) {
    std::string* string = dumpToString();
    std::ofstream file; file.open(path);
    file << *string;
    file.close();
}
