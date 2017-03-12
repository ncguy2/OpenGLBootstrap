//
// Created by Guy on 12/03/2017.
//

#ifndef OPENGLBOOTSTRAP_GLYPHRENDERER_H
#define OPENGLBOOTSTRAP_GLYPHRENDERER_H

#include <ft2build.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <map>
#include FT_FREETYPE_H
#include "../gl/Shader.h"
#include "../library.h"

struct Character {
    GLuint id;
    glm::ivec2 size;
    glm::ivec2 bearing;
    GLuint advance;
};

class GlyphRenderer {
public:
    GlyphRenderer(std::string path = "fonts/ariel.ttf");
    void RenderText(bootstrap::RenderContext context, std::string text, GLfloat x, GLfloat y, GLfloat scale = 1, glm::vec3 colour = glm::vec3(1.f));
    void RenderText(bootstrap::RenderContext context, Shader s, std::string text, GLfloat x, GLfloat y, GLfloat scale = 1, glm::vec3 colour = glm::vec3(1.f));

protected:
    std::map<char, Character> characterMap;
    GLuint VAO, VBO;
    Shader* defaultShader;
};

#ifndef TEXT_SHADER_VERT
#define TEXT_SHADER_VERT "\
#version 330 core\n \
layout (location = 0) in vec4 vertex; /* <vec2 pos, vec2 tex> */\n \
out vec2 TexCoords;\n \
uniform mat4 projection;\n \
void main() {\n \
    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);\n \
    TexCoords = vertex.zw;\n \
}\n"
#endif // TEXT_SHADER_VERT

#ifndef TEXT_SHADER_FRAG
#define TEXT_SHADER_FRAG "\
#version 330 core\n \
in vec2 TexCoords;\n \
out vec4 FinalColour;\n \
uniform sampler2D text;\n \
uniform vec3 textColour;\n \
void main() {\n \
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);\n \
    FinalColour = vec4(textColour, 1.0) * sampled;\n \
}\n"
#endif // TEXT_SHADER_FRAG

#endif //OPENGLBOOTSTRAP_GLYPHRENDERER_H
