//
// Created by Guy on 12/03/2017.
//

#ifndef OPENGLBOOTSTRAP_STAGE_H
#define OPENGLBOOTSTRAP_STAGE_H

#include "../gl/OpenGLBootstrap.h"
#include "Group.h"

class Stage {
public:
    Stage(float width, float height, TextureAtlas& atlas);

    void AddActor(Actor* actor);
    void RemoveActor(Actor* actor);
    void OnClick(double xPos, double yPos, int button);
    void OnMouseMove(double xPos, double yPos);
    void OnKeyEvent(int keyCode, int action);
    void Act(GLfloat delta);
    void Draw(bootstrap::RenderContext context);
    void UpdateHover(Actor* actor);

    void DrawRegion(TextureRegion region, glm::mat4 model, glm::vec3 scale = glm::vec3(1.f), glm::vec4 colour = glm::vec4(1.f));
    void DrawTexture(Texture texture, glm::mat4 model, glm::vec3 scale = glm::vec3(1.f), glm::vec4 colour = glm::vec4(1.f));

    TextureAtlas& GetAtlas();
    Shader* P_GetShader();

protected:

    void InitializeRenderData();
    GLuint VAO;

    TextureAtlas atlas;
    Shader shader;
    Actor* keyboardFocus;
    Actor* scrollFocus;
    float width;
    float height;
    Group root;
    std::list<Actor*> hoveredPtrs;
private:
    GLfloat lastX = 0;
    GLfloat lastY = 0;
};

#endif //OPENGLBOOTSTRAP_STAGE_H
