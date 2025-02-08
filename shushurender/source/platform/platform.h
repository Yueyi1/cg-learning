#ifndef WINDOW_H
#define PLATFROM_H

#include <memory>

#define GLFW

#ifdef GLFW
#include <GLFW/glfw3.h>
#endif // GLFW

namespace platform {

    class Platform
    {
    protected:
#ifdef GLFW
        // glfw window
        GLFWwindow* mWindow;
#endif // GLFW 

        static int mWindowWidth;
        static int mWindowHeight;

    private:
        void init();
        void update();
        void cleanup();
        static void window_size_callback(GLFWwindow* window, int width, int height);
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void char_callback(GLFWwindow* window, unsigned int codepoint);
        static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
        static void cursor_callback(GLFWwindow* window, double xposIn, double yposIn);
        static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

        Platform(const Platform&) = delete;
        Platform& operator=(const Platform&) = delete;

    public:
        Platform();
        ~Platform();
        static std::shared_ptr<Platform> GetInstance()
        {
            static std::shared_ptr<Platform> instance = std::make_shared<Platform>();
            return instance;
        }
        static void GetWindowSize(int& width, int& height);
    };
}

#endif // WINDOW_H