//
// Created by Guy on 12/03/2017.
//

#ifndef OPENGLBOOTSTRAP_OPENGLBOOTSTRAP_H
#define OPENGLBOOTSTRAP_OPENGLBOOTSTRAP_H

#include <gl/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <string>
#include <map>
#include <functional>
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include "Shader.h"
#include "../glyph/GlyphRenderer.h"

namespace bootstrap {
    namespace opengl {

        struct Callbacks {
            GLFWkeyfun* KeyCallback                     = nullptr;
            GLFWscrollfun* ScrollCallback               = nullptr;
            GLFWdropfun* DropCallback                   = nullptr;
            GLFWcharfun* CharCallback                   = nullptr;
            GLFWerrorfun* ErrorCallback                 = nullptr;
            GLFWjoystickfun* JoystickCallback           = nullptr;
            GLFWmonitorfun* MonitorCallback             = nullptr;
            GLFWwindowrefreshfun* WindowRefreshCallback = nullptr;
            GLFWcursorposfun* CursorMoveCallback        = nullptr;
            GLFWmousebuttonfun* MouseClickCallback      = nullptr;
            GLFWframebuffersizefun* ResizeCallback      = nullptr;
            GLFWcharmodsfun* CharModsCallback           = nullptr;
            GLFWcursorenterfun* CursorEnterCallback     = nullptr;
            GLFWwindowclosefun* WindowCloseCallback     = nullptr;
            GLFWwindowfocusfun* WindowFocusCallback     = nullptr;
            GLFWwindowiconifyfun* WindowIconifyCallback = nullptr;
            GLFWwindowposfun* WindowMoveCallback        = nullptr;
            GLFWwindowsizefun* WindowResizeCallback     = nullptr;
        };

        class OpenGLBootstrap {
        public:
            OpenGLBootstrap(bool useHelpers = true);
            OpenGLBootstrap* AddWindowHint(GLuint key, GLuint value);
            void SetRenderFunction(void (* function)(GLfloat));
            void SetEventCallbacks(Callbacks eventCallbacks);

            bool InitializeContext(int windowWidth, int windowHeight, std::string windowTitle);
            void RenderLoop(GLFWwindow* window = nullptr, void (* function)(GLfloat) = nullptr);

            GLFWwindow* GetWindow();
        protected:
            Callbacks eventCallbacks;
            std::map<GLuint, GLuint> windowHints;
            void (* renderFunction)(GLfloat);
            GLFWwindow* window;
            bool useHelpers;
        };
    }
}

#endif //OPENGLBOOTSTRAP_OPENGLBOOTSTRAP_H
