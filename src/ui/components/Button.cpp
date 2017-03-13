//
// Created by Guy on 12/03/2017.
//

#include "../../../include/ui/components/Button.h"

Button::Button() : label("") {}

Button::Button(const std::string &label) : label(label) {}

void Button::SetLabel(std::string label) {
    this->label = label;
}

void Button::SetCallback(std::function<void(glm::vec2, int)> callback) {
    clickCallback = callback;
    hasFunction = true;
}

void Button::ClearCallback() {
    clickCallback = NULL;
    hasFunction = false;
}

void Button::InvokeCallback(glm::vec2 point, int button) {
    if(hasFunction)
        clickCallback(point, button);
}

void Button::Draw(bootstrap::RenderContext context) {
    Actor::Draw(context);
    glm::vec2 absPos = context.currentOffset;
    context.glyphRenderer->RenderText(context, label, absPos.x + (this->bounds.w / 2), absPos.y + (this->bounds.h / 2), 1);
}

void Button::Clicked(glm::vec2 point, int button) {
    Actor::Clicked(point, button);
    InvokeCallback(point, button);
}
