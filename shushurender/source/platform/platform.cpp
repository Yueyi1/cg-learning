#include "platform.h"
//#include "render/backend/graphics_backend.h"

using namespace platform;

Platform::Platform()
{
    init();
}

Platform::~Platform()
{
    cleanup();
}

void Platform::init()
{
    DEBUG_PRINTF("enter Platform::init()\n");

#ifdef USE_GLFW
    mWindow = std::make_shared<GlfwWindow>();
    mWindow->Create(mWindowWidth, mWindowHeight, "ShuShuRender");
#endif // USE_GLFW 

}

void Platform::UpdateWindow()
{
    
}

void Platform::cleanup()
{
    DEBUG_PRINTF("enter Platform::cleanup()\n");
    mWindow->Close();
}

void Platform::window_size_callback(GLFWwindow* window, int width, int height)
{
    Platform* pThis = (Platform*)glfwGetWindowUserPointer(window);
    mWindowWidth = width;
    mWindowHeight = height;
    //pThis->mScene->OnResize(width, height);
}

void Platform::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Platform* pThis = (Platform*)glfwGetWindowUserPointer(window);

    //pThis->mScene->OnKey(key, scancode, action, mods);
}

void Platform::char_callback(GLFWwindow* window, unsigned int codepoint)
{
    Platform* pThis = (Platform*)glfwGetWindowUserPointer(window);

    //pThis->mScene->OnChar(codepoint);
}

void Platform::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Platform* pThis = (Platform*)glfwGetWindowUserPointer(window);

    //pThis->mScene->OnScoll(xoffset, yoffset);
}

void Platform::cursor_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    Platform* pThis = (Platform*)glfwGetWindowUserPointer(window);

    //pThis->mScene->OnMouseMove(xposIn, yposIn);
}

void Platform::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    Platform* pThis = (Platform*)glfwGetWindowUserPointer(window);

    //pThis->mScene->OnMouseButton(button, action, mods);
}

void Platform::GetWindowSize(int& width, int& height)
{
    width = mWindowWidth;
    height = mWindowHeight;
}