//
// Created by Guy on 12/03/2017.
//

#ifndef OPENGLBOOTSTRAP_ACTOR_H
#define OPENGLBOOTSTRAP_ACTOR_H

#include "../gl/OpenGLBootstrap.h"

class Stage;

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

    virtual void MouseMoved(glm::vec2 newPoint, glm::vec2 deltaPoint);
    virtual void Clicked(glm::vec2 point, int button);
    virtual void MouseEntered(glm::vec2 point);
    virtual void MouseExit(glm::vec2 point);
    virtual void KeyPressed(int key);
    virtual void KeyReleased(int key);

    bool ContainsPoint(glm::vec2 point);
    glm::vec2 TransformPoint(glm::vec2 point);

    virtual void Act(GLfloat delta);

    virtual void Draw(bootstrap::RenderContext context);
    Bounds bounds;
    bool hovered = false;
    Stage* owningStage;
protected:
};

#endif //OPENGLBOOTSTRAP_ACTOR_H
