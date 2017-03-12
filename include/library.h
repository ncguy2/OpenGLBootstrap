#ifndef OPENGLBOOTSTRAP_LIBRARY_H
#define OPENGLBOOTSTRAP_LIBRARY_H

#include <string>
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include "gl/Shader.h"

class GlyphRenderer;

namespace bootstrap {

    struct RenderContext {
        glm::mat4 projectionMatrix;
        Shader* shader;
        glm::mat4 modelMatrix;
        glm::vec2 currentOffset;
        GlyphRenderer* glyphRenderer;
    };

    int BootstrapVersionMajor();
    int BootstrapVersionMinor();
    int BootstrapVersionBuild();

    std::string BootstrapVersionString();

    namespace opengl {}
}

#endif