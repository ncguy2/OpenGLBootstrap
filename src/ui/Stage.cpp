//
// Created by Guy on 12/03/2017.
//

#include "../../include/ui/Stage.h"

Stage::Stage(float width, float height) : width(width), height(height), root() {
    root.SetBounds({0, 0, width, height});
}

void Stage::AddActor(Actor *actor) {
    root.Add(actor);
}

void Stage::RemoveActor(Actor *actor) {
    root.Remove(actor);
}

void Stage::OnClick(double xPos, double yPos) {
    root.Clicked({xPos, yPos});
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
