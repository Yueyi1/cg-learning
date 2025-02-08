#ifndef PLATFROM_H
#define PLATFROM_H

#include "tools/debug_tools.h"

#include <memory>

#define USE_GLFW

namespace platform {

    class Window {
    public:
        virtual ~Window() = default;

        virtual bool Create(int width, int height, const std::string& title) = 0;
        virtual void PollEvents() = 0;
        virtual void SwapBuffers() = 0;
        virtual bool ShouldClose() const = 0;
        virtual void Close() = 0;
    };

#ifdef USE_GLFW
#include <GLFW/glfw3.h>

    class GlfwWindow : public Window {
    private:
        GLFWwindow* window = nullptr;

    public:
        bool Create(int width, int height, const std::string& title) override {
            if (!glfwInit()) {
                DEBUG_PRINTF("Failed to initialize GLFW!\n");
                return false;
            }

            window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
            if (!window) {
                DEBUG_PRINTF("Failed to create GLFW window!\n");
                glfwTerminate();
                return false;
            }
            glfwMakeContextCurrent(window);
            return true;
        }

        void PollEvents() override {
            glfwPollEvents();
        }

        void SwapBuffers() override {
            if (window) {
                glfwSwapBuffers(window);
            }
        }

        bool ShouldClose() const override {
            return window && glfwWindowShouldClose(window);
        }

        void Close() override {
            if (window) {
                glfwDestroyWindow(window);
                glfwTerminate();
                window = nullptr;
            }
        }
    };

#endif // USE_GLFW

    const int WINDOW_WIDTH = 1440;
    const int WINDOW_HEIGHT = 960;

    class Platform
    {
    protected:
        std::shared_ptr<Window> mWindow;

        inline static int mWindowWidth = WINDOW_WIDTH;
        inline static int mWindowHeight = WINDOW_HEIGHT;

    private:
        void init();
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
        void UpdateWindow();
        void GetWindowSize(int& width, int& height);
    };
}

#endif // PLATFROM_H