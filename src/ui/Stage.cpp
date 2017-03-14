//
// Created by Guy on 12/03/2017.
//

#include "../../include/ui/Stage.h"
#include "../../include/gl/ResourceManager.h"

Stage::Stage(float width, float height, TextureAtlas& atlas) : width(width), height(height), root(), atlas(atlas) {
    root.owningStage = this;
    root.SetBounds({0, 0, width, height});
    InitializeRenderData();
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
    shader.SetMatrix4("projection", context.projectionMatrix, GL_TRUE);
    shader.SetVector2f("u_screenSize", width, height);
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

void Stage::DrawRegion(TextureRegion region, glm::mat4 model, glm::vec3 scale, glm::vec4 colour) {
    shader.Use();
    atlas.BindToShader(region, shader, false);
    DrawTexture(atlas.GetTexture(), model, scale, colour);
}

void Stage::DrawTexture(Texture texture, glm::mat4 model, glm::vec3 scale, glm::vec4 colour) {
    shader.Use();
    model = glm::scale(model, scale);
    shader.SetMatrix4("model", model);
    shader.SetVector4f("spriteColour", colour);
    shader.SetInteger("u_image", 0);

    glActiveTexture(GL_TEXTURE0);
    TextureBinder::GetInstance().Bind(texture);

    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Stage::InitializeRenderData() {

    shader = ResourceManager::GetInstance().LoadShader("assets/stage.vert.glsl", "assets/stage.frag.glsl", "", "Stage");

    GLuint VBO;
    GLfloat vertices[] = {
            0.f, 1.f, 0.f, 1.f,
            1.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 0.f,

            0.f, 1.f, 0.f, 1.f,
            1.f, 1.f, 1.f, 1.f,
            1.f, 0.f, 1.f, 0.f
    };

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

TextureAtlas &Stage::GetAtlas() {
    return atlas;
}

Shader *Stage::P_GetShader() {
    return &shader;
}
