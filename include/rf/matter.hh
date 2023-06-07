#ifndef RF_MATTER
#define RF_MATTER

#include <map>
#include <string>
#include <vector>
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
            void loadFromString(std::string* text);
            void loadFromFile(std::string path);
            std::string* dumpToString();
            void dumpToFile(std::string path);
            void randomMatter();
    };
}

#endif
