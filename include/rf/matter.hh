#ifndef RF_MATTER
#define RF_MATTER

#include <map>
#include <string>
#include <rf/element.hh>

namespace rf {
    class Matter {
        private:
            std::map<std::string, Element> elements;
        public:
            Matter();
            Matter(std::map<std::string, Element> elements);

            Element* getElement(std::string name);
            void setElement(std::string name, Element element);
            Element* randomElement();
            void processCommand(std::vector<std::string>* command);
            void readFromFile(std::string* text);
            void readFromString(std::string path);
    };
}

#endif
