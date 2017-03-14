//
// Created by Guy on 14/03/2017.
//

#include <GL/glew.h>
#include <fstream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include "../../include/texture/TextureAtlas.h"
#include "../../include/gl/ResourceManager.h"
#include "../../include/util/StringUtils.h"

TextureNotFoundException::TextureNotFoundException(std::string textureName) : textureName(textureName) {}

TextureAtlas::TextureAtlas(std::string file) : file(file) {
    ReadFile();
}

TextureRegion TextureAtlas::GetEntry(std::string name) {
    if(atlas.find(name) == atlas.end())
        throw TextureNotFoundException(name);
    return atlas[name];
}

void TextureAtlas::BindToShader(std::string name, Shader& shdr, bool useShader) {
    BindToShader(GetEntry(name), shdr, useShader);
}

void TextureAtlas::BindToShader(TextureRegion region, Shader& shdr, bool useShader) {
    if(useShader) shdr.Use();
    glm::vec4 bounds(region.x, region.y, region.w, region.h);
//    glm::vec4 bounds(0, 0, 512, 512);
    shdr.SetVector4f("u_regionBounds", bounds);
}

void TextureAtlas::ReadFile() {
    std::ifstream is(file);
    if(!is.is_open()) return;
    std::string line;
    // Skip empty lines
    while(std::getline(is, line) && line.empty());
    std::vector<std::string> segments;
    // Name
    texFile = line;
    texFile = utils::Dirname(file) + "\\" + line;
    ResourceManager::GetInstance().LoadTexture(texFile, GL_TRUE, "TextureAtlas");
    texture = ResourceManager::GetInstance().GetTexture("TextureAtlas");
    width = (GLuint *) texture.width;
    height = (GLuint *) texture.height;
    // Size
    std::getline(is, line);
//    segments = utils::Split(utils::Split(line, ':')[1], ',');
//    texture.width = std::atof(utils::Trim(segments[0]).c_str());
//    texture.height = std::atof(utils::Trim(segments[1]).c_str());
    // Format
    std::getline(is, line);
//    segments = utils::Split(utils::Split(line, ':')[1], ',');
//    std::transform(segments[0].begin(), segments[0].end(), segments[0].begin(), ::toupper);
//    GLuint format;
//    if(segments[0] == "RGBA8888")
//        format = GL_RGBA;
//    else format = GL_RGB;
//    texture->internalFormat = texture->imageFormat = format;

    // Filter
    // TODO extract filter types
    std::getline(is, line);
//    texture->filterMin = texture->filterMag = GL_LINEAR;

    // Wrap
    // TODO extract wrap types
    std::getline(is, line);
//    texture->wrapS = texture->wrapT = GL_NONE;

    while(std::getline(is, line)) {
        if(line.empty() || line.length() < 3) continue;
        ReadBlock(is, line);
    }
}

void TextureAtlas::ReadBlock(std::ifstream& in, std::string name) {
    std::string propLine;
    std::map<std::string, std::string> props;
    std::vector<std::string> propSegment;
    while(in.peek() == ' ') {
        std::getline(in, propLine);
        propSegment = utils::Split(propLine, ':');
        if(propSegment.size() < 2) continue;
        if(propSegment[0].empty() || propSegment[1].empty()) continue;
        props[utils::Trim(propSegment[0])] = utils::Trim(propSegment[1]);
    }

    std::vector<std::string> xy = utils::Split(props["xy"], ',');
    float x = std::atof(utils::Trim(xy[0]).c_str());
    float y = std::atof(utils::Trim(xy[1]).c_str());

    std::vector<std::string> size = utils::Split(props["size"], ',');
    float w = std::atof(utils::Trim(size[0]).c_str());
    float h = std::atof(utils::Trim(size[1]).c_str());

    atlasKeys.push_back(name);
    atlas[name] = {name, x, y, w, h};
}

std::vector<std::string> TextureAtlas::AtlasKeys() {
    return atlasKeys;
}

Texture& TextureAtlas::GetTexture() {
    return texture;
}
