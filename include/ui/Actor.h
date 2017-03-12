//
// Created by Guy on 12/03/2017.
//

#ifndef OPENGLBOOTSTRAP_ACTOR_H
#define OPENGLBOOTSTRAP_ACTOR_H

#include "../gl/OpenGLBootstrap.h"

struct Bounds {
    float x;
    float y;
    float w;
    float h;

    Bounds operator=(Bounds& other);
    bool operator^(glm::vec2& other);
};

class Actor {
public:
    void SetBounds(Bounds bounds);

    void MouseMoved(glm::vec2 newPoint, glm::vec2 deltaPoint);
    void Clicked(glm::vec2 point);
    bool ContainsPoint(glm::vec2 point);
    glm::vec2 TransformPoint(glm::vec2 point);

    virtual void Act(GLfloat delta);

    virtual void Draw(bootstrap::RenderContext context);
    Bounds bounds;
protected:
};

#endif //OPENGLBOOTSTRAP_ACTOR_H
