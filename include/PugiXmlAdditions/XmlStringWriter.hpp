#include <pugixml.hpp>

namespace PugiXmlAdditions {
    struct xmlStringWriter : pugi::xml_writer {
        std::string stringData;

        virtual void write(const void *data, size_t size) {
            stringData.append(static_cast<const char *>(data), size);
        }
    };
} // namespace PugiXmlAdditions
