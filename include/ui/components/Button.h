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
    void SetCallback(std::function<void(glm::vec2,int)> callback);
    void ClearCallback();

    void Clicked(glm::vec2 point, int button) override;

    void Draw(bootstrap::RenderContext context) override;

protected:
    void InvokeCallback(glm::vec2 point, int button);
private:
    std::string label;
    std::function<void(glm::vec2, int button)> clickCallback;
    bool hasFunction = false;
};

#endif //OPENGLBOOTSTRAP_BUTTON_H
