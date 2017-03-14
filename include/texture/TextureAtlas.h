//
// Created by Guy on 14/03/2017.
//

#ifndef OPENGLBOOTSTRAP_TEXTUREATLAS_H
#define OPENGLBOOTSTRAP_TEXTUREATLAS_H

#include <string>
#include <vector>
#include <glm/vec2.hpp>
#include <map>
#include "../gl/Texture.h"
#include "../gl/Shader.h"

class TextureNotFoundException : public std::exception {
public:
    TextureNotFoundException(std::string textureName);

protected:
    std::string textureName;
};

struct TextureRegion {
    std::string name;
    GLfloat x;
    GLfloat y;
    GLfloat w;
    GLfloat h;
};

class TextureAtlas {
public:
    TextureAtlas(std::string file);
    TextureRegion GetEntry(std::string name);
    void BindToShader(std::string name, Shader& shdr, bool useShader = true);
    void BindToShader(TextureRegion region, Shader& shdr, bool useShader = true);

    std::vector<std::string> AtlasKeys();

    Texture&GetTexture();

protected:

    void ReadFile();
    void ReadBlock(std::ifstream& in, std::string name);

    std::string file;
    std::string texFile;
    GLuint* width;
    GLuint* height;
    Texture texture;
    std::vector<std::string> atlasKeys;
    std::map<std::string, TextureRegion> atlas;
};

#endif //OPENGLBOOTSTRAP_TEXTUREATLAS_H
