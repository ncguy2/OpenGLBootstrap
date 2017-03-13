//
// Created by Guy on 12/03/2017.
//

#include <iostream>
#include "../../include/ui/Actor.h"
#include "../../include/ui/Stage.h"

Bounds Bounds::operator=(Bounds &other) {
    this->x = other.x;
    this->y = other.y;
    this->w = other.w;
    this->h = other.h;
    return *this;
}

bool Bounds::operator^(glm::vec2 &other) {
    if(this->x > other.x) return false;
    if(this->y > other.y) return false;

    if(this->x + this->w < other.x) return false;
    if(this->y + this->h < other.y) return false;

    return true;
}

void Actor::SetBounds(Bounds bounds) {
    this->bounds = bounds;
}

void Actor::MouseMoved(glm::vec2 newPoint, glm::vec2 deltaPoint) {

}

void Actor::Clicked(glm::vec2 point, int button) {

}

bool Actor::ContainsPoint(glm::vec2 point) {
    return bounds ^ point;
}

glm::vec2 Actor::TransformPoint(glm::vec2 point) {
    glm::vec2 otherPoint{this->bounds.x, this->bounds.y};
    return point - otherPoint;
}

void Actor::Act(GLfloat delta) {

}

void Actor::Draw(bootstrap::RenderContext context) {

}

void Actor::MouseEntered(glm::vec2 point) {
    hovered = true;
    owningStage->UpdateHover(this);
    std::cout << typeid(this).name() << " Entered" << std::endl;
}

void Actor::MouseExit(glm::vec2 point) {
    hovered = false;
    owningStage->UpdateHover(this);
    std::cout << typeid(this).name() << " Exited" << std::endl;
}

void Actor::KeyPressed(int key) {

}

void Actor::KeyReleased(int key) {

}
