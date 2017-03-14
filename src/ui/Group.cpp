//
// Created by Guy on 12/03/2017.
//

#include <algorithm>
#include "../../include/ui/Group.h"

Group::Group() : children() {}

void Group::Add(Actor *child) {
    children.push_back(child);
    child->owningStage = owningStage;
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
    for(int i = 0; i < children.size(); i++) {
        Actor* a = children[i];
        if(a->ContainsPoint(newPoint)) {
            if(!a->hovered)
                a->MouseEntered(a->TransformPoint(newPoint));
            a->MouseMoved(a->TransformPoint(newPoint), deltaPoint);
        }else if(a->hovered)
            a->MouseExit(a->TransformPoint(newPoint));
    }
}

void Group::Clicked(glm::vec2 point, int button) {
    if(children.empty()) return;
    for(int i = 0; i < children.size(); i++) {
        Actor* a = children[i];
        if(a->ContainsPoint(point))
            a->Clicked(a->TransformPoint(point), button);
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
                 glm::translate(context.modelMatrix, glm::vec3(child->bounds.xy(), 0.f)),
                 context.currentOffset +
                         glm::vec2(child->bounds.x, child->bounds.y),
                 context.glyphRenderer
                });
}

void Group::MouseEntered(glm::vec2 point) {
    Actor::MouseEntered(point);
}

void Group::MouseExit(glm::vec2 point) {
    Actor::MouseExit(point);
}

void Group::KeyPressed(int key) {
    Actor::KeyPressed(key);
}

void Group::KeyReleased(int key) {
    Actor::KeyReleased(key);
}
