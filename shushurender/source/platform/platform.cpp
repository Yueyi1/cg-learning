#include "platform.h"
#include "tools/debug_tools.h"
#include "render/backend/graphics_backend.h"

using namespace platform;

const int WINDOW_WIDTH = 1440;
const int WINDOW_HEIGHT = 960;

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

#ifdef GLFW
    // init GLFW
    DEBUG_PRINTF("Platform::init() load glfw\n");
    if (!glfwInit())
        DEBUG_PRINTF("Platform::init() glfwInit() failed\n");
#ifdef _DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif
    // Create a GLFW window
    mWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "ShuShuRender", NULL, NULL);
    if (!mWindow)
    {
        glfwTerminate();
        return;
    }
    glfwSetWindowUserPointer(mWindow, this);
    glfwSetWindowSizeCallback(mWindow, window_size_callback);
    glfwSetKeyCallback(mWindow, key_callback);
    glfwSetCharCallback(mWindow, char_callback);
    glfwSetScrollCallback(mWindow, scroll_callback);
    glfwSetCursorPosCallback(mWindow, cursor_callback);
    glfwSetMouseButtonCallback(mWindow, mouse_button_callback);

    glfwMakeContextCurrent(mWindow);
#ifdef USING_OPENGL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        DEBUG_PRINTF("Failed to initialize OpenGL context\n");
        return;
    }
    // glad populates global constants after loading to indicate,
    // if a certain extension/version is available.
    DEBUG_PRINTF("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);
#endif // USING_OPENGL
#endif // GLFW 
}

void Platform::update()
{
    while (!glfwWindowShouldClose(mWindow))
    {
        glfwPollEvents();

        // GL part
        //mScene->GLRendering();

        //// IMGUI part
        //ImGui_ImplOpenGL3_NewFrame();
        //ImGui_ImplGlfw_NewFrame();
        //ImGui::NewFrame();

        //// TODO: draw imgui stuff here
        //sceneui();
        //mScene->ImguiRendering();

        //ImGui::Render();
        //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(mWindow);
    }
}

void Platform::cleanup()
{
    DEBUG_PRINTF("enter Platform::cleanup()\n");

    glfwDestroyWindow(mWindow);
    glfwTerminate();
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