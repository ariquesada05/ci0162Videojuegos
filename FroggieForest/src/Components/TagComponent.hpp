#ifndef TAG_COMPONENT_HPP
#define TAG_COMPONENT_HPP

#include <string>

struct TagComponent
{
    std::string tag;
    std::string className;

    TagComponent(
        const std::string& tag = "",
        const std::string& className = "")
        : tag(tag), className(className) {}
};

#endif