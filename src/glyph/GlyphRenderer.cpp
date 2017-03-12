//
// Created by Guy on 12/03/2017.
//

#include <iostream>
#include "../../include/glyph/GlyphRenderer.h"


GlyphRenderer::GlyphRenderer(std::string fontPath) {
    FT_Library ft;
    if(FT_Init_FreeType(&ft))
        std::cerr << "ERROR::FREETYPE: Could not initialize FreeType library" << std::endl;

    FT_Face face;
    if(fontPath.empty())
        fontPath = "fonts/ariel.ttf";
    if (FT_New_Face(ft, fontPath.c_str(), 0, &face))
        std::cerr << "ERROR::FREETYPE: Failed to load font" << std::endl;

    FT_Set_Pixel_Sizes(face, 0, 48);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for(GLubyte c = 0; c < 128; c++) {
        if(FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cerr << "ERROR::FREETYPE: Failed to load Glyph [" << c << "]" << std::endl;
            continue;
        }

        GLuint tex;
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character = {
                tex,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                (GLuint) face->glyph->advance.x
        };
        characterMap[c] = character;
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    defaultShader = new Shader();
    defaultShader->Compile(TEXT_SHADER_VERT, TEXT_SHADER_FRAG, nullptr);
}

void GlyphRenderer::RenderText(bootstrap::RenderContext context, std::string text, GLfloat x, GLfloat y,
                               GLfloat scale, glm::vec3 colour) {
    RenderText(context, *defaultShader, text, x, y, scale, colour);
}

void GlyphRenderer::RenderText(bootstrap::RenderContext context, Shader s, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 colour) {
    s.Use();
    s.SetVector3f("textColour", colour);
    s.SetMatrix4("projection", context.projectionMatrix);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    std::string::const_iterator iter;
    for(iter = text.begin(); iter != text.end(); iter++) {
        Character c = characterMap[*iter];
        GLfloat xPos = x + c.bearing.x * scale;
        GLfloat yPos = y - (c.size.y - c.bearing.y) * scale;

        GLfloat w = c.size.x * scale;
        GLfloat h = c.size.y * scale;

        GLfloat vertices[6][4] = {
                {xPos    , yPos + h, 0.0, 0.0},
                {xPos    , yPos    , 0.0, 1.0},
                {xPos + w, yPos    , 1.0, 1.0},

                {xPos    , yPos + h, 0.0, 0.0},
                {xPos + w, yPos    , 1.0, 1.0},
                {xPos + w, yPos + h, 1.0, 0.0}
        };

        glBindTexture(GL_TEXTURE_2D, c.id);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        x += (c.advance >> 6) * scale;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    context.shader->Use();
}


