//
// Created by Guy on 12/03/2017.
//

#include <string>
#include <iostream>
#include "../../include/gl/OpenGLBootstrap.h"

bootstrap::opengl::OpenGLBootstrap *bootstrap::opengl::OpenGLBootstrap::AddWindowHint
        (GLuint key, GLuint value) {
    windowHints[key] = value;
    return this;
}

void bootstrap::opengl::OpenGLBootstrap::SetRenderFunction(void (* function)(GLfloat)) {
    this->renderFunction = function;
}

bootstrap::opengl::OpenGLBootstrap::OpenGLBootstrap(bool useHelpers) : useHelpers(useHelpers) {}

void bootstrap::opengl::OpenGLBootstrap::SetEventCallbacks(bootstrap::opengl::Callbacks eventCallbacks) {
    this->eventCallbacks = eventCallbacks;
}

bool bootstrap::opengl::OpenGLBootstrap::InitializeContext
        (int windowWidth, int windowHeight, std::string windowTitle) {

    if(glfwInit() == GL_FALSE) {
        std::cerr << "GLFW failed to initialize" << std::endl;
        return false;
    }

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    for(std::pair<GLuint, GLuint> pair : windowHints)
        glfwWindowHint(pair.first, pair.second);

    window = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), nullptr, nullptr);
    if(window == nullptr) {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if(err != GLEW_OK) {
        std::cerr << "GLEW failed to initialize" << std::endl;
        std::cerr << glewGetErrorString(err) << std::endl;
        return false;
    }

    glViewport(0, 0, windowWidth, windowHeight);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if(eventCallbacks.KeyCallback != nullptr) glfwSetKeyCallback(window, *eventCallbacks.KeyCallback);
    if(eventCallbacks.ScrollCallback != nullptr) glfwSetScrollCallback(window, *eventCallbacks.ScrollCallback);
    if(eventCallbacks.DropCallback != nullptr) glfwSetDropCallback(window, *eventCallbacks.DropCallback);
    if(eventCallbacks.CharCallback != nullptr) glfwSetCharCallback(window, *eventCallbacks.CharCallback);
    if(eventCallbacks.ErrorCallback != nullptr) glfwSetErrorCallback(*eventCallbacks.ErrorCallback);
    if(eventCallbacks.JoystickCallback != nullptr) glfwSetJoystickCallback(*eventCallbacks.JoystickCallback);
    if(eventCallbacks.MonitorCallback != nullptr) glfwSetMonitorCallback(*eventCallbacks.MonitorCallback);
    if(eventCallbacks.WindowRefreshCallback != nullptr) glfwSetWindowRefreshCallback(window, *eventCallbacks.WindowRefreshCallback);
    if(eventCallbacks.CursorMoveCallback != nullptr) glfwSetCursorPosCallback(window, *eventCallbacks.CursorMoveCallback);
    if(eventCallbacks.MouseClickCallback != nullptr) glfwSetMouseButtonCallback(window, *eventCallbacks.MouseClickCallback);
    if(eventCallbacks.ResizeCallback != nullptr) glfwSetFramebufferSizeCallback(window, *eventCallbacks.ResizeCallback);
    if(eventCallbacks.CharModsCallback != nullptr) glfwSetCharModsCallback(window, *eventCallbacks.CharModsCallback);
    if(eventCallbacks.CursorEnterCallback != nullptr) glfwSetCursorEnterCallback(window, *eventCallbacks.CursorEnterCallback);
    if(eventCallbacks.WindowCloseCallback != nullptr) glfwSetWindowCloseCallback(window, *eventCallbacks.WindowCloseCallback);
    if(eventCallbacks.WindowFocusCallback != nullptr) glfwSetWindowFocusCallback(window, *eventCallbacks.WindowFocusCallback);
    if(eventCallbacks.WindowIconifyCallback != nullptr) glfwSetWindowIconifyCallback(window, *eventCallbacks.WindowIconifyCallback);
    if(eventCallbacks.WindowMoveCallback != nullptr) glfwSetWindowPosCallback(window, *eventCallbacks.WindowMoveCallback);
    if(eventCallbacks.WindowResizeCallback != nullptr) glfwSetWindowSizeCallback(window, *eventCallbacks.WindowResizeCallback);

    return true;
}

void bootstrap::opengl::OpenGLBootstrap::RenderLoop(GLFWwindow* window, void (* function)(GLfloat)) {

    if(window == nullptr) window = this->window;
    if(function == nullptr) function = this->renderFunction;

    GLfloat deltaTime = 0.f;
    GLfloat lastTime = 0.f;
    GLfloat current = 0.f;
    while(!glfwWindowShouldClose(window)) {
        current = glfwGetTime();
        deltaTime = current - lastTime;
        lastTime = current;

        if(useHelpers) {
            glClearColor(0.f, 0.f, 0.f, 1.f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_ACCUM_BUFFER_BIT);
        }

        if(function != nullptr)
            function(deltaTime);

        glfwPollEvents();
        glfwSwapBuffers(this->window);
    }
}

GLFWwindow *bootstrap::opengl::OpenGLBootstrap::GetWindow() {
    return this->window;
}
