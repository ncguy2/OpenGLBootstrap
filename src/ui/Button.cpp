//
// Created by Guy on 12/03/2017.
//

#include "../../include/ui/components/Button.h"
#include "../../include/glyph/GlyphRenderer.h"

Button::Button() : label("") {}

Button::Button(const std::string &label) : label(label) {}

void Button::SetLabel(std::string label) {
    this->label = label;
}

void Button::SetCallback(std::function<void(glm::vec2)> callback) {
    clickCallback = callback;
    hasFunction = true;
}

void Button::ClearCallback() {
    clickCallback = NULL;
    hasFunction = false;
}

void Button::InvokeCallback(glm::vec2 point) {
    if(hasFunction)
        clickCallback(point);
}

void Button::Draw(bootstrap::RenderContext context) {
    Actor::Draw(context);
    glm::vec2 absPos = context.currentOffset;
    context.glyphRenderer->RenderText(context, label, absPos.x + (this->bounds.w / 2), absPos.y + (this->bounds.h / 2), 1);
}
