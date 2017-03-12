//
// Created by Guy on 12/03/2017.
//

#ifndef OPENGLBOOTSTRAP_GROUP_H
#define OPENGLBOOTSTRAP_GROUP_H

#include <list>
#include <vector>
#include "Actor.h"

#define USE_VECTOR

#ifdef USE_VECTOR
#define CHILDREN_TYPE std::vector
#else
#define CHILDREN_TYPE std::list
#endif

class Group : public Actor {
public:

    Group();

    void Add(Actor* child);
    void Remove(Actor* child);

    void MouseMoved(glm::vec2 newPoint, glm::vec2 deltaPoint);
    void Clicked(glm::vec2 point);

    void Act(GLfloat delta) override;

    void Draw(bootstrap::RenderContext context) override;

protected:
    CHILDREN_TYPE<Actor*> children;
};

#endif //OPENGLBOOTSTRAP_GROUP_H
