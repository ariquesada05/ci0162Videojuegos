/**
 * @file TagComponent.hpp
 * @brief Identification tags for entities
 */

#ifndef TAG_COMPONENT_HPP
#define TAG_COMPONENT_HPP

#include <string>

/**
 * @struct TagComponent
 * @brief Stores identification information for entities
 * 
 * Provides a way to tag entities with string identifiers for easy lookup
 * and classification.
 */
struct TagComponent
{
    std::string tag;       ///< Entity tag for identification
    std::string className; ///< Class name for categorization

    /**
     * @brief Construct a TagComponent
     * @param tag The entity tag (default: empty string)
     * @param className The class name (default: empty string)
     */
    TagComponent(
        const std::string& tag = "",
        const std::string& className = "")
        : tag(tag), className(className) {}
};

#endif