//
// Created by Guy on 12/03/2017.
//

#ifndef OPENGLBOOTSTRAP_RESOURCEMANAGER_H
#define OPENGLBOOTSTRAP_RESOURCEMANAGER_H

#include <map>
#include "Shader.h"
#include "Texture.h"

class ResourceManager {
public:
    static ResourceManager& GetInstance() {
        static ResourceManager instance;
        return instance;
    }

    std::map<std::string, Shader> shaders;
    std::map<std::string, Texture> textures;

    Shader LoadShader(std::string vertFile, std::string fragFile, std::string geomFile, std::string name);
    Shader GetShader(std::string name);

    Texture LoadTexture(std::string file, GLboolean alpha, std::string name);
    Texture& GetTexture(std::string name);

    void Clear();

    ResourceManager(ResourceManager const&) = delete;
    void operator=(ResourceManager const&) = delete;

    Texture LoadTextureFromFile(std::string file, GLboolean alpha);

private:
    ResourceManager() {}
    Shader LoadShaderFromFile(std::string vertFile, std::string fragFile, std::string geomFile);
};

#endif //OPENGLBOOTSTRAP_RESOURCEMANAGER_H
