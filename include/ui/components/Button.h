//
// Created by Guy on 12/03/2017.
//

#ifndef OPENGLBOOTSTRAP_BUTTON_H
#define OPENGLBOOTSTRAP_BUTTON_H

#include <functional>
#include "../Actor.h"

class Button : public Actor {
public:
    Button();
    Button(const std::string &label);

    void SetLabel(std::string label);
    void SetCallback(std::function<void(glm::vec2)> callback);
    void ClearCallback();

    void Draw(bootstrap::RenderContext context) override;

protected:
    void InvokeCallback(glm::vec2 point);
private:
    std::string label;
    std::function<void(glm::vec2)> clickCallback;
    bool hasFunction = false;
};

#endif //OPENGLBOOTSTRAP_BUTTON_H
