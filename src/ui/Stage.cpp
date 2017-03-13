//
// Created by Guy on 12/03/2017.
//

#include "../../include/ui/Stage.h"

Stage::Stage(float width, float height) : width(width), height(height), root() {
    root.owningStage = this;
    root.SetBounds({0, 0, width, height});
}

void Stage::AddActor(Actor *actor) {
    root.Add(actor);
}

void Stage::RemoveActor(Actor *actor) {
    root.Remove(actor);
}

void Stage::OnClick(double xPos, double yPos, int button) {
    root.Clicked({xPos, yPos}, button);
}

void Stage::OnMouseMove(double xPos, double yPos) {
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = yPos - lastY;
    lastX = xPos;
    lastY = yPos;

    GLfloat sensitivity = .05f;

    root.MouseMoved({xPos, yPos}, {xOffset * sensitivity, yOffset * sensitivity});
}

void Stage::Act(GLfloat delta) {
    root.Act(delta);
}

void Stage::Draw(bootstrap::RenderContext context) {
    root.Draw(context);
}

void Stage::OnKeyEvent(int keyCode, int action) {
    if(action == GLFW_PRESS)
        root.KeyPressed(keyCode);
    else if(action == GLFW_RELEASE)
        root.KeyReleased(keyCode);
}

void Stage::UpdateHover(Actor *actor) {
    if(actor->hovered) {
        hoveredPtrs.push_back(actor);
    }else{
        hoveredPtrs.remove(actor);
    }
}
