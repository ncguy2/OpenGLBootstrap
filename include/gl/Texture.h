//
// Created by Guy on 12/03/2017.
//

#ifndef OPENGLBOOTSTRAP_TEXTURE_H
#define OPENGLBOOTSTRAP_TEXTURE_H

#include <GL/gl.h>

struct Texture {

    Texture();

    GLuint id;
    GLuint width, height;
    GLuint internalFormat, imageFormat;
    GLuint wrapS, wrapT;
    GLuint filterMin, filterMag;
};

class TextureBinder {
public:
    static TextureBinder& GetInstance() {
        static TextureBinder instance;
        return instance;
    }

    void Generate(Texture tex, GLuint width, GLuint height, unsigned char* data);
    void Bind(Texture texture) const;
};

#endif //OPENGLBOOTSTRAP_TEXTURE_H