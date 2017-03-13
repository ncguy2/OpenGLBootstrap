//
// Created by Guy on 12/03/2017.
//

#ifndef OPENGLBOOTSTRAP_STAGE_H
#define OPENGLBOOTSTRAP_STAGE_H

#include "../gl/OpenGLBootstrap.h"
#include "Group.h"

class Stage {
public:
    Stage(float width, float height);

    void AddActor(Actor* actor);
    void RemoveActor(Actor* actor);
    void OnClick(double xPos, double yPos, int button);
    void OnMouseMove(double xPos, double yPos);
    void OnKeyEvent(int keyCode, int action);
    void Act(GLfloat delta);
    void Draw(bootstrap::RenderContext context);
    void UpdateHover(Actor* actor);
protected:
    Actor* keyboardFocus;
    Actor* scrollFocus;
    float width;
    float height;
    Group root;
    std::list<Actor*> hoveredPtrs;
private:
    GLfloat lastX = 0;
    GLfloat lastY = 0;
};

#endif //OPENGLBOOTSTRAP_STAGE_H
