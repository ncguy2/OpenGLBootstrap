//
// Created by Guy on 12/03/2017.
//

#include <algorithm>
#include "../../include/ui/Group.h"

Group::Group() : children() {}

void Group::Add(Actor *child) {
    children.push_back(child);
}

void Group::Remove(Actor *child) {
#ifdef USE_VECTOR
    children.erase(std::remove(children.begin(), children.end(), child), children.end());
#else
    children.remove(child);
#endif
}

void Group::MouseMoved(glm::vec2 newPoint, glm::vec2 deltaPoint) {
    if(children.empty()) return;
    for(Actor* child : children) {
        if(child->ContainsPoint(newPoint))
            child->MouseMoved(child->TransformPoint(newPoint), deltaPoint);
    }
}

void Group::Clicked(glm::vec2 point) {
    if(children.empty()) return;
    for(Actor* child : children) {
        if(child->ContainsPoint(point))
            child->Clicked(child->TransformPoint(point));
    }
}

void Group::Act(GLfloat delta) {
    Actor::Act(delta);
    if(children.empty()) return;
    for(Actor* child : children)
        child->Act(delta);
}

void Group::Draw(bootstrap::RenderContext context) {
    Actor::Draw(context);
    if(children.empty()) return;
    for(Actor* child : children)
        child->Draw(
                {context.projectionMatrix,
                 context.shader,
                 context.modelMatrix,
                 context.currentOffset +
                         glm::vec2(child->bounds.x, child->bounds.y),
                 context.glyphRenderer
                });
}
