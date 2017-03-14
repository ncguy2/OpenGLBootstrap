//
// Created by Guy on 12/03/2017.
//

#include "../../include/gl/Texture.h"

Texture::Texture() : width(0), height(0),
                     internalFormat(GL_RGB), imageFormat(GL_RGB),
                     wrapS(GL_REPEAT), wrapT(GL_REPEAT),
                     filterMin(GL_LINEAR), filterMag(GL_LINEAR) {
    glGenTextures(1, &this->id);
}

void TextureBinder::Generate(Texture& tex, GLuint width, GLuint height, unsigned char *data) {
    tex.width = width;
    tex.height = height;

    glBindTexture(GL_TEXTURE_2D, tex.id);
    glTexImage2D(GL_TEXTURE_2D, 0, tex.internalFormat, width, height, 0, tex.imageFormat, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, tex.wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tex.wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, tex.filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, tex.filterMag);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureBinder::Bind(Texture texture) const {
    glBindTexture(GL_TEXTURE_2D, texture.id);
}
